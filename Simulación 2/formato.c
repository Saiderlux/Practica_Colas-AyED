//Formato para la simulacion 2
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
#define TAM_FILA	4
#define INICIO_Y 5

//DEFINICIONES DE TIPOS DE DATO

//Definir un boolean (Se modela con un "char")
typedef unsigned char boolean;


//DECLARACIÓN DE FUNCIONES
void Encolar(cola * c, int x){//Encolar : Recibe una cola e imprime la cola con el nuevo elemento
	int tamano = Size(c), i, j;
	proceso e;
	char aux[300], resultado_str[50];
	int y = INICIO_Y;
	if(tamano < DEFAULT){
		y+=tamano * TAM_FILA;
		if(Size(c)>=1) y+=tamano;
		e = Final(c);
		MoverCursor(x-21,y-1);
		printf("-------------------------------------------");
		for(i=0, j=y; i < TAM_FILA; i++, j++){
			MoverCursor(x-21,j);
			printf("|");
			MoverCursor(x+21,j);
			printf("|");
		}
		MoverCursor(x-21,j);
		printf("¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯");
		//Imprimir ID y NOMBRE
		sprintf(aux, "%s : %s",e.id, e.nombre);
		if(strlen(aux) <= 34 ){
			if(strlen(e.id)>15)
			{
				MoverCursor(x-16,y);
				printf("%.12s... : %s", e.id, e.nombre);
			}
			if(strlen(e.nombre)>15)
			{
				MoverCursor(x-16,y);
				printf("%s... : %.12s", e.id, e.nombre);
			}
			else{
				MoverCursor(x-((int)strlen(aux)/2),y);
				printf("%s", aux);
			}
			
		}else{
			MoverCursor(x-17,y);
			printf("%.12s... : %.12s...", e.id, e.nombre);
		}
		//Imprimir DESCRIPCIÓN
		sprintf(aux, "Descripción: %s",e.descripcion);
		if(strlen(aux) <= 50){
			MoverCursor(x-((int)strlen(aux)/2),y+1);
			printf("%s", aux);
		}else{
			MoverCursor(x-20,y+1);
			printf("%.37s...", aux);
		}
		//Imprimir TIEMPO RESTANTE (tiempo_ejecucion)
		sprintf(aux, "Tiempo restante: %d",e.tiempo_ejecucion);
		MoverCursor(x-((int)strlen(aux)/2),y+2);
		printf("%s", aux);
	}else{
		y += DEFAULT*TAM_FILA;
		limpiarLinea(x,y);
		int resultado = tamano - DEFAULT+1;
		sprintf(resultado_str, "%d", resultado);
		strcpy(aux, "+ ");
		strcat(aux, resultado_str);
		MoverCursor(x-((int)strlen(aux)/2),y);
		printf("%s", aux);
	}
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
			//Imprimir ID y NOMBRE
			sprintf(aux, "%s: %s",e.id, e.nombre);
			if(strlen(aux) <= 50){
				MoverCursor(x-((int)strlen(aux)/2),y);
				printf("%s", aux);
			}else{
				MoverCursor(x-25,y);
				printf("%.47s...", aux);
			}
			//Imprimir DESCRIPCIÓN
			sprintf(aux, "Descripción: %s",e.descripcion);
			if(strlen(aux) <= 50){
				MoverCursor(x-((int)strlen(aux)/2),y+1);
				printf("%s", aux);
			}else{
				MoverCursor(x-25,y+1);
				printf("%.47s...", aux);
			}
			//Imprimir TIEMPO RESTANTE (tiempo_ejecucion)
			sprintf(aux, "Tiempo restante: %d",e.tiempo_ejecucion);
			MoverCursor(x-((int)strlen(aux)/2),y+2);
			printf("%s", aux);
			x = auxX;
		}
	}else{
		for(i=1;i<DEFAULT;i++){
			y+=TAM_FILA;
			e = Element(c, i);
			//Imprimir ID y NOMBRE
			sprintf(aux, "%s: %s",e.id, e.nombre);
			if(strlen(aux) <= 50){
				MoverCursor(x-((int)strlen(aux)/2),y);
				printf("%s", aux);
			}else{
				MoverCursor(x-25,y);
				printf("%.47s...", aux);
			}
			//Imprimir DESCRIPCIÓN
			sprintf(aux, "Descripción: %s",e.descripcion);
			if(strlen(aux) <= 50){
				MoverCursor(x-((int)strlen(aux)/2),y+1);
				printf("%s", aux);
			}else{
				MoverCursor(x-25,y+1);
				printf("%.47s...", aux);
			}
			//Imprimir TIEMPO RESTANTE (tiempo_ejecucion)
			sprintf(aux, "Tiempo restante: %d",e.tiempo_ejecucion);
			MoverCursor(x-((int)strlen(aux)/2),y+2);
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
		for(int j=0;j<3;j++){
			MoverCursor(x,y+j);
			printf("%s%s", aux, aux);
		}
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
	//limpiarCola(x);
	for(i=1;i<=tamano;i++){
		e = Element(c, i);
		//Imprimir ID y NOMBRE
		sprintf(aux, "%s: %s",e.id, e.nombre);
		MoverCursor(x-((int)strlen(aux)/2),y);
		printf("%s", aux);
		//Imprimir DESCRIPCIÓN
		sprintf(aux, "Descripción: %s",e.descripcion);
		MoverCursor(x-((int)strlen(aux)/2),y+1);
		printf("%s", aux);
		//Imprimir TIEMPO RESTANTE (tiempo_ejecucion)
		sprintf(aux, "Tiempo en total del proceso: %d",e.tiempo_real);
		MoverCursor(x-((int)strlen(aux)/2),y+2);
		printf("%s", aux);
		x = auxX;
		y+=TAM_FILA;
	}
}