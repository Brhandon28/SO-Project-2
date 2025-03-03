#ifndef _ARGUMENTOS_H_
#define _ARGUMENTOS_H_

#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


/***********************VERIFICAR ARGUMENTOS*************************/
void identificar_argumentos(int argc, char *argv[]);
int es_archivo_valido(const char *ruta);
/********************************************************************/

#endif