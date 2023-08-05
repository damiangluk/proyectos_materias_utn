#include "md_memoria.h"

int main(int argc, char ** argv)
{
  if(argc > 1 && strcmp(argv[1],"-test")==0) return run_tests();

  /* ---------------- CREACION LOGGER ---------------- */
  
  logger = log_create("./cfg/md_memoria.log", "md_memoria", true, LOG_LEVEL_DEBUG);
  log_debug(logger, "Logger creado correctamente.");

  /* ---------------- LECTURA DE CONFIGS ---------------- */

  char* dir_memoria_config = argv[1];
  log_debug(logger, "Soy el directorio del config: %s\n", dir_memoria_config);
  
  t_config* config = iniciar_config();
  char *current_dir = getcwd(NULL, 0);

  char buffer[MAX_BUFFER];
  memccpy(memccpy(buffer, current_dir, '\0', MAX_BUFFER) - 1, dir_memoria_config, '\0', MAX_BUFFER);
  config = config_create(buffer);
  
  if (config != NULL) {
    if(config_has_property(config, "IP"))
    {
      ipMemoria = config_get_string_value(config, "IP");
      log_debug(logger, "Lei la IP: %s", ipMemoria);
    }
    if(config_has_property(config, "PUERTO")) 
    {
      puertoMemoria = config_get_string_value(config, "PUERTO");
      log_debug(logger, "Lei el puerto: %s", puertoMemoria);
    }
    if(config_has_property(config, "TAM_MEMORIA"))
    {
      tamMemoria = config_get_string_value(config, "TAM_MEMORIA");
      log_debug(logger, "Lei el tamaño memoria: %s", tamMemoria);
    }
    if(config_has_property(config, "TAM_SEGMENTO_0"))
    {
      tamSegmento0 = config_get_string_value(config, "TAM_SEGMENTO_0");
      log_debug(logger, "Lei el tamanio del segmento 0: %s", tamSegmento0);
    }
    if(config_has_property(config, "CANT_SEGMENTOS"))
    {
      cantSegmentos= config_get_string_value(config, "CANT_SEGMENTOS");
      log_debug(logger, "Lei la cantidad de segmentos: %s", cantSegmentos);
    }
    if(config_has_property(config, "RETARDO_MEMORIA"))
    {
      retardoMemoria = config_get_string_value(config, "RETARDO_MEMORIA");
      log_debug(logger, "Lei el retardo memoria: %s", retardoMemoria);
    }
    if(config_has_property(config, "RETARDO_COMPACTACION"))
    {
      retardoCompactacion = config_get_string_value(config, "RETARDO_COMPACTACION");
      log_debug(logger, "Lei el retardo compactacion: %s", retardoCompactacion);
    }
    if(config_has_property(config, "ALGORITMO_ASIGNACION"))
    {
      algoritmoAsignacion= config_get_string_value(config, "ALGORITMO_ASIGNACION");
      log_debug(logger, "Lei el algoritmo: %s", algoritmoAsignacion);
    }
  }

  /* ---------------- INICIO DE SERVIDOR ---------------- */
	int server_fd = iniciar_servidor(ipMemoria, puertoMemoria);
	log_debug(logger, "Servidor listo para recibir al cliente");

  while (1)
  {
    int cliente_fd = esperar_cliente(server_fd);

    int cod_op = recibir_operacion(cliente_fd);
    log_debug(logger, "El codigo de operacion que recibi es: %d", cod_op);

    if(cod_op != HANDSHAKE && cantConexiones < 3) continue;

    cantConexiones++;

    char* mensajeH = recibir_mensaje(cliente_fd);
    log_debug(logger, "Recibi handshake con mensaje: %s", mensajeH);

    if (strcmp(mensajeH, "Conexion CPU a MEMORIA") == 0) {
      log_debug(logger, "Cree hilo con CPU");
      crearHilo(CPU, cliente_fd);
    } else if (strcmp(mensajeH, "Conexion FS a MEMORIA") == 0) 
    {
      log_debug(logger, "Cree hilo con FS");
      crearHilo(FILESYSTEM, cliente_fd);
    } else if (strcmp(mensajeH, "Conexion KERNEL a MEMORIA") == 0)
    {
      conexionKernel = cliente_fd;
      log_debug(logger, "Cree hilo con KERNEL");
      crearHilo(KERNEL, conexionKernel);
    }

    free(mensajeH);
    enviar_mensaje_con_op("OK", cliente_fd, OK);
    if(cantConexiones == 3) crear_estructuras();
  }
  
  terminar_programa(-1, logger, config, current_dir);
	return EXIT_SUCCESS;
}

