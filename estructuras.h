#ifndef _ESTRUCTURAS_H_
#define _ESTRUCTURAS_H_

#include <stdio.h>
#include <stdbool.h>

extern int n; // Recursos
extern int m; // Procesos

extern int *recursosTotales; // Recursos totales
extern int *recursosDisponibles; // Recursos disponibles (available). Tamaño n
extern int **matrizDeAsignacion; // Matriz de asignación (allocation). Tamaño m x n
extern int **matrizRecursosTotales; // Matriz de recursos totales (max). Tamaño m x n
extern int **matrizDeNecesidades; // Matriz de necesidades (need). Tamaño m x n
extern int *prioridades; // Prioridades de los recursos. Tamaño m

extern int *work; // Igual a recursosDisponibles
extern bool *finish; // Tamaño m

extern int *secuenciaSegura; // Arreglo que indica la secuencia de ejecucion que mantiene el estado seguro

#endif