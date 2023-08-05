#include "shared_utils.h"

/* ---------------- FUNCIONES DE CLIENTE ---------------- */

int crear_conexion(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);
	int socket_cliente = socket(server_info->ai_family,
	                    server_info->ai_socktype,
	                    server_info->ai_protocol);

	if(connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1) {
		printf("No pude conectarme al servidor\n");
	}

	freeaddrinfo(server_info);

	return socket_cliente;
}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}

/* ---------------- FUNCIONES DE SERVIDOR ---------------- */

int iniciar_servidor(char* IP, char* PUERTO)
{
	int socket_servidor;

	struct addrinfo hints, *servinfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(IP, PUERTO, &hints, &servinfo);

	socket_servidor = socket(servinfo->ai_family,
						servinfo->ai_socktype,
						servinfo->ai_protocol);

	bind(socket_servidor, servinfo->ai_addr, servinfo->ai_addrlen);

	listen(socket_servidor, SOMAXCONN);

	freeaddrinfo(servinfo);
	// log_trace(logger, "Listo para escuchar a mi cliente");
	return socket_servidor;
}

int esperar_cliente(int socket_servidor)
{
	printf("Esperando un cliente\n");
	int socket_cliente = accept(socket_servidor, NULL, NULL);
	printf("Se conecto un cliente!\n");
	return socket_cliente;
}

/* ---------------- FUNCIONES DE PAQUETE ---------------- */

void crear_buffer(t_paquete* paquete)
{
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = 0;
	paquete->buffer->stream = NULL;
}

void* recibir_buffer(int* size, int socket_cliente)
{
	void * buffer;

	recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv(socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}

t_list* recibir_paquete(int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);
	while(desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento+=sizeof(int);
		char* valor = malloc(tamanio);
		memcpy(valor, buffer + desplazamiento, tamanio);
		desplazamiento+=tamanio;
		list_add(valores, valor);
	}
	free(buffer);
	return valores;
}

/*t_list* recibir_solicitud_cpu_a_kernel(int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);

	memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
	desplazamiento+=sizeof(int);
	char* valor = malloc(tamanio);

	memcpy(valor, buffer + desplazamiento, tamanio);
	desplazamiento+=tamanio;
	list_add(valores, valor);

	free(buffer);
	return valores;
}*/

char* recibir_mensaje(int socket_cliente)
{
	int size;
	char* buffer = recibir_buffer(&size, socket_cliente);
	return buffer;
}

int recibir_operacion(int socket_cliente)
{
	int cod_op;
	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) > 0)
		return cod_op;
	else
	{
		close(socket_cliente);
		return -1;
	}
}

void enviar_mensaje(char* mensaje, int socket_cliente)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->codigo_operacion = MENSAJE;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = strlen(mensaje) + 1;
	paquete->buffer->stream = malloc(paquete->buffer->size);
	memcpy(paquete->buffer->stream, mensaje, paquete->buffer->size);

	int bytes = paquete->buffer->size + 2*sizeof(int);

	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);
	free(a_enviar);
	eliminar_paquete(paquete);
}

void enviar_mensaje_con_op(char* mensaje, int socket_cliente, int op)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->codigo_operacion = op;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = strlen(mensaje) + 1;
	paquete->buffer->stream = malloc(paquete->buffer->size);
	memcpy(paquete->buffer->stream, mensaje, paquete->buffer->size);

	int bytes = paquete->buffer->size + 2*sizeof(int);

	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);
	free(a_enviar);
	eliminar_paquete(paquete);
}

void enviar_mensaje_con_opysol(char* mensaje, int socket_cliente, int op, int sol)
{
	Solicitud* paquete = malloc(sizeof(Solicitud));

	paquete->codigo_operacion = op;
	paquete->codigo_solicitud = sol;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = strlen(mensaje) + 1;
	paquete->buffer->stream = malloc(paquete->buffer->size);
	memcpy(paquete->buffer->stream, mensaje, paquete->buffer->size);

	int bytes = paquete->buffer->size + 3*sizeof(int);

	void * magic = malloc(bytes);
	int desplazamiento = 0;

	memcpy(magic + desplazamiento, &(paquete->codigo_operacion), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, &(paquete->codigo_solicitud), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, &(paquete->buffer->size), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, paquete->buffer->stream, paquete->buffer->size);
	desplazamiento+= paquete->buffer->size;

	send(socket_cliente, magic, bytes, 0);
	free(magic);
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}