/* ---------------- CREACION DE HILOS ---------------- */

void crearHilo(int proceso, int conexion) {

  switch(proceso)
  {  
    case KERNEL:
      // CREACION HILO KERNEL
      pthread_create(&hiloKernel, NULL, (void*)hiloConKernel, NULL);
      pthread_detach(hiloKernel);
      break;
    case CPU:
    case FILESYSTEM:
      char* procesoConectado = string_new();
      if (proceso == CPU)
      {
        string_append(&procesoConectado, "CPU");
      } else
      {
        string_append(&procesoConectado, "FILESYSTEM");
      }
      
      // CREACION HILO CPU O FILE SYSTEM 
      void* conexionVoid = malloc(sizeof(int) * 2 + 11);
      int desplazamiento = 0;
      agregar_entero_a_stream(conexionVoid, &desplazamiento, conexion);
      agregar_cadena_a_stream(conexionVoid, &desplazamiento, procesoConectado);
      pthread_create(&hiloFileSystem, NULL, (void*)hiloLecturaEscritura, conexionVoid);
      pthread_detach(hiloFileSystem);
      free(procesoConectado);
      break;
  }
}

void hiloLecturaEscritura(void* param)
{
  int desplazamiento = 0;
  int conexion = deserializar_entero_desde_buffer(param, &desplazamiento);
  char* procesoConectado = deserializar_cadena_desde_buffer(param, &desplazamiento);
  free(param);
  int cod_op = 0;
  while (cod_op != -1) 
  {
    cod_op = recibir_operacion(conexion);
    log_debug(logger, "El codigo de operacion que recibi es: %d", cod_op);
    switch(cod_op) {
      case OPERACION_MEMORIA:
        int cod_sol = recibir_operacion(conexion);
        log_debug(logger, "El codigo de solicitud que recibi es: %d", cod_sol);
        int size = recibir_operacion(conexion);
        log_debug(logger, "Recibi el size buffer: %d", size);

        void* buffer = recibir_datos(conexion, size);
        int desplazamiento = 0;

        int pid = deserializar_entero_desde_buffer(buffer, &desplazamiento);
        int direccion, tamanio; 
        switch (cod_sol) {
          case LEER:
            direccion = deserializar_entero_desde_buffer(buffer, &desplazamiento);
            tamanio = deserializar_entero_desde_buffer(buffer, &desplazamiento);
            leerEspacioUsuario(direccion, tamanio, conexion);
            log_info(logger, "PID: %d - Acción: LEER - Dirección física: %d - Tamaño: %d - Origen: %s", pid, direccion, tamanio, procesoConectado);
            break;

          case ESCRIBIR:
            direccion = deserializar_entero_desde_buffer(buffer, &desplazamiento);
            tamanio = deserializar_entero_desde_buffer(buffer, &desplazamiento);
            void *informacion = malloc(tamanio);
            memcpy(informacion, buffer + desplazamiento, tamanio);
            escribirEspacioUsuario(direccion, tamanio, informacion, conexion);
            free(informacion);
            log_info(logger, "PID: %d - Acción: ESCRIBIR - Dirección física: %d - Tamaño: %d - Origen: %s", pid, direccion, tamanio, procesoConectado);
            break;

          case -1:
            log_debug(logger, "el cliente se desconecto.");
            break;
            
          default:
            log_debug(logger, "Operacion desconocida. No quieras meter la pata");
            break;
        }
        free(buffer);
        break;

    }
  };
  free(procesoConectado);
}

