#include "md_kernel.h"

int main(int argc, char ** argv)
{
  if(argc > 1 && strcmp(argv[1],"-test")==0) return run_tests();

  //---------------- INICIAR PROGRAMA ----------------
  inicializarColas();
  inicializarLogger();
  inicializarTablaArchivosGlobales();
  // ---------------- LECTURA DE CONFIGS ----------------

  char* dir_kernel_config = argv[1];
  log_debug(logger, "Soy el directorio del config: %s", dir_kernel_config);

  config = iniciar_config();
  char *current_dir = getcwd(NULL, 0);

  char buffer[MAX_BUFFER];
  memccpy(memccpy(buffer, current_dir, '\0', MAX_BUFFER) - 1, dir_kernel_config, '\0', MAX_BUFFER);

  config = config_create(buffer);
  
  if (config == NULL) return EXIT_FAILURE;
  if(config_has_property(config, "IP"))
  {
    ip = config_get_string_value(config, "IP");
    log_debug(logger, "Lei la IP Kernel: %s", ip);
  }
  if(config_has_property(config, "PUERTO"))
  {
    puerto = config_get_string_value(config, "PUERTO");
    log_debug(logger, "Lei el puerto Kernel %s", puerto);
  }
  if(config_has_property(config, "ALGORITMO_PLANIFICACION"))
  {
    algoritmoDePlanificacion = config_get_string_value(config, "ALGORITMO_PLANIFICACION");
    log_debug(logger, "Lei el algoritmo de planificacion %s", algoritmoDePlanificacion);
  }
  if(config_has_property(config, "ESTIMACION_INICIAL"))
  {
    estimacionInicial = config_get_string_value(config, "ESTIMACION_INICIAL");
    log_debug(logger, "Lei el estimacion inicial %s", estimacionInicial);
  }
  if(config_has_property(config, "HRRN_ALFA"))
  {
    hrrnAlfa = config_get_string_value(config, "HRRN_ALFA");
    log_debug(logger, "Lei el hrrn alfa %s", hrrnAlfa);
  }
  if(config_has_property(config, "IP_CPU"))
  {
    ipCpu = config_get_string_value(config, "IP_CPU");
    log_debug(logger, "Lei la ip cpu: %s", ipCpu);
  }
  if(config_has_property(config, "PUERTO_CPU"))
  {
    puertoCpu = config_get_string_value(config, "PUERTO_CPU");
    log_debug(logger, "Lei el puerto cpu: %s", puertoCpu);
  }
  if(config_has_property(config, "IP_MEMORIA"))
  {
    ipMemoria = config_get_string_value(config, "IP_MEMORIA");
    log_debug(logger, "Lei la ip memoria: %s", ipMemoria);
  }
  if(config_has_property(config, "PUERTO_MEMORIA"))
  {
    puertoMemoria = config_get_string_value(config, "PUERTO_MEMORIA");
    log_debug(logger, "Lei el puerto memoria: %s", puertoMemoria);
  }
  if(config_has_property(config, "IP_FILESYSTEM"))
  {
    ipFileSystem = config_get_string_value(config, "IP_FILESYSTEM");
    log_debug(logger, "Lei la ip memoria: %s", ipFileSystem);
  }
  if(config_has_property(config, "PUERTO_FILESYSTEM"))
  {
    puertoFileSystem = config_get_string_value(config, "PUERTO_FILESYSTEM");
    log_debug(logger, "Lei el puerto memoria: %s", puertoFileSystem);
  }
  if(config_has_property(config, "GRADO_MAX_MULTIPROGRAMACION"))
  {
    gradoMaxMulti = config_get_string_value(config, "GRADO_MAX_MULTIPROGRAMACION");
    log_debug(logger, "Lei el grado maximo de multi: %s", gradoMaxMulti);
  }
   if(config_has_property(config, "RECURSOS"))
  {
    nombresRecurso = config_get_array_value(config, "RECURSOS");
    int contNombres=0;

    while(nombresRecurso[contNombres]!=NULL) {
      log_debug(logger, "Lei el nombre del recurso: %s", nombresRecurso[contNombres]);
      contNombres++;
    }
  }
  if(config_has_property(config, "INSTANCIAS_RECURSOS"))
  {
    instanciaRecurso = config_get_array_value(config, "INSTANCIAS_RECURSOS");
    int contRecursos=0;

    while(nombresRecurso[contRecursos]!=NULL) {
        log_debug(logger, "Lei la instancia de %s: %s", nombresRecurso[contRecursos], instanciaRecurso[contRecursos]);
        contRecursos++;
    }

  }

  if(strcmp(algoritmoDePlanificacion, "HRRN") == 0) {
    algoritmoActual = HRRN;
  } else {
    algoritmoActual = FIFO;
  }

  // ---------------- INICIALIZACION RECURSOS ----------------

  inicializarRecursos();

  // ---------------- INICIALIZACION SEMAFOROS ----------------

  sem_init(&sem_dispatcher, 0, 0);
  sem_init(&sem_fin, 0, 0);
  sem_init(&sem_colaNew, 0, 0);
  sem_init(&sem_colaReady, 0, 0);
  sem_init(&sem_gradoMultiprog, 0, atoi(gradoMaxMulti));
  sem_init(&sem_cpu_not_running, 0, 1);
  semaforosProcesos = list_create();
  procesosActivos = list_create();

  // ---------------- CREANDO HILOS PLANIFICADORES ----------------

  pthread_create(&planificadorLargoPlazo, NULL, (void*)newAReady, NULL);
  pthread_create(&planificadorCortoPlazo, NULL, (void*)dispatcher, NULL);

  /* ---------------- HANDSHAKE A MEMORIA ---------------- */
  conexionMemoria = crear_conexion(ipMemoria, puertoMemoria);
  enviar_mensaje_con_op("Conexion KERNEL a MEMORIA", conexionMemoria, HANDSHAKE);
  int respuesta = recibir_operacion(conexionMemoria);
  char* mensaje = recibir_mensaje(conexionMemoria);

  if(respuesta != OK)
  {
    log_error(logger, "No me pude conectar a la memoria");
    return EXIT_FAILURE;
  }
  log_debug(logger, "Respuesta memoria: %s", mensaje);
  free(mensaje);

  /* ---------------- HANDSHAKE A FILESYSTEM ---------------- */
  conexionFileSystem = crear_conexion(ipFileSystem, puertoFileSystem);
  enviar_mensaje_con_op("Conexion KERNEL a FILESYSTEM", conexionFileSystem, HANDSHAKE);
  respuesta = recibir_operacion(conexionFileSystem);
  mensaje = recibir_mensaje(conexionFileSystem);

  if(respuesta != OK)
  {
    log_error(logger, "No me pude conectar a la filesystem");
    return EXIT_FAILURE;
  }
  log_debug(logger, "Respuesta filesystem: %s", mensaje);
  free(mensaje);

  /* ---------------- HANDSHAKE A CPU ---------------- */
  conexionCpu = crear_conexion(ipCpu, puertoCpu);
  enviar_mensaje_con_op("Conexion KERNEL a CPU", conexionCpu, HANDSHAKE);
  respuesta = recibir_operacion(conexionCpu);
  mensaje = recibir_mensaje(conexionCpu);

  if(respuesta != OK)
  {
    log_error(logger, "No me pude conectar a la cpu");
    return EXIT_FAILURE;
  }
  log_debug(logger, "Respuesta cpu: %s", mensaje);
  free(mensaje);

  // ---------------- INICIO SERVIDOR ----------------

  server_fd = iniciar_servidor(ip, puerto);
  pthread_create(&hiloKernelConsola, NULL, (void*)hiloXConsola, NULL);
  pthread_create(&hiloKernelCpu, NULL, (void*)hiloCpu, NULL);
  
  sem_wait(&sem_fin);

  pthread_join(planificadorLargoPlazo, NULL);
  pthread_join(planificadorCortoPlazo, NULL);
  pthread_join(hiloKernelCpu, NULL);
  pthread_join(hiloKernelConsola, NULL);

  sem_destroy(&sem_dispatcher);
  sem_destroy(&sem_fin);
  sem_destroy(&sem_colaNew);
  sem_destroy(&sem_colaReady);
  sem_destroy(&sem_gradoMultiprog);
  sem_destroy(&sem_cpu_not_running);

  list_destroy(recursos);
  list_destroy(procesosActivos);

  liberar_colas();
  //liberarTablaArchivosGlobales();
  list_iterate(recursos, (void*) liberar_recurso);
  log_debug(logger, "Termino el programa");
  terminar_programa(-1, logger, config, current_dir);
	return EXIT_SUCCESS;
}

