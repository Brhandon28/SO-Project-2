#include "operacionesEstructuras.h"
#include "estructuras.h"

struct bloqueados *listaBloqueados = NULL;
struct terminados *listaTerminados = NULL;

void insertarTerminados(int idProceso, int fueTerminado) {

    struct terminados *nuevoTerminado = (struct terminados *)malloc(sizeof(struct terminados));
    nuevoTerminado->idProceso = idProceso;
    nuevoTerminado->fueTerminado = fueTerminado;
    nuevoTerminado->siguiente = NULL;

    if (listaTerminados == NULL || idProceso < listaTerminados->idProceso) {
        nuevoTerminado->siguiente = listaTerminados;
        listaTerminados = nuevoTerminado;
        //return nuevoProceso;
    }else{
        struct terminados* actual = listaTerminados;
        while (actual->siguiente != NULL && actual->siguiente->idProceso < idProceso) {
            actual = actual->siguiente;
        }

        nuevoTerminado->siguiente = actual->siguiente;
        actual->siguiente = nuevoTerminado;
    }
}


void insertarBloqueados(int idProceso, int prioridad) {

    struct bloqueados *nuevoBloqueado = (struct bloqueados *)malloc(sizeof(struct bloqueados));
    nuevoBloqueado->idProceso = idProceso;
    nuevoBloqueado->prioridad = prioridad;
   
    if (listaBloqueados == NULL || idProceso < listaBloqueados->idProceso) {
        nuevoBloqueado->siguiente = listaBloqueados;
        listaBloqueados = nuevoBloqueado;
        
    }else{
        struct bloqueados* actual = listaBloqueados;
        while (actual->siguiente != NULL && actual->siguiente->idProceso < idProceso) {
            actual = actual->siguiente;
        }

        nuevoBloqueado->siguiente = actual->siguiente;
        actual->siguiente = nuevoBloqueado;
    }
}

void eliminarBloqueado(int idProceso){
    struct bloqueados* actual = listaBloqueados;
    struct bloqueados* anterior = NULL;

    while (actual != NULL && actual->idProceso != idProceso) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (anterior == NULL) {
        listaBloqueados = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    free(actual);
}

int prioridadMenor(){
    struct bloqueados* listRunner = listaBloqueados;
    int prioridad = 0;
    int idProceso = 0;

    while (listRunner!=NULL)
    {
        if(listRunner->prioridad > prioridad){
            prioridad = listRunner->prioridad;
            idProceso = listRunner->idProceso;
        }
        
        listRunner = listRunner->siguiente;
    }
    return idProceso;
}

int estaContenido(int idProceso){
    struct bloqueados* listRunner = listaBloqueados;

    while (listRunner!=NULL)
    {
        if(listRunner->idProceso == idProceso){
            return 1;
        }
        
        listRunner = listRunner->siguiente;
    }
    return 0;
}

void imprimirlistaTerminados(){ 

    struct terminados *impreso = listaTerminados;

    while(impreso != NULL){

        printf("P%d ", impreso->idProceso);
        if(impreso->fueTerminado == 1){
            printf("terminado\n");
        }else{
            printf("Proceso finalizado\n");
        }
        impreso = impreso->siguiente;
    }
}

void imprimirListaBloqueados(){ 

    struct bloqueados *impreso = listaBloqueados;

    while(impreso != NULL){
        printf("P%d ", impreso->idProceso);
        impreso = impreso->siguiente;
    }
}

void imprimirRecursos(){
    printf("\nRecursos disponibles: ");
    for(int i = 0; i < n; i++){
        printf("%d ", work[i]);
    }
    printf("\n");
}

void imprimirSecuenciaSegura(int *secuenciaSegura){
    struct terminados *impreso;

    for(int i = 0; i < m; i++) {
        impreso = listaTerminados;
        printf("P%d", secuenciaSegura[i]);

        while(impreso != NULL){

            if(impreso->fueTerminado == 1 && impreso->idProceso == secuenciaSegura[i]){
                printf(" terminado, ");
                break;
            }
            impreso = impreso->siguiente;
        }
        if(impreso == NULL && i != m-1){
            printf(", ");
        }else if(i == m-1){
            printf("\n");
        }
    }
}


void liberarListaTerminados(){
    struct terminados *aux = listaTerminados;
    struct terminados *borrado;
    while(aux!=NULL){
        borrado = aux;
        aux = aux->siguiente;
        free(borrado);
    }
}

void liberarListaBloqueados(){
    struct bloqueados *aux = listaBloqueados;
    struct bloqueados *borrado;
    while(aux!=NULL){
        borrado = aux;
        aux = aux->siguiente;
        free(borrado);
    }
}