void hiloConKernel()
{
  int cod_op;
  do {
    cod_op = recibir_operacion(conexionKernel);
    log_debug(logger, "El codigo de operacion que recibi es: %d", cod_op);
    switch(cod_op) {
      case OPERACION_DE_KERNEL:
        int cod_sol = recibir_operacion(conexionKernel);
        log_debug(logger, "El codigo de solicitud que recibi es: %d", cod_sol);
        int size;
        recv(conexionKernel, &size, sizeof(int), 0);
        printf("Recibi el size buffer: %d\n", size);

        void* buffer = recibir_datos(conexionKernel, size);
        int desplazamiento = 0;

        int PID;
        int idSegmento;

        switch (cod_sol) {
          case INICIAR_PROCESO:
            PID = deserializar_entero_desde_buffer(buffer, &desplazamiento);
            log_debug(logger, "Recibi iniciar proceso %d", PID);
            iniciarProceso(PID);
            break;
          case CREATE_SEGMENTO:
            PID = deserializar_entero_desde_buffer(buffer, &desplazamiento);
            idSegmento = deserializar_entero_desde_buffer(buffer, &desplazamiento);
            int TamSegmento = deserializar_entero_desde_buffer(buffer, &desplazamiento);
            log_debug(logger, "Recibi create segment del proceso %d para segmento %d de tamanio %d", PID, idSegmento, TamSegmento);
            createSegment(PID, idSegmento, TamSegmento);
            break;
          case DELETE_SEGMENTO:
            PID = deserializar_entero_desde_buffer(buffer, &desplazamiento);
            idSegmento = deserializar_entero_desde_buffer(buffer, &desplazamiento);
            log_debug(logger, "Recibi delete segment del proceso %d para segmento %d", PID, idSegmento);
            deleteSegment(PID, idSegmento);
            break;
          case FINALIZAR_PROCESO:
            PID = deserializar_entero_desde_buffer(buffer, &desplazamiento);
            log_debug(logger, "Recibi finalizar proceso %d", PID);
            finalizarProceso(PID);
            break;
          case SOLICITUD_COMPACTACION:
            log_debug(logger, "Recibi permiso para compactar");
            compactarMemoria();
            log_de_resultado_compactacion();
            break;
          case -1:
            log_debug(logger, "el cliente se desconecto.");
            break;
          default:
            log_debug(logger, "Operacion desconocida. No quieras meter la pata");
            break;
        }
        free(buffer);
        break;
    }
  } while (cod_op != -1);
}

/* ---------------- TAREAS DE MEMORIA PARA PROCESO ---------------- */

void iniciarProceso(int PID)
{
  item_tablas_segmentos* itemTablaSegmentos = malloc(sizeof(item_tablas_segmentos));
  itemTablaSegmentos->ListaSegmentos = list_create();
  itemTablaSegmentos->PID = PID;
  list_add(itemTablaSegmentos->ListaSegmentos, segmento0);
  list_add(tablasSegmentos, itemTablaSegmentos);
  log_info(logger, "Creación de Proceso PID: %d", PID);
  enviarTablaSegmentos(PID, itemTablaSegmentos);
  calcular_espacio_disponible();
}

void createSegment(int PID, int idSegmento, int Tamanio)
{
  item_tablas_segmentos* itemTablaSegmentos = buscarTablaSegmentosDeProceso(PID);
  
  if(list_size(itemTablaSegmentos->ListaSegmentos) == atoi(cantSegmentos))
  {
    log_error(logger, "Se supero el limite de %d segmentos para un proceso", atoi(cantSegmentos));
    enviar_mensaje_con_op("Se supero el limite de segmentos para un proceso", conexionKernel, ERROR);
    return;
  }

  int direccionFisica = buscarEspacio(Tamanio);
  if(direccionFisica < 0)
  {
    if(direccionFisica == -1)
      enviar_mensaje_con_op("Out of memory", conexionKernel, ERROR);
    if(direccionFisica == -2)
      enviar_mensaje_con_op("Necesito compactacion para crear segmento", conexionKernel, SOLICITUD_COMPACTAR);
    return;
  }
  
  Segmento* nuevoSegmento = malloc(sizeof(Segmento));
  nuevoSegmento->Id = idSegmento;
  nuevoSegmento->Base = direccionFisica;
  nuevoSegmento->Tamanio = Tamanio;

  list_add(itemTablaSegmentos->ListaSegmentos, nuevoSegmento);
  log_info(logger, "PID: %d - Crear Segmento: %d - Base: %d - TAMAÑO: %d", PID, idSegmento, direccionFisica, Tamanio);
  
  enviarTablaSegmentos(PID, itemTablaSegmentos);
  calcular_espacio_disponible();
}

