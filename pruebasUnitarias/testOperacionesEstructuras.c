#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
// #include "../operacionesEstructuras.h"
#include "../estructuras.h"

int m, n, *work;

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
            printf("Terminado\n");
        }else{
            printf("Finalizado\n");
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
                printf(" Terminado, ");
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

// Prueba para insertarBloqueados
void test_insertarBloqueados() {
    // Inicializar lista de bloqueados
    listaBloqueados = NULL;

    // Insertar procesos bloqueados
    insertarBloqueados(1, 5);
    insertarBloqueados(2, 3);

    // Verificar que los procesos se insertaron correctamente
    CU_ASSERT_PTR_NOT_NULL(listaBloqueados);
    CU_ASSERT_EQUAL(listaBloqueados->idProceso, 2);
    CU_ASSERT_EQUAL(listaBloqueados->prioridad, 3);
    CU_ASSERT_EQUAL(listaBloqueados->siguiente->idProceso, 1);
    CU_ASSERT_EQUAL(listaBloqueados->siguiente->prioridad, 5);

    // Liberar lista de bloqueados
    liberarListaBloqueados();
}

// Prueba para insertarTerminados
void test_insertarTerminados() {
    // Inicializar lista de terminados
    listaTerminados = NULL;

    // Insertar procesos terminados
    insertarTerminados(1, 1);
    insertarTerminados(2, 0);

    // Verificar que los procesos se insertaron correctamente
    CU_ASSERT_PTR_NOT_NULL(listaTerminados);
    CU_ASSERT_EQUAL(listaTerminados->idProceso, 2);
    CU_ASSERT_EQUAL(listaTerminados->fueTerminado, 0);
    CU_ASSERT_EQUAL(listaTerminados->siguiente->idProceso, 1);
    CU_ASSERT_EQUAL(listaTerminados->siguiente->fueTerminado, 1);

    // Liberar lista de terminados
    liberarListaTerminados();
}

// Prueba para eliminarBloqueado
void test_eliminarBloqueado() {
    // Inicializar lista de bloqueados
    listaBloqueados = NULL;
    insertarBloqueados(1, 5);
    insertarBloqueados(2, 3);

    // Eliminar un proceso bloqueado
    eliminarBloqueado(1);

    // Verificar que el proceso se eliminó correctamente
    CU_ASSERT_PTR_NOT_NULL(listaBloqueados);
    CU_ASSERT_EQUAL(listaBloqueados->idProceso, 2);
    CU_ASSERT_PTR_NULL(listaBloqueados->siguiente);

    // Liberar lista de bloqueados
    liberarListaBloqueados();
}

// Prueba para prioridadMenor
void test_prioridadMenor() {
    // Inicializar lista de bloqueados
    listaBloqueados = NULL;
    insertarBloqueados(1, 5);
    insertarBloqueados(2, 3);
    insertarBloqueados(3, 1);

    // Verificar que se obtiene el proceso con menor prioridad
    CU_ASSERT_EQUAL(prioridadMenor(), 3);

    // Liberar lista de bloqueados
    liberarListaBloqueados();
}

// Prueba para estaContenido
void test_estaContenido() {
    // Inicializar lista de bloqueados
    listaBloqueados = NULL;
    insertarBloqueados(1, 5);
    insertarBloqueados(2, 3);

    // Verificar si un proceso está contenido en la lista
    CU_ASSERT_EQUAL(estaContenido(1), 1);
    CU_ASSERT_EQUAL(estaContenido(2), 1);
    CU_ASSERT_EQUAL(estaContenido(3), 0);

    // Liberar lista de bloqueados
    liberarListaBloqueados();
}

int main() {
    // Inicializar el registro de pruebas
    CU_initialize_registry();

    // Crear un suite de pruebas
    CU_pSuite suite = CU_add_suite("operacionesEstructuras", 0, 0);

    // Agregar pruebas al suite
    CU_add_test(suite, "test_insertarBloqueados", test_insertarBloqueados);
    CU_add_test(suite, "test_insertarTerminados", test_insertarTerminados);
    CU_add_test(suite, "test_eliminarBloqueado", test_eliminarBloqueado);
    CU_add_test(suite, "test_prioridadMenor", test_prioridadMenor);
    CU_add_test(suite, "test_estaContenido", test_estaContenido);

    // Ejecutar las pruebas
    CU_basic_run_tests();

    // Limpiar el registro de pruebas
    CU_cleanup_registry();

    return 0;
}