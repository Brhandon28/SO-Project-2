#include <stdio.h>
#include <stdlib.h>
#include "seguridad.h"
#include "estructuras.h"

int estadoSeguro() {

    int *secuenciaSegura = (int *)malloc(m * sizeof(int));

    // Asignar memoria para work
    work = (int *)malloc(n * sizeof(int));
    if (work == NULL) {
        perror("Error: Asignando memoria");
        exit(1);
    }

    // Asignar memoria para finish
    finish = (bool *)malloc(m * sizeof(bool));
    if (finish == NULL) {
        perror("Error: Asignando memoria");
        exit(1);
    }

    // Inicializar work
    for (int i = 0; i < n; i++) {
        work[i] = recursosDisponibles[i];
    }

    // Inicializar finish
    for (int i = 0; i < m; i++) {
        finish[i] = false;
    }

    int count = 0;

    while (count < m) {
        bool found = false;
        for (int i = 0; i < m; i++) {
            // Se buscan los procesos marcados con false
            if (finish[i] == false) {
                int j;
                for (j = 0; j < n; j++) {
                    // Si la necesidad es mayor que los recursos disponibles, se rompe el ciclo
                    if (matrizDeNecesidades[i][j] > work[j]) {
                        break;
                    }
                }
                // Si j es igual a n, significa que todos los recursos necesarios estan disponibles
                if (j == n) {
                    for (int k = 0; k < n; k++) {
                        work[k] += matrizDeAsignacion[i][k];
                    }
                    secuenciaSegura[count] = i;
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        // Si no se encontro ningun proceso, el sistema no esta en estado seguro
        if (found == false) {
            printf("El sistema no esta en estado seguro\n");
            free(work);
            //free(secuenciaSegura);
            //free(finish);
            return 0;
        }
    }
    // Si se recorrieron todos los procesos y se encontraron, el sistema esta en estado seguro
    printf("El sistema esta en estado seguro\n");

    for(int i = 0; i < m; i++) {
        printf("P%d\n", secuenciaSegura[i]);
    }

    // Liberar memoria
    free(work);
    //free(finish);

    return 1;
}