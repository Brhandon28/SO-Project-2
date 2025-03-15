#ifndef _BLOQUEADOS_H_
#define _BLOQUEADOS_H_
#include <stdlib.h>
//#include "seguridad.h"
#include "estructuras.h"

void verificarBloqueados();
int terminarProcesoSeleccionado(int proceso);
int terminarProcesoPrioridad(int proceso);
int terminarProcesoAleatorio(int proceso);

#endif