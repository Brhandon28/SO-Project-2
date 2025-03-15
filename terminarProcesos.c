#include <stdlib.h>
//#include "seguridad.h"
#include "estructuras.h"

void verificarBloqueados() {
    for(int i = 0; i < m; i++) {
        if(finish[i] == false) {
            printf("Proceso P%d bloqueado\n", i);
        }
    }
}