t_paquete* crear_paquete(int codigo_operacion)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));
	paquete->codigo_operacion = codigo_operacion;
	crear_buffer(paquete);
	return paquete;
}

void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio)
{
	paquete->buffer->stream = realloc(paquete->buffer->stream, paquete->buffer->size + tamanio + sizeof(int));

	memcpy(paquete->buffer->stream + paquete->buffer->size, &tamanio, sizeof(int));
	memcpy(paquete->buffer->stream + paquete->buffer->size + sizeof(int), valor, tamanio);

	paquete->buffer->size += tamanio + sizeof(int);
}

void enviar_paquete(t_paquete* paquete, int socket_cliente)
{
	int bytes = paquete->buffer->size + 2*sizeof(int);
	void* a_enviar = serializar_paquete(paquete, bytes);
	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
}

void eliminar_paquete(t_paquete* paquete)
{
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}

/* ---------------- FUNCIONES DE PROGRAMA ---------------- */

void s_list_iterate(t_list* lista) {
	for(int i = 0; i < list_size(lista); i++) {
		printf("Me llego el valor %s\n", (char*) list_get(lista, i));
	}
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = NULL;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = NULL;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	while (1) {
		 leido = readline(">");

	        if (!strcmp(leido, "")) {
	            break;
	        }
	        printf("Lei la linea: %s\n", leido);
	        free(leido);
	} ;
}

void terminar_programa(int conexion, t_log* logger, t_config* config, char* current_dir)
{
	if(logger != NULL ){
		log_destroy(logger);
	}
	if(config != NULL ){
		config_destroy(config);
	}
	if(conexion != -1)
	{
		liberar_conexion(conexion);
	}

	free(current_dir);
}


/* ---------------- FUNCIONES DE SERIALIZACION ---------------- */

void* serializar_paquete(t_paquete* paquete, int bytes)
{
	void * magic = malloc(bytes);
	int desplazamiento = 0;

	memcpy(magic + desplazamiento, &(paquete->codigo_operacion), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, &(paquete->buffer->size), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, paquete->buffer->stream, paquete->buffer->size);
	desplazamiento+= paquete->buffer->size;

	return magic;
}

void* serializar_pcb(PCB* pcb, int* desplazamiento) 
{
	int bytes = pcb->Size;

    void* stream = malloc(bytes);


	agregar_entero_a_stream(stream, desplazamiento, pcb->Size);
	agregar_entero_a_stream(stream, desplazamiento, pcb->PID);

    int cantidad_instrucciones = list_size(pcb->Instrucciones);
	agregar_entero_a_stream(stream, desplazamiento, cantidad_instrucciones);

    int i;
    for (i = 0; i < cantidad_instrucciones; i++) {
        char* instruccion = list_get(pcb->Instrucciones, i);
		agregar_cadena_a_stream(stream, desplazamiento, instruccion);
    }

	agregar_entero_a_stream(stream, desplazamiento, pcb->PC);

	//Registros
	agregar_registro_a_stream(stream, desplazamiento, pcb->RegistrosCPU->AX, 4);
	agregar_registro_a_stream(stream, desplazamiento, pcb->RegistrosCPU->BX, 4);
	agregar_registro_a_stream(stream, desplazamiento, pcb->RegistrosCPU->CX, 4);
	agregar_registro_a_stream(stream, desplazamiento, pcb->RegistrosCPU->DX, 4);
	agregar_registro_a_stream(stream, desplazamiento, pcb->RegistrosCPU->EAX, 8);
	agregar_registro_a_stream(stream, desplazamiento, pcb->RegistrosCPU->EBX, 8);
	agregar_registro_a_stream(stream, desplazamiento, pcb->RegistrosCPU->ECX, 8);
	agregar_registro_a_stream(stream, desplazamiento, pcb->RegistrosCPU->EDX, 8);
	agregar_registro_a_stream(stream, desplazamiento, pcb->RegistrosCPU->RAX, 16);
	agregar_registro_a_stream(stream, desplazamiento, pcb->RegistrosCPU->RBX, 16);
	agregar_registro_a_stream(stream, desplazamiento, pcb->RegistrosCPU->RCX, 16);
	agregar_registro_a_stream(stream, desplazamiento, pcb->RegistrosCPU->RDX, 16);

	memcpy(stream + *desplazamiento, &(pcb->tiempo.estimacion), sizeof(double));
    *desplazamiento += sizeof(double);
	memcpy(stream + *desplazamiento, &(pcb->tiempo.ratioResponse), sizeof(double));
    *desplazamiento += sizeof(double);

	agregar_tabla_segmentos_a_stream(stream, desplazamiento, pcb->TablaSegmentos);

	memcpy(stream + *desplazamiento, &(pcb->aging->current), sizeof(struct timespec));
    *desplazamiento += sizeof(struct timespec);
	memcpy(stream + *desplazamiento, &(pcb->aging->elapsed_ms), sizeof(int64_t));
    *desplazamiento += sizeof(int64_t);
	agregar_entero_a_stream(stream, desplazamiento, (int) pcb->aging->status);

	memcpy(stream + *desplazamiento, &(pcb->tiempoEjecucion->current), sizeof(struct timespec));
    *desplazamiento += sizeof(struct timespec);
	memcpy(stream + *desplazamiento, &(pcb->tiempoEjecucion->elapsed_ms), sizeof(int64_t));
    *desplazamiento += sizeof(int64_t);
	agregar_entero_a_stream(stream, desplazamiento, (int) pcb->tiempoEjecucion->status);

    int cantidad_archivos = list_size(pcb->TablaArchivosAbiertos);
    memcpy(stream + *desplazamiento, &cantidad_archivos, sizeof(int));
    *desplazamiento += sizeof(int);

    for (i = 0; i < cantidad_archivos; i++) {
        /*Archivo* archivo = list_get(pcb->TablaArchivosAbiertos, i);
		agregar_entero_a_stream(stream, desplazamiento, archivo->Id);
		agregar_cadena_a_stream(stream, desplazamiento, archivo->Nombre);
        memcpy(stream + *desplazamiento, &(archivo->Direccion), sizeof(int*));
        *desplazamiento += sizeof(int*);*/

		archivo_local_proceso* archivo = list_get(pcb->TablaArchivosAbiertos, i);
		agregar_entero_a_stream(stream, desplazamiento, archivo->puntero);
		agregar_cadena_a_stream(stream, desplazamiento, archivo->nombre);
		agregar_cadena_a_stream(stream, desplazamiento, archivo->modoApertura);
    }

    memcpy(stream + *desplazamiento, &(pcb->Estado), sizeof(int));
    *desplazamiento += sizeof(int);

    return stream;
}

