#ifndef md_file_system_H
#define md_file_system_H
#include <stdio.h>
#include <commons/log.h>
#include <stdbool.h>
#include "shared_utils.h"
#include "tests.h"
#include <commons/bitarray.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<commons/collections/queue.h>
#include <commons/collections/list.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
int conexionMemoria;
char *ip, *puerto, *ipMemoria, *puertoMemoria, *pathSuperbloque, *pathBitmap, *pathBloques, *retardoAccesoBloque;
t_log* logger;
t_bitarray *arrayDeBits;
char **bloques;


typedef struct {
    int tamanoBloque,
            cantidadBloques;
} superbloque_t;

FILE * archivoBitmap;
FILE * archivoBloques;
t_config * archivoSuperbloque;

t_bitarray* bitmap;

superbloque_t *superbloque;

t_list* archivos;
void inicializarArchivos();
void inicializarBitmap();
void inicializarBitmap2();
void levantarSuperBloque();
void inicializarBloques();
void imprimirBitmap();
void inicializarArchivoBitmap();
void inicializarEstructuras();
void freecadenas(char**, int );
char** splitString(char*, int, int*);

FCB_t* buscarArchivo(char* );
void logAccesoBitmap(int , int );
void logListaArchivos();
void truncarArchivo(char*, uint32_t);
int crearArchivo(char*);
int abrirArchivo(char*);
void leerArchivoFCB(char*);
void levantarArchivoDeBloques();
int conexionKernel, conexionMemoria;
void agregarBloque(FCB_t*, uint32_t);

char* obtenerBloque(uint32_t);
uint32_t* leerBloqueDePunteros(uint32_t);
void liberarListaArchivos();
void liberarArchivo(void*);
void levantarFCBs();

uint32_t obtenerBloqueDisponible();
uint32_t* traerBloqueDePunteros(uint32_t );

void escribirBloquePunteros(uint32_t, uint32_t*);
int calcularBloquesNuevos(uint32_t , uint32_t );
int calcularBloquesDeMas(uint32_t , uint32_t );

void actualizarFCB(FCB_t*);
bool filtradoPunteros(void * );
void leerArchivo(char*, uint32_t, int , int, int);
void leerArchivoDeBloques(uint32_t, uint32_t, char*, int*);
void escribirEnMemoria(int,int, void*,int);
void leerDeMemoria(int,int, int);
void escribirArchivo(char*, uint32_t, int, int, int);
void inicializarArchivoDeBloques();
void eliminarBloque(int);
void sincronizarBitmap();
void imprimirFCBs();
void loggeoAccesoABloque(char* , uint32_t , uint32_t );
void escribirArchivoDeBloques(uint32_t , uint32_t , char* , int *);
void leerBloqueDeDatos(uint32_t);
int cantidadPunterosEnBloque(uint32_t*);

#endif