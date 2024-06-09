/*
Main de la simulación 2: Ejecución de procesos en el sistema operativo
AUTOR: 
VERSIÓN: 1.1

DESCRIPCIÓN: Simular lña ejecución de los procesos gestionados por el sistema
	operativo en un monoprocesador sin manejo de prioridades.
	
OBSERVACIONES: Una vez que ya se halla terminado el proceso, este se envia a la
	cola de terminados

COMPILACIÓN: 
Windows (en Windows Terminal):
	CHCP 65001
	gcc Cajeras.c formato.c presentacionWin/Lin.c TadColaDin.c -o cajeras
Linux:
	(chcp 65001/sudo locale-gen es_ES.UTF-8 && sudo update-locale LANG=es_ES.UTF-8) 
		&& gcc simulacionSO.c formato.c presentacion(Win/Lin).c TADColaDin.c -o prueba
	
*/

// LIBRERÍAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TADColaDin.h"    //Si se usa la implemtentación estática (TADColaEst.c|TADColaEstCirc.c)
#include "formato.h"
#include "presentacion.h"
#include <locale.h>

#define POS_COLA_LISTOS 25
#define POS_COLA_TERMINADOS 125
#define POS_PROCESO 75


//DECLARACIÓN DE LAS COLAS GLOBALES
cola listos, terminados;

// DECLARACIÓN DE FUNCIONES
void Transicion();
void borrarTexto(int filas, int y);
int ingresar_proceso(cola *c);
void mostrarProceso(proceso e);
void limpiar_buffer();


//******************************************************************************************************
//	MAIN
//******************************************************************************************************
int main() {
	setlocale(LC_ALL, "es_ES.UTF-8");
	int mas_procesos = 1, i;

    // Inicializar las colas
    Initialize(&listos);
    Initialize(&terminados);

    // Ingresar los procesos
	
	BorrarPantalla();
	EsperarMiliSeg(2000);
	
    while (mas_procesos) {
        mas_procesos=ingresar_proceso(&listos);
		borrarTexto(6,0);
		MoverCursor(0,0);// 
    }
	proceso p;

	//Cabezas de las colas
	char auxL[] = "Cola de procesos:"; 
	char auxT[] = "Procesos terminados:"; 
	MoverCursor(POS_COLA_LISTOS-((int)strlen(auxL)/2), 6);
	printf("%s", auxL);
	MoverCursor(POS_COLA_TERMINADOS-((int)strlen(auxT)/2), 6);
	printf("%s", auxT);
	EsperarMiliSeg(2000);

    // Ciclo principal de ejecución//simulacion
    while (!Empty(&listos)) {
		p = Dequeue(&listos);
		Desencolar(&listos, POS_COLA_LISTOS);
		mostrarProceso(p);
		p.tiempo_ejecucion--;
		p.tiempo_real++;
		EsperarMiliSeg(1000);
		if(p.tiempo_ejecucion==0){
			Queue(&terminados, p);
			Encolar(&terminados, POS_COLA_TERMINADOS);
		}else{
			p.tiempo_real+=Size(&listos);
			Queue(&listos, p);
			Encolar(&listos, POS_COLA_LISTOS);
		}
    }
	//para terminar de dar un buen diseño, borrar lo ultimo del proceso
	for(i=0; i<=5 ;i++){
		limpiarLinea(POS_PROCESO, 3+i);
	}

	//transicion para el final
	Transicion();
	
	//imprimir los procesos
	char aux[] = "PROCESOS TERMINADOS:";
	MoverCursor(POS_PROCESO - ((int)strlen(aux)/2), 4);
	printf("%s", aux);
	MostrarCola(&terminados, POS_PROCESO);
	
    // Liberar las colas
    Destroy(&listos);
    Destroy(&terminados);

	EsperarMiliSeg(7000);
    return 0;
}

//******************************************************************************************************
//	FUNCIONES
//******************************************************************************************************
/*
void borrarTexto(int filas, int y);
Descripción: Función que elimina todo una línea de texto en la terminal
Recibe: int filas (Número de lineas a eliminar), int y (posición en y en la que se
	empezara a eliminar)
Devuelve: void
Observaciones: Lo que se eliminara en la línea va a depender del número de caracteres
	en aux
*/
void borrarTexto(int filas, int y){
	char aux [] = "                                                                                                                                            ";
	int i;
	for(i =0;i<filas;i++, y++){
		MoverCursor(0,y);
		printf("%s", aux);
	}
}

