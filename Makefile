TARGET = main
SRC = main.c leerArchivos.c argumentos.c seguridad.c
OBJ = $(SRC:.c=.o)
INCLUDE = argumentos.h leerArchivos.h estructuras.h seguridad.h
CFLAGS = -g 
LDLIBS = -pthread -lm
CC = gcc

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDLIBS) $(OBJ) -o $(TARGET) 

%.o: %.c $(INCLUDE) 
	$(CC) -c $(LDLIBS) -o $@ $< 

.PHONY: clean
clean:
	@rm -f *.o $(TARGET)