void deleteSegment(int PID, int idSegmento)
{
  bool encontre_segmento(void *item) 
  {
    Segmento* segmento = (Segmento*)item;
    return segmento->Id == idSegmento;
  }
  
  item_tablas_segmentos* itemTablaSegmentos = buscarTablaSegmentosDeProceso(PID);
  Segmento* segmento = list_find(itemTablaSegmentos->ListaSegmentos, encontre_segmento);
  log_info(logger, "PID: %d - Eliminar Segmento: %d - Base: %d - TAMAÑO: %d", PID, idSegmento, segmento->Base, segmento->Tamanio);
  list_remove_element(itemTablaSegmentos->ListaSegmentos, segmento);
  liberar_segmento(segmento);

  consolidarHuecos();

  enviarTablaSegmentos(PID, itemTablaSegmentos);
  calcular_espacio_disponible();
}

void finalizarProceso(int PID)
{
  item_tablas_segmentos* itemTablaSegmentos = buscarTablaSegmentosDeProceso(PID);
  
  while(list_size(itemTablaSegmentos->ListaSegmentos) > 0)
  {
    Segmento* segmento = list_remove(itemTablaSegmentos->ListaSegmentos, 0);
    if(segmento->Id == 0) continue;
    liberar_segmento(segmento);
  }
  
  list_destroy(itemTablaSegmentos->ListaSegmentos);
  list_remove_element(tablasSegmentos, itemTablaSegmentos);
  free(itemTablaSegmentos);

  consolidarHuecos();
  log_info(logger, "Eliminacion de Proceso PID: %d", PID);
  calcular_espacio_disponible();
}

void compactarMemoria()
{
  log_info(logger, "Solicitud de Compactación");
  if(list_size(espaciosLibres) < 2) return;

	list_sort(espaciosLibres, compara_base);
  t_list* procesosActualizados = list_create();

  for(int i = 0; i < list_size(espaciosLibres) - 1; i++)
  {
    espacio_libre *hueco = list_get(espaciosLibres, i);
    espacio_libre *hueco2 = list_get(espaciosLibres, i + 1);

    if(hueco2->Base > hueco->Base + hueco->Tamanio + 1)
    {
      int destinoInformacion = hueco->Base;
      int origenInformacion = hueco->Base + hueco->Tamanio - 1;
      int tamanioInformacion = hueco2->Base - hueco->Base - hueco->Tamanio;
      hueco->Base += tamanioInformacion;
      memcpy(espacio_usuario + destinoInformacion, espacio_usuario + origenInformacion + 1, tamanioInformacion);
      log_info(logger, "Se movio un hueco de %d - %d a %d - %d", destinoInformacion + 1, origenInformacion, hueco->Base, hueco->Base + hueco->Tamanio - 1);

      t_list* segmentosEntreHuecos = buscarSegmentosEntrePosiciones(origenInformacion, hueco2->Base);

      for(int f = 0; f < list_size(segmentosEntreHuecos); f++)
      {
        segmentoConPID* segmento = list_get(segmentosEntreHuecos, f);
        int a = segmento->segmento->Base;
        segmento->segmento->Base = destinoInformacion + (segmento->segmento->Base - origenInformacion) - 1;
        log_info(logger, "Se movio segmento de id %d de %d a %d", segmento->segmento->Id, a, segmento->segmento->Base);

        bool estaActualizado(int* valor)
        {
          return *valor == segmento->PID;
        }

        void* pid = malloc(sizeof(int));
        int desp = 0;
        agregar_entero_a_stream(pid, &desp, segmento->PID);
        if(!list_any_satisfy(procesosActualizados, (void*) estaActualizado)) list_add(procesosActualizados, pid);
        free(segmento);
      }

      list_destroy(segmentosEntreHuecos);
    }
  }

  log_info(logger, "Fin compactacion memoria");

  consolidarHuecos();
  sleep(atoi(retardoCompactacion) / 1000);

  t_list* tablas = list_map(procesosActualizados, (void*) buscarTablaSegmentosDeProcesoStream);
  enviarTablasActualizadas(tablas);
  list_destroy_and_destroy_elements(procesosActualizados, free);
}

