#ifndef _OPERACIONES_H_
#define _OPERACIONES_H_
#include <stdlib.h>

/********************Operaciones para manipular las listas********************/

// Inserta un proceso en la lista de procesos terminados
void insertarTerminados(int idProceso, int fueTerminado);

// Inserta un proceso en la pila de procesos bloqueados
void insertarBloqueados(int idProceso, int prioridad); 

// Elimina un proceso de la lista de procesos bloqueados
void eliminarBloqueado(int idProceso); 

// Imprime la lista de procesos terminados y finalizados
void imprimirlistaTerminados(); 

// Imprime la lista de procesos bloqueados
void imprimirListaBloqueados(); 

// Libera la memoria de la lista de procesos terminados
void liberarListaTerminados(); 

// Libera la memoria de la lista de procesos bloqueados
void liberarListaBloqueados(); 

/*****************************************************************************/

// Imprime la secuencia segura de asignación de recursos
void imprimirSecuenciaSegura(int *secuenciaSegura);

// Imprime los recursos disponibles
void imprimirRecursos(); 

// Obtiene el id del proceso de prioridad menor de los procesos bloqueados
int prioridadMenor(); 

// Verifica si un proceso esta contenido en la pila de procesos bloqueados
int estaContenido(int idProceso); 

#endif