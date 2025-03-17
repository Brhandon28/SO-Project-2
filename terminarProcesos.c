#include <stdlib.h>
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

//Funcion para obtener el proceso con menor prioridad
int terminarProcesoPrioridad(int count, int *secuenciaSegura) {
    
    int proceso = 0;
    proceso = prioridadMenor();

    if(finish[proceso] == false) {
        for(int i = 0; i < n; i++) {
            work[i] += matrizDeAsignacion[proceso][i];
        }
        secuenciaSegura[count] = proceso;
        finish[proceso] = true;
        eliminarBloqueado(proceso);
    }
    return proceso;
}