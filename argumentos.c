#include "argumentos.h"

int es_archivo_valido(const char *ruta) {
    struct stat info;

    if (stat(ruta, &info) != 0) {
        // Error al obtener información del archivo
        if (errno == ENOENT) {
          fprintf(stderr,"Error: El archivo no existe\n");
        } else if(errno == EACCES){
          fprintf(stderr,"Error: No tienes permisos para acceder a este archivo\n");
        } else {
          fprintf(stderr,"Error desconocido al acceder al archivo\n");
        }
        return 0; // No es un archivo válido
    }

    if (S_ISREG(info.st_mode)) {
        return 1; // Es un archivo regular
    } else {
        fprintf(stderr,"Error: La ruta proporcionada no es un archivo\n");
        return 0; // No es un archivo
    }
}

// ./prevencion <nombre del archivo>
void identificar_argumentos(int argc, char *argv[]) {

    //Comprobar que hay máximo 2 argumentos
    if(argc > 2) {
        printf("Hay muchos argumentos\n");
        printf("Usa: %s -m d <nombre del archivo>\n", argv[0]);
        exit(1);
    } 
    //Comprobar que hay mínimo 2 argumentos
    else if(argc < 2) { 
        printf("Faltan argumentos\n");
        printf("Usa: %s -m d <nombre del archivo>\n", argv[0]);
        exit(1);
    }

    //Comprobacion segundo argumento
    if(es_archivo_valido(argv[1]) == 0) {
        exit(1);
    }
}