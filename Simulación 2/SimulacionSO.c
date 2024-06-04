
//Compilar: (chcp 65001/sudo locale-gen es_ES.UTF-8 && sudo update-locale LANG=es_ES.UTF-8) && gcc simulacionSO.c formato.c presentacion(Win/Lin).c TADColaDin.c -o prueba
// para que se muestren bien los acentos se debe ejecutar el sguiente comando
//   	para windows: chcp 65001
//		para linux: sudo locale-gen es_ES.UTF-8 && sudo update-locale LANG=es_ES.UTF-8

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


// Declarar las colas globales
cola listos, terminados;

void Transicion();
void borrarTexto(int filas, int y);
int ingresar_proceso(cola *c);
void mostrarProceso(proceso e);
void limpiar_buffer();


int main() {
	setlocale(LC_ALL, "es_ES.UTF-8");
    // Inicializar las colas
    Initialize(&listos);
    Initialize(&terminados);

    // Ingresar los procesos
	
	BorrarPantalla();
	
    int mas_procesos = 1;
    while (mas_procesos) {
        mas_procesos=ingresar_proceso(&listos);
		borrarTexto(5,0);
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
	
    // Ciclo principal de ejecución
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
	
	Transicion();
	
	char aux[] = "PROCESOS TERMINADOS:";
	MoverCursor(POS_PROCESO - ((int)strlen(aux)/2), 4);
	printf("%s", aux);
	MostrarCola(&terminados, POS_PROCESO);
	
    // Liberar las colas
    Destroy(&listos);
    Destroy(&terminados);

    return 0;
}

/*********************************************************************************************/
//FUNCIONES
/*********************************************************************************************/
//Función para borrar el texto al leer los procesos
void borrarTexto(int filas, int y){
	char aux [] = "                                                                                                                                            ";
	for(int i =0;i<filas;i++, y++){
		MoverCursor(0,y);
		printf("%s", aux);
	}
}

// Función para ingresar un nuevo proceso
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

//Función para imprimir el proceso en ejecución
void mostrarProceso(proceso e){
	char aux[100], resultado_str[100];
	for(int i=0;i<3;i++){
		limpiarLinea(POS_PROCESO, 3+i);
	}
	strcpy(aux, "En proceso:");
	MoverCursor(POS_PROCESO-((int)strlen(aux)/2),3);
	printf("%s", aux);
	sprintf(resultado_str, "%s: %s",e.id, e.nombre);
	strcpy(aux, resultado_str);
	if(strlen(aux) <= 50){
		MoverCursor(POS_PROCESO-((int)strlen(aux)/2),4);
		printf("%s", aux);
	}else{
		MoverCursor(POS_PROCESO-25,4);
		printf("%.47s...", aux);
	}
	sprintf(resultado_str, "Tiempo restante: %d",e.tiempo_ejecucion);
	strcpy(aux, resultado_str);
	MoverCursor(POS_PROCESO-((int)strlen(aux)/2),5);
	printf("%s", aux);
}

// Función de transición de esquina a esquina
void Transicion() {
    int tamX = 150;
    int tamY = 30;
	//Imprimir asteriscos
    for (int d = 0; d < tamX + tamY - 1; d++) {
        for (int x = 0; x <= d; x++) {
            int y = d - x;
            if (x < tamX && y < tamY) {
                MoverCursor(x, y); 
                printf("*");
            }
        }
		EsperarMiliSeg(5);
    }
	//Borrar los asteriscos
	for (int d = 0; d < tamX + tamY - 1; d++) {
        for (int x = 0; x <= d; x++) {
            int y = d - x;
            if (x < tamX && y < tamY) {
                MoverCursor(x, y); 
                printf(" ");
            }
        }
		EsperarMiliSeg(5);
    }
}

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}