#include "TADColaDin.h"
#include <stdio.h>
#include <windows.h>

// Declarar las colas globales
cola listos, ejecucion, terminados;

// Función para ingresar un nuevo proceso
void ingresar_proceso(cola *c) {
    proceso p;
    printf("Ingrese el nombre del proceso: ");
    scanf("%s", p.nombre);
    printf("Ingrese el ID del proceso: ");
    scanf("%s", p.id);
    printf("Ingrese la descripción del proceso: ");
    scanf(" %[^\n]s", p.descripcion);
    printf("Ingrese el tiempo de ejecución del proceso (en segundos): ");
    scanf("%d", &p.tiempo_ejecucion);
    Queue(c, p);
}

// Función para imprimir las colas
void imprimir_colas() {
    printf("Cola de listos:\n");
    for (int i = 1; i <= Size(&listos); i++) {
        proceso p = Element(&listos, i);
        printf("%s %s\n", p.id, p.nombre);
    }

    printf("\nCola de ejecución:\n");
    for (int i = 1; i <= Size(&ejecucion); i++) {
        proceso p = Element(&ejecucion, i);
        printf("%s %s (Tiempo restante: %d)\n", p.id, p.nombre, p.tiempo_ejecucion);
    }

    printf("\nCola de terminados:\n");
    for (int i = 1; i <= Size(&terminados); i++) {
        proceso p = Element(&terminados, i);
        printf("%s %s\n", p.id, p.nombre);
    }
    printf("\n");
}

int main() {
    // Inicializar las colas
    Initialize(&listos);
    Initialize(&ejecucion);
    Initialize(&terminados);

    // Ingresar los procesos
    int mas_procesos = 1;
    while (mas_procesos) {
        ingresar_proceso(&listos);
        printf("¿Ingresar otro proceso? (1 = Sí, 0 = No): ");
        scanf("%d", &mas_procesos);
    }

    // Ciclo principal de ejecución
    while (!Empty(&listos) || !Empty(&ejecucion)) {
        // Despachar un proceso de la cola de listos a la cola de ejecución
        if (!Empty(&listos)) {
            proceso p = Dequeue(&listos);
            Queue(&ejecucion, p);
            printf("Proceso %s %s despachado a ejecución\n", p.id, p.nombre);
        }

        // Ejecutar los procesos de la cola de ejecución
        if (!Empty(&ejecucion)) {
            for (int i = 1; i <= Size(&ejecucion); i++) {
                proceso p = Element(&ejecucion, i);
                printf("Proceso %s %s en ejecución\n", p.id, p.nombre);
                p.tiempo_ejecucion--;
                if (p.tiempo_ejecucion == 0) {
                    printf("Proceso %s %s terminado\n", p.id, p.nombre);
                    Queue(&terminados, p);
                    Dequeue(&ejecucion);
                }
            }
        }

        // Imprimir las colas
        imprimir_colas();
        Sleep(1000); // Esperar 1 segundo antes de la siguiente iteración
    }

    // Liberar las colas
    Destroy(&listos);
    Destroy(&ejecucion);
    Destroy(&terminados);

    return 0;
}