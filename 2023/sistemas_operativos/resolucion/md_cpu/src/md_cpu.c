#include "md_cpu.h"

int main(int argc, char ** argv){
  if(argc > 1 && strcmp(argv[1],"-test")==0) return run_tests();

  /* ---------------- CREACION LOGGER ---------------- */

  logger = log_create("./cfg/md_cpu.log", "md_cpu", true, LOG_LEVEL_DEBUG);
  log_debug(logger, "Logger creado correctamente.");

  /* ---------------- LECTURA DE CONFIGS ---------------- */

  char* dir_cpu_config = argv[1];
  log_debug(logger, "Soy el directorio del config: %s", dir_cpu_config);
  
  char *current_dir = getcwd(NULL, 0);

  char buffer[MAX_BUFFER];
  memccpy(memccpy(buffer, current_dir, '\0', MAX_BUFFER) - 1, dir_cpu_config, '\0', MAX_BUFFER);

  t_config* config = iniciar_config();
  config = config_create(buffer);
  
  if (config == NULL) return EXIT_FAILURE;

  if(config_has_property(config, "IP_MEMORIA"))
  {
    ipMemoria = config_get_string_value(config, "IP_MEMORIA");
    log_debug(logger, "Lei la IP MEMORIA: %s", ipMemoria);
  }
  if(config_has_property(config, "PUERTO_MEMORIA"))
  {
    puertoMemoria = config_get_string_value(config, "PUERTO_MEMORIA");
    log_debug(logger, "Lei el PUERTO MEMORIA: %s", puertoMemoria);
  }
  if(config_has_property(config, "RETARDO_INSTRUCCION"))
  {
    retardoInstruccion = config_get_string_value(config, "RETARDO_INSTRUCCION");
    log_debug(logger, "Lei el RETARDO INSTRUCCION: %s", retardoInstruccion);
  }
  if(config_has_property(config, "TAM_MAX_SEGMENTO"))
  {
    tamMaxSegmento = config_get_string_value(config, "TAM_MAX_SEGMENTO");
    log_debug(logger, "Lei el TAM MAX_BUFFER SEGMENTO: %s", tamMaxSegmento);
  }
  if(config_has_property(config, "IP"))
  {
    ip = config_get_string_value(config, "IP");
    log_debug(logger, "Lei la IP: %s", ip);
  }
  if(config_has_property(config, "PUERTO"))
  {
    puerto = config_get_string_value(config, "PUERTO");
    log_debug(logger, "Lei el PUERTO: %s", puerto);
  }

  /* ---------------- HANDSHAKE A MEMORIA ---------------- */
  conexionMemoria = crear_conexion(ipMemoria, puertoMemoria);
	enviar_mensaje_con_op("Conexion CPU a MEMORIA", conexionMemoria, HANDSHAKE);
  int respuesta = recibir_operacion(conexionMemoria);
  char* mensaje = recibir_mensaje(conexionMemoria);

  if(respuesta != OK)
  {
    log_error(logger, "No me pude conectar a la memoria");
    return EXIT_FAILURE;
  }
  log_debug(logger, "Respuesta memoria: %s", mensaje);
  free(mensaje);
  
  /* ---------------- INICIO DE SERVIDOR ---------------- */
	int server_fd = iniciar_servidor(ip, puerto);
	log_debug(logger, "Servidor listo para recibir al cliente");

  while (1)
  {
    conexionKernel = esperar_cliente(server_fd);
    int cod_op;
    do {
      log_debug(logger, "Esperando codigo de operacion");
      cod_op = recibir_operacion(conexionKernel);
      log_debug(logger, "El codigo de operacion que recibi es: %d", cod_op);
      switch (cod_op) {
        case HANDSHAKE:
          char* mensajeH = recibir_mensaje(conexionKernel);
          log_debug(logger, "Recibi handshake con mensaje: %s", mensajeH);
          free(mensajeH);
          enviar_mensaje_con_op("OK", conexionKernel, OK);
          break;
        case MENSAJE:
          char* mensaje = recibir_mensaje(conexionKernel);
          free(mensaje);
          break;
        case OP_PCB:
        	  int codigoSolicitud;
            recv(conexionKernel, &codigoSolicitud, sizeof(int), 0);
            log_debug(logger, "Recibi el cod sol: %d", codigoSolicitud);
            int size;
            recv(conexionKernel, &size, sizeof(int), 0);
            log_debug(logger, "Recibi el size buffer: %d", size);

            void* buffer = recibir_datos(conexionKernel, size);
            int desplazamiento = 0;

            log_debug(logger, "ANTES DE RECIBIR PCB");
            pcb = recibir_pcb(buffer, &desplazamiento);

            free(buffer);
            log_debug(logger, "DESPUES DE RECIBIR PCB");
            log_debug(logger, "El program counter es: %d", pcb->PC);
            int repetirCiclo = 0;
            do{
              repetirCiclo = ciclo_de_instruccion();
            } while(repetirCiclo == 1);
            if(repetirCiclo == -1) {
              yield_or_exit(ERRORCPU);
            }
            liberar_pcb(pcb);
          break;
        case -1:
          log_debug(logger, "el cliente se desconecto.");
          break;
        default:
          log_warning(logger, "Operacion desconocida. No quieras meter la pata: %d", cod_op);
          break;
      }
    } while (cod_op != -1);
  }

  terminar_programa(-1, logger, config, current_dir);
  return EXIT_SUCCESS;
}

