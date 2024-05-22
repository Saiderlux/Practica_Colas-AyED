/*
AUTOR: Edgardo Adrián Franco Martínez (C) Septiembre 2012
VERSIÓN: 1.3
MODIFICADO POR: Claude (Anthropic)

DESCRIPCIÓN: Simulación de una tienda con 5 cajas para atender a 100 clientes por sesión.
Los tiempos de atención de las cajas son: 20, 30, 50, 70 y 100 milisegundos.
Los clientes llegan cada 50 milisegundos.
Si ya se han atendido 100 clientes pero aún faltan por atender, estos se atenderán hasta que se terminen todos los clientes.
*/

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "TADColaDin.h"

#define TIEMPO_BASE 50         // Tiempo base en ms
#define TIEMPO_CLIENTE 1       // Tiempo base en ms * 1 (50 ms)
#define NUM_CAJAS 5            // Número de cajas
#define MAX_CLIENTES 100       // Máximo número de clientes por sesión
#define MAX_FILA 10            // Máximo número de clientes a mostrar en cada fila

int AllEmpty(cola *cajas, int num_cajas);
void moverCursor(int x, int y);
void imprimirFilas(cola *cajas);

int main(void)
{
    unsigned int tiempo = 0;
    unsigned int cliente = 1;
    unsigned int clientes_atendidos = 0;
    int i, fila;
    elemento e;
    srand(time(NULL));

    // Tiempos de atención de las cajas en ms
    int tiempos_atencion[] = {20, 30, 50, 70, 100};

    // Crear las colas para las cajas
    cola cajas[NUM_CAJAS];

    // Inicializar las colas
    for (i = 0; i < NUM_CAJAS; i++)
    {
        Initialize(&cajas[i]);
    }

    // Encabezado de la tabla
    printf("     ┌───────────┬───────────┬───────────┬───────────┬───────────┐\n");
    printf("     │   Caja 0  │   Caja 1  │   Caja 2  │   Caja 3  │   Caja 4  │\n");
    printf("     ├───────────┼───────────┼───────────┼───────────┼───────────┤\n");

    // Ciclo principal
    while (clientes_atendidos < MAX_CLIENTES || !AllEmpty(cajas, NUM_CAJAS))
    {
        Sleep(TIEMPO_BASE);
        tiempo++;

        // Atender a los clientes en las cajas
        for (i = 0; i < NUM_CAJAS; i++)
        {
            if (tiempo % tiempos_atencion[i] == 0)
            {
                if (!Empty(&cajas[i]))
                {
                    e = Dequeue(&cajas[i]);
                    clientes_atendidos++;
                    if (clientes_atendidos > MAX_CLIENTES)
                    {
                        cliente = 1; // Reiniciar el contador de clientes
                    }
                }
            }
        }

        // Llegada de nuevos clientes
        if (tiempo % TIEMPO_CLIENTE == 0 && clientes_atendidos < MAX_CLIENTES)
        {
            e.n = cliente++;
            fila = rand() % NUM_CAJAS;
            Queue(&cajas[fila], e);
        }

        // Mover el cursor y actualizar las filas
        moverCursor(0, 3);
        imprimirFilas(cajas);
    }

    return 0;
}

// Función auxiliar para verificar si todas las colas están vacías
int AllEmpty(cola *cajas, int num_cajas)
{
    int i;
    for (i = 0; i < num_cajas; i++)
    {
        if (!Empty(&cajas[i]))
        {
            return 0; // Al menos una cola no está vacía
        }
    }
    return 1; // Todas las colas están vacías
}

// Función para mover el cursor en la consola
void moverCursor(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Función para imprimir las filas de los cajeros
void imprimirFilas(cola *cajas)
{
    int i, j;
    elemento e;

    for (i = 0; i < NUM_CAJAS; i++)
    {
        printf("     │");
        for (j = 1; j <= Size(&cajas[i]) && j <= MAX_FILA; j++)
        {
            e = Element(&cajas[i], j);
            printf(" %3d ", e.n);
        }
        if (j <= Size(&cajas[i]))
        {
            printf(" +%d", Size(&cajas[i]) - MAX_FILA);
        }
        for (int k = j - 1; k < MAX_FILA; k++)
        {
            printf("     ");
        }
        printf("│");
        printf("\n");
    }
    printf("     └───────────┴───────────┴───────────┴───────────┴───────────┘\n");
}