void agregar_registro_a_stream(void * stream, int* desplazamiento, char* reg, int tam)
{
	memcpy(stream + *desplazamiento, reg, tam);
    *desplazamiento += tam;
}

void agregar_cadena_a_stream(void * stream, int* desplazamiento, char* cadena)
{
	int tamanio_cadena = strlen(cadena) + 1;
	agregar_entero_a_stream(stream, desplazamiento, tamanio_cadena);
	memcpy(stream + *desplazamiento, cadena, tamanio_cadena);
	*desplazamiento += tamanio_cadena;
}

void agregar_cadena_a_stream_con_tamanio(void * stream, int* desplazamiento, char* cadena, int tamanio)
{
	memcpy(stream + *desplazamiento, cadena, tamanio);
	*desplazamiento += tamanio;
}
void agregar_entero_a_stream(void * stream, int* desplazamiento, int entero)
{
	memcpy(stream + *desplazamiento, &entero, sizeof(int));
	*desplazamiento += sizeof(int);
}

void enviar_solicitud(int socket_cliente, int cod_solicitud, int size_buffer, void* stream, int cod_op)
{
	t_buffer* buffer = malloc(sizeof(t_buffer));
	buffer->size = size_buffer;
	buffer->stream = stream;

	Solicitud* solicitud = malloc(sizeof(Solicitud)); 
	solicitud->codigo_operacion = cod_op;
	solicitud->codigo_solicitud = cod_solicitud;
	solicitud->buffer = buffer;

	void* a_enviar = serializar_solicitud(solicitud, &size_buffer);

	send(socket_cliente, a_enviar, size_buffer, 0);
	//printf("SOLICITUD ENVIADA - SOLICITUD: %d - TAMANIO: %d\n", cod_solicitud, size_buffer);

	free(a_enviar);
	free(solicitud->buffer->stream);
	free(solicitud->buffer);
	free(solicitud);
}

