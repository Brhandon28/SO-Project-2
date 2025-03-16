#include <stdio.h>
#include <stdlib.h>
#include "seguridad.h"
#include "estructuras.h"
#include "terminarProcesos.h"
#include "operacionesEstructuras.h"
#include "menu.h"

int estadoSeguro() {

    int count = 0; //Contador de procesos terminados
    int countBloqueados = 0; //Contador de procesos bloqueados
    int idAleatorio = 0; //Id del proceso aleatorio
    int idPrioridad = 0; //Id del proceso con prioridad menor

    bool found = false; //flag para verificar si se encontro un proceso
    
    // Asignar memoria para secuenciaSegura
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

    // Verificar si hay procesos que puedan finalizar su ejecución
    while (count < m) {
        found = false;
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
                        work[k] += matrizDeAsignacion[i][k]; //Se liberan los recursos asignados al proceso
                    }
                    
                    secuenciaSegura[count] = i; //Se inserta el proceso en la secuencia segura de asignacion de reursos
                    finish[i] = true; //Se marca el proceso como finalizado
                    found = true; //Se indica que se encontró un proceso
                    insertarTerminados(i, 0); //Se inserta el proceso en la lista de terminados como un proceso finalizado
                    count++;
                }
            }
        }
        // Si no se encontro ningun proceso que cumpla las condiciones, el sistema no esta en estado seguro
        if (found == false) {
            countBloqueados++; //Se incrementa el contador de procesos bloqueados
            printf("Es un estado inseguro\n");
            printf("Procesos involucrados ");
            verificarBloqueados();
            imprimirRecursos();
            printf("\n");

            if(desplegarMenu(count, secuenciaSegura)>0){
                count++;
            }
        }
    }
    
    /*****************Prints finales*********************/

    // Si se recorrieron todos los procesos y el sistema estuvo en estado inseguro
    if(countBloqueados>0){ 
        printf("Hubo un estado inseguro\n\n");
    }else{ // Si se recorrieron todos los procesos y se encontraron, el sistema esta en estado seguro
        printf("Es un estado seguro\n\n");
    }

    printf("Estado de los procesos: \n\n");

    imprimirlistaTerminados();

    printf("\nOrden de asignación de recursos\n\n");
    imprimirSecuenciaSegura(secuenciaSegura);
    printf("\n");


    /*******Liberar memoria*******/ 
    free(work);
    liberarListaBloqueados();
    liberarListaTerminados();
    free(finish);

    return 1;
}