int ciclo_de_instruccion() 
{
  // FETCH
  char* instruccion = fetch();
  pcb->PC++;
  //DECODE
  Instruccion* instruccionDecodificada = decode(instruccion);
  if(instruccionDecodificada == NULL) return -1;

  //EXECUTE
  int repetirCiclo = execute(instruccionDecodificada);

  //FREES
  list_destroy_and_destroy_elements(instruccionDecodificada->Parametros, free);
  free(instruccionDecodificada->Operacion);
  free(instruccionDecodificada);

  return repetirCiclo;
}

char* fetch()
{
  return list_get(pcb->Instrucciones, pcb->PC);
}

Instruccion* decode(char* instruccion){
  log_debug(logger, "Instruccion a decodificar: %s", instruccion);
  char** arrayInstruccion = string_split(instruccion, " ");
  Instruccion* instruccionDecodificada = malloc(sizeof(Instruccion));
  instruccionDecodificada->Parametros = list_create();

  instruccionDecodificada->Operacion = arrayInstruccion[0];
  for(int i = 1; arrayInstruccion[i] != NULL; i++)
  { 
    list_add(instruccionDecodificada->Parametros, arrayInstruccion[i]);
  }

  if (strcmp(instruccionDecodificada->Operacion, "SET") == 0) {
    usleep(atoi(retardoInstruccion) * 1000);
  }

  int traducir(int posDirLogica, int cantBytes) {
    char* dirLogicaText = (char*) list_remove(instruccionDecodificada->Parametros, posDirLogica);
    int dirFisica = traducir_dir_logica_fisica(atoi(dirLogicaText), cantBytes);
    int num_segmento = floor(atoi(dirLogicaText) / atoi(tamMaxSegmento));
    int desplazamiento = 0;
    void *stream = malloc(sizeof(int) * 2);
    agregar_entero_a_stream(stream, &desplazamiento, dirFisica);
    agregar_entero_a_stream(stream, &desplazamiento, num_segmento);
    list_add_in_index(instruccionDecodificada->Parametros, posDirLogica, stream);
    free(dirLogicaText);
    //free(stream);
    return dirFisica;
  }

  if (strcmp(instruccionDecodificada->Operacion, "MOV_IN") == 0) {

    if(traducir(1, registerSize(list_get(instruccionDecodificada->Parametros, 0))) == -1) return NULL;
  }

  if (strcmp(instruccionDecodificada->Operacion, "MOV_OUT") == 0) {
    if(traducir(0, registerSize(list_get(instruccionDecodificada->Parametros, 1))) == -1) return NULL;
  }

  if (strcmp(instruccionDecodificada->Operacion, "F_WRITE") == 0 || strcmp(instruccionDecodificada->Operacion, "F_READ") == 0) {
    if(traducir(1, atoi(list_get(instruccionDecodificada->Parametros, 2))) == -1) return NULL;
  }
  
  free(arrayInstruccion);
  return instruccionDecodificada;
}

