# Simulador de Prevención de Interbloqueo (deadlock)

## Propósito

El propósito de este proyecto es desarrollar un simulador que implemente un algoritmo de
prevención de interbloqueo (deadlock) en sistemas operativos. Los objetivos específicos son:

1. **Entender** y **explicar** el funcionamiento del algoritmo de prevención de interbloqueo.
2. **Diseñar** y **programar** un simulador que permita visualizar el proceso de prevención de interbloqueo.
3. **Probar** el simulador con diferentes escenarios para verificar su correcto funcionamiento.
4. **Documentar** el diseño y el uso del simulador.

## Consideraciones de implementación

El formato de ejecución de su programa debe ser el siguiente:
    ./prevencion < nombreDelArchivo >

El archivo contiene un snapshot del flujo de recursos y ejecución de N cantidad de procesos,
dicho archivo está definido por el siguiente formato:

1. N recursos
2. Vector recursos totales, este vector tiene el tamaño de N
3. Vector recursos disponibles, este vector tiene el tamaño de N
4. M procesos – Nombrar todos por P, los números van del [0,M-1]
5. Recursos asignados | Recursos necesarios para ejecución | Prioridad
Donde la prioridad va del 1 hasta el 10 siendo 1 mayor prioridad que 10

**Salida:**
Si el algoritmo encuentra un estado inseguro y no puede continuar su ejecución, va a imprimir
los procesos que faltan por finalizar, Ejemplo:


    Es un estado inseguro
    Procesos involucrados P1 P3 P4
    Recursos disponibles 2 3 1


Para este algoritmo del banquero modificado, en este estado inseguro, se debe dar la opción al usuario de finalizar el algoritmo o terminar los procesos 1 a 1 hasta tener los recursos suficientes para continuar con el algoritmo, por cada proceso terminado continuar con el algoritmo y la asignación de recursos, hasta que todos los procesos finalicen, los procesos terminados a la fuerza deben ser clasificados como procesos terminados.

Implementar alguno de estos tres criterios para elegir un proceso a terminar y apropiarse de sus
recursos:

- Aleatorio
- Prioridad, donde se termina el proceso con menor prioridad.
- Selectivo, donde 0 es el proceso 0, 1 es el proceso 1 2 es el proceso 2...

Si el algoritmo termina y encuentra un estado seguro, imprimir el posible orden de ejecución de los procesos y asignación de recursos. Por cada proceso debe imprimir su estado si finalizo su ejecución o fue terminado para apropiarse de sus recursos. Ejemplo:


    Es un estado seguro
    Estado de los procesos:
    P0 Finalizado
    P1 Finalizado
    P2 Finalizado
    P3 Finalizado
    P4 Finalizado
    Orden de asignación de recursos:
    P2, P0, P1, P3, P4


Si el algoritmo tuvo que terminar procesos para finalizar su ejecucion, tiene que indicarse qué
procesos fueron terminados para continuar con la ejecución del algoritmo, en el orden de
asignación de recursos en el que se tomó la decisión de terminarlos, ejemplo:


    Hubo un estado inseguro
    Estado de los procesos:
    P0 Terminado
    P1 Finalizado
    P2 Finalizado
    P3 Terminado
    P4 Finalizado
    Orden de asignación de recursos:
    P2, P3 Terminado, P0 Terminado, P1, P4

