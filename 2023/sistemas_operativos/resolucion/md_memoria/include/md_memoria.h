#ifndef md_memoria_H
#define md_memoria_H
#include <stdio.h>
#include <commons/log.h>
#include <stdbool.h>
#include "shared_utils.h"
#include "tests.h"

t_log* logger;
char *ipMemoria, *puertoMemoria, *tamMemoria, *tamSegmento0, *cantSegmentos, *retardoMemoria, *retardoCompactacion, *algoritmoAsignacion;
int cantConexiones = 0, conexionKernel, PID;
void* espacio_usuario;
t_list *tablasSegmentos, *espaciosLibres;
pthread_t hiloCPU, hiloKernel, hiloFileSystem;
Segmento* segmento0;

typedef struct {
  int Base;
  int Tamanio;
} espacio_libre;

typedef enum {
  CPU,
  FILESYSTEM,
  KERNEL
} Proceso;

typedef struct {
  int PID;
  t_list* ListaSegmentos;
} item_tablas_segmentos;


typedef struct {
  int PID;
  Segmento* segmento;
} segmentoConPID;

void crear_estructuras();
int calcular_espacio_disponible();
void crearHilo(int, int);
void hiloLecturaEscritura(void*);
void hiloConKernel();
void enviarTablaSegmentos(int, item_tablas_segmentos*);
void enviarTablasActualizadas(t_list*);
void liberar_segmento(Segmento*);
bool compara_base(void*, void *);

int buscarEspacio(int);
t_list* buscarSegmentosEntrePosiciones(int, int);
item_tablas_segmentos* buscarTablaSegmentosDeProceso(int);
item_tablas_segmentos* buscarTablaSegmentosDeProcesoStream(void*);

void compactarMemoria();
void consolidarHuecos();

void iniciarProceso(int);
void createSegment(int, int, int);
void deleteSegment(int, int);
void finalizarProceso(int);

void leerEspacioUsuario(int, int, int);
void escribirEspacioUsuario(int, int, void*, int);
void log_de_resultado_compactacion();


#endif