/* ---------------- HILOS ---------------- */

void hiloXConsola () 
{
  while(1)
  {
		int conexionConsola = esperar_cliente(server_fd);
    log_debug(logger, "Recibi nuevo paquete consola");

    void* conexionVoid = malloc(sizeof(int));
    int desplazamiento = 0;
    agregar_entero_a_stream(conexionVoid, &desplazamiento, conexionConsola);

		pthread_t hiloPorConsola;
    pthread_create(&hiloPorConsola, NULL, (void*)armarProceso, conexionVoid);
    pthread_detach(hiloPorConsola);
	}
}

void armarProceso(void* param)
{
  int desplazamiento = 0;
  int conexionConsola = deserializar_entero_desde_buffer(param, &desplazamiento);
  free(param);

  int cod_op = recibir_operacion(conexionConsola);
  log_debug(logger, "El codigo de operacion que recibi es: %d", cod_op);
  char* mensajeH = recibir_mensaje(conexionConsola);
  log_debug(logger, "Recibi handshake con mensaje: %s", mensajeH);
  free(mensajeH);
  enviar_mensaje_con_op("OK", conexionConsola, OK);

  cod_op = recibir_operacion(conexionConsola);
  log_debug(logger, "El codigo de operacion que recibi es: %d", cod_op);
  t_list* lista = recibir_paquete(conexionConsola);
  PCB* pcb = armar_pcb(lista);
  enviar_mensaje_con_op("OK", conexionConsola, OK); 

  item_semaforo *nuevoItem = malloc(sizeof(item_semaforo));
  nuevoItem->PID = pcb->PID;
  nuevoItem->semProceso = malloc(sizeof(sem_t));
  sem_init(nuevoItem->semProceso, 0, 0);

  pthread_mutex_lock(&mutexSemaforosProcesos);
  list_add(semaforosProcesos, nuevoItem);
  pthread_mutex_unlock(&mutexSemaforosProcesos);
  
  log_info(logger, "Se crea el proceso %d", pcb->PID);
  agregarANew(pcb);
  bool error = false;

  while(instruccionAEjecutar != EXITS && instruccionAEjecutar != ERRORCPU && !error)
  {
    sem_wait(nuevoItem->semProceso);

    PCB* pcb_actual = pcb_running;
    void* buffer_actual = bufferCPU;
    int desplazamiento_actual = desplazamientoBufferCPU;
    char *archivo;

    switch(instruccionAEjecutar)
    {
      case IO:
        int tiempoEnMilisegundos = deserializar_entero_desde_buffer(buffer_actual, &desplazamiento_actual);
        log_info(logger, "Recibimos IO de proceso %d con tiempo %d", pcb_actual->PID, tiempoEnMilisegundos);
        pcb_actual->Estado = BLOCK;
        logCambiarEstado(pcb_actual->PID, EXEC, BLOCK);
        sem_post(&sem_dispatcher);
        sem_post(&sem_cpu_not_running);
        sleep(tiempoEnMilisegundos);
        if(queue_size(colaReady) == 0) sem_post(&sem_cpu_not_running);
        agregarAReady(pcb_actual, false);
        break;
      case YIELD:
        log_info(logger, "Recibimos YIELD de proceso: %d", pcb_actual->PID);
        estimador(pcb_actual);
        agregarAReady(pcb_actual, true);
        break;
      case FOPEN:
        archivo = deserializar_cadena_desde_buffer(buffer_actual, &desplazamiento_actual);
        log_info(logger, "Recibimos FOPEN de proceso: %d para archivo %s", pcb_actual->PID, archivo);
        abrirArchivoFS(archivo, pcb_actual);
        free(archivo);
        break;
      case FCLOSE:
        archivo = deserializar_cadena_desde_buffer(buffer_actual, &desplazamiento_actual);
        log_info(logger, "Recibimos FCLOSE de proceso %d para archivo %s", pcb_actual->PID, archivo);
        cerrarArchivoFS(archivo, pcb_actual);
        agregarAReady(pcb_actual, true);
        free(archivo);
        break;
      case FSEEK:
        archivo = deserializar_cadena_desde_buffer(buffer_actual, &desplazamiento_actual);
        int posicion = deserializar_entero_desde_buffer(buffer_actual, &desplazamiento_actual);
        log_info(logger, "Recibimos FSEEK de proceso %d para archivo %s en posicion %d", pcb_actual->PID, archivo, posicion);
        seekArchivoFS(archivo, posicion, pcb_actual);
        agregarAReady(pcb_actual, true);
        free(archivo);
        break;
      case FREAD:
        archivo = deserializar_cadena_desde_buffer(buffer_actual, &desplazamiento_actual);
        int dirFisicaRead = deserializar_entero_desde_buffer(buffer_actual, &desplazamiento_actual);
        int tamanioRead = deserializar_entero_desde_buffer(buffer_actual, &desplazamiento_actual);
        log_info(logger, "Recibimos FREAD de proceso %d para archivo %s en dir %d un tamanio de %d", pcb_actual->PID, archivo, dirFisicaRead, tamanioRead);
        leerArchivoFS(archivo, dirFisicaRead, tamanioRead, pcb_actual);
        agregarAReady(pcb_actual, true);
        free(archivo);
        break;
      case FWRITE:
        archivo = deserializar_cadena_desde_buffer(buffer_actual, &desplazamiento_actual);
        int dirFisicaWrite = deserializar_entero_desde_buffer(buffer_actual, &desplazamiento_actual);
        int tamanioWrite = deserializar_entero_desde_buffer(buffer_actual, &desplazamiento_actual);
        log_info(logger, "Recibimos FWRITE de proceso %d para archivo %s en dir %d un tamanio de %d", pcb_actual->PID, archivo, dirFisicaWrite, tamanioWrite);
        escribirArchivoFS(archivo, dirFisicaWrite, tamanioWrite, pcb_actual);
        agregarAReady(pcb_actual, true);
        free(archivo);
        break;
      case FTRUNCATE:
        archivo = deserializar_cadena_desde_buffer(buffer_actual, &desplazamiento_actual);
        int tamanioTruncate = deserializar_entero_desde_buffer(buffer_actual, &desplazamiento_actual);
        log_info(logger, "Recibimos FTRUNCATE de proceso %d para archivo %s un tamanio de %d", pcb_actual->PID, archivo, tamanioTruncate);
        solicitarTruncarArchivo(archivo, tamanioTruncate);
        int truncarArchivo = recibir_operacion(conexionFileSystem);
        char* mensajeFTRUNCATE = recibir_mensaje(conexionFileSystem);
        if (truncarArchivo == OK) {
            log_debug(logger, "Truncate del archivo %s exitoso", archivo);
        } else {
            log_error(logger, "Error en el truncate del archivo %s", archivo);
        }
        free(mensajeFTRUNCATE);
        agregarAReady(pcb_actual, true);
        free(archivo);
        break;
      case WAIT:
        char *recursoWait = deserializar_cadena_desde_buffer(buffer_actual, &desplazamiento_actual);
        log_debug(logger, "Recibimos WAIT de proceso %d para recurso %s", pcb_actual->PID, recursoWait);
        error = waitRecurso(pcb_actual, recursoWait);
        if (error) sem_post(&sem_cpu_not_running); 
        free(recursoWait);
        break;
      case SIGNAL:
        char *recursoSignal = deserializar_cadena_desde_buffer(buffer_actual, &desplazamiento_actual);
        log_debug(logger, "Recibimos SIGNAL de proceso %d para recurso %s", pcb_actual->PID, recursoSignal);
        error = signalRecurso(pcb_actual, recursoSignal);
        if (!error) agregarAReady(pcb_actual, true);
        
        free(recursoSignal);
        break;
      case CREATE_SEGMENT:
        int nroSegmentoCre = deserializar_entero_desde_buffer(buffer_actual, &desplazamiento_actual);
        int tamanioSegmento = deserializar_entero_desde_buffer(buffer_actual, &desplazamiento_actual);
        log_debug(logger, "Recibimos CREATE_SEGMENT de proceso %d para segmento %d de tamanio %d", pcb_actual->PID, nroSegmentoCre, tamanioSegmento);
        error = create_segment(pcb_actual, nroSegmentoCre, tamanioSegmento);
        if(!error) agregarAReady(pcb_actual, true);
        break;
      case DELETE_SEGMENT:
        int nroSegmentoDel = deserializar_entero_desde_buffer(buffer_actual, &desplazamiento_actual);
        log_debug(logger, "Recibimos DELETE_SEGMENT de proceso %d para segmento %d", pcb_actual->PID, nroSegmentoDel);
        error = delete_segment(pcb_actual, nroSegmentoDel);
        if(!error)agregarAReady(pcb_actual, true);
        break;
      case -1:
        log_debug(logger, "la cpu se desconecto.");
        break;
    }
    free(buffer_actual);
    if(instruccionAEjecutar != WAIT && instruccionAEjecutar != IO)
    {
      sem_post(&sem_cpu_not_running);
    }
  }

  PCB* pcb_terminado = pcb_running;
  if(!error && instruccionAEjecutar != ERRORCPU) {
    log_info(logger, "Recibimos EXIT de proceso: %d", pcb_terminado->PID); 
    // enviar_mensaje_con_op("Ejecutado correctamente", conexionConsola, OK);
  }
  else
  {
    char* resultado;
    if(instruccionAEjecutar == ERRORCPU)
    {
      resultado = string_new();
      /*char* proc = itoa(pcb_terminado->PID);
      string_append(&resultado,"EXIT proceso ");
      string_append(&resultado, proc);*/
      string_append(&resultado, "EXIT - Ocurrio un error al traducir DL a DF - Segmentation Fault");
    }
    else
    {
      resultado = malloc(58);
      sprintf(resultado, "%s%d", "EXIT - Ocurrio un error en la instruccion con codigo: ", instruccionAEjecutar);
    }
    log_error(logger, "%s", resultado);
    // enviar_mensaje_con_op(resultado, conexionConsola, OK);
    free(resultado);
  }

  list_remove_element(semaforosProcesos, nuevoItem);
  sem_destroy(nuevoItem->semProceso);
  free(nuevoItem->semProceso);
  free(nuevoItem);
  finalizarProceso(pcb_terminado);
  instruccionAEjecutar = -1;
}

