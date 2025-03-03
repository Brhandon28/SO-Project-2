#include "leerArchivos.h"
#include "argumentos.h"

int main(int argc, char *argv[]) {
    identificar_argumentos(argc, argv);
    es_archivo_valido(argv[3]);
    leerArchivos(argc, argv);
    return 0;
}