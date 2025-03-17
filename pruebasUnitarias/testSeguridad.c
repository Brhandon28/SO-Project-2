#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "../estructuras.h"
#include "../seguridad.h"

int n; // Recursos
int m; // Procesos

int *recursosTotales; // Recursos totales
int *recursosDisponibles; // Recursos disponibles (available). Tamaño n
int **matrizDeAsignacion; // Matriz de asignación (allocation). Tamaño m x n
int **matrizDeNecesidades; // Matriz de necesidades (need). Tamaño m x n
int *prioridades; // Prioridades de los recursos. Tamaño m

// Función auxiliar para inicializar las estructuras globales
void inicializarEstructurasPrueba(int recursos, int procesos) {
    n = recursos;
    m = procesos;

    recursosTotales = (int *)malloc(n * sizeof(int));
    recursosDisponibles = (int *)malloc(n * sizeof(int));
    matrizDeAsignacion = (int **)malloc(m * sizeof(int *));
    matrizDeNecesidades = (int **)malloc(m * sizeof(int *));
    prioridades = (int *)malloc(m * sizeof(int));

    for (int i = 0; i < m; i++) {
        matrizDeAsignacion[i] = (int *)malloc(n * sizeof(int));
        matrizDeNecesidades[i] = (int *)malloc(n * sizeof(int));
    }
}

// Función auxiliar para liberar las estructuras globales
void liberarEstructurasPrueba() {
    free(recursosTotales);
    free(recursosDisponibles);
    for (int i = 0; i < m; i++) {
        free(matrizDeAsignacion[i]);
        free(matrizDeNecesidades[i]);
    }
    free(matrizDeAsignacion);
    free(matrizDeNecesidades);
    free(prioridades);
}

// Prueba para estadoSeguro en un estado seguro
void test_estadoSeguro_seguro() {
    // Inicializar estructuras para la prueba
    inicializarEstructurasPrueba(3, 5);

    // Configurar recursos disponibles
    recursosDisponibles[0] = 3;
    recursosDisponibles[1] = 3;
    recursosDisponibles[2] = 2;

    // Configurar matriz de asignación
    int asignacion[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}};
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            matrizDeAsignacion[i][j] = asignacion[i][j];
        }
    }

    // Configurar matriz de necesidades
    int necesidades[5][3] = {
        {7, 4, 3},
        {1, 2, 2},
        {6, 0, 0},
        {0, 1, 1},
        {4, 3, 1}};
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            matrizDeNecesidades[i][j] = necesidades[i][j];
        }
    }

    // Liberar estructuras
    liberarEstructurasPrueba();
}

// Prueba para estadoSeguro en un estado inseguro
void test_estadoSeguro_inseguro() {
    // Inicializar estructuras para la prueba
    inicializarEstructurasPrueba(3, 3);

    // Configurar recursos disponibles
    recursosDisponibles[0] = 0;
    recursosDisponibles[1] = 0;
    recursosDisponibles[2] = 0;

    // Configurar matriz de asignación
    int asignacion[3][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrizDeAsignacion[i][j] = asignacion[i][j];
        }
    }

    // Configurar matriz de necesidades
    int necesidades[3][3] = {
        {7, 4, 3},
        {1, 2, 2},
        {6, 0, 0}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrizDeNecesidades[i][j] = necesidades[i][j];
        }
    }

    // Liberar estructuras
    liberarEstructurasPrueba();
}

int main() {
    // Inicializar el registro de pruebas
    CU_initialize_registry();

    // Crear un suite de pruebas
    CU_pSuite suite = CU_add_suite("estadoSeguro", 0, 0);

    // Agregar pruebas al suite
    CU_add_test(suite, "test_estadoSeguro_seguro", test_estadoSeguro_seguro);
    CU_add_test(suite, "test_estadoSeguro_inseguro", test_estadoSeguro_inseguro);

    // Ejecutar las pruebas
    CU_basic_run_tests();

    // Limpiar el registro de pruebas
    CU_cleanup_registry();

    return 0;
}