void hiloCpu() 
{
  int cod_op;
  do {
    cod_op = recibir_operacion(conexionCpu);
    log_debug(logger, "El codigo de operacion que recibi es: %d", cod_op);

    switch(cod_op) {
      case INSTRUCCION_CPU:
        instruccionAEjecutar = recibir_operacion(conexionCpu);
        log_debug(logger, "El codigo de solicitud que recibi es: %d", instruccionAEjecutar);

        int size;
        recv(conexionCpu, &size, sizeof(int), 0);
        log_debug(logger, "Recibi el size buffer: %d", size);

        bufferCPU = recibir_datos(conexionCpu, size);
        desplazamientoBufferCPU = 0;
        log_debug(logger, "ANTES DE RECIBIR PCB");
        pcb_running = recibir_pcb(bufferCPU, &desplazamientoBufferCPU);
        temporal_stop(pcb_running->tiempoEjecucion);
        
        PCB* pcb_recibido = pcb_running;

        bool encontre_semaforo(void *item)
        {
          item_semaforo* item_sem = (item_semaforo*)item;
          return item_sem->PID == pcb_recibido->PID;
        }

        pthread_mutex_lock(&mutexSemaforosProcesos);
        log_debug(logger, "Cantidad de semaforos de procesos: %d", list_size(semaforosProcesos));
        item_semaforo *item = list_find(semaforosProcesos, encontre_semaforo);
        pthread_mutex_unlock(&mutexSemaforosProcesos);
        if(item == NULL) log_error(logger, "No se encontro el semaforo que habilita el proceso %d", pcb_recibido->PID);
        sem_post(item->semProceso);
        
        break;
      default:
        log_warning(logger, "Operacion desconocida. No quieras meter la pata: %d", cod_op);
        break;
    }
  } while(cod_op != -1);
}

