/*
Formato de la simulación 3: Banco
AUTOR: 
VERSIÓN: 3.0

DESCRIPCIÓN: Funciones necesarias para mostrar de manera agradable el Queue y
	Dequeue de elementos en las colas
	
OBSERVACIONES: Se hace uso de caracteres especiales
*/

// LIBRERÍAS
#include <string.h>
#include "TADColaDin.h"
//#include <windows.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "formato.h"
#include "presentacion.h"

//DEFINICIONES DE CONSTANTES
#define TRUE	1
#define FALSE	0
#define DEFAULT	5
#define TAM_FILA	2
#define INICIO_Y 5

//DEFINICIONES DE TIPOS DE DATO

//Definir un boolean (Se modela con un "char")
typedef unsigned char boolean;


/*
void Encolar(cola *c, int x, int y);
Descripción: Imprimir el último elemento agregado a la cola
Recibe: cola *c (apuntador a la cola en que se agregó un elemento), int x (posición en x de esa cola)
	int y (posición en y de esa cola)
Devuelve: void
Observaciones: La cola ya debe estar inicializada, la función depende de constantes como lo son:
	DEFAULT (número de elementos que se mostraran), TAM_FILA (posición en y que se movera tras agregar
	un nuevo elemento)
*/
void Encolar(cola * c, int x, int y){
	int tamano = Size(c);
	char aux[100], resultado_str[20];
	if(tamano < DEFAULT){
		y+=tamano * TAM_FILA;
		sprintf(aux, "%s", Final(c).t_cliente);
		MoverCursor(x-((int)strlen(aux)/2),y);
	}else{
		y += DEFAULT*TAM_FILA;
		limpiarLinea(x,y);
		int resultado = tamano - DEFAULT+1;
		sprintf(resultado_str, "%d", resultado);
		strcpy(aux, "+ ");
		strcat(aux, resultado_str);
		MoverCursor(x-((int)strlen(aux)/2),y);
	}
	printf("%s", aux);
}

/*
void Desencolar(cola *c, int x, int y);
Descripción: Reimprimir la cola sin el primer elemento (elemento de frente)
Recibe: cola *c (apuntador a la cola en que se eliminó el elemento), int x (posición en x de esa cola)
	int y (posición en y de esa cola)
Devuelve: void
Observaciones: La cola ya debe estar inicializada, la función depende de constantes como lo son:
	DEFAULT (número de elementos que se mostraran), TAM_FILA (posición en y que se movera tras agregar
	un nuevo elemento)
*/
void Desencolar(cola * c, int x,int y){
	int auxX = x;
	int tamano = Size(c);
	int i;
	char aux[100], resultado_str[20];
	limpiarCola(x, y);
	if(tamano < DEFAULT){
		for(i=1;i<=tamano;i++){
			y+=TAM_FILA;
			sprintf(aux, "%s", Element(c, i).t_cliente);
			MoverCursor(x-((int)strlen(aux)/2),y);
			printf("%s", aux);
			x = auxX;
		}
	}else{
		for(i=1;i<DEFAULT;i++){
			y+=TAM_FILA;
			sprintf(aux, "%s", Element(c, i).t_cliente);
			MoverCursor(x-((int)strlen(aux)/2),y);
			printf("%s", aux);
			x = auxX;
		}
		int resultado = tamano - DEFAULT + 1;
		sprintf(resultado_str, "%d", resultado);
		strcpy(aux, "+ ");
		strcat(aux, resultado_str);
		MoverCursor(x-((int)strlen(aux)/2),y+TAM_FILA);
		printf("%s", aux);
	}
}

/*
void limpiarCola(int x, int y);
Descripción: Eliminar la cola que se encuentra en la posición en x, para evitar errores al sobreescribir
Recibe: int x (posición en x de la cola a eliminar), int y (posición en y de la cola a eliminar)
Devuelve: void
Observaciones: La cola ya debe estar inicializada, la función depende de constantes como lo son:
	DEFAULT (número de elementos que se mostraran), TAM_FILA (posición en y que se movera al recorrer
	los elementos)
*/
void limpiarCola(int x, int y){
	int i;
	x = x - 5;
	char aux [] = "          ";
	for(i=0;i<=DEFAULT;i++){
		y+=TAM_FILA;
		MoverCursor(x,y);
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
void limpiarLinea(int x, int y){
	char aux [] = "          ";
	MoverCursor(x-5,y);
	printf("%s", aux);
}