int execute(Instruccion* instruccion) 
{  
  int repetirCiclo = 0;

  if (strcmp(instruccion->Operacion, "SET") == 0) {
    log_info(logger, "PID: %d - Ejecutando: %s - Parametros: %s, %s", pcb->PID, instruccion->Operacion, (char*) list_get(instruccion->Parametros, 0), (char*)list_get(instruccion->Parametros, 1));
    set(list_get(instruccion->Parametros, 0), list_get(instruccion->Parametros, 1));
    repetirCiclo = 1;
  }
  else if (strcmp(instruccion->Operacion, "MOV_IN") == 0) {
    void *DirFisicaYSegmento = list_get(instruccion->Parametros, 1);
    int desplazamiento = 0;
    int dirFis = deserializar_entero_desde_buffer(DirFisicaYSegmento, &desplazamiento);
    int segmento = deserializar_entero_desde_buffer(DirFisicaYSegmento, &desplazamiento);
    log_info(logger, "PID: %d - Ejecutando: %s - Parametros: %s, %d", pcb->PID, instruccion->Operacion, (char*)list_get(instruccion->Parametros, 0), dirFis);
    mov_in(list_get(instruccion->Parametros, 0), dirFis, segmento);
    //list_remove(instruccion->Parametros, 1);
    repetirCiclo = 1;
  }
  else if (strcmp(instruccion->Operacion, "MOV_OUT") == 0) {
    void *DirFisicaYSegmento = list_get(instruccion->Parametros, 0);
    int desplazamiento = 0;
    int dirFis = deserializar_entero_desde_buffer(DirFisicaYSegmento, &desplazamiento);
    int segmento = deserializar_entero_desde_buffer(DirFisicaYSegmento, &desplazamiento);
    log_info(logger, "PID: %d - Ejecutando: %s - Parametros: %d, %s", pcb->PID, instruccion->Operacion, dirFis, (char*) list_get(instruccion->Parametros, 1));
    mov_out(dirFis, list_get(instruccion->Parametros, 1), segmento);
    //list_remove(instruccion->Parametros, 0);
    repetirCiclo = 1;
  }
  else if (strcmp(instruccion->Operacion, "I/O") == 0) {
    log_info(logger, "PID: %d - Ejecutando: %s - Parametros: %s", pcb->PID, instruccion->Operacion, (char*)list_get(instruccion->Parametros, 0));
    int milis = atoi(list_get(instruccion->Parametros,0));
    inputOutput(milis);
  }
  else if (strcmp(instruccion->Operacion, "F_OPEN") == 0) {
    log_info(logger, "PID: %d - Ejecutando: %s - Parametros: %s", pcb->PID, instruccion->Operacion, (char*)list_get(instruccion->Parametros, 0));
    fclose_or_fopen(list_get(instruccion->Parametros, 0), FOPEN);
  }
  else if (strcmp(instruccion->Operacion, "F_CLOSE") == 0) {
    log_info(logger, "PID: %d - Ejecutando: %s - Parametros: %s", pcb->PID, instruccion->Operacion, (char*)list_get(instruccion->Parametros, 0));
    fclose_or_fopen(list_get(instruccion->Parametros, 0), FCLOSE);
  }
  else if (strcmp(instruccion->Operacion, "F_SEEK") == 0) {
    log_info(logger, "PID: %d - Ejecutando: %s - Parametros: %s, %s", pcb->PID, instruccion->Operacion, (char*)list_get(instruccion->Parametros, 0), (char*)list_get(instruccion->Parametros, 1));
    int posicion = atoi(list_get(instruccion->Parametros,1));
    f_seek(list_get(instruccion->Parametros, 0), posicion);
  }
  else if (strcmp(instruccion->Operacion, "F_READ") == 0) {
    void *DirFisicaYSegmento = list_get(instruccion->Parametros, 1);
    int desplazamiento = 0;
    int dirFis = deserializar_entero_desde_buffer(DirFisicaYSegmento, &desplazamiento);
    int segmento = deserializar_entero_desde_buffer(DirFisicaYSegmento, &desplazamiento);
    log_info(logger, "PID: %d - Ejecutando: %s - Parametros: %s, %d, %s", pcb->PID, instruccion->Operacion, (char*)list_get(instruccion->Parametros, 0), dirFis, (char*)list_get(instruccion->Parametros, 2));
    fread_or_fwrite(list_get(instruccion->Parametros, 0), dirFis, atoi(list_get(instruccion->Parametros, 2)), FREAD, segmento);
    //list_remove(instruccion->Parametros, 1);
  }
  else if (strcmp(instruccion->Operacion, "F_WRITE") == 0) {
    void *DirFisicaYSegmento = list_get(instruccion->Parametros, 1);
    int desplazamiento = 0;
    int dirFis = deserializar_entero_desde_buffer(DirFisicaYSegmento, &desplazamiento);
    int segmento = deserializar_entero_desde_buffer(DirFisicaYSegmento, &desplazamiento);
    log_info(logger, "PID: %d - Ejecutando: %s - Parametros: %s, %d, %s", pcb->PID, instruccion->Operacion, (char*)list_get(instruccion->Parametros, 0), dirFis, (char*)list_get(instruccion->Parametros, 2));
    fread_or_fwrite(list_get(instruccion->Parametros, 0), dirFis, atoi(list_get(instruccion->Parametros, 2)), FWRITE, segmento);
    //list_remove(instruccion->Parametros, 1);
  }
  else if (strcmp(instruccion->Operacion, "F_TRUNCATE") == 0) {
    int tamanio = atoi(list_get(instruccion->Parametros,1));
    log_info(logger, "PID: %d - Ejecutando: F_TRUNCATE - Parametros: %s, %d", pcb->PID, (char*)list_get(instruccion->Parametros, 0), tamanio);
    f_truncate(list_get(instruccion->Parametros, 0), tamanio);
  }
  else if (strcmp(instruccion->Operacion, "WAIT") == 0) {
    log_info(logger, "PID: %d - Ejecutando: WAIT - Parametros: %s", pcb->PID, (char*)list_get(instruccion->Parametros, 0));
    wait_or_signal(list_get(instruccion->Parametros, 0), WAIT);
  }
  else if (strcmp(instruccion->Operacion, "SIGNAL") == 0) {
    log_info(logger, "PID: %d - Ejecutando: SIGNAL - Parametros: %s", pcb->PID, (char*)list_get(instruccion->Parametros, 0));
    wait_or_signal(list_get(instruccion->Parametros, 0), SIGNAL);
  }
  else if (strcmp(instruccion->Operacion, "CREATE_SEGMENT") == 0) {
    log_info(logger, "PID: %d - Ejecutando: CREATE_SEGMENT - Parametros: %s %s", pcb->PID, (char*)list_get(instruccion->Parametros, 0), (char*)list_get(instruccion->Parametros, 1));
    create_segment(atoi(list_get(instruccion->Parametros, 0)), atoi(list_get(instruccion->Parametros, 1)));
  }
  else if (strcmp(instruccion->Operacion, "DELETE_SEGMENT") == 0) {
    log_info(logger, "PID: %d - Ejecutando: DELETE_SEGMENT - Parametros: %s", pcb->PID, (char*)list_get(instruccion->Parametros, 0));
    delete_segment(atoi(list_get(instruccion->Parametros, 0)));
  }
  else if (strcmp(instruccion->Operacion, "YIELD") == 0) {
    log_info(logger, "PID: %d - Ejecutando: YIELD", pcb->PID);
    yield_or_exit(YIELD);
  }
  else if (strcmp(instruccion->Operacion, "EXIT") == 0) {
    log_info(logger, "PID: %d - Ejecutando: EXIT", pcb->PID);
    yield_or_exit(EXITS);
  }
  else {
    pcb->PC--;
    log_error(logger, "Se envio una operacion no conocida: %s", instruccion->Operacion);
  }

  return repetirCiclo;
}

