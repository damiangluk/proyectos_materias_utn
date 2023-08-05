#ifndef md_kernel_H
#define md_kernel_H
#include <stdio.h>
#include <commons/log.h>
#include <stdbool.h>
#include "shared_utils.h"
#include "tests.h"

#include <time.h>
#include <sys/time.h>


// ESTRUCTURAS

typedef struct {
  int PID;
  sem_t* semProceso;
} item_semaforo;

// VARIABLES
int server_fd, conexionMemoria, conexionFileSystem, conexionCpu, procesosId = 1, instruccionAEjecutar, desplazamientoBufferCPU = 0;
t_log* logger;
t_config* config;
char *ip, *puerto, *algoritmoDePlanificacion, *hrrnAlfa, *ipCpu, *puertoCpu, *ipMemoria, *puertoMemoria, *ipFileSystem, *puertoFileSystem, *estimacionInicial, *gradoMaxMulti;
pthread_t hiloKernelConsola, planificadorLargoPlazo, planificadorCortoPlazo, hiloKernelCpu;
sem_t sem_gradoMultiprog, sem_dispatcher, sem_fin, sem_colaNew, sem_colaReady, sem_cpu_not_running;
t_list *semaforosProcesos, *recursos, *procesosActivos;
pthread_mutex_t mutexNew, mutexSacarNew, mutexColaReady, mutexRunning, mutexSemaforosProcesos;
char **nombresRecurso, **instanciaRecurso;
int pcb_empty_size = sizeof(int) * 4 + sizeof(t_list) * 3 + sizeof(t_temporal) * 2 + sizeof(tiempo_t) + 112 /*registers*/;
t_queue *colaNew, *colaReady;
Algoritmo algoritmoActual;
PCB* pcb_running;
void* bufferCPU;


/* ---------------- FUNCIONES DE PLANIFICADORES ---------------- */

PCB* traerMayorRR();
void estimador(PCB*);
void estimador_HRRN(PCB*);
void OrdernarColaPorHRRN(PCB*);

/* ---------------- MANEJO DE ESTADOS DE PROCESO ---------------- */

void agregarAReady(PCB*, bool);
void newAReady();
void agregarANew(PCB*);
PCB* sacarDeNew();
PCB* sacarDeReady();
void finalizarProceso(PCB*);

/* ---------------- FUNCIONES DE HILOS ---------------- */

void armarProceso();
void hiloXConsola();
void dispatcher();
void hiloCpu();

/* ---------------- FUNCIONES PARA MEMORIA ---------------- */

void inicializar_proceso_en_memoria(PCB*);
void finalizar_proceso_en_memoria(int);
void recibir_segmentos_y_actualizar_procesos();
PCB* buscarProcesoActivo(int);

/* ---------------- FUNCIONES PARA FS ---------------- */
t_list *tabla_archivos_globales;

archivo_local_proceso* buscarArchivoLocalProceso(char*, t_list*);
void agregarArchivoGlobal(char*);
void aumentarAperturasArchivo(entrada_archivo_global*);
void disminuirAperturasArchivo(entrada_archivo_global*);
void liberarTablaArchivosGlobales();
void solicitarEscribirArchivo(char*, int, int, int, int);
void solicitarLeerArchivo(char*, int, int, int, int);
void solicitarTruncarArchivo(char*, int);
void mostrarNombresArchivos();
entrada_archivo_global* buscarArchivoGlobal(char*);
void abrirArchivoFS(char*, PCB*);
void cerrarArchivoFS(char*, PCB*);
void inicializarTablaArchivosGlobales();
void seekArchivoFS(char*, int,PCB*);
void leerArchivoFS(char*,int,int,PCB*);
void escribirArchivoFS(char*,int,int, PCB*);

/* ---------------- FUNCIONES PARA CPU ---------------- */

void yield(PCB*);
bool waitRecurso(PCB*, char*);
bool signalRecurso(PCB*, char*);
void enviar_pcb_a_cpu(PCB*);
bool create_segment(PCB*, int, int);
bool delete_segment(PCB*, int);

/* ---------------- UTILIDADES ---------------- */

void sizeElem(char*);
recursos_t* buscar_recurso_en_array(char*);
void logCambiarEstado(int, Estado, Estado);
int sizeLista(t_list*);
const char* estadoToString(Estado);
const char* algoritmoToString(Algoritmo);
void queue_push_in_index(t_queue* queue, int index, void* element);
void inicializarRecursos();
void inicializarColas();
void liberar_colas();
PCB* armar_pcb(t_list*);
void inicializarLogger();
void leerConfig(char**);
void liberar_recurso(recursos_t*);
void liberar_archivos_pcb(PCB*);
void eliminar_proceso_de_recurso(recursos_t*, PCB*);
void liberar_recursos_pcb(PCB*);

#endif