/* ---------------- LECTURA Y ESCRITURA DE MEMORIA ---------------- */

void leerEspacioUsuario(int direccion, int tamanio, int conexion)
{
  sleep(atoi(retardoMemoria) / 1000);

  void* leido = malloc(tamanio);
  memcpy(leido, espacio_usuario + direccion, tamanio);
  int desplazamiento = 0;
  char *m = deserializar_cadena_desde_buffer_con_tamanio(leido, &desplazamiento, tamanio);
  /*m = realloc(m, tamanio + 1);
  m[tamanio] = '\0';*/
  log_info(logger, "Lo leido es %s", m);
  enviar_mensaje_con_opysol(m, conexion, OPERACION_MEMORIA, LEER);
  //enviar_mensaje_con_op(m, conexion, LEER);
  free(m);
  free(leido);
}

void escribirEspacioUsuario(int direccion, int tamanio, void* informacion, int conexion)
{
  sleep(atoi(retardoMemoria) / 1000);

  memcpy(espacio_usuario + direccion, informacion, tamanio - 1);

  int desplazamiento = 0;
  char *m = deserializar_cadena_desde_buffer_con_tamanio(informacion, &desplazamiento, tamanio);
  //m = realloc(m, tamanio + 1);
  //m[tamanio] = '\0';
  log_info(logger, "Lo escrito es %s", m);
  free(m);
  enviar_mensaje_con_opysol("OK", conexion, OPERACION_MEMORIA, ESCRIBIR);
}

/* ---------------- BUSQUEDAS ---------------- */

int buscarEspacio(int tamanio)
{
  bool equals(void *espacio)
  {
    espacio_libre* espacioLibre = (espacio_libre*)espacio;
    return espacioLibre->Tamanio >= tamanio;
  }

  bool comparador_best(void *espacio1, void *espacio2)
  {
    espacio_libre* espacioLibre1 = (espacio_libre*)espacio1;
    espacio_libre* espacioLibre2 = (espacio_libre*)espacio2;
    return espacioLibre1->Tamanio < espacioLibre2->Tamanio;
  }
  bool comparador_worst(void *espacio1, void *espacio2)
  {
    espacio_libre* espacioLibre1 = (espacio_libre*)espacio1;
    espacio_libre* espacioLibre2 = (espacio_libre*)espacio2;
    return espacioLibre1->Tamanio > espacioLibre2->Tamanio;
  }

  t_list* espacios_donde_entra = list_filter(espaciosLibres, equals);
  espacio_libre* espacio;

  if(strcmp(algoritmoAsignacion, "BEST") == 0){
    list_sort(espacios_donde_entra, comparador_best);
  }
  else if(strcmp(algoritmoAsignacion, "WORST") == 0){
    list_sort(espacios_donde_entra, comparador_worst);
  }

  if(list_is_empty(espacios_donde_entra))
  {
    if(calcular_espacio_disponible() >= tamanio)
    {
      log_debug(logger, "No hay espacio disponible pero con compactacion se resuelve");
      return -2;
    }
    
    log_error(logger, "No hay espacio disponible de tamanio %d", tamanio);
    return -1;
  }
  
  espacio = list_get(espacios_donde_entra, 0);

  list_destroy(espacios_donde_entra);

  int direccionARetornar = espacio->Base;
  int espacioLibreSobrante = espacio->Tamanio - tamanio;

  if(espacioLibreSobrante > 0)
  {
    espacio->Base += tamanio;
    espacio->Tamanio = espacioLibreSobrante;
  } else
  {
    list_remove_element(espaciosLibres, espacio);
    free(espacio);
  }

  return direccionARetornar;
}