void dispatcher () 
{
  log_debug(logger, "ANTES DE ENTRAR AL WHILE DEL DISPATCHER");
  while(1) {
    sem_wait(&sem_dispatcher);
    sem_wait(&sem_cpu_not_running);
    log_debug(logger, "ENTRE AL WHILE DEL DISPATCHER");
    if(queue_size(colaReady) > 0)
    {
      PCB* proximoProcesoAEjecutar = NULL;
      switch (algoritmoActual)
      {
        case FIFO:
          proximoProcesoAEjecutar = sacarDeReady();
          break;
        case HRRN:
          proximoProcesoAEjecutar = traerMayorRR();
          break;
      }
      logCambiarEstado(proximoProcesoAEjecutar->PID, proximoProcesoAEjecutar->Estado, EXEC);
      proximoProcesoAEjecutar->Estado = EXEC;
      enviar_pcb_a_cpu(proximoProcesoAEjecutar); 
    }
  }
}

/* ---------------- MANEJO DE CPU ---------------- */

void enviar_pcb_a_cpu(PCB* proximoProcesoAEjecutar) 
{
  temporal_stop(proximoProcesoAEjecutar->aging);
  proximoProcesoAEjecutar->aging->elapsed_ms = 0;
  temporal_resume(proximoProcesoAEjecutar->tiempoEjecucion);

  int desplazamiento = 0;
  void* stream = serializar_pcb(proximoProcesoAEjecutar, &desplazamiento);
  enviar_solicitud(conexionCpu, OP_PCB, desplazamiento, stream, OP_PCB);
}

bool waitRecurso(PCB* pcb, char* nombreRecurso) 
{
  recursos_t* recurso = buscar_recurso_en_array(nombreRecurso);
  if (recurso == NULL) 
  {
    log_error(logger, "PID: %d - Recurso no encontrado: %s", pcb->PID, nombreRecurso);
    
    return true;
  }
  log_info(logger,"PID: %d - Wait: %s - Instancias: %d", pcb->PID, nombreRecurso, recurso->instanciasRecurso);

  bool encontre_semaforo(void *item)
  {
    item_semaforo* item_sem = (item_semaforo*)item;
    return item_sem->PID == pcb->PID;
  }

  if(recurso->instanciasRecurso == 0) 
  { 
    queue_push(recurso->procesosBloqueados, pcb);
    pthread_mutex_lock(&mutexSemaforosProcesos);
    item_semaforo *item = list_find(semaforosProcesos, encontre_semaforo);
    pthread_mutex_unlock(&mutexSemaforosProcesos);
    log_info(logger, "Bloqueo proceso %d por wait de recurso %s", pcb->PID, nombreRecurso);
    pcb->Estado = BLOCK;
    logCambiarEstado(pcb->PID, EXEC, BLOCK);

    sem_post(&sem_dispatcher);
    sem_post(&sem_cpu_not_running);
    sem_wait(item->semProceso);
    if(queue_size(colaReady) == 0) sem_post(&sem_cpu_not_running);
    agregarAReady(pcb, false);
  }
  else
  {
    agregarAReady(pcb, true);
    sem_post(&sem_cpu_not_running);
  }

  int desplazamiento = 0;
  void* stream = malloc(sizeof(int));
  agregar_entero_a_stream(stream, &desplazamiento, pcb->PID);
  list_add(recurso->idsProcesosQueLoTienen, stream);
  recurso->instanciasRecurso--;
  return false;
}

bool signalRecurso(PCB* pcb, char* nombreRecurso)
{
  recursos_t* recurso = buscar_recurso_en_array(nombreRecurso);
  
  if (recurso == NULL) 
  {
    log_error(logger, "PID: %d - Recurso no encontrado: %s\n", pcb->PID, nombreRecurso);
    return true;
  }
  log_info(logger, "PID: %d - Signal: %s - Instancias: %d", pcb->PID, nombreRecurso, recurso->instanciasRecurso);
  
  if(queue_size(recurso->procesosBloqueados) > 0) 
  { 
    PCB* pcbAReady = queue_pop(recurso->procesosBloqueados);
    bool encontre_semaforo(void *item)
    {
      item_semaforo* item_sem = (item_semaforo*)item;
      return item_sem->PID == pcbAReady->PID;
    }
    pthread_mutex_lock(&mutexSemaforosProcesos);
    item_semaforo *item = list_find(semaforosProcesos, encontre_semaforo);
    pthread_mutex_unlock(&mutexSemaforosProcesos);
    log_info(logger, "Desbloqueo proceso %d por signal de recurso %s", pcbAReady->PID, nombreRecurso);
    sem_post(item->semProceso);
  }

  eliminar_proceso_de_recurso(recurso, pcb);

  
  
  recurso->instanciasRecurso++;
  return false;
}

bool create_segment(PCB* pcb, int nroSegmentoCre, int tamanioSegmento)
{
  int desplazamiento = 0;
  void* stream = malloc(sizeof(int) * 3);
  agregar_entero_a_stream(stream, &desplazamiento, pcb->PID);
  agregar_entero_a_stream(stream, &desplazamiento, nroSegmentoCre);
  agregar_entero_a_stream(stream, &desplazamiento, tamanioSegmento);
  enviar_solicitud(conexionMemoria, CREATE_SEGMENTO, desplazamiento, stream, OPERACION_DE_KERNEL);

  int cod_op = recibir_operacion(conexionMemoria);
  log_debug(logger, "El codigo de operacion que recibi es: %d", cod_op);

  if(cod_op == TABLA_SEGMENTO)
  {
    int cod_sol = recibir_operacion(conexionMemoria);
    log_debug(logger, "El codigo de solicitud que recibi es: %d", cod_sol);
    int size;
    recv(conexionMemoria, &size, sizeof(int), 0);
    log_debug(logger, "Recibi el size buffer: %d", size);

    void* buffer = recibir_datos(conexionMemoria, size);
    desplazamiento = 0;
    list_clean_and_destroy_elements(pcb->TablaSegmentos, free);
    deserializar_lista_segmentos(buffer, &desplazamiento, pcb->TablaSegmentos);
    log_info(logger, "Se creo segmento de tamanio %d para el proceso %d y su nueva cantidad de segmentos es %d", tamanioSegmento, pcb->PID, list_size(pcb->TablaSegmentos));
    free(buffer);
  } else if (cod_op == SOLICITUD_COMPACTAR)
  {
    char* mensaje = recibir_mensaje(conexionMemoria);
    log_debug(logger, "Recibi mensaje de memoria: %s", mensaje);
    free(mensaje);
    enviar_mensaje_con_op("Solicitud compactacion", conexionFileSystem, HANDSHAKE);
    recibir_operacion(conexionFileSystem);
    mensaje = recibir_mensaje(conexionFileSystem);
    log_info(logger, "Se solicito permiso compactacion a FS");
    free(mensaje);

    enviar_mensaje_con_opysol("Solicitud de compactacion del kernel", conexionMemoria, OPERACION_DE_KERNEL, SOLICITUD_COMPACTACION);
    recibir_segmentos_y_actualizar_procesos();
    log_info(logger, "Se finalizo el proceso de compactacion");
    create_segment(pcb, nroSegmentoCre, tamanioSegmento);
  } else if (cod_op == ERROR)
  {
    char* mensaje = recibir_mensaje(conexionMemoria);
    log_error(logger, "Recibi error de memoria: %s", mensaje);
    free(mensaje);
    return true;
  }
  return false;
}

