#ifndef _ESTRUCTURAS_H_
#define _ESTRUCTURAS_H_ 

#include <stdio.h>


int n = 0; //Recursos
int m = 0; //Procesos

int *recursosTotales; //Recursos totales 

int *recursosDisponibles; //Recursos disponibles (available). Tamano n
int **matrizDeAsignacion; //Matriz de asignacion (allocation). Tamano m x n
int **matrizRecursosTotales; //Matriz de recursos totales (max). Tamano m x n
int **matrizDeNecesidades; //Matriz de necesidades (need). Tamano m x n
int *prioridades; //Prioridades de los recursos. Tamano m

#endif 