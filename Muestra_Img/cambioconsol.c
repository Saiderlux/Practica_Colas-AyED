#include <Windows.h>
#include <stdio.h>
#include "cambioconsol.h"
#include <stdlib.h>

void cambiarTamanoConsola(int ancho, int alto) {

    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    SMALL_RECT rect;

    coord.X = ancho;
    coord.Y = alto;

    if (!SetConsoleScreenBufferSize(consola, coord)) {
        printf("Error al establecer el tamaño del buffer de pantalla.\n");
        return;
    }

    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = alto - 1;
    rect.Right = ancho - 1;

    if (!SetConsoleWindowInfo(consola, TRUE, &rect)) {
        printf("Error al establecer el tamaño de la ventana de la consola.\n");
        return;
    }

    printf("Tamaño de la consola cambiado a %d x %d\n", ancho, alto);
}
