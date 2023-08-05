#ifndef SHARED_UTILS_H
#define SHARED_UTILS_H

#include <stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<stdbool.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include<commons/collections/list.h>
#include<string.h>
#include<assert.h>
#include<time.h>
#include <sys/time.h>
#include <semaphore.h>
#include <pthread.h>
#include <commons/temporal.h>
#include<commons/collections/queue.h>

/* ---------------- ESTRUCTURAS DE PROCESOS ---------------- */
typedef struct
{
    char* AX, *BX, *CX, *DX;
    char* EAX, *EBX, *ECX, *EDX;
    char* RAX, *RBX, *RCX, *RDX;
} Registros;

typedef struct
{   
    int Id;
    int Base;
    int Tamanio;
} Segmento;

typedef struct
{
    int Id;
    char* Nombre;
    int* Direccion;
} Archivo;

typedef struct {
    char* nombre; // Estructura que contiene el nombre del archivo
    t_queue *colaBloqueados;
    sem_t lockArchivo; // garantizar la exclusividad de acceso al archivo
} entrada_archivo_global;
typedef struct {
    char* nombre;
    char* modoApertura;
    int puntero;
} archivo_local_proceso;
typedef struct {
char* nombreArchivo;
uint32_t  tamanoArchivo, 
        punteroArchivo, 
        punteroIndirecto;
} FCB_t;

typedef enum
{
	NEW,
	READY,
    BLOCK,
    EXEC,
    EXIT
} Estado;

typedef enum
{
    HRRN,
    FIFO
} Algoritmo;

typedef struct tiempo_t{
    double estimacion;
    double ratioResponse;

}tiempo_t;
typedef struct
{
    int Size;
	int PID; // Process ID
	t_list* Instrucciones; // Lista de Char*
    int PC; // Program Counter: Proxima instruccion a ejecutar
    tiempo_t tiempo; // tiempo_ejecutado, estimacion, tiempo_de_espera
    Registros* RegistrosCPU;
    t_list* TablaSegmentos; // Lista de Segmento
    t_list* TablaArchivosAbiertos; // Lista de Archivo
    Estado Estado; 
    // Calculos
    t_temporal* aging;
    t_temporal* tiempoEjecucion;
} PCB;

typedef enum
{
	MENSAJE,
	PAQUETE,
    PAQUETE_CONSOLA,
    OK,
    ERROR,
    HANDSHAKE,
    OP_PCB,
    INSTRUCCION_CPU,
    LEER_DE_MEMORIA,
    OPERACION_DE_KERNEL,
    TABLA_SEGMENTO,
    TABLAS_SEGMENTOS,
    SOLICITUD_COMPACTAR,
    OPERACION_MEMORIA
} op_code;

typedef enum
{
    INICIAR_PROCESO,
    CREATE_SEGMENTO,
    DELETE_SEGMENTO,
    FINALIZAR_PROCESO,
    SOLICITUD_COMPACTACION, 
    LEER,
    ESCRIBIR
} op_memoria;


typedef enum
{
	IO,
    FOPEN,
    FCLOSE,
    FSEEK,
    FREAD,
    FWRITE,
    FTRUNCATE,
    WAIT,
    SIGNAL,
    CREATE_SEGMENT,
    DELETE_SEGMENT,
    YIELD,
    EXITS,
    F_OPEN,
    F_CLOSE,
    F_SEEK,
    F_TRUNCATE,
    F_READ,
    F_WRITE,
    F_CREATE,
    NO_EXISTE_FCB,
    ERRORCPU
} cpu_instruction_code;

typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	int codigo_operacion; //op_code
	t_buffer* buffer;
} t_paquete;

typedef struct
{
    int NumeroSegmento;
    int Desplazamiento;
} DireccionLogica;

typedef struct
{
	int codigo_operacion; //op_code
    int codigo_solicitud; //cpu_instruction_code
	t_buffer* buffer;
} Solicitud;

typedef struct {
    char* nombreRecurso;    
    short instanciasRecurso;
    t_queue *procesosBloqueados;
    t_list *idsProcesosQueLoTienen;
} recursos_t;

/* ---------------- VARIABLES GLOBALES ---------------- */
#define MAX_BUFFER 100

/* ---------------- FUNCIONES DE CLIENTE ---------------- */

int crear_conexion(char*, char*);
void liberar_conexion(int);

/* ---------------- FUNCIONES DE SERVIDOR ---------------- */

int iniciar_servidor(char*, char*);
int esperar_cliente(int);

/* ---------------- FUNCIONES DE PAQUETE ---------------- */

void log_tabla_segmentos(PCB*, t_log*);
void crear_buffer(t_paquete*);
void* recibir_buffer(int*, int);
t_list* recibir_paquete(int);
char* recibir_mensaje(int);
int recibir_operacion(int);
void enviar_mensaje(char*, int);
void enviar_mensaje_con_op(char*, int, int);
void enviar_mensaje_con_opysol(char*, int, int, int);
t_paquete* crear_paquete(int);
void agregar_a_paquete(t_paquete*, void*, int );
void enviar_paquete(t_paquete*, int);
void eliminar_paquete(t_paquete* );

/* ---------------- FUNCIONES DE PROGRAMA ---------------- */

void s_list_iterate(t_list*);
t_log* iniciar_logger(void);
t_config* iniciar_config(void);
void leer_consola(t_log*);
void terminar_programa(int, t_log*, t_config*, char*);
int min (int , int );
int max (int, int);

/* ------------ ARMAR PCB ------------*/

PCB* inicializar_pcb();
t_temporal* inicializar_cronometro(void);
void liberar_pcb(PCB*);

/* --------------- FUNCIONES DE SERIALIZACION ------- */

void* serializar_solicitud(Solicitud*, int*);
void enviar_solicitud(int, int, int, void*, int);
void* serializar_paquete(t_paquete*, int);
void* serializar_pcb(PCB*, int*);
void agregar_registro_a_stream(void*, int*, char*, int);
void agregar_entero_a_stream(void *, int*, int);
void agregar_cadena_a_stream(void*, int*, char*);
void agregar_cadena_a_stream_con_tamanio(void *, int*, char* , int);

void agregar_tabla_segmentos_a_stream(void*, int*, t_list*);



/* --------------- FUNCIONES DE DESERIALIZACION ------- */

PCB* recibir_pcb(void*, int*);
void* recibir_datos(int, int);
int deserializar_entero_desde_buffer(void*, int*);
void deserializar_lista_instrucciones(void*, int*, t_list*);
void deserializar_registros(void*, int*, Registros*);
void deserializar_registro_desde_buffer(void*, int*, char*, int);
void deserializar_cronometro_desde_buffer(void*, int*, t_temporal*);
void deserializar_tiempo_desde_buffer(void*, int*, tiempo_t*);
void deserializar_lista_segmentos(void*, int*, t_list*);
void deserializar_lista_archivos(void*, int*, t_list*);
void deserializar_puntero_entero_desde_buffer(void*, int*, int*);
char* deserializar_cadena_desde_buffer(void*, int*);
char* deserializar_cadena_desde_buffer_con_tamanio(void*, int*, int );


#endif