/* ---------------- EJECUCION INSTRUCCIONES ---------------- */

void set (char* registro, char* valor) 
{
  if (strcmp(registro, "AX") == 0)
  {
    strcpy(pcb->RegistrosCPU->AX, valor);
  }
  else if (strcmp(registro, "BX") == 0)
  {
    strcpy(pcb->RegistrosCPU->BX, valor);
  }
  else if (strcmp(registro, "CX") == 0)
  {
    strcpy(pcb->RegistrosCPU->CX, valor);
  }
  else if (strcmp(registro, "DX") == 0)
  {
    strcpy(pcb->RegistrosCPU->DX, valor);
  }
  else if (strcmp(registro, "EAX") == 0)
  {
    strcpy(pcb->RegistrosCPU->EAX, valor);
  }
  else if (strcmp(registro, "EBX") == 0)
  {
    strcpy(pcb->RegistrosCPU->EBX, valor);
  }
  else if (strcmp(registro, "ECX") == 0)
  {
    strcpy(pcb->RegistrosCPU->ECX, valor);
  }
  else if (strcmp(registro, "EDX") == 0)
  {
    strcpy(pcb->RegistrosCPU->EDX, valor);
  }
  else if (strcmp(registro, "RAX") == 0)
  {
    strcpy(pcb->RegistrosCPU->RAX, valor);
  }
  else if (strcmp(registro, "RBX") == 0)
  {
    strcpy(pcb->RegistrosCPU->RBX, valor);
  }
  else if (strcmp(registro, "RCX") == 0)
  {
    strcpy(pcb->RegistrosCPU->RCX, valor);
  }
  else if (strcmp(registro, "RDX") == 0)
  {
    strcpy(pcb->RegistrosCPU->RDX, valor);
  }
}