bool delete_segment(PCB* pcb, int nroSegmentoDel)
{
  int desplazamiento = 0;
  void* stream = malloc(sizeof(int) * 2);
  agregar_entero_a_stream(stream, &desplazamiento, pcb->PID);
  agregar_entero_a_stream(stream, &desplazamiento, nroSegmentoDel);
  enviar_solicitud(conexionMemoria, DELETE_SEGMENTO, desplazamiento, stream, OPERACION_DE_KERNEL);
  
  int cod_op = recibir_operacion(conexionMemoria);
  log_debug(logger, "El codigo de operacion que recibi es: %d", cod_op);
  int cod_sol = recibir_operacion(conexionMemoria);
  log_debug(logger, "El codigo de solicitud que recibi es: %d", cod_sol);
  int size = recibir_operacion(conexionMemoria);
  log_debug(logger, "Recibi el size buffer: %d", size);

  void* buffer = recibir_datos(conexionMemoria, size);
  desplazamiento = 0;
  list_clean_and_destroy_elements(pcb->TablaSegmentos, free);
  deserializar_lista_segmentos(buffer, &desplazamiento, pcb->TablaSegmentos);
  log_info(logger, "Se elimino segmento para el proceso %d y su nueva cantidad de segmentos es %d", pcb->PID, list_size(pcb->TablaSegmentos));
  free(buffer);
  return false;
}

/* ---------------- MANEJO DE ESTADOS DE PROCESO ---------------- */

void agregarANew(PCB* pcb) 
{
	pthread_mutex_lock(&mutexNew);
	queue_push(colaNew, pcb);
	log_debug(logger,"Entra a new el proceso %d y el tamanio de cola es %d", pcb->PID, queue_size(colaNew));
	pthread_mutex_unlock(&mutexNew);
  sem_post(&sem_colaNew);
}

PCB* sacarDeNew() 
{
  pthread_mutex_lock(&mutexSacarNew);
	PCB* pcb = queue_pop(colaNew);
	log_debug(logger,"[NEW] Se saca de new el proceso %d y la cantidad en cola es %d", pcb->PID, queue_size(colaNew));
  pthread_mutex_unlock(&mutexSacarNew);
	return pcb;
}

PCB* sacarDeReady()
{
  pthread_mutex_lock(&mutexColaReady);
	PCB* pcb = queue_pop(colaReady);
	log_debug(logger,"[NEW] Se saca de ready el proceso %d y la cantidad en cola es %d", pcb->PID, queue_size(colaReady));
  pthread_mutex_unlock(&mutexColaReady);
	return pcb;
}

void agregarAReady(PCB* pcb, bool activarDispatcher)
{
  pcb->Estado = READY; 
  pthread_mutex_lock(&mutexColaReady);
  int size = queue_size(colaReady);
  queue_push(colaReady, pcb);
  pthread_mutex_unlock(&mutexColaReady);
	log_info(logger,"Entra a la cola ready el proceso %d y la cantidad en cola es %d", pcb->PID, size + 1);
  temporal_resume(pcb->aging);
  if (activarDispatcher || size == 0) sem_post(&sem_dispatcher);
}

void newAReady()
{
  while(1)
  {
    log_debug(logger, "EL SEMAFORO MULTIPROG CONTIENE: %ld", sem_gradoMultiprog.__align);
    sem_wait(&sem_colaNew);
    sem_wait(&sem_gradoMultiprog);
    PCB* pcb = sacarDeNew();
    inicializar_proceso_en_memoria(pcb);
    list_add(procesosActivos, pcb);
    agregarAReady(pcb, true);
  }
}

void finalizarProceso(PCB* pcb)
{
  //liberar memoria LISTO
  finalizar_proceso_en_memoria(pcb->PID);
  list_remove_element(procesosActivos, pcb);
  //liberar recursos
  liberar_recursos_pcb(pcb);
  //liberar archivos
  liberar_archivos_pcb(pcb);
  //liberar pcb
  liberar_pcb(pcb);
  sem_post(&sem_gradoMultiprog);
  sem_post(&sem_dispatcher);
  sem_post(&sem_cpu_not_running);
}

/* ---------------- FUNCIONES DE PLANIFICADORES ---------------- */

PCB* traerMayorRR() 
{
  PCB* pcb = NULL;
  for (int i = 0; i < queue_size(colaReady); i++)
  {
    pcb = queue_pop(colaReady);
    estimador_HRRN(pcb);
    log_debug(logger, "El tiempo en ready es: %ld para el pcb %d", temporal_gettime(pcb->aging), pcb->PID);

    queue_push(colaReady, pcb);
  }
  pcb = NULL;
	
  PCB* pcbARetirar = NULL;
  t_queue* nuevaColaReady = queue_create();

  pthread_mutex_lock(&mutexColaReady);
  
  pcbARetirar = queue_pop(colaReady);
  //estimador_HRRN(pcbARetirar);

  while(queue_size(colaReady) > 0)
  {
    pcb = queue_pop(colaReady);
    //estimador_HRRN(pcb);

    log_debug(logger, "COMPARACION PCB PID %d RATIO %f", pcb->PID, pcb->tiempo.ratioResponse);
    log_debug(logger, "COMPARACION COMPARADO PID %d RATIO %f", pcbARetirar->PID, pcbARetirar->tiempo.ratioResponse);
    
    if (pcb->tiempo.ratioResponse > pcbARetirar->tiempo.ratioResponse) 
    {
      queue_push(nuevaColaReady, pcbARetirar);
      pcbARetirar = pcb;
    } else
    {
      queue_push(nuevaColaReady, pcb);
    }
  }
  
  queue_destroy(colaReady);
  colaReady = nuevaColaReady;

  pthread_mutex_unlock(&mutexColaReady);
 
	return pcbARetirar;
}

void estimador(PCB *pcb)
{
  log_debug(logger,"el viejo tiempo de estimacion es:  %f", pcb->tiempo.estimacion);
  double aux = (pcb->tiempo.estimacion * atof(hrrnAlfa));
  pcb->tiempo.estimacion = aux + temporal_gettime(pcb->tiempoEjecucion) * (1 - atof(hrrnAlfa));
  log_debug(logger, "La ult rafaga cpu es: %ld para el pcb %d", temporal_gettime(pcb->tiempoEjecucion), pcb->PID);
  pcb->tiempoEjecucion->elapsed_ms = 0;
  log_debug(logger,"el nuevo tiempo de estimacion es:  %f", pcb->tiempo.estimacion);
}

void estimador_HRRN(PCB *pcb)
{    
  if (pcb->tiempo.estimacion != 0.000000)
  {
    pcb->tiempo.ratioResponse = (temporal_gettime(pcb->aging) + pcb->tiempo.estimacion) / pcb->tiempo.estimacion;
    log_debug(logger,"la nueva tasa de respuesta del proceso %d es %f", pcb->PID, pcb->tiempo.ratioResponse);
  }
}

/* ---------------- FUNCIONES PARA MEMORIA ---------------- */

