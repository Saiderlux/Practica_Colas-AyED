// Formato para la simulación 1
/*
LIBRERIA: Cabecera del TAD COLA DINÁMICA
AUTOR: Edgardo Adrián Franco Martínez (C) Noviembre 2022
VERSIÓN: 1.7

DESCRIPCIÓN: TAD cola o Queue.
Estructura de datos en la que se cumple:
Los elementos se insertan en un extremo (el posterior) y 
la supresiones tienen lugar en el otro extremo (frente).

OBSERVACIONES: Hablamos de una Estructura de datos dinámica 
cuando se le asigna memoria a medida que es necesitada, 
durante la ejecución del programa. 
 
*/

#include <string.h>
#include "TADColaDin.h"
#include <windows.h>
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

// DECLARACIÓN DE FUNCIONES
void Encolar(cola *c, int x); 
void Desencolar(cola *c, int x); 
void limpiarCola(int x);
void limpiarLinea(int x, int y);
void imprimirCliente(int numero, int x, int y, const char* color, const char* icono);

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
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2), y, COLOR_CLIENTE_ATENDIDO, "💵");
            } else {
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2), y, COLOR_CLIENTE_NO_ATENDIDO, "🛒");
            }
        }
    } else {
        for (int i = 1; i < DEFAULT; i++) {
            y += TAM_FILA;
            sprintf(aux, "%d", Element(c, i).n);
            if (i == 1) {
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2), y, COLOR_CLIENTE_ATENDIDO, "💵");
            } else {
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2), y, COLOR_CLIENTE_NO_ATENDIDO, "🛒");
            }
        }
        int resultado = tamano - DEFAULT + 1;
        sprintf(resultado_str, "%d", resultado);
        strcpy(aux, "+ ");
        strcat(aux, resultado_str);
        MoverCursor(x - ((int)strlen(aux) / 2), y + TAM_FILA);
        printf("%s%s%s", COLOR_CLIENTE_NO_ATENDIDO, aux, COLOR_RESET);
    }
}

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
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2), y, COLOR_CLIENTE_ATENDIDO, "💵");
            } else {
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2), y, COLOR_CLIENTE_NO_ATENDIDO, "🛒");
            }
            x = auxX;
        }
    } else {
        for (i = 1; i < DEFAULT; i++) {
            y += TAM_FILA;
            sprintf(aux, "%d", Element(c, i).n);
            if (i == 1) {
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2), y, COLOR_CLIENTE_ATENDIDO, "💵");
            } else {
                imprimirCliente(Element(c, i).n, x - ((int)strlen(aux) / 2), y, COLOR_CLIENTE_NO_ATENDIDO, "🛒");
            }
            x = auxX;
        }
        int resultado = tamano - DEFAULT + 1;
        sprintf(resultado_str, "%d", resultado);
        strcpy(aux, "+ ");
        strcat(aux, resultado_str);
        MoverCursor(x - ((int)strlen(aux) / 2), y + TAM_FILA);
        printf("%s%s%s", COLOR_CLIENTE_NO_ATENDIDO, aux, COLOR_RESET);
    }
}

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

void limpiarLinea(int x, int y) {
    char aux[] = "          ";
    MoverCursor(x - 5, y);
    printf("%s", aux);
}

void imprimirCliente(int numero, int x, int y, const char* color, const char* icono) {
    MoverCursor(x, y);
    printf("%s%d %s%s", color, numero, icono, COLOR_RESET);
}
