#include "leerArchivos.h"
#include "argumentos.h"
#include "seguridad.h"
#include "menu.h"

int main(int argc, char *argv[]) {
    identificar_argumentos(argc, argv);
    es_archivo_valido(argv[1]);
    leerArchivos(argc, argv);

    return 0;
}