t_list* buscarSegmentosEntrePosiciones(int posMin, int posMax)
{
  bool cumpleCondicionEntre(void* seg)
  {
    Segmento *s = (Segmento*)seg;
    return s->Base >= posMin && s->Base < posMax;
  }
  
  t_list* segmentos = list_create();
  t_list_iterator* iterator = list_iterator_create(tablasSegmentos);
  while(list_iterator_has_next(iterator))
  {
    item_tablas_segmentos *item = (item_tablas_segmentos*) list_iterator_next(iterator);
    t_list* lista_segmentos_proceso = list_filter(item->ListaSegmentos, cumpleCondicionEntre);
    t_list_iterator* iteratorSegmentos = list_iterator_create(lista_segmentos_proceso);
    while(list_iterator_has_next(iteratorSegmentos))
    {
      Segmento *s = (Segmento*) list_iterator_next(iteratorSegmentos);
      segmentoConPID *Segmento = malloc(sizeof(int)*4);
      Segmento->PID = item->PID;
      Segmento->segmento = s;
      list_add(segmentos, Segmento);
    };
    list_iterator_destroy(iteratorSegmentos);
  };
  list_iterator_destroy(iterator);
  return segmentos;
}

item_tablas_segmentos* buscarTablaSegmentosDeProceso(int PID)
{
  bool encontre_tabla_segmentos(void *item) 
  {
    item_tablas_segmentos* itemTablasSegmentos = (item_tablas_segmentos*)item;
    return itemTablasSegmentos->PID == PID;
  }

  item_tablas_segmentos* itemTablaSegmentos = list_find(tablasSegmentos, encontre_tabla_segmentos);
  return itemTablaSegmentos;
}

item_tablas_segmentos* buscarTablaSegmentosDeProcesoStream(void* item)
{
  int desp = 0;
  int PID = deserializar_entero_desde_buffer(item, &desp);
  return buscarTablaSegmentosDeProceso(PID);
}

/* ---------------- ENVIOS ---------------- */

void enviarTablaSegmentos(int PID, item_tablas_segmentos* tablaSegmentosDelProceso)
{
  int desplazamiento = 0;
  void* stream = malloc(sizeof(int) * (list_size(tablaSegmentosDelProceso->ListaSegmentos) * 3 + 1));
  agregar_tabla_segmentos_a_stream(stream, &desplazamiento, tablaSegmentosDelProceso->ListaSegmentos);
  enviar_solicitud(conexionKernel, INICIAR_PROCESO, desplazamiento, stream, TABLA_SEGMENTO);
  log_debug(logger, "Envie tabla de segmentos del proceso: %d con %d elementos", PID, list_size(tablaSegmentosDelProceso->ListaSegmentos));
}

void enviarTablasActualizadas(t_list* tablas)
{
  int desplazamiento = 0;
  void* stream = malloc(sizeof(int));

  log_debug(logger, "Se actualizaron las tablas de segmentos de %d procesos", list_size(tablas));
  agregar_entero_a_stream(stream, &desplazamiento, list_size(tablas));
  
  for(int i = 0; i < list_size(tablas); i++) 
  {
    item_tablas_segmentos* tabla = list_get(tablas, i);
    stream = realloc(stream, desplazamiento + sizeof(int) * (list_size(tabla->ListaSegmentos) * 3 + 2));
    log_debug(logger, "COMPACTACION - Se movieron segmentos del proceso %d", tabla->PID);
    agregar_entero_a_stream(stream, &desplazamiento, tabla->PID);
    agregar_tabla_segmentos_a_stream(stream, &desplazamiento, tabla->ListaSegmentos);
  }

  enviar_solicitud(conexionKernel, TABLAS_SEGMENTOS, desplazamiento, stream, TABLA_SEGMENTO);
  list_destroy(tablas);
}

/* ---------------- UTILIDADES DE MEMORIA ---------------- */