void inputOutput(int milisegundos) 
{
  int desplazamiento = 0;
  void* stream = serializar_pcb(pcb, &desplazamiento);

  if((desplazamiento + sizeof(int)) > pcb->Size)
    stream = realloc(stream, pcb->Size + sizeof(int) + 1);

  agregar_entero_a_stream(stream, &desplazamiento, milisegundos);

  enviar_solicitud(conexionKernel, IO, desplazamiento, stream, INSTRUCCION_CPU);
}

void fclose_or_fopen(char* nombreArchivo, int op)
{
  int desplazamiento = 0;
  void* stream = serializar_pcb(pcb, &desplazamiento);

  if((desplazamiento + strlen(nombreArchivo) + 1) > pcb->Size)
    stream = realloc(stream, pcb->Size + strlen(nombreArchivo) + 1);

  agregar_cadena_a_stream(stream, &desplazamiento, nombreArchivo);

  enviar_solicitud(conexionKernel, op, desplazamiento, stream, INSTRUCCION_CPU);
}

void fread_or_fwrite(char* nombreArchivo, int direccionFisica, int tamanioALeerOEscribir, int op, int segmento)
{
  int desplazamiento = 0;
  void* stream = serializar_pcb(pcb, &desplazamiento);

  if((desplazamiento + sizeof(int) * 2 + strlen(nombreArchivo) + 1) > pcb->Size)
    stream = realloc(stream, pcb->Size + sizeof(int) * 2 + strlen(nombreArchivo) + 1);

  agregar_cadena_a_stream(stream, &desplazamiento, nombreArchivo);
  agregar_entero_a_stream(stream, &desplazamiento, direccionFisica);
  agregar_entero_a_stream(stream, &desplazamiento, tamanioALeerOEscribir);

  enviar_solicitud(conexionKernel, op, desplazamiento, stream, INSTRUCCION_CPU);
}

void f_seek(char* nombreArchivo, int posicion)
{
	int desplazamiento = 0;
  void* stream = serializar_pcb(pcb, &desplazamiento);

  if((desplazamiento + strlen(nombreArchivo) + 1 + sizeof(int)) > pcb->Size)
    stream = realloc(stream, pcb->Size + strlen(nombreArchivo) + 1 + sizeof(int));

  agregar_cadena_a_stream(stream, &desplazamiento, nombreArchivo);
  agregar_entero_a_stream(stream, &desplazamiento, posicion);

  enviar_solicitud(conexionKernel, FSEEK, desplazamiento, stream, INSTRUCCION_CPU);
}

void f_truncate(char* nombreArchivo, int tamanio)
{
  int desplazamiento = 0;
  void* stream = serializar_pcb(pcb, &desplazamiento);

  if((desplazamiento + strlen(nombreArchivo) + 1 + sizeof(int)) > pcb->Size)
    stream = realloc(stream, pcb->Size + strlen(nombreArchivo) + 1 + sizeof(int));

  agregar_cadena_a_stream(stream, &desplazamiento, nombreArchivo);
  agregar_entero_a_stream(stream, &desplazamiento, tamanio);

  enviar_solicitud(conexionKernel, FTRUNCATE, desplazamiento, stream, INSTRUCCION_CPU);
}

