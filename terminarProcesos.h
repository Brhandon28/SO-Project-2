#ifndef _BLOQUEADOS_H_
#define _BLOQUEADOS_H_
#include <stdlib.h>
//#include "seguridad.h"

void verificarBloqueados();
int terminarProcesoAleatorio(int count, int *secuenciaSegura);
int terminarProcesoPrioridad(int count, int *secuenciaSegura);
int terminarProcesoSeleccionado(int proceso, int count, int *secuenciaSegura); 


#endif