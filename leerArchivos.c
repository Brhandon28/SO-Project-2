#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "leerArchivos.h"

void leerArchivos(int argc, char *argv[]) {
    
    FILE *file;
    char buffer[256];

    // Se abre el archivo en modo lectura
    file = fopen(argv[3], "r");
    if (file == NULL) {
        perror("Error: Abriendo archivo");
        exit(1);
    }
    
    // Se lee la primera linea del archivo
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error: Abriendo archivo");
        fclose(file);
        exit(1);
    }
    
    n = atoi(buffer); // Numero de recursos
    
    // Asignar memoria para recursosTotales
    recursosTotales = (int *)malloc(n * sizeof(int));
    if (recursosTotales == NULL) {
        perror("Error: Asignando memoria");
        fclose(file);
        exit(1);
    }
    
    // Se lee la segunda linea del archivo
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error: Abriendo archivo");
        fclose(file);
        free(recursosTotales);
        exit(1);
    }
    
    // Se separa la cadena por espacios y se almacenan los valores en el arreglo de recursos totales
    char *token = strtok(buffer, " ");
    for (int j = 0; j < n; j++) {
        if (token != NULL) {
            recursosTotales[j] = atoi(token);
            token = strtok(NULL, " ");
        } else {
            fprintf(stderr, "Error: no hay suficientes valores\n");
            fclose(file);
            free(recursosTotales);
            exit(1);
        }
    }
    
    // Asignar memoria para recursosDisponibles
    recursosDisponibles = (int *)malloc(n * sizeof(int));
    if (recursosDisponibles == NULL) {
        perror("Error: Asignando memoria");
        fclose(file);
        free(recursosTotales);
        exit(1);
    }

    // Se lee la tercera linea del archivo
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error: Abriendo archivo");
        fclose(file);
        free(recursosTotales);
        free(recursosDisponibles);
        exit(1);
    }

    // Se separa la cadena por espacios y se almacenan los valores en el arreglo de recursos disponibles
    token = strtok(buffer, " ");
    for (int j = 0; j < n; j++) {
        if (token != NULL) {
            recursosDisponibles[j] = atoi(token);
            token = strtok(NULL, " ");
        } else {
            fprintf(stderr, "Error: no hay suficientes valores\n");
            fclose(file);
            free(recursosTotales);
            free(recursosDisponibles);
            exit(1);
        }
    }

    // Se lee la cuarta linea del archivo
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error: Abriendo archivo");
        fclose(file);
        free(recursosTotales);
        free(recursosDisponibles);
        exit(1);
    }

    m = atoi(buffer); // Numero de procesos

    // Asignar memoria para las matrices y prioridades
    matrizDeAsignacion = (int **)malloc(m * sizeof(int *));
    matrizRecursosTotales = (int **)malloc(m * sizeof(int *));
    matrizDeNecesidades = (int **)malloc(m * sizeof(int *));
    prioridades = (int *)malloc(m * sizeof(int));
    if (matrizDeAsignacion == NULL || matrizRecursosTotales == NULL || prioridades == NULL || matrizDeNecesidades == NULL) {
        perror("Error: Asignando memoria");
        fclose(file);
        free(recursosTotales);
        free(recursosDisponibles);
        free(matrizDeAsignacion);
        free(matrizRecursosTotales);
        free(matrizDeNecesidades);
        free(prioridades);
        exit(1);
    }
    
    for (int i = 0; i < m; i++) {
        matrizDeAsignacion[i] = (int *)malloc(n * sizeof(int));
        matrizRecursosTotales[i] = (int *)malloc(n * sizeof(int));
        matrizDeNecesidades[i] = (int *)malloc(n * sizeof(int));
        if (matrizDeAsignacion[i] == NULL || matrizRecursosTotales[i] == NULL || matrizDeNecesidades[i] == NULL) {
            perror("Error: Asignando memoria");
            fclose(file);
            free(recursosTotales);
            free(recursosDisponibles);
            for (int k = 0; k <= i; k++) {
                free(matrizDeAsignacion[k]);
                free(matrizRecursosTotales[k]);
                free(matrizDeNecesidades[k]);
            }
            free(matrizDeAsignacion);
            free(matrizRecursosTotales);
            free(matrizDeNecesidades);
            free(prioridades);
            exit(1);
        }
    }
    
    for (int i = 0; i < m; i++) {
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            perror("Error: Abriendo archivo");
            fclose(file);
            free(recursosTotales);
            free(recursosDisponibles);
            for (int k = 0; k < m; k++) {
                free(matrizDeAsignacion[k]);
                free(matrizRecursosTotales[k]);
            }
            free(matrizDeAsignacion);
            free(matrizRecursosTotales);
            free(prioridades);
            exit(1);
        }

        // Se separa la cadena por espacios y el caracter '|', y se almacenan los valores en la matriz de asignacion
        token = strtok(buffer, " |");
        for (int j = 0; j < n; j++) {
            if (token != NULL) {
                matrizDeAsignacion[i][j] = atoi(token);
                token = strtok(NULL, " |");
            } else {
                fprintf(stderr, "Error: no hay suficientes valores\n");
                fclose(file);
                free(recursosTotales);
                free(recursosDisponibles);
                for (int k = 0; k < m; k++) {
                    free(matrizDeAsignacion[k]);
                    free(matrizRecursosTotales[k]);
                }
                free(matrizDeAsignacion);
                free(matrizRecursosTotales);
                free(prioridades);
                exit(1);
            }
        }
        
        // Se separa la cadena por espacios y el caracter '|', y se almacenan los valores en la matriz de recursos totales
        for (int j = 0; j < n; j++) {
            if (token != NULL) {
                matrizRecursosTotales[i][j] = atoi(token);
                token = strtok(NULL, " |");
            } else {
                fprintf(stderr, "Error: no hay suficientes valores\n");
                fclose(file);
                free(recursosTotales);
                free(recursosDisponibles);
                for (int k = 0; k < m; k++) {
                    free(matrizDeAsignacion[k]);
                    free(matrizRecursosTotales[k]);
                }
                free(matrizDeAsignacion);
                free(matrizRecursosTotales);
                free(prioridades);
                exit(1);
            }
        }

        // Almacenar la prioridad
        if (token != NULL) {
            prioridades[i] = atoi(token);
        } else {
            fprintf(stderr, "Error: no hay suficientes valores para prioridades\n");
            fclose(file);
            free(recursosTotales);
            free(recursosDisponibles);
            for (int k = 0; k < m; k++) {
                free(matrizDeAsignacion[k]);
                free(matrizRecursosTotales[k]);
            }
            free(matrizDeAsignacion);
            free(matrizRecursosTotales);
            free(prioridades);
            exit(1);
        }
    }
    
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            matrizDeNecesidades[i][j] = matrizRecursosTotales[i][j] - matrizDeAsignacion[i][j];
        }
    }

    // Liberar memoria
    free(recursosTotales);
    free(recursosDisponibles);
    for (int i = 0; i < m; i++) {
        free(matrizDeAsignacion[i]);
        free(matrizRecursosTotales[i]);
    }
    free(matrizDeAsignacion);
    free(matrizRecursosTotales);
    free(prioridades);

    fclose(file);
}