void wait_or_signal(char* recurso, int op)
{
	int desplazamiento = 0;
  void* stream = serializar_pcb(pcb, &desplazamiento);

  if((desplazamiento + strlen(recurso) + 1 + sizeof(int)) > pcb->Size)
    stream = realloc(stream, pcb->Size + strlen(recurso) + 1 + sizeof(int));

  agregar_cadena_a_stream(stream, &desplazamiento, recurso);

  enviar_solicitud(conexionKernel, op, desplazamiento, stream, INSTRUCCION_CPU);
}

void yield_or_exit(int op) 
{
  int desplazamiento = 0;
  void* stream = serializar_pcb(pcb, &desplazamiento);

  enviar_solicitud(conexionKernel, op, desplazamiento, stream, INSTRUCCION_CPU);
}

void mov_in(char* registro, int direccionFisica, int segmento)
{
  char* valor = pedir_de_direccion_memoria(direccionFisica, registerSize(registro));
  log_info(logger, "PID: %d - Accion: LEER - Segmento: %d - Direccion Fisica: %d - Valor: %s", pcb->PID, segmento, direccionFisica, valor);
  set(registro, valor);
  free(valor);
}

void mov_out(int direccionFisica, char* registro, int segmento)
{
  int tamanio = registerSize(registro);
  char* valor = get(registro);
  char* valorAEnviar = malloc(tamanio + 1);
  memcpy((void*) valorAEnviar, (void*)valor, tamanio);
  valorAEnviar[tamanio] = '\0';
  log_info(logger, "PID: %d - Accion: ESCRIBIR - Segmento: %d - Direccion Fisica: %d - Valor: %s", pcb->PID, segmento, direccionFisica, valorAEnviar);
  enviar_a_direccion_memoria(direccionFisica, valorAEnviar);
}

void create_segment(int idSegmento, int tamanioSegmento)
{
  int desplazamiento = 0;
  void* stream = serializar_pcb(pcb, &desplazamiento);

  if((desplazamiento + sizeof(int) * 2) > pcb->Size)
    stream = realloc(stream, pcb->Size + sizeof(int) * 2);

  agregar_entero_a_stream(stream, &desplazamiento, idSegmento);
  agregar_entero_a_stream(stream, &desplazamiento, tamanioSegmento);

  enviar_solicitud(conexionKernel, CREATE_SEGMENT, desplazamiento, stream, INSTRUCCION_CPU);
}

void delete_segment(int idSegmento)
{
  int desplazamiento = 0;
  void* stream = serializar_pcb(pcb, &desplazamiento);

  if((desplazamiento + sizeof(int)) > pcb->Size)
    stream = realloc(stream, pcb->Size + sizeof(int));

  agregar_entero_a_stream(stream, &desplazamiento, idSegmento);

  enviar_solicitud(conexionKernel, DELETE_SEGMENT, desplazamiento, stream, INSTRUCCION_CPU);
}

/* ---------------- UTILIDADES ---------------- */

int traducir_dir_logica_fisica(int direccion, int tamanioLeerOEscribir) 
{
  num_segmento = floor(direccion / atoi(tamMaxSegmento));
  int desplazamiento_segmento = direccion % atoi(tamMaxSegmento);

  bool equals(void *segmento) {
    Segmento* seg = (Segmento*)segmento;
    return seg->Id == num_segmento;
  }
  
  Segmento* segmento = list_find(pcb->TablaSegmentos, equals);
  if(segmento == NULL) {
    log_error(logger, "PID: %d - Error No se encontro el segmento - Numero segmento: %d", pcb->PID, num_segmento);
    return -1;
  }

  int dirFisica = segmento->Base + desplazamiento_segmento;

  if((dirFisica + tamanioLeerOEscribir) > (segmento->Base + segmento->Tamanio)) {
    log_error(logger, "PID: %d - Error SEG_FAULT- Segmento: %d - Offset: %d - Tamaño: %d", pcb->PID, segmento->Id, desplazamiento_segmento, segmento->Tamanio);
    return -1;
  }

  return dirFisica;
}

