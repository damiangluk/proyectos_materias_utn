#ifndef md_cpu_H
#define md_cpu_H
#include <stdio.h>
#include <commons/log.h>
#include <stdbool.h>
#include "shared_utils.h"
#include "tests.h"

/* ---------------- VARIABLES GLOBALES ---------------- */
t_log* logger;
PCB* pcb;
int num_segmento;
int pcb_empty_size = sizeof(int) * 4 + sizeof(t_list) * 3 + sizeof(t_temporal) * 2 + sizeof(tiempo_t) + 112 /*registers*/;
int conexionKernel, conexionMemoria;
char *ipMemoria, *puertoMemoria, *retardoInstruccion, *tamMaxSegmento, *ip, *puerto;

typedef struct
{
    char* Operacion;
    t_list* Parametros;
} Instruccion;

int ciclo_de_instruccion();
char* fetch();
Instruccion* decode(char*);
int execute(Instruccion*);

void set(char*, char*);
void f_seek(char*, int);
void fclose_or_fopen(char*, int);
void fread_or_fwrite(char*, int, int, int, int);
void wait_or_signal(char*, int);
void inputOutput(int);
void f_truncate(char*, int);
void yield_or_exit(int);
void mov_in(char*, int, int);
void mov_out(int, char*, int);
void create_segment(int, int);
void delete_segment(int);

int traducir_dir_logica_fisica(int, int);
bool equals(Segmento*);
char* get(char*);
int registerSize(char*);
int traducir(int, int);

void enviar_sol(int, int, t_list*);
char* pedir_de_direccion_memoria(int, int);
void enviar_a_direccion_memoria(int, char*);
char* recibir_respuesta_memoria(int);
int segmento_que_pertenece(int);



#endif