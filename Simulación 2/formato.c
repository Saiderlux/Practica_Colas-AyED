//Formato para la simulacion 1
/*
LIBRERIA: Cabecera de el TAD COLA DINÁMICA
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
//#define TAM_COLUMNA	10
#define INICIO_Y 5

//DEFINICIONES DE TIPOS DE DATO

//Definir un boolean (Se modela con un "char")
typedef unsigned char boolean;


//DECLARACIÓN DE FUNCIONES
void Encolar(cola * c, int x){//Encolar : Recibe una cola e imprime la cola con el nuevo elemento
	int tamano = Size(c);
	char aux[100], resultado_str[20];
	int y = INICIO_Y;
	if(tamano < DEFAULT){
		y+=tamano * TAM_FILA;
		proceso e = Final(c);
		sprintf(aux, "%s: %s - %d",e.id, e.nombre, e.tiempo_ejecucion);
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

void Desencolar(cola * c, int x){//Desencolar (Dequeue): Recibe una cola y recorre la fila para eliminar el primer elemento
	int auxX = x,y = INICIO_Y;
	int tamano = Size(c);
	int i;
	char aux[100], resultado_str[20];
	proceso e;
	limpiarCola(x);
	if(tamano < DEFAULT){
		for(i=1;i<=tamano;i++){
			y+=TAM_FILA;
			e = Element(c, i);
			sprintf(aux, "%s: %s - %d",e.id, e.nombre, e.tiempo_ejecucion);
			MoverCursor(x-((int)strlen(aux)/2),y);
			printf("%s", aux);
			x = auxX;
		}
	}else{
		for(i=1;i<DEFAULT;i++){
			y+=TAM_FILA;
			e = Element(c, i);
			sprintf(aux, "%s: %s - %d",e.id, e.nombre, e.tiempo_ejecucion);
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

void limpiarCola(int x){
	int y = INICIO_Y, i;
	x = x - 25;
	char aux [] = "                         ";
	for(i=0;i<=DEFAULT;i++){
		y+=TAM_FILA;
		MoverCursor(x,y);
		printf("%s%s", aux, aux);
	}
}

void limpiarLinea(int x, int y){
	char aux [] = "                         ";
	MoverCursor(x-25,y);
	printf("%s%s", aux, aux);
}

void MostrarCola(cola * c, int x){
	int auxX = x,y = INICIO_Y;
	int tamano = Size(c);
	int i;
	char aux[100], resultado_str[20];
	proceso e;
	limpiarCola(x);
	if(tamano < DEFAULT){
		for(i=1;i<=tamano;i++){
			y+=TAM_FILA;
			e = Element(c, i);
			sprintf(aux, "%s: %s - %d",e.id, e.nombre, e.tiempo_real);
			MoverCursor(x-((int)strlen(aux)/2),y);
			printf("%s", aux);
			x = auxX;
		}
	}else{
		for(i=1;i<DEFAULT;i++){
			y+=TAM_FILA;
			e = Element(c, i);
			sprintf(aux, "%s: %s - %d",e.id, e.nombre, e.tiempo_real);
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