char* get(char* registro) {
  if (strcmp(registro, "AX") == 0)
  {
    return pcb->RegistrosCPU->AX;
  }
  else if (strcmp(registro, "BX") == 0)
  {
    return pcb->RegistrosCPU->BX;
  }
  else if (strcmp(registro, "CX") == 0)
  {
    return pcb->RegistrosCPU->CX;
  }
  else if (strcmp(registro, "DX") == 0)
  {
    return pcb->RegistrosCPU->DX;
  }
  else if (strcmp(registro, "EAX") == 0)
  {
    return pcb->RegistrosCPU->EAX;
  }
  else if (strcmp(registro, "EBX") == 0)
  {
    return pcb->RegistrosCPU->EBX;
  }
  else if (strcmp(registro, "ECX") == 0)
  {
    return pcb->RegistrosCPU->ECX;
  }
  else if (strcmp(registro, "EDX") == 0)
  {
    return pcb->RegistrosCPU->EDX;
  }
  else if (strcmp(registro, "RAX") == 0)
  {
    return pcb->RegistrosCPU->RAX;
  }
  else if (strcmp(registro, "RBX") == 0)
  {
    return pcb->RegistrosCPU->RBX;
  }
  else if (strcmp(registro, "RCX") == 0)
  {
    return pcb->RegistrosCPU->RCX;
  }
  else if (strcmp(registro, "RDX") == 0)
  {
    return pcb->RegistrosCPU->RDX;
  }

  return '\0';
}

int registerSize(char* reg) {
  if(strlen(reg) == 2)
    return 4;
  else if(strchr(reg, 'E'))
    return 8;
  else if(strchr(reg, 'R'))
    return 16;
  else {
    log_error(logger, "No existe un registro con ese nombre");
    return 0;
  }
}

/* ---------------- ENVIO SOLICITUDES ---------------- */

char *pedir_de_direccion_memoria(int direccionFisica, int regSize)
{
  int desplazamiento = 0;
  void* stream = malloc(sizeof(int) * 3);
  agregar_entero_a_stream(stream, &desplazamiento, pcb->PID);
  agregar_entero_a_stream(stream, &desplazamiento, direccionFisica);
  agregar_entero_a_stream(stream, &desplazamiento, regSize);
  enviar_solicitud(conexionMemoria, LEER, desplazamiento, stream, OPERACION_MEMORIA);
  char* respuesta = recibir_respuesta_memoria(regSize);
  return respuesta;
}

void enviar_a_direccion_memoria(int direccionFisica, char* valor) 
{
  string_append(&valor, "\0");
  int desplazamiento = 0;
  void* stream = malloc(sizeof(int) * 4 + strlen(valor) + 1);
  agregar_entero_a_stream(stream, &desplazamiento, pcb->PID);
  agregar_entero_a_stream(stream, &desplazamiento, direccionFisica);
  agregar_cadena_a_stream(stream, &desplazamiento, valor);
  enviar_solicitud(conexionMemoria, ESCRIBIR, desplazamiento, stream, OPERACION_MEMORIA);

  char* respuesta = recibir_respuesta_memoria(strlen(valor) + 1);
  if (strcmp(respuesta, "OK") != 0) {
    log_error(logger, "Se recibio un error de la memoria");
  }
  else{
    log_debug(logger, "Se escribio correctamente el registro en memoria");
  }
  free(respuesta);
  free(valor);
}

char* recibir_respuesta_memoria(int tamanio_registro)
{
  int cod_op;
  cod_op = recibir_operacion(conexionMemoria);
  log_debug(logger, "El codigo de operacion que recibi es: %d", cod_op);
  switch(cod_op) {
    case OPERACION_MEMORIA:
      int cod_sol = recibir_operacion(conexionMemoria);
      log_debug(logger, "El codigo de solicitud que recibi es: %d", cod_sol);

      switch (cod_sol) {
        case ESCRIBIR:
          char* respuesta = recibir_mensaje(conexionMemoria);
          return respuesta;
          break;
        case LEER:
          char *valor = recibir_mensaje(conexionMemoria);
          return valor;
          break;
        default:
          log_debug(logger, "Operacion desconocida. No quieras meter la pata");
          break;
      }
      break;
  }
  return NULL;
}

int segmento_que_pertenece(int dirFisica){
  bool equals(void *segmento) {
    Segmento* seg = (Segmento*)segmento;
    return seg->Base < dirFisica && seg->Base + seg->Tamanio > dirFisica;
  }
  Segmento* segmento = list_find(pcb->TablaSegmentos, equals);
  return segmento->Id;
}