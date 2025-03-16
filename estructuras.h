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

//Estructura de datos de tipo pila que contendra los procesos bloqueados
struct bloqueados{
    int idProceso;
    int prioridad;
    struct bloqueados *siguiente;
};

//Estructura de datos de tipo pila que contendra los procesos terminados
struct terminados{
    int idProceso;
    int fueTerminado;
    struct terminados *siguiente;
};

extern struct bloqueados *listaBloqueados;
extern struct terminados *listaTerminados;

extern int *secuenciaSegura; // Arreglo que indica la secuencia de asignacion de recursos segura

#endif