/*
int ingresar_proceso(cola *c);
Descripción: Función para leer los datos de cada procesos 
Recibe: cola * c (cola en la que se guardaran los procesos)
Devuelve: int (para saber si se van a seguir ingresando procesos)
Observaciones: La cola debe de estar inicializada y el usuario debe	
	tener cuidado con los datos que ingrese
*/
int ingresar_proceso(cola *c) {
    proceso p;
	int aux;
    printf("Ingrese el nombre del proceso: ");
    scanf("%[^\n]s", p.nombre);
	if(strlen(p.nombre)>45){
		printf("\nNo se aceptan nombres con más de 45 carateres.");
		exit(1);
	}
	limpiar_buffer();
    printf("Ingrese el ID del proceso: ");
    scanf("%s", p.id);
	if(strlen(p.id)>45){
		printf("\nNo se aceptan ID con más de 45 carateres.");
		exit(1);
	}
	limpiar_buffer();
    printf("Ingrese la descripción del proceso: ");
    scanf(" %[^\n]s", p.descripcion);
	if(strlen(p.descripcion)>200){
		printf("\nNo se acepta descripción con más de 200 carateres.");
		exit(1);
	}
	limpiar_buffer();
    printf("Ingrese el tiempo de ejecución del proceso (en segundos): ");
    scanf("%d", &p.tiempo_ejecucion);
	limpiar_buffer();
	p.tiempo_real = Size(c);
	printf("¿Ingresar otro proceso? (1 = Sí, 0 = No): ");
	scanf("%d", &aux);
	limpiar_buffer();
    Queue(c, p);
	Encolar(c, POS_COLA_LISTOS);
	return aux;
}

/*
void mostrarProceso(proceso e);
Descripción: Función para imprimir el proceso que esta en ejecución
Recibe: proceso e (Recibe el proceso que esta en ejecución en ese momento)
Devuelve: void
Observaciones: El proceso debe de tener ya inicializada la información a utilizar
*/
void mostrarProceso(proceso e){
	char aux[200], resultado_str[100];
	int i, j;
	for(i=0;i<5	;i++){
		limpiarLinea(POS_PROCESO, 3+i);
	}
	strcpy(aux, "En proceso:");
	MoverCursor(POS_PROCESO-((int)strlen(aux)/2),3);
	printf("%s", aux);
	strcpy(aux, "┌───────────────────────────────────┐");
	MoverCursor(POS_PROCESO-18,4);
	printf("%s", aux);
	for(i=5; i <8 ; i++){
		MoverCursor(POS_PROCESO-18,i);
		printf("│");
		MoverCursor(POS_PROCESO+18 ,i);
		printf("│");
	}
	strcpy(aux, "└───────────────────────────────────┘");
	MoverCursor(POS_PROCESO-18,8);
	printf("%s", aux);
	sprintf(resultado_str, "%s : %s",e.id, e.nombre);
	strcpy(aux, resultado_str);
	if(strlen(aux) <= 34){
		MoverCursor(POS_PROCESO-((int)strlen(aux)/2),5);
		printf("%s", aux);
	}else{
		MoverCursor(POS_PROCESO-16,5);
		printf("%.12s... : %.12s...", e.id, e.nombre);
	}
	sprintf(resultado_str, "Tiempo restante: %d",e.tiempo_ejecucion);
	strcpy(aux, resultado_str);
	MoverCursor(POS_PROCESO-((int)strlen(aux)/2),6);
	printf("%s", aux);
}

/*
void Transicion();
Descripción: Función para imprimir una breve transición para evitar cambios bruscos
	en el formato
Recibe: 
Devuelve: void
Observaciones: La transición va a depender de dos variables la anchura: tamX y altura
	tamY
*/
void Transicion() {
    int tamX = 150, tamY = 30, d, x, y;
	//Imprimir asteriscos
    for ( d = 0; d < tamX + tamY - 1; d++) {
        for (x = 0; x <= d; x++) {
            y = d - x;
            if (x < tamX && y < tamY) {
                MoverCursor(x, y); 
                printf("*");
            }
        }
		EsperarMiliSeg(5);
    }
	//Borrar los asteriscos
	for (d = 0; d < tamX + tamY - 1; d++) {
        for (x = 0; x <= d; x++) {
            y = d - x;
            if (x < tamX && y < tamY) {
                MoverCursor(x, y); 
                printf(" ");
            }
        }
		EsperarMiliSeg(5);
    }
}

/*
void limpiar_buffer();
Descripción: Función que se encarga de limpiar el buffer para evitar leer datos
	incorrectos en las cadenas
Recibe: 
Devuelve: void
Observaciones: Funciona "tragando" datos hasta encontrar un salto de línea
*/
void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}