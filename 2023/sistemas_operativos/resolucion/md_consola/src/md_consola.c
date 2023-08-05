#include "md_consola.h"

//PREGUNTAR PORQUE NO FUNCIONA LA LINEA 10
/*void TrimEnd(char** str, const char* chars) {
  size_t len = strcspn(*str, chars); // encontrar la posición de \n
  *str[len] = '\0';
}*/

int main(int argc, char ** argv){    
  if(argc > 1 && strcmp(argv[1],"-test")==0) return run_tests();

  /* ---------------- CREACION LOGGER ---------------- */
  t_log* logger = log_create("./cfg/md_consola.log", "md_consola", true, LOG_LEVEL_DEBUG);
  log_debug(logger, "Logger creado correctamente");

  /* ---------------- LECTURA DE CONFIGS ---------------- */

  char* dir_consola_config = argv[1];
  log_debug(logger, "Directorio config: %s", dir_consola_config);
  char* dir_pseudocodigo_config = argv[2];
  log_debug(logger, "Directorio pseudocodigo: %s", dir_pseudocodigo_config);
  
  t_config* config = iniciar_config();
  char *current_dir = getcwd(NULL, 0);

  char buffer[MAX_BUFFER];
  memccpy(memccpy(buffer, current_dir, '\0', MAX_BUFFER) - 1, dir_consola_config, '\0', MAX_BUFFER);
  config = config_create(buffer);
  
  if (config != NULL) {
    if(config_has_property(config, "IP_KERNEL"))
    {
      ipKernel = config_get_string_value(config, "IP_KERNEL");
      log_debug(logger, "Lei la IP Kernel: %s", ipKernel);
    }
    if(config_has_property(config, "PUERTO_KERNEL"))
    {
      puertoKernel = config_get_string_value(config, "PUERTO_KERNEL");
      log_debug(logger, "Lei el puerto Kernel: %s", puertoKernel);
    }
  }

  /* ---------------- HANDSHAKE A KERNEL ---------------- */
  conexionKernel = crear_conexion(ipKernel, puertoKernel);
	enviar_mensaje_con_op("Conexion CONSOLA a KERNEL", conexionKernel, HANDSHAKE);
  int respuesta = recibir_operacion(conexionKernel);
  char* mensaje = recibir_mensaje(conexionKernel);

  if(respuesta != OK)
  {
    log_error(logger, "No me pude conectar al kernel");
    return EXIT_FAILURE;
  }
  log_debug(logger, "Respuesta kernel: %s", mensaje);
  free(mensaje);

  /* ---------------- LECTURA PSEUDOCODIGO ---------------- */
  file_pseudocodigo = fopen(dir_pseudocodigo_config, "r");
  
  if(!file_pseudocodigo)
  {
    log_debug(logger, "No se pudo abrir el archivo");
    return EXIT_FAILURE;
  }

  t_paquete* paquete = crear_paquete(PAQUETE_CONSOLA);
  char* line = NULL;
  size_t length;
  
  do {
    getline(&line, &length, file_pseudocodigo);
	  
    //TrimEnd(&line, "\n");
    size_t len = strcspn(line, "\n"); // encontrar la posición de \n
    line[len] = '\0';
    
    log_debug(logger, "Linea leida: %s", line);
	  agregar_a_paquete(paquete, line, strlen(line) + 1);
	} while(strcmp(line, "EXIT"));
  free(line);

	log_debug(logger, "Enviando codigo de operacion: %d", paquete->codigo_operacion);
	
  enviar_paquete(paquete, conexionKernel);
  respuesta = recibir_operacion(conexionKernel);
  mensaje = recibir_mensaje(conexionKernel);

  if(respuesta != OK)
  {
    log_error(logger, "Recibi error del kernel");
    return EXIT_FAILURE;
  }
  log_debug(logger, "Paquete recibido en kernel");

  /* free(mensaje);
  respuesta = recibir_operacion(conexionKernel);
  mensaje = recibir_mensaje(conexionKernel);
  log_debug(logger, "Proceso finalizado: %s", mensaje);*/ 
  
  free(mensaje);
	eliminar_paquete(paquete);
  terminar_programa(conexionKernel, logger, config, current_dir);
}

