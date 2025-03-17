#ifndef _BLOQUEADOS_H_
#define _BLOQUEADOS_H_
#include <stdlib.h>

//Verifica si un proceso esta contenido en la lista de bloqueados y lo inserta si no lo esta
void verificarBloqueados();

/*********************Criterio para terminar los proceso*********************/

//termina el proceso con menor prioridad
int terminarProcesoPrioridad(int count, int *secuenciaSegura); //termina el proceso con menor prioridad

/****************************************************************************/ 


#endif