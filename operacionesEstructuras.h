#ifndef _OPERACIONES_H_
#define _OPERACIONES_H_

#include <stdlib.h>

void insertarTerminados(int idProceso, int fueTerminado);// Inserta un proceso en la pila de procesos terminados
void insertarBloqueados(int idProceso, int prioridad); // Inserta un proceso en la pila de procesos bloqueados
void eliminarBloqueado(int idProceso); // Elimina un proceso de la lista de procesos bloqueados
void imprimirlistaTerminados(); // Imprime la lista de procesos terminados y finalizados
void imprimirListaBloqueados(); // Imprime la pila de procesos bloqueados
void imprimirSecuenciaSegura(int *secuenciaSegura); // Imprime la secuencia segura de asignación de recursos
void imprimirRecursos(); // Imprime los recursos disponibles
int prioridadMenor(); // Obtiene el id del proceso de prioridad menor de los procesos bloqueados
int estaContenido(int idProceso); // Verifica si un proceso esta contenido en la pila de procesos bloqueados
void liberarListaTerminados(); // Libera la memoria de la pila de procesos terminados
void liberarListaBloqueados(); // Libera la memoria de la pila de procesos bloqueados

#endif