void inicializar_proceso_en_memoria(PCB* pcb)
{
  int desplazamiento = 0;
  void* stream = malloc(sizeof(int));
  agregar_entero_a_stream(stream, &desplazamiento, pcb->PID);
  enviar_solicitud(conexionMemoria, INICIAR_PROCESO, desplazamiento, stream, OPERACION_DE_KERNEL);
  int cod_op = recibir_operacion(conexionMemoria);
  log_debug(logger, "El codigo de operacion que recibi es: %d", cod_op);
  int cod_sol = recibir_operacion(conexionMemoria);
  log_debug(logger, "El codigo de solicitud que recibi es: %d", cod_sol);
  int size;
  recv(conexionMemoria, &size, sizeof(int), 0);
  log_debug(logger, "Recibi el size buffer: %d", size);

  void* buffer = recibir_datos(conexionMemoria, size);
  desplazamiento = 0;
  deserializar_lista_segmentos(buffer, &desplazamiento, pcb->TablaSegmentos);
  log_debug(logger, "se recibio la tabla de segmentos iniciada por memoria con %d elementos", list_size(pcb->TablaSegmentos));
  free(buffer);
}

void finalizar_proceso_en_memoria(int PID)
{
  int desplazamiento = 0;
  void* stream = malloc(sizeof(int));
  agregar_entero_a_stream(stream, &desplazamiento, PID);
  enviar_solicitud(conexionMemoria, FINALIZAR_PROCESO, desplazamiento, stream, OPERACION_DE_KERNEL);
}

void recibir_segmentos_y_actualizar_procesos()
{
  int cod_op = recibir_operacion(conexionMemoria);
  log_debug(logger, "El codigo de operacion que recibi es: %d", cod_op);
  int cod_sol = recibir_operacion(conexionMemoria);
  log_debug(logger, "El codigo de solicitud que recibi es: %d", cod_sol);
  int size = recibir_operacion(conexionMemoria);
  log_debug(logger, "Recibi el size buffer: %d", size);

  void* buffer = recibir_datos(conexionMemoria, size);
  int desplazamiento = 0;
  int cantidadTablas = deserializar_entero_desde_buffer(buffer, &desplazamiento);

  for (int i = 0; i < cantidadTablas; i++)
  {
    int PID = deserializar_entero_desde_buffer(buffer, &desplazamiento);
    PCB* proceso = buscarProcesoActivo(PID);
    list_clean_and_destroy_elements(proceso->TablaSegmentos, free);
    deserializar_lista_segmentos(buffer, &desplazamiento, proceso->TablaSegmentos);
    log_debug(logger, "ACTUALIZANDO TABLA SEGMENTO DE PROCESO %d", PID);
    log_tabla_segmentos(proceso, logger);
  }
  
  log_debug(logger, "Se actualizaron las tablas de segmentos de los procesos activos por compactacion");
  free(buffer);
}

PCB* buscarProcesoActivo(int PID)
{
  bool encontre_proceso(void *item) 
  {
    PCB* pcb = (PCB*)item;
    return pcb->PID == PID;
  }
  if(pcb_running->PID == PID) return pcb_running;

  PCB* proceso = list_find(colaReady->elements, encontre_proceso);
  if(proceso != NULL) return proceso;
  
  for(int i = 0; i < list_size(recursos); i++) {
    recursos_t* recurso = list_get(recursos, i);
    proceso = list_find(recurso->procesosBloqueados->elements, encontre_proceso);
    if(proceso != NULL) return proceso;
  }

  for(int i = 0; i < list_size(tabla_archivos_globales); i++) {
    entrada_archivo_global* entrada = list_get(tabla_archivos_globales, i);
    proceso = list_find(entrada->colaBloqueados->elements, encontre_proceso);
    if(proceso != NULL) return proceso;
  }

  log_error(logger, "No se encontro el proceso %d activo para actualizar", PID);
  return NULL;
}

/* ---------------- UTILIDADES ---------------- */

PCB* armar_pcb(t_list* lista) 
{
  PCB* pcb = inicializar_pcb();
  int tamLista = sizeLista(lista);

  pcb = realloc(pcb, pcb->Size + tamLista);
  pcb->Size += tamLista;
  pcb->PID = procesosId;

  void s_list_add(char* elem) {
    list_add(pcb->Instrucciones, elem);
  }
  list_iterate(lista, (void*) s_list_add);
  list_destroy(lista);

  pcb->tiempo.estimacion = atoi(estimacionInicial);
  procesosId++;

  return pcb;
}

int sizeLista(t_list *list) 
{
    int size = 0;

    t_link_element *current = list->head;
    while (current != NULL) 
    {
        size += sizeof(*current);
        size += strlen((char*)current->data) + 1;
        current = current->next;
    }

    return size;
}

recursos_t* buscar_recurso_en_array(char* nombreRecurso)
{
  bool equals(void *recurso) {
    recursos_t* rec = (recursos_t*)recurso;
    return strcmp(rec->nombreRecurso, nombreRecurso) == 0;
  }

  return list_find(recursos, equals);
}

const char* estadoToString(Estado estado)
{
    switch (estado) {
        case NEW:
            return "NEW";
        case READY:
            return "READY";
        case EXEC:
            return "EXEC";
        case BLOCK:
            return "BLOCK";
        case EXIT:
            return "EXIT";
        default:
            return "Estado Desconocido";
    }
}

const char* algoritmoToString(Algoritmo algoritmo)
{
    switch (algoritmo) {
        case HRRN:
            return "HRRN";
        case FIFO:
            return "FIFO";
        default:
            return "Algoritmo Desconocido";
    }
}

void inicializarLogger()
{
  logger = iniciar_logger();
  logger = log_create("./cfg/md_kernel.log", "md_kernel", true, LOG_LEVEL_DEBUG);
}

void inicializarRecursos()
{
  int i = 0;
  recursos = list_create();
  while(nombresRecurso[i] != NULL) {
    recursos_t* nuevoRecurso = malloc(sizeof(recursos_t));

    nuevoRecurso->nombreRecurso = nombresRecurso[i];
    nuevoRecurso->instanciasRecurso = atoi(instanciaRecurso[i]);
    nuevoRecurso->procesosBloqueados = queue_create();
    nuevoRecurso->idsProcesosQueLoTienen = list_create();
    list_add(recursos, nuevoRecurso);
    i++;
  } 
}

void inicializarColas()
{
  colaNew = queue_create();
  colaReady = queue_create();
}

void queue_push_in_index(t_queue* queue, int index, void* element)
{
    if (index < 0 || index > queue_size(queue)) {
        log_error(logger, "Índice fuera de rango");
        return;
    }

    t_queue* tempQueue = queue_create();
    int count = 0;
    
    while (!queue_is_empty(queue)) {
        if (count == index) {
            queue_push(tempQueue, element);
        }
        
        queue_push(tempQueue, queue_pop(queue));
        count++;
    }
    
    while (!queue_is_empty(tempQueue)) {
      queue_push(queue, queue_pop(tempQueue));
    }
    
    queue_destroy(tempQueue);
}

