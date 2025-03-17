#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

int es_archivo_valido(const char *ruta) {
    struct stat info;

    if (stat(ruta, &info) != 0) {
        // Error al obtener información del archivo
        if (errno == ENOENT) {
          fprintf(stderr,"Error: El archivo no existe\n");
        } else if(errno == EACCES){
          fprintf(stderr,"Error: No tienes permisos para acceder a este archivo\n");
        } else {
          fprintf(stderr,"Error desconocido al acceder al archivo\n");
        }
        return 0; // No es un archivo válido
    }

    if (S_ISREG(info.st_mode)) {
        return 1; // Es un archivo regular
    } else {
        fprintf(stderr,"Error: La ruta proporcionada no es un archivo\n");
        return 0; // No es un archivo
    }
}

// ./prevencion <nombre del archivo>
int identificar_argumentos(int argc, char *argv[]) {

    //Comprobar que hay máximo 2 argumentos
    if(argc > 2) {
        printf("Hay muchos argumentos\n");
        printf("Usa: %s -m d <nombre del archivo>\n", argv[0]);
        return 1;
    } 
    //Comprobar que hay mínimo 2 argumentos
    else if(argc < 2) { 
        printf("Faltan argumentos\n");
        printf("Usa: %s -m d <nombre del archivo>\n", argv[0]);
        return 1;
    }

    //Comprobacion segundo argumento
    if(es_archivo_valido(argv[1]) == 0) {
        return 1;
    }
}

// Función para inicializar la suite de pruebas
int init_suite(void) {
    return 0;
}

// Función para limpiar la suite de pruebas
int clean_suite(void) {
    return 0;
}

// Prueba para verificar que un archivo existente es válido
void test_es_archivo_valido_existente(void) {
    const char *ruta = "../Pruebas/safeCase.txt"; // Crear un archivo de prueba
    FILE *file = fopen(ruta, "w");
    fclose(file);

    CU_ASSERT(es_archivo_valido(ruta) == 1);

    remove(ruta); // Eliminar el archivo de prueba
}

// Prueba para verificar que un archivo inexistente no es válido
void test_es_archivo_valido_inexistente(void) {
    const char *ruta = "archivo_inexistente.txt";
    CU_ASSERT(es_archivo_valido(ruta) == 0);
}

// Prueba para verificar que un directorio no es un archivo válido
void test_es_archivo_valido_directorio(void) {
    const char *ruta = "testdir";
    mkdir(ruta, 0777);

    CU_ASSERT(es_archivo_valido(ruta) == 0);

    rmdir(ruta); // Eliminar el directorio de prueba
}

// Prueba para verificar que identificar_argumentos maneja correctamente el número de argumentos
void test_identificar_argumentos_numero_argumentos(void) {
    char *argv1[] = {"./prevencion", "archivo.txt"};
    CU_ASSERT(identificar_argumentos(2, argv1) == 0);

    char *argv2[] = {"./prevencion"};
    CU_ASSERT(identificar_argumentos(1, argv2) == 1);

    char *argv3[] = {"./prevencion", "archivo1.txt", "archivo2.txt"};
    CU_ASSERT(identificar_argumentos(3, argv3) == 1);
}

// Función principal para ejecutar las pruebas
int main() {
    CU_pSuite pSuite = NULL;

    // Inicializar el registro de pruebas
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Añadir una suite al registro
    pSuite = CU_add_suite("Suite de pruebas", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Añadir las pruebas a la suite
    if ((NULL == CU_add_test(pSuite, "test_es_archivo_valido_existente", test_es_archivo_valido_existente)) ||
        (NULL == CU_add_test(pSuite, "test_es_archivo_valido_inexistente", test_es_archivo_valido_inexistente)) ||
        (NULL == CU_add_test(pSuite, "test_es_archivo_valido_directorio", test_es_archivo_valido_directorio)) ||
        (NULL == CU_add_test(pSuite, "test_identificar_argumentos_numero_argumentos", test_identificar_argumentos_numero_argumentos))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Ejecutar todas las pruebas
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}