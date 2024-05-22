/*
Ejecucion:
gcc Cajeras.c formato.c presentacionWin/Lin.c TadColaDin.c -o cajeras

Ya funciona(en teoria), solo falta la condición de término, solo que
	no entiendo si cuando llegue a minimo 100 personas dejaran de llegar
	personas o ya después de las 100 personas esperemos hasta que esten vacias las colas
	y terminamos el "dia"
	
Otra cosa esto es solo la logica de como podría funcionar solo faltaría que se vea bien
*/

//LIBRERAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include "TADCola/TADColaEst.h" 	//Si se usa la implemtentación dinámica (TADColaDin.c)
#include "TADColaDin.h" 	//Si se usa la implemtentación estática (TADColaEst.c|TADColaEstCirc.c)
#include "formato.h"
#include "presentacion.h"

// DEFINICIÓN DE CONSTANTES
#define TIEMPO_BASE 200 // Tiempo base en ms
#define MAX_CLIENTES 100 // Cantidad máxima de clientes
int main(void)
{
    char nombre[100];
    int n, tiempo_cliente;
    unsigned int tiempo = 0;
    unsigned int cliente = 0;
    int i, fila;
    elemento e;
    printf("Ingresa el nombre del supermercado: ");
    scanf("%s", nombre);
    printf("Ingresa la cantidad de cajas: ");
    scanf("%d", &n);
    // Variables dependientes de n
    int tiempos_atencion[n];
    // Crear n colas
    cola cajera[n];
    printf("Ingresa el tiempo en atender de cada caja: \n");
    for (i = 0; i < n; i++) {
        printf("%d: ", i + 1);
        scanf("%d", &tiempos_atencion[i]);
        Initialize(&cajera[i]);
    }
    printf("Ingresa el tiempo de llegada de los clientes ms: ");
    scanf("%d", &tiempo_cliente);
    // Inicializar la función rand
    srand(time(NULL));

    BorrarPantalla();
    imprimirFilasInicio(cajera, n); // Imprimir las filas iniciales

    // Ciclo principal
    while (cliente < MAX_CLIENTES)
    {
        EsperarMiliSeg(TIEMPO_BASE); // Esperar el tiempo base
        tiempo++;                    // Incrementar el contador de tiempo

        // Atender clientes
        for (i = 0; i < n; i++) {
            if (tiempo % (tiempos_atencion[i] / 10) == 0) { // se divide sobre 10 ya que tiene que ser un múltiplo de 10
                if (!Empty(&cajera[i]))
                {
                    e = Dequeue(&cajera[i]);
                    Desencolar(&cajera[i], i + 1);
                }
            }
        }

        // Llegada de clientes
        if (tiempo % (tiempo_cliente / 10) == 0)
        {
            cliente++;                         // Incrementar el número de clientes
            e.n = cliente;                     // Dar el número que identifica al cliente
            fila = rand() % n;                 // Escoger la fila para formarse aleatoriamente
            Queue(&cajera[fila], e);           // Formarse en la fila seleccionada
            Encolar(&cajera[fila], fila + 1);
        }

        imprimirFilas(cajera, n); // Imprimir las filas actualizadas
    }

    printf("Se ha alcanzado el máximo de clientes (%d). Esperando a que se vacíen las filas...\n", MAX_CLIENTES);
    while (1) {
        EsperarMiliSeg(TIEMPO_BASE); // Esperar el tiempo base
        tiempo++;                    // Incrementar el contador de tiempo

        int filas_vacias = 1; // Suponer que todas las filas están vacías

        // Atender clientes
        for (i = 0; i < n; i++) {
            if (tiempo % (tiempos_atencion[i] / 10) == 0) { // se divide sobre 10 ya que tiene que ser un múltiplo de 10
                if (!Empty(&cajera[i]))
                {
                    e = Dequeue(&cajera[i]);
                    Desencolar(&cajera[i], i + 1);
                    filas_vacias = 0; // Al menos una fila no está vacía
                }
            }
        }

        imprimirFilas(cajera, n); // Imprimir las filas actualizadas

        if (filas_vacias) {
            printf("Todas las filas están vacías. Fin del día.\n");
            break;
        }
    }

    return 0;
}