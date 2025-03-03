#include "seguridad.h"
#include "estructuras.h"

int estadoSeguro(int **matrizDeAsignacion, int **matrizDeNecesidades, int *recursosDisponibles)
{
    int work[n]; // Igual a recursosDisponibles
    bool finish[m];

    // Inicializar work
    for (int i = 0; i < n; i++)
    {
        work[i] = recursosDisponibles[i];
    }

    // Inicializar finish
    for (int i = 0; i < m; i++)
    {
        finish[i] = false;
    }

    int count = 0;

    while (count < m)
    {
        bool found = false;
        for (int i = 0; i < m; i++)
        {
            // Se buscan los procesos marcados con false
            if (finish[i] == false)
            {
                int j;
                for (j = 0; j < n; j++)
                {
                    // Si la necesidad es mayor que los recursos disponibles, se rompe el ciclo
                    if (matrizDeNecesidades[i][j] > work[j])
                    {
                        break;
                    }
                }
                // Si j es igual a n, significa que todos los recursos necesarios estan disponibles
                if (j == n)
                {
                    for (int k = 0; k < n; k++)
                    {
                        work[k] += matrizDeAsignacion[i][k];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        // Si no se encontro ningun proceso, el sistema no esta en estado seguro
        if (found == false)
        {
            printf("El sistema no esta en estado seguro\n");
            return 0;
        }
    }
    // Si se recorrieron todos los procesos y se encontraron, el sistema esta en estado seguro
    printf("El sistema esta en estado seguro\n");
    return 1;
}