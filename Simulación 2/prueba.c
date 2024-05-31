
//Compilar: gcc prueba.c formato.c presentacion(Win/Lin).c TADColaDin.c -o prueba

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TADColaDin.h"    //Si se usa la implemtentación estática (TADColaEst.c|TADColaEstCirc.c)
#include "formato.h"
#include "presentacion.h"

#define POS_COLA_LISTOS 25
#define POS_COLA_TERMINADOS 125
#define POS_PROCESO 75


// Declarar las colas globales
cola listos, ejecucion, terminados;


//Función para borrar el texto al leer los procesos
void borrarTexto(int filas, int y){
	char aux [] = "                                                                             ";
	for(int i =0;i<filas;i++, y++){
		MoverCursor(0,y);
		printf("%s", aux);
	}
}

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
	p.tiempo_real = Size(c);
    Queue(c, p);
	Encolar(c, POS_COLA_LISTOS);
}

// Función para imprimir las colas
void imprimir_colas() {
    printf("Cola de listos:\n");
    for (int i = 1; i <= Size(&listos); i++) {
        proceso p = Element(&listos, i);
        printf("%s %s: tiempo: %d\n", p.id, p.nombre, p.tiempo_ejecucion);
    }

    /*printf("\nCola de ejecución:\n");
    for (int i = 1; i <= Size(&ejecucion); i++) {
        proceso p = Element(&ejecucion, i);
        printf("%s %s (Tiempo restante: %d)\n", p.id, p.nombre, p.tiempo_ejecucion);
    }*/

    printf("\nCola de terminados:\n");
    for (int i = 1; i <= Size(&terminados); i++) {
        proceso p = Element(&terminados, i);
        printf("%s %s\n", p.id, p.nombre);
    }
    printf("\n");
}


//Función para imprimir el proceso en ejecución
void mostrarProceso(proceso e){
	char aux[100], resultado_str[45];
	for(int i=0;i<3;i++){
		limpiarLinea(POS_PROCESO, 3+i);
	}
	strcpy(aux, "En proceso:");
	sprintf(resultado_str, "%s: %s",e.id, e.nombre);
	MoverCursor(POS_PROCESO-((int)strlen(aux)/2),3);
	printf("%s", aux);
	strcpy(aux, resultado_str);
	MoverCursor(POS_PROCESO-((int)strlen(aux)/2),4);
	printf("%s", aux);
	sprintf(resultado_str, "Tiempo restante: %d",e.tiempo_ejecucion);
	strcpy(aux, resultado_str);
	MoverCursor(POS_PROCESO-((int)strlen(aux)/2),5);
	printf("%s", aux);
}

int main() {
    // Inicializar las colas
    Initialize(&listos);
    //Initialize(&ejecucion);
    Initialize(&terminados);

    // Ingresar los procesos
	
	BorrarPantalla();
	
    int mas_procesos = 1;
    while (mas_procesos) {
        ingresar_proceso(&listos);
		MoverCursor(0,4);
        printf("¿Ingresar otro proceso? (1 = Sí, 0 = No): ");
        scanf("%d", &mas_procesos);
		borrarTexto(5,0);
		MoverCursor(0,0);
    }
	proceso p;
    // Ciclo principal de ejecución
    while (!Empty(&listos)) {
		p = Dequeue(&listos);
		Desencolar(&listos, POS_COLA_LISTOS);
		mostrarProceso(p);
		//printf("Proceso %s %s en ejecución\n\n", p.id, p.nombre);
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
	
	BorrarPantalla();
	char aux[] = "PROCESOS TERMINADOS:";
	MoverCursor(POS_PROCESO - ((int)strlen(aux)/2), 4);
	printf("%s", aux);
	MostrarCola(&terminados, POS_PROCESO);
	
    // Liberar las colas
    Destroy(&listos);
    //Destroy(&ejecucion);
    Destroy(&terminados);

    return 0;
}