void crear_estructuras()
{
  log_debug(logger, "Creando estructuras administrativas");

  //CREACION ESTRUCTURAS  ADMINISTRATIVAS
  espacio_usuario = malloc(atoi(tamMemoria));
  tablasSegmentos = list_create();
  espaciosLibres = list_create();

  // CREACION SEGMENTO 0
  segmento0 = malloc(sizeof(Segmento));
  segmento0->Id = 0;
  segmento0->Base = 0;
  segmento0->Tamanio = atoi(tamSegmento0);

  //CREACION ESPACIO LIBRE
  espacio_libre* espacio = malloc(sizeof(espacio_libre));
  espacio->Base = segmento0->Tamanio;
  espacio->Tamanio = atoi(tamMemoria) - segmento0->Tamanio;
  list_add(espaciosLibres, espacio);
}

void liberar_segmento(Segmento* segmento)
{
  espacio_libre* nuevoEspacio= malloc(sizeof(espacio_libre));
  nuevoEspacio->Base = segmento->Base;
  nuevoEspacio->Tamanio = segmento->Tamanio;
  
  list_add(espaciosLibres, nuevoEspacio);
  log_debug(logger, "Se elimino el segmento %d con tamanio %d", segmento->Id, segmento->Tamanio);
  free(segmento);
}

int calcular_espacio_disponible()
{
  int espacioTotal = 0;
  void sumar(void* espacioLibre)
  {
    espacio_libre* espacio = (espacio_libre*) espacioLibre;
    espacioTotal += espacio->Tamanio;
    log_debug(logger, "HUECO MEMORIA - Posicion inicio: %d - Posicion fin: %d", espacio->Base, espacio->Base + espacio->Tamanio - 1);
  }
  
  list_iterate(espaciosLibres, (void*) sumar);
  log_debug(logger, "El espacio libre total de memoria es %d", espacioTotal);
  return espacioTotal;
}

void consolidarHuecos()
{
  list_sort(espaciosLibres, compara_base);
  for (int i = 0; i < list_size(espaciosLibres) - 1; i++) 
  {
    log_debug(logger, "Consolidando - Hay %d huecos", list_size(espaciosLibres));
    espacio_libre *hueco1 = list_get(espaciosLibres, i);
    espacio_libre *hueco2 = list_get(espaciosLibres, i + 1);

    if (hueco1->Base + hueco1->Tamanio == hueco2->Base)
    {
      int huecoBase = hueco1->Base;
      int huecoLimite = hueco1->Base + hueco1->Tamanio - 1;
      hueco1->Base = min(hueco1->Base, hueco2->Base);
      hueco1->Tamanio += hueco2->Tamanio;
      log_debug(logger, "Se consolidaron dos huecos: %d a %d y %d a %d en %d a %d", huecoBase, huecoLimite, hueco2->Base, hueco2->Base + hueco2->Tamanio - 1, hueco1->Base, hueco1->Base + hueco1->Tamanio - 1);
      list_remove_element(espaciosLibres, hueco2);
      i--;
      free(hueco2);
    }
  }
}

bool compara_base(void *espacio1, void *espacio2)
{
  espacio_libre *e1 = (espacio_libre *)espacio1;
  espacio_libre *e2 = (espacio_libre *)espacio2;

  if (e1->Base < e2->Base) {
    return true;
  } else if (e1->Base > e2->Base) {
    return false;
  } else {
    log_error(logger, "Dos espacios libres no pueden tener la misma base");
    return false;
  }
}

void log_de_resultado_compactacion()
{
  t_list_iterator* iterator = list_iterator_create(tablasSegmentos);
  while(list_iterator_has_next(iterator))
  {
    item_tablas_segmentos *item = (item_tablas_segmentos*) list_iterator_next(iterator);
    t_list_iterator* iteratorSegmentos = list_iterator_create(item->ListaSegmentos);
    while(list_iterator_has_next(iteratorSegmentos))
    {
      Segmento *s = (Segmento*) list_iterator_next(iteratorSegmentos);
      segmentoConPID *Segmento = malloc(sizeof(int)*4);
      Segmento->PID = item->PID;
      Segmento->segmento = s;
      log_debug(logger, "PID: %d - Segmento: %d - Base: %d - Tamaño %d", Segmento->PID, Segmento->segmento->Id, Segmento->segmento->Base, Segmento->segmento->Tamanio);
    };
    list_iterator_destroy(iteratorSegmentos);
  };
  list_iterator_destroy(iterator);
}