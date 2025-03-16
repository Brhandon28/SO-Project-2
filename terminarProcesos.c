#include <stdlib.h>
//#include "seguridad.h"
#include "terminarProcesos.h"
#include "estructuras.h"
#include "operacionesEstructuras.h"
#include <time.h>

//Funcion que verifica si un proceso esta contenido en la lista de bloqueados
void verificarBloqueados() {
    int *bloqueados = (int *)malloc(m * sizeof(int));
    for(int i = 0; i < m; i++) {
        if(finish[i] == false) {
            if(estaContenido(i) != 1) {
                insertarBloqueados(i, prioridades[i]);
            }
        }
    }
    imprimirListaBloqueados();
}

//Funcion para terminar un proceso aleatorio
int terminarProcesoAleatorio(int count, int *secuenciaSegura) {
    
    srand(time(NULL));

    // Seleccionar un número aleatorio del conjunto de procesos
    int procesoAleatorio = rand() % m;

    if(finish[procesoAleatorio] == false) {
        printf("\nProceso P%d terminado\n", procesoAleatorio);
        for(int i = 0; i < n; i++) {
            work[i] += matrizDeAsignacion[procesoAleatorio][i];
        }
        secuenciaSegura[count] = procesoAleatorio;
        finish[procesoAleatorio] = true;
        eliminarBloqueado(procesoAleatorio);
        return procesoAleatorio;

    }else{
        printf("\nProceso P%d ya terminado\n", procesoAleatorio);
    }
    return -1;
}

//Funcion para obtener el proceso con menor prioridad
int terminarProcesoPrioridad(int count, int *secuenciaSegura) {
    
    int proceso = 0;
    proceso = prioridadMenor();

    if(finish[proceso] == false) {
        printf("\nProceso P%d terminado\n", proceso);
        for(int i = 0; i < n; i++) {
            work[i] += matrizDeAsignacion[proceso][i];
        }
        secuenciaSegura[count] = proceso;
        finish[proceso] = true;
        eliminarBloqueado(proceso);
    }
    return proceso;
}

//Funcion para terminar un proceso seleccionado
int terminarProcesoSeleccionado(int proceso, int count, int *secuenciaSegura) {
    if(finish[proceso] == false) {
        printf("\nProceso P%d terminado\n", proceso);
        for(int i = 0; i < n; i++) {
            work[i] += matrizDeAsignacion[proceso][i];
        }
        secuenciaSegura[count] = proceso;
        finish[proceso] = true;
        eliminarBloqueado(proceso);
    }else{
        printf("\nProceso P%d ya ha finalizado su ejecucion\n", proceso);
        return 0;
    } 
    return 1;
}