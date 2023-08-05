#include "md_file_system.h"
int main(int argc, char ** argv)
{
  if(argc > 1 && strcmp(argv[1],"-test")==0) return run_tests();

  /* ---------------- CREACION LOGGER ---------------- */
  logger = iniciar_logger();
  logger = log_create("./cfg/md_file_system.log", "md_file_system", true, LOG_LEVEL_DEBUG);

  /* ---------------- LECTURA DE CONFIGS ---------------- */

  char* dir_file_system_config = argv[1];
  log_debug(logger, "Soy el directorio del config: %s", dir_file_system_config);
  
  char *current_dir = getcwd(NULL, 0);

  char buffer[MAX_BUFFER];
  memccpy(memccpy(buffer, current_dir, '\0', MAX_BUFFER) - 1, dir_file_system_config, '\0', MAX_BUFFER);
  
  t_config* config = iniciar_config();
  config = config_create(buffer);

  if (config != NULL) {
    if(config_has_property(config, "IP"))
    {
      ip = config_get_string_value(config, "IP");
      log_debug(logger, "Lei la IP: %s", ip);
    }
    if(config_has_property(config, "PUERTO"))
    {
      puerto = config_get_string_value(config, "PUERTO");
      log_debug(logger, "Lei el puerto: %s", puerto);
    }
    if(config_has_property(config, "IP_MEMORIA"))
    {
      ipMemoria = config_get_string_value(config, "IP_MEMORIA");
      log_debug(logger, "Lei la ipMemoria: %s", ipMemoria);
    }
    if(config_has_property(config, "PUERTO_MEMORIA"))
    {
      puertoMemoria = config_get_string_value(config, "PUERTO_MEMORIA");
      log_debug(logger, "Lei el puerto memoria: %s", puertoMemoria);
    }
    if(config_has_property(config, "PATH_SUPERBLOQUE"))
    {
      pathSuperbloque = config_get_string_value(config, "PATH_SUPERBLOQUE");
      log_debug(logger, "Lei el path superbloque: %s", pathSuperbloque);
    }
    if(config_has_property(config, "PATH_BITMAP"))
    {
      pathBitmap = config_get_string_value(config, "PATH_BITMAP");
      log_debug(logger, "Lei el path bitmap: %s", pathBitmap);
    }
    if(config_has_property(config, "PATH_BLOQUES"))
    {
      pathBloques = config_get_string_value(config, "PATH_BLOQUES");
      log_debug(logger, "Lei el path bloques: %s", pathBloques);
    }
    if(config_has_property(config, "RETARDO_ACCESO_BLOQUE"))
    {
      retardoAccesoBloque = config_get_string_value(config, "RETARDO_ACCESO_BLOQUE");
      log_debug(logger, "Lei el retardo acceso bloque: %s", retardoAccesoBloque);
    }
  }

    pathSuperbloque = argv[2];
    pathBitmap = argv[3];
    pathBloques = argv[4];
    
    /* ---------------- LEVANTAR ARCHIVOS ---------------- */
    inicializarArchivos();

    /* ---------------- HANDSHAKE A MEMORIA ---------------- */
    conexionMemoria = crear_conexion(ipMemoria, puertoMemoria);
    enviar_mensaje_con_op("Conexion FS a MEMORIA", conexionMemoria, HANDSHAKE);
    int respuesta = recibir_operacion(conexionMemoria);
    char* mensaje = recibir_mensaje(conexionMemoria);

    if(respuesta != OK)
    {
      log_error(logger, "No me pude conectar a la memoria");
      return EXIT_FAILURE;
    }
    log_debug(logger, "Respuesta memoria: %s", mensaje);
    free(mensaje);

 /*
  while (1)
  {
    int cliente_fd = esperar_cliente(server_fd);
    t_list* lista = malloc(sizeof(t_list));

    int cod_op = -2;
    while (cod_op != -1) {
      cod_op = recibir_operacion(cliente_fd);
      printf("El codigo de operacion que recibi es: %d\n", cod_op);

      switch (cod_op) {
        case HANDSHAKE:
          char* mensajeH = recibir_mensaje(cliente_fd);
          log_debug(logger, "Recibi handshake con mensaje: %s", mensajeH);
          free(mensajeH);
          enviar_mensaje_con_op("OK", cliente_fd, OK);
          break;

        case MENSAJE:
          char* mensaje = recibir_mensaje(cliente_fd);
          log_debug(logger, "Recibi mensaje: %s", mensaje);
          free(mensaje);
          break;

        case PAQUETE:
          lista = recibir_paquete(cliente_fd);
          s_list_iterate(lista);
          free(lista);
          break;

        case F_OPEN:
          break;
        
        case F_CLOSE:
          break;

        case F_CLOSE:
          break;

        case -1:
          printf( "el cliente se desconecto.\n");
          break;

        default:
          printf("Operacion desconocida. No quieras meter la pata\n");
          break;
      }
    }
  }


  */

  /* ---------------- INICIO DE SERVIDOR ---------------- */
	int server_fd = iniciar_servidor(ip, puerto);
	log_debug(logger, "Servidor listo para recibir al cliente");

  while (1)
  {
    conexionKernel = esperar_cliente(server_fd);
    int cod_op, respuesta;
    char* archivo;
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
       
        case F_OPEN:
          archivo = recibir_mensaje(conexionKernel);
          log_debug(logger, "el cliente hizo un F_OPEN y el FS recibio el archivo");
          respuesta = abrirArchivo(archivo);
          enviar_mensaje_con_op("abrir archivo", conexionKernel, respuesta);
          free(archivo);
          break;
       
        case F_CREATE: 
          archivo = recibir_mensaje(conexionKernel);
          log_debug(logger, "el cliente hizo un F_CREATE y el FS recibio el archivo");
          respuesta = crearArchivo(archivo);
          enviar_mensaje_con_op("OK", conexionKernel, respuesta);
          free(archivo);
          break;
       
        case F_TRUNCATE:
          log_debug(logger, "el cliente hizo un F_TRUNCATE.");
          recibir_operacion(conexionKernel);
          int sizeFT = recibir_operacion(conexionKernel);
          log_debug(logger, "Recibi el size buffer: %d\n", sizeFT);
          void* bufferFT = recibir_datos(conexionKernel, sizeFT);
          int desplazamientoFT = 0;
          int tamanioArchivoFT = deserializar_entero_desde_buffer(bufferFT, &desplazamientoFT);
          char* nombreArchivoFT = deserializar_cadena_desde_buffer(bufferFT, &desplazamientoFT);
          log_debug(logger, "Truncar Archivo: %s:", nombreArchivoFT);
          truncarArchivo(nombreArchivoFT, tamanioArchivoFT /* aca el tamanio deberia ser uint32_t */);
          free(nombreArchivoFT);
          enviar_mensaje_con_op("OK", conexionKernel, OK);
          free(bufferFT);
        break;
        case F_READ:
          log_debug(logger, "el cliente hizo un F_READ.");
          recibir_operacion(conexionKernel);
          int sizeFR = recibir_operacion(conexionKernel);
          printf("Recibi el size buffer: %d\n", sizeFR);

          void* bufferFR = recibir_datos(conexionKernel, sizeFR);
          int desplazamientoFR = 0;
          int tamanioArchivoFR = deserializar_entero_desde_buffer(bufferFR, &desplazamientoFR); 
          int dirFisicaFR = deserializar_entero_desde_buffer(bufferFR, &desplazamientoFR);
          char* nombreArchivoFR = deserializar_cadena_desde_buffer(bufferFR, &desplazamientoFR);
          int puntero = deserializar_entero_desde_buffer(bufferFR, &desplazamientoFR);
          int pidFR = deserializar_entero_desde_buffer(bufferFR, &desplazamientoFR);
          leerArchivo(nombreArchivoFR, puntero, tamanioArchivoFR, dirFisicaFR, pidFR);
          enviar_mensaje_con_op("leer archivo", conexionKernel, OK);
          free(nombreArchivoFR);
          free(bufferFR);
        break;
        case F_WRITE:
          log_debug(logger, "el cliente hizo un F_WRITE.");
          recibir_operacion(conexionKernel);
          int sizeFW = recibir_operacion(conexionKernel);
          log_debug(logger, "Recibi el size buffer: %d\n", sizeFW);

          void* bufferFW = recibir_datos(conexionKernel, sizeFW);
          int desplazamientoFW = 0;
          int tamanioArchivoFW = deserializar_entero_desde_buffer(bufferFW, &desplazamientoFW); 
          int dirFisicaFW = deserializar_entero_desde_buffer(bufferFW, &desplazamientoFW);
          char* nombreArchivoFW = deserializar_cadena_desde_buffer(bufferFW, &desplazamientoFW);
          int punteroFW = deserializar_entero_desde_buffer(bufferFW, &desplazamientoFW);
          int pidFW = deserializar_entero_desde_buffer(bufferFW, &desplazamientoFW);
          escribirArchivo(nombreArchivoFW, punteroFW, tamanioArchivoFW, dirFisicaFW, pidFW);
          enviar_mensaje_con_op("escribir archivo", conexionKernel, OK);
          free(nombreArchivoFW);
          free(bufferFW);
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
  liberarListaArchivos();
  free(superbloque);

  terminar_programa(-1, logger, config, current_dir);
  return EXIT_SUCCESS;

}

void inicializarArchivos()
{

  // Superbloque
  levantarSuperBloque();

  // BITMAP
  inicializarBitmap2();

  //Bloques
  inicializarBloques();

  inicializarEstructuras();

}

void levantarSuperBloque()
{
  
  char *current_dir2 = getcwd(NULL, 0);

  char buffer2[MAX_BUFFER];
  memccpy(memccpy(buffer2, current_dir2, '\0', MAX_BUFFER) - 1, pathSuperbloque, '\0', MAX_BUFFER);
  
  t_config* config2 = iniciar_config();
  config2 = config_create(buffer2);

  log_debug(logger, "Voy a levantar el archivo de superbloque ");

  superbloque = malloc(sizeof(int)*2);

  config_create(pathBloques);

  superbloque->tamanoBloque = config_get_int_value(config2, "BLOCK_SIZE");
  superbloque->cantidadBloques = config_get_int_value(config2, "BLOCK_COUNT");
  config_destroy(config2);

  log_debug(logger, "Termine de levantar el archivo de superbloque");

  free(current_dir2);
}

void inicializarBitmap2()
{
  
  log_debug(logger, "Voy a levantar el archivo de bitmap ");

  inicializarArchivoBitmap();
  
  char *current_dir3 = getcwd(NULL, 0);

  char buffer3[MAX_BUFFER];
  memccpy(memccpy(buffer3, current_dir3, '\0', MAX_BUFFER) - 1, pathBitmap, '\0', MAX_BUFFER);

  int fd = open(buffer3, O_RDWR);
  if(fd < 0){
    log_error(logger, "No se puede abrir el archivo de bitmap");
  }
  struct stat statbuf;
  int err = fstat(fd, &statbuf);

  if(err<0){
        log_error(logger, "No se puede obtener la informacion del archivo de bitmap");
        close(fd);
  }
  char *ptr = mmap(NULL,statbuf.st_size,
            PROT_READ | PROT_WRITE, MAP_SHARED,
            fd,0);
  if(ptr == MAP_FAILED){
     log_error(logger, "No se puede mapear el archivo de bitmap");
  }
  arrayDeBits = bitarray_create_with_mode(ptr, statbuf.st_size, LSB_FIRST);
 
  imprimirBitmap();
 
  log_debug(logger, "Termine de levantar el archivo de bitmap ");

  close(fd);
  free(current_dir3);
}

void inicializarBloques()
{
  
  char *current_dir4 = getcwd(NULL, 0);

  inicializarArchivoDeBloques();

  char buffer4[MAX_BUFFER];
  memccpy(memccpy(buffer4, current_dir4, '\0', MAX_BUFFER) - 1, pathBloques, '\0', MAX_BUFFER);


  int fd = open(buffer4, O_RDWR);
  if(fd < 0){
    log_error(logger, "No se puede abrir el archivo de bloques");
  }
  struct stat statbuf;
  fstat(fd, &statbuf);



  char *ptr = mmap(NULL,statbuf.st_size,
            PROT_READ | PROT_WRITE, MAP_SHARED,
            fd,0);
  if(ptr == MAP_FAILED){
     log_error(logger, "No se puede mapear el archivo de bloques");
  }
    int cadenaSize = superbloque->tamanoBloque;

    int numcadenas;
    bloques = splitString(ptr, cadenaSize, &numcadenas);  
    int i=0;
    while(i < numcadenas){
      log_debug(logger, "Se leyo del archivo de bloques lo siguiente: %s\n", bloques[i]);
      i++;
    }
    close(fd);
    free(current_dir4);
}

char** splitString(char* str, int cadenasize, int* numcadenas)
{
  int strLength = strlen(str);
  *numcadenas = (strLength + cadenasize - 1) / cadenasize;  // Calcula el número de fragmentos

  char** cadenas = malloc(sizeof(char*) * (*numcadenas));

  for (int i = 0; i < *numcadenas; i++) {
      int start = i * cadenasize;
      int end = start + cadenasize;

      // Asegura que no se exceda la longitud de la cadena
      if (end > strLength) {
          end = strLength;
      }

      int cadenaLength = end - start;
      cadenas[i] = malloc(sizeof(char) * (cadenaLength + 1));  // Reserva memoria para la subcadena
      strncpy(cadenas[i], str + start, cadenaLength);  // Copia la subcadena al fragmento correspondiente
      cadenas[i][cadenaLength] = '\0';  // Agrega el carácter nulo al final del fragmento
  }

  return cadenas;
}

void freecadenas(char** cadenas, int numcadenas)
{
    for (int i = 0; i < numcadenas; i++) {
        free(cadenas[i]);
    }
    free(cadenas);
}

void inicializarEstructuras()
{
  archivos = list_create();
  levantarFCBs();
}

// COMUNICACION CON KERNEL Y MEMORIA (INICIO)

int abrirArchivo(char* nombreArchivo)
{
    log_info(logger, "Abrir Archivo: %s", nombreArchivo);
    FCB_t* archivo = buscarArchivo(nombreArchivo);
    if(archivo){
      log_debug(logger, "Si existe el archivo: %s", nombreArchivo);
        return OK;
    }else{
      log_debug(logger, "No existe el archivo: %s", nombreArchivo);
        return NO_EXISTE_FCB;
    }
}

int crearArchivo(char* nombreArchivo)
{
  log_info(logger, "Crear Achivo: %s", nombreArchivo);
  char* nuevoFcb = string_from_format("nombreArchivo=%s\n""tamanoArchivo=0\n""punteroArchivo=0\n""punteroIndirecto=0\n", nombreArchivo);
  FCB_t* nuevoFcbStruct = malloc(sizeof(FCB_t));
  nuevoFcbStruct->nombreArchivo = malloc(strlen(nombreArchivo)+1);
  strcpy(nuevoFcbStruct->nombreArchivo,nombreArchivo);
  nuevoFcbStruct->tamanoArchivo=0;
  nuevoFcbStruct->punteroArchivo=0;
  nuevoFcbStruct->punteroIndirecto=0;

  //char* ruta = string_substring_from (pathFCB, 1);
  char* rutaCompleta = string_from_format("%s%s%s", "cfg/FCB/", nombreArchivo,".config"); 


  FILE * nuevoArchivo = fopen(rutaCompleta,"wb+");
  if(nuevoArchivo == NULL) {
    log_debug(logger, "No se pudo abrir el archivo.");
    //return 1; // Otra acción en caso de error
  } else {
    // fwrite(nuevoFcb, sizeof(FCB_t),1, nuevoArchivo);
    fputs(nuevoFcb, nuevoArchivo);
    fclose(nuevoArchivo); 
  }
 
  list_add(archivos,nuevoFcbStruct);
  free(nuevoFcb);
  free(rutaCompleta);
  return OK;
}

void truncarArchivo(char* nombreArchivo, uint32_t nuevoTamano)
{
  log_info(logger, "Truncar Archivo: %s - Tamano: %d", nombreArchivo, nuevoTamano);

  FCB_t* fcb = buscarArchivo(nombreArchivo);

  if(fcb == NULL)
  {
    log_debug(logger, "No existe el archivo: %s", nombreArchivo);
    return;
  }
  
  if(fcb->tamanoArchivo == nuevoTamano)
  {
    log_debug(logger, "El tamanio actual y nuevo son iguales. No se trunco nada");
    return;
  }

  //imprimirBitmap();
  if(fcb->tamanoArchivo < nuevoTamano)
  { 
    int bloquesAdicionales = calcularBloquesNuevos(fcb->tamanoArchivo, nuevoTamano);

    for(uint32_t i = 0; i < bloquesAdicionales;i++)
    {
      //Asigno bloques adicionales
      uint32_t bloqueDisponible = obtenerBloqueDisponible();
      agregarBloque(fcb, bloqueDisponible);
      fcb->tamanoArchivo += 64;
    }
  } 
  else 
  {
    int bloquesALiberar = calcularBloquesDeMas(fcb->tamanoArchivo, nuevoTamano);
    log_debug(logger, "Los bloques a liberar por el FTRUNCATE son: %d", bloquesALiberar);

    if(fcb->punteroIndirecto != 0)
    {
      uint32_t* listaPunteros = leerBloqueDePunteros(fcb->punteroIndirecto);
      int posicionUltimoBloque = cantidadPunterosEnBloque(listaPunteros) - 1;
      for(int i = posicionUltimoBloque; bloquesALiberar > 0 && posicionUltimoBloque > 0; i--)
      {
        eliminarBloque(listaPunteros[posicionUltimoBloque]);
        listaPunteros[posicionUltimoBloque] = 0;
        bloquesALiberar--;
        posicionUltimoBloque--;
        fcb->tamanoArchivo -= 64;
      }

      if(posicionUltimoBloque == 0)
      {
        eliminarBloque(fcb->punteroIndirecto);
        fcb->punteroIndirecto = 0;
      }
      free(listaPunteros);
    }

    if(nuevoTamano == 0)
    {
      eliminarBloque(fcb->punteroArchivo);
      fcb->punteroArchivo = 0;
      bloquesALiberar--;
      fcb->tamanoArchivo -= 64;
    }

    fcb->tamanoArchivo = nuevoTamano;
  }
    //imprimirBitmap();
  actualizarFCB(fcb);
  sincronizarBitmap();
}

// COMUNICACION CON KERNEL Y MEMORIA (FIN)

void actualizarFCB(FCB_t* fcb)
{

  char* rutaCompleta = string_from_format("%s%s%s", "cfg/FCB/", fcb->nombreArchivo, ".config");
  t_config* configFcb = config_create(rutaCompleta);
  if (configFcb != NULL) {
    config_set_value(configFcb, "nombreArchivo", fcb->nombreArchivo);
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%u", fcb->tamanoArchivo);
    config_set_value(configFcb, "tamanoArchivo", buffer);
    snprintf(buffer, sizeof(buffer), "%u", fcb->punteroArchivo);
    config_set_value(configFcb, "punteroArchivo", buffer);
    snprintf(buffer, sizeof(buffer), "%u", fcb->punteroIndirecto);
    config_set_value(configFcb, "punteroIndirecto", buffer);
    config_save(configFcb);
  }
  config_destroy(configFcb);
  free(rutaCompleta);
}

FCB_t* buscarArchivo(char* nombreArchivo)
{
  for (int i = 0; i < list_size(archivos); i++){
    FCB_t* fcb = list_get(archivos, i);
    if (fcb != NULL && fcb->nombreArchivo != NULL && strcmp(fcb->nombreArchivo, nombreArchivo) == 0) {
      return fcb;
    }
  }
  return NULL;
}

void logAccesoBitmap(int nroBloque, int estado)
{
  log_info(logger, "Acceso a Bitmap - Bloque: %d - Estado: %d", nroBloque, estado);
}

void logListaArchivos()
{
  log_debug(logger, "Lista de archivos:");
  FCB_t* archivo = malloc(sizeof(FCB_t));
  for(int i=0; i<list_size(archivos);i++){
     archivo = list_get(archivos, i);
     log_debug(logger, "Nombre: %s - Tamano: %d",archivo->nombreArchivo, archivo->tamanoArchivo);
  }
  free(archivo);
}

void imprimirBitmap()
{
  for(int i =0; i < bitarray_get_max_bit(arrayDeBits);i++){
    int bit = bitarray_test_bit(arrayDeBits, i);
    logAccesoBitmap(i,bit);
  }
}

void inicializarArchivoBitmap()
{
  char* ruta = string_substring_from (pathBitmap, 1);
  archivoBitmap = fopen(ruta, "rb");

  if(!archivoBitmap){
    archivoBitmap = fopen(ruta, "wb");
    if(archivoBitmap){
    int cantBytes = superbloque->cantidadBloques / 8;
    if(archivoBitmap != NULL ){
      for(int i=0;i<cantBytes;i++){
        fputc(0,archivoBitmap);
      }
    log_debug(logger, "Archivo de Bitmap creado e inicializado.");

   }
    }else{
    log_debug(logger, "No se pudo crear el archivo de Bitmap.");
    }
  } else{
        log_debug(logger, "Ya existe el Archivo de Bitmap.");
  }
  free(ruta);
  fclose(archivoBitmap);
}

void inicializarArchivoDeBloques()
{
  char* ruta = string_substring_from (pathBloques, 1);
  archivoBloques = fopen(ruta, "rb");

 if (!archivoBloques) {
        archivoBloques = fopen(ruta, "wb");
        if (archivoBloques) {


            char* buffer = malloc(superbloque->tamanoBloque);

            if (buffer) {
                memset(buffer, 0, superbloque->tamanoBloque);

                for (uint32_t i = 0; i < superbloque->cantidadBloques; i++) {
                    fwrite(buffer, 1, superbloque->tamanoBloque, archivoBloques);
                }

                log_debug(logger, "Archivo de bloques creado e inicializado.");
                free(buffer);
            } else {
                log_debug(logger, "No se pudo asignar memoria para inicializar el archivo de bloques.");
            }
        } else {
            log_debug(logger, "No se pudo crear el archivo de bloques.");
        }
    } else{
        log_debug(logger, "Ya existe el Archivo de Bloques.");
    }
  free(ruta);
  fclose(archivoBloques);
}

/*
char* leerBloqueDeDatos(uint32_t pos) {
  char* bloque = malloc(superbloque->tamanoBloque);
  archivoBloques = fopen(pathBloques, "rb");

  fseek(archivoBloques, puntero * superbloque->tamanoBloque,SEEK_SET);

  fread(bloque, sizeof(char), superbloque->tamanoBloque, archivoBloques);


	return bloque;
}
*/
void leerBloqueDeDatos(uint32_t puntero)
{
  char* bloque = malloc(superbloque->tamanoBloque + 1);
  char* ruta = string_substring_from (pathBloques, 1);
  archivoBloques = fopen(ruta, "rb+");
  // La multiplicacion me lleva al tamaño de bloque requerido.
  fseek(archivoBloques, puntero * superbloque->tamanoBloque, SEEK_SET);

  fread(bloque, superbloque->tamanoBloque, 1, archivoBloques);
  bloque[superbloque->tamanoBloque] = '\0';
  log_debug(logger, "En el bloque %d hay: %s", puntero, bloque);

  fclose(archivoBloques);
  free(bloque);
  free(ruta);
}

uint32_t* traerBloqueDePunteros(uint32_t puntero)
{
  uint32_t* bloque = malloc(superbloque->tamanoBloque);
  char* ruta = string_substring_from (pathBloques, 1);
  archivoBloques = fopen(ruta, "rb+");
  int cantPunteros = superbloque->tamanoBloque / sizeof(uint32_t);
  // La multiplicacion me lleva al tamaño de bloque requerido.
  fseek(archivoBloques, puntero * superbloque->tamanoBloque,SEEK_SET);
  fread(bloque, sizeof(uint32_t), cantPunteros, archivoBloques);
  fclose(archivoBloques);
  free(ruta);
  return bloque;
}

uint32_t* leerBloqueDePunteros(uint32_t puntero)
{
  uint32_t* bloque = malloc(superbloque->tamanoBloque);
  char* ruta = string_substring_from (pathBloques, 1);
  archivoBloques = fopen(ruta, "rb+");
  int cantPunteros = superbloque->tamanoBloque / sizeof(uint32_t);
  // La multiplicacion me lleva al tamaño de bloque requerido.
  void* stream = malloc(superbloque->tamanoBloque);
  int desp = 0;
  fseek(archivoBloques, puntero * superbloque->tamanoBloque, SEEK_SET);
  fread(stream, superbloque->tamanoBloque, 1, archivoBloques);
  for(int i = 0; i < cantPunteros; i++)
  {
    bloque[i] = deserializar_entero_desde_buffer(stream, &desp);
    log_debug(logger, "LEO - PUNTERO INDIRECTO ( Pos: %d - Contenido: %d ) ", i,  bloque[i]);
  }
  fclose(archivoBloques);
  free(ruta);
  free(stream);
  return bloque;
}

void logueoAccesoBloque(FCB_t* archivo, uint32_t bloque)
{
  	log_debug(logger, "Acceso Bloque - Archivo: <%s> - Bloque Archivo: <%d> - Bloque File System <%d>", archivo->nombreArchivo, archivo->punteroArchivo, bloque);
}

void leerArchivoFCB(char* nombre_archivo)
{
    FCB_t* fcb = malloc(sizeof(FCB_t));
    char* rutaCompleta = string_from_format("%s%s%s", "cfg/FCB/", nombre_archivo, ".config");
    t_config* configFcb = config_create(rutaCompleta);
    if (configFcb != NULL) {
      if(config_has_property(configFcb, "nombreArchivo"))
      {
        fcb->nombreArchivo = config_get_string_value(configFcb, "nombreArchivo");
        log_debug(logger, "Lei la nombreArchivo: %s", fcb->nombreArchivo);
      }
      if(config_has_property(configFcb, "tamanoArchivo"))
      {
        fcb->tamanoArchivo = config_get_int_value(configFcb, "tamanoArchivo");
        log_debug(logger, "Lei la tamanoArchivo: %d", fcb->tamanoArchivo);
      }
      if(config_has_property(configFcb, "punteroArchivo"))
      {
        fcb->punteroArchivo = (uint32_t)config_get_int_value(configFcb, "punteroArchivo");
        log_debug(logger, "Lei la punteroArchivo: %d", fcb->punteroArchivo);
      }
      if(config_has_property(configFcb, "punteroIndirecto"))
      {
        fcb->punteroIndirecto = (uint32_t)config_get_int_value(configFcb, "punteroIndirecto");
        log_debug(logger, "Lei la punteroIndirecto: %d", fcb->punteroIndirecto);
      }
      config_destroy(configFcb);
    }
    // Liberar la memoria asignada
    //free(fcb);
    list_add(archivos,fcb);
    free(rutaCompleta);
}

void liberarArchivo(void* elemento)
{
    FCB_t* archivo = (FCB_t*)elemento;
    //free(archivo->nombreArchivo);
    free(archivo);
}

void liberarListaArchivos()
{
    list_iterate(archivos, liberarArchivo);
    list_destroy(archivos);
}

void levantarFCBs()
{
    log_debug(logger, "Voy a levantar los FCBs");
    char* rutaCompleta = string_from_format("%s", "cfg/FCB/");
    DIR* dir = opendir(rutaCompleta);

    if(!dir){
      log_error(logger, "Error abriendo el directorio de FCBs");
      return;
    }

    struct dirent* ent;

        while((ent = readdir(dir))!=NULL){
          if(strstr(ent->d_name,".config")){
            FCB_t* fcb = malloc(sizeof(FCB_t));
            char* rutaFCB = string_from_format("%s%s", "cfg/FCB/", ent->d_name);
            t_config* configFcb = config_create(rutaFCB);
            if (configFcb != NULL) {
              if(config_has_property(configFcb, "nombreArchivo"))
                {
                  char* aux = config_get_string_value(configFcb, "nombreArchivo");
                  fcb->nombreArchivo = malloc(strlen(aux)+1);
                  strcpy(fcb->nombreArchivo, aux);
                 }
          if(config_has_property(configFcb, "tamanoArchivo"))
          {
            fcb->tamanoArchivo = config_get_int_value(configFcb, "tamanoArchivo");
            log_debug(logger, "Lei la tamanoArchivo: %d", fcb->tamanoArchivo);
          }
          if(config_has_property(configFcb, "punteroArchivo"))
          {
            fcb->punteroArchivo = (uint32_t)config_get_int_value(configFcb, "punteroArchivo");
            log_debug(logger, "Lei la punteroArchivo: %d", fcb->punteroArchivo);
          }
          if(config_has_property(configFcb, "punteroIndirecto"))
          {
            fcb->punteroIndirecto = (uint32_t)config_get_int_value(configFcb, "punteroIndirecto");
            log_debug(logger, "Lei la punteroIndirecto: %d", fcb->punteroIndirecto);
          }
          config_destroy(configFcb);
        }  
        list_add(archivos,fcb);
        free(rutaFCB);

              }
        }

        closedir(dir);
        imprimirFCBs();
        free(rutaCompleta);

}

void agregarBloque(FCB_t* archivo, uint32_t pos)
{
  if(archivo->tamanoArchivo == 0){
    archivo->punteroArchivo = pos;
  }
  else
  {
    if(archivo->punteroIndirecto == 0){
      uint32_t* bloqueIndirecto = malloc(superbloque->tamanoBloque);
      bloqueIndirecto[0] = pos;
      for (int j = 1; j < superbloque->tamanoBloque / sizeof(uint32_t); j++) {
          bloqueIndirecto[j] = 0;
      }
      
      bitarray_set_bit(arrayDeBits, pos);
      archivo->punteroIndirecto = obtenerBloqueDisponible();
      escribirBloquePunteros(archivo->punteroIndirecto, bloqueIndirecto);
      bitarray_set_bit(arrayDeBits, archivo->punteroIndirecto);
      free(bloqueIndirecto);
    }
    else{
      uint32_t* punteros = traerBloqueDePunteros(archivo->punteroIndirecto);
      for (int j = 0; j < superbloque->tamanoBloque / sizeof(uint32_t); j++) {
        if(punteros[j]==0)
        {
          punteros[j] = pos;
          escribirBloquePunteros(archivo->punteroIndirecto, punteros);
          bitarray_set_bit(arrayDeBits, pos);
          free(punteros);
          return;
        }
      }
    }
  }
  bitarray_set_bit(arrayDeBits, pos);
}

uint32_t obtenerBloqueDisponible()
{
  for(uint32_t j = 0; j <superbloque->cantidadBloques - 1; j++){
    if(bitarray_test_bit(arrayDeBits,j)==0){
      bitarray_set_bit(arrayDeBits, j);
      return j;
    }
  }
  return -1;
}

void escribirBloquePunteros(uint32_t pos, uint32_t* punteros)
{
  int cantPunteros = superbloque->tamanoBloque / sizeof(uint32_t);
  char* ruta = string_substring_from (pathBloques, 1);
  archivoBloques = fopen(ruta, "rb+");    
  fseek(archivoBloques, pos * superbloque->tamanoBloque, SEEK_SET);

  void* stream = malloc(superbloque->tamanoBloque);
  int desp = 0;
  for(int i = 0; i < cantPunteros; i++)
  {
    agregar_entero_a_stream(stream, &desp, punteros[i]);
  }
  fwrite(stream, superbloque->tamanoBloque, 1, archivoBloques);

  fclose(archivoBloques);
  free(ruta);
  free(stream);
}

int calcularBloquesNuevos(uint32_t tamanioActual, uint32_t tamanioNuevo) 
{     
  int bloquesActuales = (tamanioActual + superbloque->tamanoBloque - 1) / superbloque->tamanoBloque;
  int bloquesNuevos = (tamanioNuevo + superbloque->tamanoBloque - 1) / superbloque->tamanoBloque;
  return bloquesNuevos - bloquesActuales; 
}

int calcularBloquesDeMas(uint32_t tamanioActual, uint32_t tamanioNuevo) 
{     
  int bloquesActuales = (tamanioActual + superbloque->tamanoBloque - 1) / superbloque->tamanoBloque;
  int bloquesNuevos = (tamanioNuevo + superbloque->tamanoBloque - 1) / superbloque->tamanoBloque;
  return bloquesActuales - bloquesNuevos; 
}

bool filtradoPunteros(void * elemento)
{
  uint32_t* puntero = (uint32_t*)elemento;
  return (*puntero !=0);
}

void eliminarBloque(int posBloque)
{
  logAccesoBitmap(posBloque,1);
  log_debug(logger, "Eliminando bloque: %d", posBloque);
  bitarray_clean_bit(arrayDeBits, posBloque);
}

void sincronizarBitmap()
{
  int resultadoSincro = msync(arrayDeBits->bitarray, arrayDeBits->size, MS_SYNC);
  if(resultadoSincro!=0){
          log_error(logger, "No se pudo sincronizar el bitmap");
  }
}

void imprimirFCBs()
{

  for(int i=0; i <list_size(archivos);i++){
    FCB_t* fcb = list_get(archivos,i);
      log_debug(logger, "FCB N.%d", i);
      log_debug(logger, "Nombre: %s", fcb->nombreArchivo);
      log_debug(logger, "Tamano: %d", fcb->tamanoArchivo);
      log_debug(logger, "Puntero Archivo: %d", fcb->punteroArchivo);
      log_debug(logger, "Puntero Indirecto: %d", fcb->punteroIndirecto);

  }

}

void leerArchivo(char* nombreArchivo, uint32_t puntero, int bytesALeer, int direccionFisica, int pid){ // ISSUE 3077
  log_info(logger, "Leer Archivo: %s - Puntero: %d - Memoria: %d - Tamaño: %d", nombreArchivo, puntero, direccionFisica, bytesALeer);
  FCB_t* fcbDelArchivo = buscarArchivo(nombreArchivo);
  int bloqueInicial = puntero / superbloque->tamanoBloque; 
  uint32_t contadorDeBloque = max(bloqueInicial-1,0);
  uint32_t bloqueReal; 
  int bytesLeidos = 0;    
  log_debug(logger,"Voy a leer %d bytes", bytesALeer);
  char* informacionALeer = malloc(bytesALeer+1);
  if(bloqueInicial == 0)
  {
    bloqueReal = superbloque->tamanoBloque * fcbDelArchivo->punteroArchivo;  // Byte del bloque real
    loggeoAccesoABloque(nombreArchivo, contadorDeBloque + 1, fcbDelArchivo->punteroArchivo);
    log_debug(logger, "[LECTURA] Voy a leer %d bytes en el bloque %d del FS (Bloque %d del archivo)", min(superbloque->tamanoBloque, puntero + bytesALeer), fcbDelArchivo->punteroArchivo, contadorDeBloque + 1);
    log_debug(logger, "[LECTURA] Puntero: %d", puntero);
    leerArchivoDeBloques(bloqueReal + puntero, bloqueReal + min(superbloque->tamanoBloque-1, puntero + bytesALeer -1), informacionALeer, &bytesLeidos);
    bytesALeer -= min(superbloque->tamanoBloque, bytesALeer); 
    bloqueInicial = -1;
  }
  uint32_t* listaPunteros;
  if(bytesALeer > 0 ) {
    listaPunteros = leerBloqueDePunteros(fcbDelArchivo->punteroIndirecto);

    while(bytesALeer > 0){
      uint32_t bloqueALeer = listaPunteros[contadorDeBloque];
      bloqueReal = bloqueALeer * superbloque->tamanoBloque; 
      if(bloqueInicial!=-1){

        int offset = puntero % superbloque->tamanoBloque;
        log_debug(logger,"El offset quedo en: %d",offset);
        loggeoAccesoABloque(nombreArchivo, contadorDeBloque + 1, bloqueALeer);
        log_debug(logger, "[LECTURA] Voy a leer %d bytes en el bloque %d del FS (Bloque %d del archivo)", min(superbloque->tamanoBloque, bytesALeer), bloqueALeer, contadorDeBloque + 1);
        leerArchivoDeBloques(bloqueReal + offset, bloqueReal + min(superbloque->tamanoBloque-1, offset + bytesALeer -1), informacionALeer, &bytesLeidos);
        bloqueInicial=-1;
      }
      else {
        loggeoAccesoABloque(nombreArchivo, contadorDeBloque + 1, bloqueALeer);
        log_debug(logger, "[LETURA] Voy a escribir %d bytes en el bloque %d del FS (Bloque %d del archivo)", min(superbloque->tamanoBloque, bytesALeer), bloqueALeer, contadorDeBloque + 1);
        leerArchivoDeBloques(bloqueReal, bloqueReal + min(superbloque->tamanoBloque-1, bytesALeer -1), informacionALeer, &bytesLeidos);
      }

      bytesALeer-= superbloque->tamanoBloque;
      contadorDeBloque++;
    }
    free(listaPunteros);
  }


  int despl = 0;
  void* stream = malloc(bytesLeidos);
  agregar_cadena_a_stream_con_tamanio(stream, &despl, informacionALeer, bytesLeidos);
  escribirEnMemoria(direccionFisica, bytesLeidos, stream, pid);
  free(informacionALeer);
  free(stream);
}

/* -------------------------------*/
void escribirArchivo(char* nombreArchivo, uint32_t puntero, int bytesAEscribir, int direccionFisica, int pid){ // ISSUE 3077
  log_info(logger, "Escribir Archivo: %s - Puntero: %d - Memoria: %d - Tamaño: %d", nombreArchivo, puntero, direccionFisica, bytesAEscribir);
  leerDeMemoria(direccionFisica, bytesAEscribir, pid);
  recibir_operacion(conexionMemoria);
  recibir_operacion(conexionMemoria);
  char *informacionAEscrbir = recibir_mensaje(conexionMemoria);
  log_debug(logger, " Info a escribir: %s", informacionAEscrbir);
  FCB_t* fcbDelArchivo = buscarArchivo(nombreArchivo);
  int bloqueInicial = puntero / superbloque->tamanoBloque; 
  uint32_t contadorDeBloque = max(bloqueInicial-1,0);
  uint32_t bloqueReal; 
  int  bytesEscritos = 0;    
  log_debug(logger,"Voy a escribir los %d bytes", bytesAEscribir);
  if(bloqueInicial == 0)
  {
    bloqueReal = superbloque->tamanoBloque * fcbDelArchivo->punteroArchivo;  // Byte del bloque real
    loggeoAccesoABloque(nombreArchivo, contadorDeBloque + 1, fcbDelArchivo->punteroArchivo);
    log_debug(logger, "[ESCRITURA] voy a escribir %d bytes en el bloque %d del FS (Bloque %d del archivo)", min(superbloque->tamanoBloque, puntero + bytesAEscribir), fcbDelArchivo->punteroArchivo, contadorDeBloque + 1);
    log_debug(logger, "[ESCRITURA] Puntero: %d", puntero);
    escribirArchivoDeBloques(bloqueReal + puntero, bloqueReal + min(superbloque->tamanoBloque-1, puntero + bytesAEscribir -1), informacionAEscrbir, &bytesEscritos);
    bytesAEscribir -= min(superbloque->tamanoBloque, bytesAEscribir); 
    bloqueInicial = -1;
  }
  uint32_t* listaPunteros;
  if(bytesAEscribir > 0) {
    listaPunteros = leerBloqueDePunteros(fcbDelArchivo->punteroIndirecto);
  
    while(bytesAEscribir > 0)
    {
      uint32_t bloqueAEscribir = listaPunteros[contadorDeBloque];
      bloqueReal = bloqueAEscribir * superbloque->tamanoBloque; 
      if(bloqueInicial!=-1)
      {
        int offset = puntero % superbloque->tamanoBloque;
        log_debug(logger,"El offset quedo en: %d",offset);
        loggeoAccesoABloque(nombreArchivo, contadorDeBloque + 1, bloqueAEscribir);
        log_debug(logger, "[ESCRITURA] Voy a escribir %d bytes en el bloque %d del FS (Bloque %d del archivo)", min(superbloque->tamanoBloque, bytesAEscribir), bloqueAEscribir, contadorDeBloque + 1);
        escribirArchivoDeBloques(bloqueReal + offset, bloqueReal + min(superbloque->tamanoBloque-1, offset + bytesAEscribir -1), informacionAEscrbir, &bytesEscritos);
        bloqueInicial=-1;
      }
      else {
        loggeoAccesoABloque(nombreArchivo, contadorDeBloque + 1, bloqueAEscribir);
        log_debug(logger, "[ESCRITURA] Voy a escribir %d bytes en el bloque %d del FS (Bloque %d del archivo)", min(superbloque->tamanoBloque, bytesAEscribir), bloqueAEscribir, contadorDeBloque + 1);
        escribirArchivoDeBloques(bloqueReal, bloqueReal + min(superbloque->tamanoBloque-1, bytesAEscribir -1), informacionAEscrbir, &bytesEscritos);
      }

      bytesAEscribir-= superbloque->tamanoBloque;
      contadorDeBloque++;
      // leerBloqueDeDatos(bloqueAEscribir);
    }
    free(listaPunteros);
  }
  free(informacionAEscrbir);
}

void leerArchivoDeBloques(uint32_t byteInicial, uint32_t byteFinal, char* informacionLeida, int *bytesLeidos)
{
  uint32_t bytesALeer = byteFinal - byteInicial + 1;
  char* buffer = malloc(bytesALeer);
  char* ruta = string_substring_from (pathBloques, 1);
  archivoBloques = fopen(ruta, "rb+");  
  fseek(archivoBloques, byteInicial, SEEK_SET);
  fread(buffer, 1, bytesALeer, archivoBloques);
  memcpy((void*)informacionLeida + *bytesLeidos, buffer, bytesALeer);
  *bytesLeidos += bytesALeer;
  informacionLeida[*bytesLeidos] = '\0';
  log_debug(logger, "Se leyo: %s", informacionLeida);
  fclose(archivoBloques);
  free(ruta);
  free(buffer);
}

void escribirArchivoDeBloques(uint32_t byteInicial, uint32_t byteFinal, char* informacionAEscribir, int *bytesEscritos)
{
  uint32_t bytesAEscribir = byteFinal - byteInicial + 1;
  char* informacionRealAEscribir = string_substring(informacionAEscribir, *bytesEscritos, bytesAEscribir); 
  log_debug(logger, "En este bloque se va a escribir: %s", informacionRealAEscribir);

  char* ruta = string_substring_from(pathBloques, 1);
  void* stream = malloc(bytesAEscribir);
  int desp = 0;
  FILE* archivoBloques = fopen(ruta, "rb+");
  fseek(archivoBloques, byteInicial, SEEK_SET);
  agregar_cadena_a_stream_con_tamanio(stream, &desp, informacionRealAEscribir, bytesAEscribir);
  fwrite(stream, bytesAEscribir, 1, archivoBloques);
  fclose(archivoBloques);
  *bytesEscritos += bytesAEscribir;
  free(stream);
  free(ruta);
  free(informacionRealAEscribir);
}

void escribirEnMemoria(int direccionFisica,int tamanio, void* informacionLeida, int pid)
{
  int desplazamiento = 0;
  void* stream = malloc(sizeof(int) * 3 + tamanio);
  agregar_entero_a_stream(stream, &desplazamiento, pid);  
  agregar_entero_a_stream(stream, &desplazamiento, direccionFisica);  
  agregar_entero_a_stream(stream, &desplazamiento, tamanio);  
  memcpy(stream + desplazamiento, informacionLeida, tamanio);
  desplazamiento += tamanio;
  enviar_solicitud(conexionMemoria, ESCRIBIR, desplazamiento, stream, OPERACION_MEMORIA);
  recibir_operacion(conexionMemoria);
  recibir_operacion(conexionMemoria);
  char* mensaje = recibir_mensaje(conexionMemoria);
  free(mensaje);
  log_debug(logger, "Pude enviar ARCHIVO a memoria para ecribir");
}

void leerDeMemoria(int direccionFisica, int tamanio, int pid)
{
  int desplazamiento = 0;
  void* stream = malloc(sizeof(int) * 3);
  agregar_entero_a_stream(stream, &desplazamiento, pid);  
  agregar_entero_a_stream(stream, &desplazamiento, direccionFisica);  
  agregar_entero_a_stream(stream, &desplazamiento, tamanio);  
  enviar_solicitud(conexionMemoria, LEER, desplazamiento, stream,OPERACION_MEMORIA);
  log_debug(logger, "Pude enviar a Memoria para leer");

}

void loggeoAccesoABloque(char* nombreArchivo, uint32_t bloqueArchivo, uint32_t bloqueFileSystem)
{
  log_info(logger, "Acceso Bloque - Archivo: %s - Bloque Archivo: %d - Bloque File System %d", nombreArchivo, bloqueArchivo, bloqueFileSystem);
  sleep(atoi(retardoAccesoBloque)/1000);
}

int cantidadPunterosEnBloque(uint32_t* bloquePunteros)
{
  int cantidadMaxima = superbloque->tamanoBloque / sizeof(uint32_t);
  int cantidadReal = 0;
  for(int i = 0; i < cantidadMaxima; i++)
  {
    if(bloquePunteros[i] != 0)
      cantidadReal++;
  }
  return cantidadReal;
}