void* serializar_solicitud(Solicitud* solicitud, int *desplazamiento)
{
	void* magic = malloc(*desplazamiento + sizeof(int)*3);
	int bytes = 0;

	memcpy(magic + bytes, &(solicitud->codigo_operacion), sizeof(int));
	bytes+= sizeof(int);
  	memcpy(magic + bytes, &(solicitud->codigo_solicitud), sizeof(int));
	bytes+= sizeof(int);
	memcpy(magic + bytes, &(solicitud->buffer->size), sizeof(int));
	bytes+= sizeof(int);
	memcpy(magic + bytes, solicitud->buffer->stream, *desplazamiento);
	bytes += *desplazamiento;
	*desplazamiento = bytes;
	return magic;
}

void agregar_tabla_segmentos_a_stream(void *stream, int* desplazamiento, t_list* TablaSegmentos)
{
	int cantidad_segmentos = list_size(TablaSegmentos);
	agregar_entero_a_stream(stream, desplazamiento, cantidad_segmentos);

    for (int i = 0; i < cantidad_segmentos; i++) {
        Segmento* segmento = list_get(TablaSegmentos, i);
		agregar_entero_a_stream(stream, desplazamiento, segmento->Id);
		agregar_entero_a_stream(stream, desplazamiento, segmento->Base);
		agregar_entero_a_stream(stream, desplazamiento, segmento->Tamanio);
    }
}



/* ---------------- FUNCIONES DE DESERIALIZACION ---------------- */

PCB* recibir_pcb(void* buffer, int* desplazamiento) 
{
    PCB* pcb = inicializar_pcb();

    pcb->Size = deserializar_entero_desde_buffer(buffer, desplazamiento);
    pcb->PID = deserializar_entero_desde_buffer(buffer, desplazamiento);
    deserializar_lista_instrucciones(buffer, desplazamiento, pcb->Instrucciones);
    pcb->PC = deserializar_entero_desde_buffer(buffer, desplazamiento);
    deserializar_registros(buffer, desplazamiento, pcb->RegistrosCPU);
    deserializar_tiempo_desde_buffer(buffer, desplazamiento, &(pcb->tiempo));
    deserializar_lista_segmentos(buffer, desplazamiento, pcb->TablaSegmentos);
    deserializar_cronometro_desde_buffer(buffer, desplazamiento, pcb->aging);
	deserializar_cronometro_desde_buffer(buffer, desplazamiento, pcb->tiempoEjecucion);
    deserializar_lista_archivos(buffer, desplazamiento, pcb->TablaArchivosAbiertos);
    pcb->Estado = deserializar_entero_desde_buffer(buffer, desplazamiento);

    return pcb;										
}

void* recibir_datos(int socket, int size) 
{
    void* buffer = malloc(size);
    recv(socket, buffer, size, 0);
    return buffer;
}

int deserializar_entero_desde_buffer(void* buffer, int* desplazamiento)
{
    int entero;
	memcpy(&entero, buffer + *desplazamiento, sizeof(int));
    *desplazamiento += sizeof(int);

	return entero;
}

char* deserializar_cadena_desde_buffer(void* buffer, int* desplazamiento) 
{
	int longitud = deserializar_entero_desde_buffer(buffer, desplazamiento);
	char* cadena = malloc(longitud + 1);
    memcpy(cadena, buffer + *desplazamiento, longitud);
	cadena[longitud] = '\0';
    *desplazamiento += longitud;

	return cadena;
}

char* deserializar_cadena_desde_buffer_con_tamanio(void* buffer, int* desplazamiento, int tamanio) 
{
	char* cadena = malloc(tamanio + 1);
    memcpy(cadena, buffer + *desplazamiento, tamanio);
    *desplazamiento += tamanio;
	cadena[tamanio] = '\0';
	return cadena;
}

void deserializar_puntero_entero_desde_buffer(void* buffer, int* desplazamiento, int* entero) 
{
    memcpy(&entero, buffer + *desplazamiento, sizeof(int*));
    *desplazamiento += sizeof(int*);
}

void deserializar_lista_instrucciones(void* buffer, int* desplazamiento, t_list* lista) 
{
    int cantidad_instrucciones;
    memcpy(&cantidad_instrucciones, buffer + *desplazamiento, sizeof(int));
    *desplazamiento += sizeof(int);

    for (int i = 0; i < cantidad_instrucciones; i++) {
        int tamanio_instruccion;
        memcpy(&tamanio_instruccion, buffer + *desplazamiento, sizeof(int));
        *desplazamiento += sizeof(int);

        char* instruccion = malloc(tamanio_instruccion);
        memcpy(instruccion, buffer + *desplazamiento, tamanio_instruccion);
        *desplazamiento += tamanio_instruccion;

        list_add(lista, instruccion);
    }
}
 