void liberar_colas()
{
  while (!queue_is_empty(colaNew)) {
      PCB* pcb = queue_pop(colaNew);
      liberar_pcb(pcb);
  }
  queue_destroy(colaNew);
  while (!queue_is_empty(colaReady)) {
      PCB* pcb = queue_pop(colaReady);
      liberar_pcb(pcb);
  }
  queue_destroy(colaReady);
}

void logCambiarEstado(int pid, Estado estadoAnterior, Estado estadoActual)
{
  log_info(logger,"PID: %d - Estado Anterior: %s - Estado Actual: %s ", pid, estadoToString(estadoAnterior), estadoToString(estadoActual));
}

void liberar_recurso(recursos_t* recurso)
{
  //free(nombreRecurso);
  list_destroy_and_destroy_elements(recurso->idsProcesosQueLoTienen, free);
  queue_destroy(recurso->procesosBloqueados);
  free(recurso);
}


/*  ------------------------ TABLA DE ARCHIVOS GENERALES ---------------------- */

void abrirArchivoFS(char *archivo, PCB* pcb_actual) {
  bool setReady = false;
  mostrarNombresArchivos();
  archivo_local_proceso* archivoDelproceso = buscarArchivoLocalProceso(archivo, pcb_actual->TablaArchivosAbiertos);
  if (archivoDelproceso == NULL) {
    log_debug(logger, "[FOPEN] El archivo: %s ,no estaba abierto en el proceso: %d", archivo, pcb_actual->PID);
    archivoDelproceso = malloc(sizeof(archivo_local_proceso));
    archivoDelproceso->nombre = strdup(archivo);
    archivoDelproceso->puntero = 0; // FIJARSE ESTE DATO
    archivoDelproceso->modoApertura = "-"; // FIJARSE ESTE DATO-> READ/WRITE/...
    list_add(pcb_actual->TablaArchivosAbiertos, archivoDelproceso);
  }
  entrada_archivo_global* archivoGlobal = buscarArchivoGlobal(archivo);
  if (archivoGlobal == NULL) {
    // PREGUNTAR AL FS
    enviar_mensaje_con_op(archivo, conexionFileSystem, F_OPEN);
    int abrirArchivo = recibir_operacion(conexionFileSystem);
    char* mensajeAbrir = recibir_mensaje(conexionFileSystem);
    if(abrirArchivo != OK)
    {
      log_debug(logger, "No encontro el archivo, Hay que crearlo");
      enviar_mensaje_con_op(archivo, conexionFileSystem, F_CREATE);
      int crearArchivo = recibir_operacion(conexionFileSystem);
      free(mensajeAbrir);
      mensajeAbrir = recibir_mensaje(conexionFileSystem);
      if(crearArchivo != OK)
      {
        log_debug(logger, "No pudo crear el archivo: %s", archivo);
      } else {
        log_debug(logger, "Pude Crear el archivo %s del proceso %d", archivo, pcb_actual->PID);
      }
    }
    agregarArchivoGlobal(archivo);
    archivoGlobal = buscarArchivoGlobal(archivo);
    free(mensajeAbrir);
    setReady=true;
    // agregarAReady(pcb_actual, true);
  } else {
    bool encontre_semaforo(void *item)
    {
      item_semaforo* item_sem = (item_semaforo*)item;
      return item_sem->PID == pcb_actual->PID;
    }
    queue_push(archivoGlobal->colaBloqueados, pcb_actual);
    pthread_mutex_lock(&mutexSemaforosProcesos);
    item_semaforo *item = list_find(semaforosProcesos, encontre_semaforo);
    pthread_mutex_unlock(&mutexSemaforosProcesos);
    log_info(logger, "Bloqueo proceso %d por open de archivo %s", pcb_actual->PID, archivo);
    pcb_actual->Estado = BLOCK;
    logCambiarEstado(pcb_actual->PID, EXEC, BLOCK);

    sem_post(&sem_dispatcher);
    sem_post(&sem_cpu_not_running);
    sem_wait(item->semProceso); // BLOQUEA ESTE PROCESO
  }
  // aumentarAperturasArchivo(archivoGlobal);
  agregarAReady(pcb_actual, setReady);
  // enviar_pcb_a_cpu(pcb_actual);
}

void inicializarTablaArchivosGlobales() {
    tabla_archivos_globales = list_create();
}

entrada_archivo_global* buscarArchivoGlobal(char* nombreArchivo) {
    bool equals(void* entrada) {
        entrada_archivo_global* archivo = (entrada_archivo_global*)entrada;
        return strcmp(archivo->nombre, nombreArchivo) == 0;
    }

    return list_find(tabla_archivos_globales, equals);
}

archivo_local_proceso* buscarArchivoLocalProceso(char* nombreArchivo, t_list* listaLocal) {
    bool equals(void* entrada) {
        archivo_local_proceso* archivo = (archivo_local_proceso*)entrada;
        return strcmp(archivo->nombre, nombreArchivo) == 0;
    }

    return list_find(listaLocal, equals);
}

void agregarArchivoGlobal(char* nombreArchivo) {
    entrada_archivo_global* archivo = malloc(sizeof(entrada_archivo_global));
    archivo->nombre = strdup(nombreArchivo);
    //archivo->cantidadAperturas = 0;
    archivo->colaBloqueados = queue_create();
    sem_init(&(archivo->lockArchivo), 0, 1); // Lo inicializo desbloqueado
    list_add(tabla_archivos_globales, archivo);
}

void aumentarAperturasArchivo(entrada_archivo_global* archivo) {
    sem_wait(&(archivo->lockArchivo));
    //archivo->cantidadAperturas++;
    sem_post(&(archivo->lockArchivo));
}

void disminuirAperturasArchivo(entrada_archivo_global* archivo) {
    sem_wait(&(archivo->lockArchivo));
    //archivo->cantidadAperturas--;
    sem_post(&(archivo->lockArchivo));
}

void liberarTablaArchivosGlobales() {
    void liberarEntradaGlobal(void* entrada) {
        entrada_archivo_global* archivo = (entrada_archivo_global*) entrada;
        sem_destroy(&(archivo->lockArchivo));
        free(archivo->nombre);
        free(archivo);
    }
    list_destroy_and_destroy_elements(tabla_archivos_globales, liberarEntradaGlobal);
}

void solicitarTruncarArchivo(char* archivoNombre, int tamanioArchivo) 
{
  int desplazamiento = 0;
  void* stream = malloc(sizeof(int) *2 + strlen(archivoNombre) + 1);
  agregar_entero_a_stream(stream, &desplazamiento, tamanioArchivo);  
  agregar_cadena_a_stream(stream, &desplazamiento, archivoNombre);
  enviar_solicitud(conexionFileSystem, F_TRUNCATE, desplazamiento, stream, F_TRUNCATE);
  log_debug(logger, "Pude enviar ARCHIVO para truncar");
}

