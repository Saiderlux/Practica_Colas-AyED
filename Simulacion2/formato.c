/*
Formato de la simulación 2: Ejecución de procesos en el sistema operativo
AUTOR: 
VERSIÓN: 2.0

DESCRIPCIÓN: Funciones necesarias para mostrar de manera agradable el Queue y
	Dequeue de elementos en las colas
	
OBSERVACIONES: Se hace uso de caracteres especiales
*/

// LIBRERÍAS
#include <string.h>
#include "TADColaDin.h"    //Si se usa la implemtentación estática (TADColaEst.c|TADColaEstCirc.c)
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
#define TAM_FILA 5
#define INICIO_Y 5

//DEFINICIONES DE TIPOS DE DATO

//Definir un boolean (Se modela con un "char")
typedef unsigned char boolean;


/*
void Encolar(cola *c, int x);
Descripción: Imprimir el último proceso agregado a la cola
Recibe: cola *c (apuntador a la cola en que se agregó un proceso), int x (posición en x de esa cola)
Devuelve: void
Observaciones: La cola ya debe estar inicializada, la función depende de constantes como lo son:
	DEFAULT (número de elementos que se mostraran), TAM_FILA (posición en y que se movera tras agregar
	un nuevo elemento), INICIO_Y (posición en y a partir de la cual se empezaran a imprimir los elementos)
	La función se encarga de adaptar las cadenas dependiendo del texto que tiene el nombre, id y descripción
*/
void Encolar(cola * c, int x){
	int tamano = Size(c), i, j;
	proceso e;
	char aux[220], resultado_str[50];
	int y = INICIO_Y;

	//mostrar el nuevo proceso agregado
	if(tamano < DEFAULT){// si el tamaño aun no sobrepasa los 4 procesos en la cola de listos, se muestran "normal"
		
		y+=tamano * TAM_FILA;//es para colocar correctamente el cursor para imprir cada "caja" de procesos
		e = Final(c);

		//Diseño de cajas de la cola
		MoverCursor(x-21,y);
		printf("┌─────────────────────────────────────────┐");
		for(i=0, j=y+1; i < 4; i++, j++){
			MoverCursor(x-21,j);
			printf("│");
			MoverCursor(x+21,j);
			printf("│");
		}
		MoverCursor(x-21,j-1);
		printf("└─────────────────────────────────────────┘");


		//Imprimir ID y NOMBRE
		sprintf(aux, "%s: %s",e.id, e.nombre);
		if(strlen(aux) <= 34){
			if(strlen(e.id)>15)
			{
				MoverCursor(x-16,y+1);
				printf("%.12s... : %s", e.id, e.nombre);
			}
			if(strlen(e.nombre)>15)
			{
				MoverCursor(x-16,y+1);
				printf("%s... : %.12s", e.id, e.nombre);
			}
			else{
				MoverCursor(x-((int)strlen(aux)/2),y+1);
				printf("%s", aux);
			}
		}else{
			MoverCursor(x-17,y+1);
			printf("%.12s... : %.12s...", e.id, e.nombre);
		}


		//Imprimir DESCRIPCIÓN
		sprintf(aux, "Descripción: %s",e.descripcion);
		if(strlen(aux) <= 34){
			MoverCursor(x-((int)strlen(aux)/2),y+2);
			printf("%s", aux);
		}else{
			MoverCursor(x-20,y+2);
			printf("%.37s...", aux);
		}


		//Imprimir TIEMPO RESTANTE (tiempo_ejecucion)
		sprintf(aux, "Tiempo restante: %d",e.tiempo_ejecucion);
		MoverCursor(x-((int)strlen(aux)/2),y+3);
		printf("%s", aux);


	}else{//si hay mas de cuatro procesos para mostrar, se imprime un "+cantidaddemas"
		y += DEFAULT*TAM_FILA+1;
		limpiarLinea(x,y);
		int resultado = tamano - DEFAULT+1;
		sprintf(resultado_str, "%d", resultado);
		strcpy(aux, "+ ");
		strcat(aux, resultado_str);
		MoverCursor(x-((int)strlen(aux)/2),y);
		printf("%s", aux);
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
	La función se encarga de adaptar las cadenas dependiendo del texto que tiene el nombre, id y descripción
*/
void Desencolar(cola * c, int x){//Desencolar (Dequeue): Recibe una cola y recorre la fila para eliminar el primer elemento
	int auxX = x,y = INICIO_Y;
	int tamano = Size(c);
	int i,j,k;
	char aux[220], resultado_str[20];
	proceso e;
	limpiarCola(x);
	//aqui se vuelve a imprir la cola completa en cada ejecucion ya que va cambaindo en cada estado
	// por eso se usan lo s ciclos
	if(tamano < DEFAULT){
		for(k=1;k<=tamano;k++){
			y+=TAM_FILA;
			e = Element(c, k);

			//diseño de caja
			MoverCursor(x-21,y);
			printf("┌─────────────────────────────────────────┐");
			for(i=0, j=y+1; i < 4 ; i++, j++){
				MoverCursor(x-21,j);
				printf("│");
				MoverCursor(x+21,j);
				printf("│");
			}
			MoverCursor(x-21,j-1);
			printf("└─────────────────────────────────────────┘");
			

			//Imprimir ID y NOMBRE
			sprintf(aux, "%s : %s",e.id, e.nombre);
			if(strlen(aux) <= 34 ){
				if(strlen(e.id)>15)
				{
					MoverCursor(x-16,y+1);
					printf("%.12s... : %s", e.id, e.nombre);
				}
				if(strlen(e.nombre)>15)
				{
					MoverCursor(x-16,y+1);
					printf("%s... : %.12s", e.id, e.nombre);
				}
				else{
					MoverCursor(x-((int)strlen(aux)/2),y+1);
					printf("%s", aux);
				}
				
			}else{
				MoverCursor(x-17,y+1);
				printf("%.12s... : %.12s...", e.id, e.nombre);
			}


			//Imprimir DESCRIPCIÓN
			sprintf(aux, "Descripción: %s",e.descripcion);
			if(strlen(aux) <= 34){
				MoverCursor(x-((int)strlen(aux)/2),y+2);
				printf("%s", aux);
			}else{
				MoverCursor(x-20,y+2);
				printf("%.37s...", aux);
			}


			//Imprimir TIEMPO RESTANTE (tiempo_ejecucion)
			sprintf(aux, "Tiempo restante: %d",e.tiempo_ejecucion);
			MoverCursor(x-((int)strlen(aux)/2),y+3);
			printf("%s", aux);
			x = auxX;
		}
	}else{
		for(k=1;k<DEFAULT;k++){
			y+=TAM_FILA;
			e = Element(c, k);
			//diseño de caja
			MoverCursor(x-21,y);
			printf("┌─────────────────────────────────────────┐");
			for(i=0, j=y+1; i < TAM_FILA; i++, j++){
				MoverCursor(x-21,j);
				printf("│");
				MoverCursor(x+21,j);
				printf("│");
			}
			MoverCursor(x-21,j-1);
			printf("└─────────────────────────────────────────┘");
			

			//Imprimir ID y NOMBRE
			sprintf(aux, "%s : %s",e.id, e.nombre);
			if(strlen(aux) <= 34 ){
				if(strlen(e.id)>15)
				{
					MoverCursor(x-16,y+1);
					printf("%.12s... : %s", e.id, e.nombre);
				}
				if(strlen(e.nombre)>15)
				{
					MoverCursor(x-16,y+1);
					printf("%s... : %.12s", e.id, e.nombre);
				}
				else{
					MoverCursor(x-((int)strlen(aux)/2),y+1);
					printf("%s", aux);
				}
				
			}else{
				MoverCursor(x-17,y+1);
				printf("%.12s... : %.12s...", e.id, e.nombre);
			}


			//Imprimir DESCRIPCIÓN
			sprintf(aux, "Descripción: %s",e.descripcion);
			if(strlen(aux) <= 34){
				MoverCursor(x-((int)strlen(aux)/2),y+2);
				printf("%s", aux);
			}else{
				MoverCursor(x-20,y+2);
				printf("%.37s...", aux);
			}
			

			//Imprimir TIEMPO RESTANTE (tiempo_ejecucion)
			sprintf(aux, "Tiempo restante: %d",e.tiempo_ejecucion);
			MoverCursor(x-((int)strlen(aux)/2),y+3);
			printf("%s", aux);
			x = auxX;
		}
		int resultado = tamano - DEFAULT + 1;
		sprintf(resultado_str, "%d", resultado);
		strcpy(aux, "+ ");
		strcat(aux, resultado_str);
		MoverCursor(x-((int)strlen(aux)/2),y+TAM_FILA+1);
		printf("%s", aux);
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
	El texto que va a eliminar va a depender de la variable aux
*/
void limpiarCola(int x){
	int y = INICIO_Y, i;
	x = x - 25;
	char aux [] = "                         ";
	for(i=0;i<=DEFAULT;i++){
		y+=TAM_FILA;
		for(int j=0;j<TAM_FILA;j++){
			MoverCursor(x,y+j);
			printf("%s%s", aux, aux);
		}
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
	char aux [] = "                         ";
	MoverCursor(x-25,y);
	printf("%s%s", aux, aux);
}

/*
void MostrarCola(cola *c, int x);
Descripción: Imprimir la cola en la posición dada en x
Recibe: cola *c (apuntador a la cola a imprimir), int x (posición en x en la que se imprimira)
Devuelve: void
Observaciones: La cola ya debe estar inicializada, la función depende de constantes como lo son:
	DEFAULT (número de elementos que se mostraran), TAM_FILA (posición en y que se movera tras agregar
	un nuevo elemento), INICIO_Y (posición en y a partir de la cual se empezaran a imprimir los elementos)
	En este caso no se limitan las cadenas, ya que queremos mostrar todo lo que ingreso el usuario
*/
void MostrarCola(cola * c, int x){
	int auxX = x,y = INICIO_Y;
	int tamano = Size(c);
	int i;
	char aux[220], resultado_str[20];
	proceso e;
	if(tamano<6)
	{
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
	else
	{
		for(i=1;i<=DEFAULT;i++){
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

		int resultado = tamano - DEFAULT + 1;
		sprintf(resultado_str, "%d", resultado);
		strcpy(aux, "+ ");
		strcat(aux, resultado_str);
		MoverCursor(x-((int)strlen(aux)/2),y+TAM_FILA+1);
		printf("%s", aux);
	}
}