void deserializar_registros(void* buffer, int* desplazamiento, Registros* registros) 
{
    deserializar_registro_desde_buffer(buffer, desplazamiento, registros->AX, 4);
    deserializar_registro_desde_buffer(buffer, desplazamiento, registros->BX, 4);
    deserializar_registro_desde_buffer(buffer, desplazamiento, registros->CX, 4);
    deserializar_registro_desde_buffer(buffer, desplazamiento, registros->DX, 4);
    deserializar_registro_desde_buffer(buffer, desplazamiento, registros->EAX, 8);
    deserializar_registro_desde_buffer(buffer, desplazamiento, registros->EBX, 8);
    deserializar_registro_desde_buffer(buffer, desplazamiento, registros->ECX, 8);
    deserializar_registro_desde_buffer(buffer, desplazamiento, registros->EDX, 8);
    deserializar_registro_desde_buffer(buffer, desplazamiento, registros->RAX, 16);
    deserializar_registro_desde_buffer(buffer, desplazamiento, registros->RBX, 16);
    deserializar_registro_desde_buffer(buffer, desplazamiento, registros->RCX, 16);
    deserializar_registro_desde_buffer(buffer, desplazamiento, registros->RDX, 16);
}

void deserializar_registro_desde_buffer(void* buffer, int* desplazamiento, char* reg, int tamanio) 
{
	memcpy(reg, buffer + *desplazamiento, tamanio);
	*desplazamiento += tamanio;
}

void deserializar_tiempo_desde_buffer(void* buffer, int* desplazamiento, tiempo_t* tiempo) 
{
	memcpy(&(tiempo->estimacion), buffer + *desplazamiento, sizeof(double));
    *desplazamiento += sizeof(double);

	memcpy(&(tiempo->ratioResponse), buffer + *desplazamiento, sizeof(double));
    *desplazamiento += sizeof(double);
}

void log_tabla_segmentos(PCB* pcb, t_log* logger)
{
  t_list_iterator* iteratorSegmentos = list_iterator_create(pcb->TablaSegmentos);
  while(list_iterator_has_next(iteratorSegmentos))
  {
    Segmento *segmento = (Segmento*) list_iterator_next(iteratorSegmentos);
    log_debug(logger, "(TABLA SEGMENTOS) PID: %d - Segmento: %d - Base: %d - Tamaño %d", pcb->PID, segmento->Id, segmento->Base, segmento->Tamanio);
  };
  list_iterator_destroy(iteratorSegmentos);
}

void deserializar_cronometro_desde_buffer(void* buffer, int* desplazamiento, t_temporal* cronometro) 
{
	memcpy(&(cronometro->current), buffer + *desplazamiento, sizeof(struct timespec));
    *desplazamiento += sizeof(struct timespec);

	memcpy(&(cronometro->elapsed_ms), buffer + *desplazamiento, sizeof(int64_t));
    *desplazamiento += sizeof(int64_t);

	memcpy(&(cronometro->status), buffer + *desplazamiento, sizeof(int));
    *desplazamiento += sizeof(int);
}

void deserializar_lista_segmentos(void* buffer, int* desplazamiento, t_list* lista_segmentos) 
{
    int cantidad_segmentos;
    memcpy(&cantidad_segmentos, buffer + *desplazamiento, sizeof(int));
    *desplazamiento += sizeof(int);

    for (int i = 0; i < cantidad_segmentos; i++) {
        Segmento* segmento = malloc(sizeof(Segmento));
        segmento->Id = deserializar_entero_desde_buffer(buffer, desplazamiento);
        segmento->Base = deserializar_entero_desde_buffer(buffer, desplazamiento);
        segmento->Tamanio = deserializar_entero_desde_buffer(buffer, desplazamiento);
        list_add(lista_segmentos, segmento);
    }
}

