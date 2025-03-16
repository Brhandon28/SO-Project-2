#include "menu.h"
#include "estructuras.h"
#include "operacionesEstructuras.h"
#include "terminarProcesos.h"

int desplegarMenu(int count, int* secuenciaSegura){

    printf("\n1. Terminar proceso aleatorio\n");
    printf("2. Terminar proceso por prioridad\n");
    printf("3. Terminar proceso seleccionado\n");
    printf("4. Salir\n");
    printf("\nSeleccione una opcion: "); 

    char opcion[10];
    char proceso[10];

    int idAleatorio;
    int idPrioridad;

    fgets(opcion, 10, stdin);

    switch(opcion[0]){
        case '1': //Terminar proceso aleatorio

            //Obtenemos el id del proceso aleatorio
            idAleatorio = terminarProcesoAleatorio(count, secuenciaSegura);
            //verificamos si el id es mayor o igual a 0, insertamos el proceso en la lista de terminados
            if(idAleatorio >= 0){
                insertarTerminados(idAleatorio, 1);  
                return 1;
            }

        break;
        case '2': //Terminar proceso con prioridad menor

            //obtenemos el id del proceso con prioridad menor
            idPrioridad = terminarProcesoPrioridad(count, secuenciaSegura);
            //insertamos el proceso en la lista de terminados
            insertarTerminados(idPrioridad, 1);  
            return 1;

        break;
        case '3': //Terminar proceso seleccionado
        
            printf("Ingrese el proceso a terminar: ");
            //Obtenemos desde la entrada estandar el proceso a terminar
            fgets(proceso, 10, stdin);
            //verificamos que el proceso sea un id valido
            while(atoi(proceso)<0 || atoi(proceso)>=m){
                printf("No es un id de proceso, intente de nuevo ");
                fgets(proceso, 10, stdin);
            }
            //terminamos el proceso dado por el usuario
            if(terminarProcesoSeleccionado(atoi(proceso), count, secuenciaSegura)){
                insertarTerminados(atoi(proceso), 1);  
                return 1;
            }

        break;
        case '4':
            exit(0);
        break;
        default:
            printf("Opcion no valida\n");
        break;
    }

    return 0;
}