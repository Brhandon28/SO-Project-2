#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leerArchivos(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usa: %s <nombreArchivo>\n", argv[0]);
        exit(1);
    }

    FILE *file;
    char buffer[256];

    // Se abre el archivo en modo lectura
    file = fopen(argv[1], "r");
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
    
    int n = atoi(buffer); // Numero de recursos
    
    // Se lee la segunda linea del archivo
    int recursosTotales[n]; // Recursos totales
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error: Abriendo archivo");
        fclose(file);
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
            exit(1);
        }
    }

    // Se lee la tercera linea del archivo
    int recursosDisponibles[n]; // Recursos disponibles
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error: Abriendo archivo");
        fclose(file);
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
            exit(1);
        }
    }

    // Se lee la cuarta linea del archivo
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error: Abriendo archivo");
        fclose(file);
        exit(1);
    }

    int m = atoi(buffer); // Numero de procesos
    // printf("Numero de procesos: %d\n", m);

    // Se lee el resto del archivo
    int matrizDeAsignacion[m][n]; // Asignacion de recursos
    int matrizRecursosTotales[m][n]; // Total de recursos
    int prioridades[m]; // Prioridades

    for (int i = 0; i < m; i++) {
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            perror("Error: Abriendo archivo");
            fclose(file);
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
                exit(1);
            }
        }

        // Almacenar la prioridad
        if (token != NULL) {
            prioridades[i] = atoi(token);
        } else {
            fprintf(stderr, "Error: no hay suficientes valores para prioridades\n");
            fclose(file);
            exit(1);
        }
    }
    
    // Imprimir los recursos totales para verificar
    printf("Recursos totales: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", recursosTotales[i]);
    }
    printf("\n");

    // Imprimir los recursos disponibles para verificar
    printf("Recursos disponibles: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", recursosDisponibles[i]);
    }
    printf("\n");
    
    // Imprimir la matriz de asignacion para verificar
    printf("Matriz de asignacion:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrizDeAsignacion[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // Imprimir la matriz de recursos totales para verificar
    printf("Matriz de recursos totales:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrizRecursosTotales[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Imprimir las prioridades para verificar
    printf("Prioridades:\n");
    for (int i = 0; i < m; i++) {
        printf("%d ", prioridades[i]);
    }
    printf("\n");

    fclose(file);
}