void deserializar_lista_archivos(void* buffer, int* desplazamiento, t_list* lista_archivos) 
{
    int cantidad_archivos;
    memcpy(&cantidad_archivos, buffer + *desplazamiento, sizeof(int));
    *desplazamiento += sizeof(int);

    for (int i = 0; i < cantidad_archivos; i++) {
        archivo_local_proceso* archivo = malloc(sizeof(archivo_local_proceso));
        archivo->puntero = deserializar_entero_desde_buffer(buffer, desplazamiento);
        /*archivo->nombre = deserializar_cadena_desde_buffer(buffer, desplazamiento);
        archivo->modoApertura = deserializar_cadena_desde_buffer(buffer, desplazamiento);*/
        int tamanio_nombre;
        memcpy(&tamanio_nombre, buffer + *desplazamiento, sizeof(int));
        *desplazamiento += sizeof(int);

        archivo->nombre = malloc(tamanio_nombre);
        memcpy(archivo->nombre, buffer + *desplazamiento, tamanio_nombre);
        *desplazamiento += tamanio_nombre;

		int tamanio_modoApertura;
        memcpy(&tamanio_modoApertura, buffer + *desplazamiento, sizeof(int));
        *desplazamiento += sizeof(int);
		
        archivo->modoApertura = malloc(tamanio_modoApertura);
        memcpy(archivo->modoApertura, buffer + *desplazamiento, tamanio_modoApertura);
        *desplazamiento += tamanio_modoApertura;
        list_add(lista_archivos, archivo);
    }

}

/* ---------------- ARMAR PCB ---------------- */

PCB* inicializar_pcb() 
{
	int pcb_empty_size = sizeof(int) * 4 + sizeof(t_list) * 3 + sizeof(t_temporal) * 2 + sizeof(tiempo_t) + 112 /*registers*/;
	Registros* reg = malloc(sizeof(Registros));
	reg->AX = string_new();
	reg->BX = string_new();
	reg->CX = string_new();
	reg->DX = string_new();
	reg->EAX = string_new();
	reg->EBX = string_new();
	reg->ECX = string_new();
	reg->EDX = string_new();
	reg->RAX = string_new();
	reg->RBX = string_new();
	reg->RCX = string_new();
	reg->RDX = string_new();
	
	string_append(&reg->AX, "oooo");
	string_append(&reg->BX, "oooo");
	string_append(&reg->CX, "oooo");
	string_append(&reg->DX, "oooo");
	string_append(&reg->EAX, "oooooooo");
	string_append(&reg->EBX, "oooooooo");
	string_append(&reg->ECX, "oooooooo");
	string_append(&reg->EDX, "oooooooo");
	string_append(&reg->RAX, "oooooooooooooooo");
	string_append(&reg->RBX, "oooooooooooooooo");
	string_append(&reg->RCX, "oooooooooooooooo");
	string_append(&reg->RDX, "oooooooooooooooo");

	PCB* pcb = malloc(pcb_empty_size);
	pcb->Size = pcb_empty_size;
	pcb->PID = 0;
	pcb->Instrucciones = list_create();
	pcb->PC = 0;
	pcb->RegistrosCPU = reg;
	pcb->TablaSegmentos = list_create();
	pcb->tiempo.ratioResponse = 0;
	pcb->tiempo.estimacion = 0;
	pcb->aging = inicializar_cronometro();
	pcb->tiempoEjecucion = inicializar_cronometro();
	pcb->TablaArchivosAbiertos = list_create(); 
	pcb->Estado=NEW;

	return pcb;
}

void liberar_pcb(PCB* pcb) 
{
	//list_destroy(pcb->Instrucciones);
	free(pcb->RegistrosCPU->AX);
	free(pcb->RegistrosCPU->BX);
	free(pcb->RegistrosCPU->CX);
	free(pcb->RegistrosCPU->DX);
	free(pcb->RegistrosCPU->EAX);
	free(pcb->RegistrosCPU->EBX);
	free(pcb->RegistrosCPU->ECX);
	free(pcb->RegistrosCPU->EDX);
	free(pcb->RegistrosCPU->RAX);
	free(pcb->RegistrosCPU->RBX);
	free(pcb->RegistrosCPU->RCX);
	free(pcb->RegistrosCPU->RDX);
	free(pcb->RegistrosCPU);
	free(pcb->aging);
	free(pcb->tiempoEjecucion);
	list_destroy_and_destroy_elements(pcb->Instrucciones, free);
	list_destroy_and_destroy_elements(pcb->TablaSegmentos, free);
	list_destroy_and_destroy_elements(pcb->TablaArchivosAbiertos, free);
	free(pcb);
}

t_temporal* inicializar_cronometro(void) 
{
    t_temporal* self = malloc(sizeof(t_temporal));

    self->elapsed_ms = 0;
    self->status = TEMPORAL_STATUS_STOPPED;

    clock_gettime(CLOCK_MONOTONIC_RAW, &self->current);

    return self;
}

int min (int n1, int n2)
{
  if (n1 <= n2) return n1;
  else return n2;
}
int max (int n1, int n2)
{
  if (n1 >= n2) return n1;
  else return n2;
}