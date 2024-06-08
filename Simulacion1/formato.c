/*
Formato de la simulación 1: Supermercado
AUTOR: 
VERSIÓN: 1.0

DESCRIPCIÓN: Funciones necesarias para mostrar de manera agradable el Queue y
	Dequeue de elementos en las colas
	
OBSERVACIONES: Se hace uso de caracteres especiales
*/

// LIBRERÍAS
#include <string.h>
#include "TADColaDin.h"
//#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "formato.h"
#include "presentacion.h"

// DEFINICIONES DE CONSTANTES
#define TRUE	1
#define FALSE	0
#define DEFAULT	5
#define TAM_FILA	2
#define INICIO_Y 5

// DEFINICIONES DE TIPOS DE DATO
typedef unsigned char boolean;

// Secuencias de escape ANSI para colores
#define COLOR_RESET   "\x1b[0m"
#define COLOR_CLIENTE_NO_ATENDIDO "\x1b[31m" // Rojo
#define COLOR_CLIENTE_ATENDIDO "\x1b[32m" // Verde

/*
void Encolar(cola *c, int x);
Descripción: Imprimir el último elemento agregado a la cola
Recibe: cola *c (apuntador a la cola en que se agregó un elemento), int x (posición en x de esa cola)
Devuelve: void
Observaciones: La cola ya debe estar inicializada, la función depende de constantes como lo son:
	DEFAULT (número de elementos que se mostraran), TAM_FILA (posición en y que se movera tras agregar
	un nuevo elemento), INICIO_Y (posición en y a partir de la cual se empezaran a imprimir los elementos)
*/
void Encolar(cola *c, int x) {
    int tamano = Size(c);
    char aux[100], resultado_str[20];
    int y = INICIO_Y;

    limpiarCola(x);  // Limpiar la cola para actualizar los colores correctamente

    if (tamano < DEFAULT) {
        for (int i = 1; i <= tamano; i++) {
            y += TAM_FILA;
            sprintf(aux, "%d", Element(c, i).n);
            if (i == 1) {
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2)-2, y, COLOR_CLIENTE_ATENDIDO, "💵");
            } else {
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2)-2, y, COLOR_CLIENTE_NO_ATENDIDO, "🛒");
            }
        }
    } else {
        for (int i = 1; i < DEFAULT; i++) {
            y += TAM_FILA;
            sprintf(aux, "%d", Element(c, i).n);
            if (i == 1) {
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2)-2, y, COLOR_CLIENTE_ATENDIDO, "💵");
            } else {
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2)-2, y, COLOR_CLIENTE_NO_ATENDIDO, "🛒");
            }
        }
        int resultado = tamano - DEFAULT + 1;
        sprintf(resultado_str, "%d", resultado);
        strcpy(aux, "+ ");
        strcat(aux, resultado_str);
        MoverCursor(x - ((int)strlen(aux) / 2)-1, y + TAM_FILA);
        printf("%s%s%s", COLOR_CLIENTE_NO_ATENDIDO, aux, COLOR_RESET);
    }
}

/*
void Desencolar(cola *c, int x);
Descripción: Reimprimir la cola sin el primer elemento (elemento de frente)
Recibe: cola *c (apuntador a la cola en que se eliminó el elemento), int x (posición en x de esa cola)
Devuelve: void
Observaciones: La cola ya debe estar inicializada, la función depende de constantes como lo son:
	DEFAULT (número de elementos que se mostraran), TAM_FILA (posición en y que se movera tras agregar
	un nuevo elemento), INICIO_Y (posición en y a partir de la cual se empezaran a imprimir los elementos)
*/
void Desencolar(cola *c, int x) {
    int auxX = x, y = INICIO_Y;
    int tamano = Size(c);
    int i;
    char aux[100], resultado_str[20];

    limpiarCola(x);  // Limpiar la cola para actualizar los colores correctamente

    if (tamano < DEFAULT) {
        for (i = 1; i <= tamano; i++) {
            y += TAM_FILA;
            sprintf(aux, "%d", Element(c, i).n);
            if (i == 1) {
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2)-2, y, COLOR_CLIENTE_ATENDIDO, "💵");
            } else {
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2)-2, y, COLOR_CLIENTE_NO_ATENDIDO, "🛒");
            }
            x = auxX;
        }
    } else {
        for (i = 1; i < DEFAULT; i++) {
            y += TAM_FILA;
            sprintf(aux, "%d", Element(c, i).n);
            if (i == 1) {
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2)-2, y, COLOR_CLIENTE_ATENDIDO, "💵");
            } else {
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2)-2, y, COLOR_CLIENTE_NO_ATENDIDO, "🛒");
            }
            x = auxX;
        }
        int resultado = tamano - DEFAULT + 1;
        sprintf(resultado_str, "%d", resultado);
        strcpy(aux, "+ ");
        strcat(aux, resultado_str);
        MoverCursor(x - ((int)strlen(aux) / 2)-1, y + TAM_FILA);
        printf("%s%s%s", COLOR_CLIENTE_NO_ATENDIDO, aux, COLOR_RESET);
    }
}

/*
void limpiarCola(int x);
Descripción: Eliminar la cola que se encuentra en la posición en x, para evitar errores al sobreescribir
Recibe: int x (posición en x de la cola a eliminar)
Devuelve: void
Observaciones: La cola ya debe estar inicializada, la función depende de constantes como lo son:
	DEFAULT (número de elementos que se mostraran), TAM_FILA (posición en y que se movera al recorrer
	los elementos), INICIO_Y (posición en y a partir de la cual se empezaran a eliminar los elementos)
*/
void limpiarCola(int x) {
    int y = INICIO_Y, i;
    x = x - 5;
    char aux[] = "          ";
    for (i = 0; i <= DEFAULT; i++) {
        y += TAM_FILA;
        MoverCursor(x, y);
        printf("%s", aux);
    }
}

/*
void limpiarLinea(int x, int y);
Descripción: Eliminar solo una línea en la posición indicada (x,y)
Recibe: int x (posición en x del texto a eliminar), int y (posición en y del texto a eliminar)
Devuelve: void
Observaciones: El texto a eliminar no debe exceder el tamaño de la cadena aux
*/
void limpiarLinea(int x, int y) {
    char aux[] = "          ";
    MoverCursor(x - 5, y);
    printf("%s", aux);
}

/*
void imprimirCliente(int numero, int x, int y, const char* color, const char* icono);
Descripción: Imprimir el cliente según su tipo y color
Recibe: int numero (número del cliente), int x (posición en x en la que se imprimira el
	cliente), int y (posición en y en la que se imprimira el cliente), const char* color
	(color que le corresponde a el cliente en ANSI), const char* icono (emoji según el
	tipo de cliente)
Devuelve: void
Observaciones: Todos los datos estan correctamente inicialzados
*/
void imprimirCliente(int numero, int x, int y, const char* color, const char* icono) {
    MoverCursor(x, y);
    printf("%s%d %s%s", color, numero, icono, COLOR_RESET);
}
