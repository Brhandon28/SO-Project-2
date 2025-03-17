# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -Wall -Wextra -g -I.

# Bibliotecas necesarias (en este caso, CUnit)
LIBS = -lcunit

# Archivos de pruebas
TEST_SRC = testArgumentos.c testLeerArchivos.c testOperacionesEstructuras.c testSeguridad.c

# Nombre del ejecutable de pruebas
TEST_EXEC = $(TEST_SRC:.c=)

# Regla por defecto
all: $(TEST_EXEC)

# Regla para compilar cada prueba
%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

# Regla para ejecutar las pruebas
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Regla para limpiar los archivos generados
clean:
	rm -f $(TEST_EXEC) *.o

# Regla para limpiar y recompilar las pruebas
rebuild: clean all

.PHONY: all test clean rebuild