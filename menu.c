#include "menu.h"
#include "estructuras.h"
#include "operacionesEstructuras.h"
#include "terminarProcesos.h"

int desplegarMenu(int count, int* secuenciaSegura){

    printf("\n1. Terminar el programa\n");
    printf("2. Resolver el conflicto\n");
    printf("\nSeleccione una opcion: "); 

    char opcion[10];
    char proceso[10];

    fgets(opcion, 10, stdin);

    switch(opcion[0]){
        case '1': //Terminar proceso aleatorio

            printf("\nAlgoritmo finalizado\n\n");
            exit(0);
        break;
        case '2': //Terminar proceso con prioridad menor

            //obtenemos el id del proceso con prioridad menor
            if(terminarProcesoPrioridad(count, secuenciaSegura)){
                return 1;
            }
        break;
        default:
            printf("Opcion no valida\n");
        break;
    }

    return 0;
}