void solicitarLeerArchivo(char* archivoNombre, int tamanioArchivo, int dirFisicaRead, int puntero, int pid) {
  int desplazamiento = 0;
  void* stream = malloc( sizeof(int)*5 + strlen(archivoNombre) + 1);
  agregar_entero_a_stream(stream, &desplazamiento, tamanioArchivo);  
  agregar_entero_a_stream(stream, &desplazamiento, dirFisicaRead);  
  agregar_cadena_a_stream(stream, &desplazamiento, archivoNombre);
  agregar_entero_a_stream(stream, &desplazamiento, puntero);
  agregar_entero_a_stream(stream, &desplazamiento, pid);
  enviar_solicitud(conexionFileSystem, F_READ, desplazamiento, stream, F_READ);
  log_debug(logger, "Pude enviar ARCHIVO para leer");
}

void solicitarEscribirArchivo(char* archivoNombre, int tamanioArchivo, int dirFisicaRead,  int puntero, int pid) {
  int desplazamiento = 0;
  void* stream = malloc(sizeof(int) * 5 + strlen(archivoNombre) + 1);
  agregar_entero_a_stream(stream, &desplazamiento, tamanioArchivo);  
  agregar_entero_a_stream(stream, &desplazamiento, dirFisicaRead);  
  agregar_cadena_a_stream(stream, &desplazamiento, archivoNombre);
  agregar_entero_a_stream(stream, &desplazamiento, puntero);
  agregar_entero_a_stream(stream, &desplazamiento, pid);
  enviar_solicitud(conexionFileSystem, F_WRITE, desplazamiento, stream, F_WRITE);
  log_debug(logger, "Pude enviar ARCHIVO para escribir");
}

void mostrarNombresArchivos() {
    void imprimirNombre(void* entrada) {
      entrada_archivo_global* archivo = (entrada_archivo_global*)entrada;
      log_debug(logger, "Nombre del archivo: %s", archivo->nombre);
    }

    list_iterate(tabla_archivos_globales, (void*)imprimirNombre);
}

void cerrarArchivoFS(char *archivo, PCB *pcb_actual) {
  entrada_archivo_global* archivoGlobal = buscarArchivoGlobal(archivo);
  if(archivoGlobal != NULL) {
    // disminuirAperturasArchivo(archivoGlobal);
    if (queue_size(archivoGlobal->colaBloqueados) == 0) {
      list_remove_element(tabla_archivos_globales, archivoGlobal);
      sem_destroy(&(archivoGlobal->lockArchivo));
      queue_destroy(archivoGlobal->colaBloqueados);
      free(archivoGlobal->nombre);
      free(archivoGlobal);
    } else {
      PCB* pcbAReady = queue_pop(archivoGlobal->colaBloqueados);
      bool encontre_semaforo(void *item)
      {
        item_semaforo* item_sem = (item_semaforo*)item;
        return item_sem->PID == pcbAReady->PID;
      }
      pthread_mutex_lock(&mutexSemaforosProcesos);
      item_semaforo *item = list_find(semaforosProcesos, encontre_semaforo);
      pthread_mutex_unlock(&mutexSemaforosProcesos);
      log_info(logger, "Desbloqueo proceso %d por FCLOSE de archivo %s", pcbAReady->PID, archivo);
      sem_post(item->semProceso);
    }
  }
  archivo_local_proceso* archivoDelproceso = buscarArchivoLocalProceso(archivo, pcb_actual->TablaArchivosAbiertos);
  if(archivoDelproceso != NULL) {
    log_debug(logger, "El archivo: %s sera borrado del proceso: %d", archivo, pcb_actual->PID);
    list_remove_element(pcb_actual->TablaArchivosAbiertos, archivoDelproceso);
    free(archivoDelproceso);
  } else {
    log_warning(logger, "El archivo: %s no está abierto por el proceso: %d", archivo, pcb_actual->PID);
  }
}

void seekArchivoFS(char* archivo, int posicion,PCB* pcb_actual) {
  archivo_local_proceso* archivoDelproceso = buscarArchivoLocalProceso(archivo, pcb_actual->TablaArchivosAbiertos);
  if (archivoDelproceso != NULL) {
    archivoDelproceso->puntero = posicion;
    log_debug(logger, "Se actualizó el puntero del archivo: %s a la posición: %d", archivo, posicion);
  } else {
    log_warning(logger, "El archivo: %s no está abierto por el proceso actual", archivo);
  }
}

void leerArchivoFS(char* archivo,int dirFisicaRead,int tamanioRead, PCB* pcb_actual) {
  archivo_local_proceso* archivoLocal = buscarArchivoLocalProceso(archivo, pcb_actual->TablaArchivosAbiertos);
  if (archivoLocal != NULL) {
    solicitarLeerArchivo(archivo, tamanioRead, dirFisicaRead, archivoLocal->puntero, pcb_actual->PID);
    int LeerArchivo = recibir_operacion(conexionFileSystem);
    char* mensajeLeer = recibir_mensaje(conexionFileSystem);
    if (LeerArchivo == OK) {
      log_debug(logger, "Leer del archivo %s exitoso", archivo);
    } else {
      log_error(logger, "Error en el Leer del archivo %s", archivo);
    }
    free(mensajeLeer);
  } else {
    log_warning(logger, "El archivo: %s no está abierto por el proceso actual", archivo);
  }
}
void escribirArchivoFS(char* archivo,int dirFisicaWrite,int tamanioWrite, PCB* pcb_actual) {
  archivo_local_proceso* archivoLocal = buscarArchivoLocalProceso(archivo, pcb_actual->TablaArchivosAbiertos);
  solicitarEscribirArchivo(archivo, tamanioWrite, dirFisicaWrite, archivoLocal->puntero, pcb_actual->PID);
  int escribirArchivo = recibir_operacion(conexionFileSystem);
  char* mensajeEscribir = recibir_mensaje(conexionFileSystem);
  if (escribirArchivo == OK) {
    log_debug(logger, "Escribir del archivo %s exitoso", archivo);
  } else {
    log_error(logger, "Error en el escribir del archivo %s", archivo);
  }
  free(mensajeEscribir);
}

void liberar_archivos_pcb(PCB* pcb) {
  for(int i = 0; i < list_size(pcb->TablaArchivosAbiertos); i++)
  {
    archivo_local_proceso* archivoDelproceso  = list_get(pcb->TablaArchivosAbiertos,i);
    cerrarArchivoFS(archivoDelproceso->nombre, pcb);
  }
}

void eliminar_proceso_de_recurso(recursos_t* recurso, PCB* pcb)
{
  for (int i = 0; i < list_size(recurso->idsProcesosQueLoTienen); i++) {
    void* stream = list_get(recurso->idsProcesosQueLoTienen, i);
    int desp = 0;
    int id = deserializar_entero_desde_buffer(stream, &desp);
    if (id == pcb->PID){
      list_remove(recurso->idsProcesosQueLoTienen, i);
      free(stream);
    }
    
  }
}

void liberar_recursos_pcb(PCB* pcb) {
  for(int i = 0; i < list_size(recursos); i++) {
    recursos_t* recurso = list_get(recursos, i);
    eliminar_proceso_de_recurso(recurso, pcb);
  }
}
