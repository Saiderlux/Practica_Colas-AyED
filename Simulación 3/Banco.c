
//LIBRERAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "presentacion.h"
#include <time.h>
#include "TADColaDin.h"
#include "formato.h"

//DEFINICION DE CONSTANTES
#define TIEMPO_BASE	200
#define POS_Y_CAJAS 3
#define POS_Y_CLIENTES 7
#define TAM_MAX_X 100


int calcularPosicionX(int columna, int n_columnas) {
    // Calcular el ancho de cada columna
    int ancho_columna = TAM_MAX_X / (n_columnas + 1);
    // Calcular la posición x de la columna específica
    int posicion_x = ancho_columna * columna;
    
    return posicion_x;
}

int colocarCajas(int i, int x, int y){
	char aux[20], resultado_str[2];
	sprintf(resultado_str, "%d", i);
	strcpy(aux, "[ ");
	strcat(aux, resultado_str);
	strcat(aux, " ]");
	MoverCursor(x-((int)strlen(aux)/2), y-1);
	printf("%s", aux);
}

int main(void)
{
	int n, tiempo_atencion, tiempos_cliente[3];
	unsigned int tiempo = 0;
	unsigned int cliente = 0;
	int i, j,fila;
	elemento e;
	//Leemos cuantos cajeros van a atender en el banco
	printf("Ingresa la cantidad de cajeros: ");
	scanf("%d", &n);
	
	//Leemos el tiempo de atención de los cajeros
	printf("Ingresa el tiempo de atención de los cajeros: ");
	scanf("%d", &tiempo_atencion);
	
	//Leemos los tiempos de llegada de los clientes
	/*
	Indices - Tipo de cliente
	0 - clientes del banco
	1 - usuarios del banco
	2 - clientes preferentes
	*/
	printf("Ingresa el tiempo de llegada de los clientes del banco: ");
	scanf("%d", &tiempos_cliente[0]);
	printf("Ingresa el tiempo de llegada de los usuarios del banco: ");
	scanf("%d", &tiempos_cliente[1]);
	printf("Ingresa el tiempo de llegada de los clientes preferentes: ");
	scanf("%d", &tiempos_cliente[2]);
	
	//Crear n colas (por caja)
	cola cajeros[n];
	int arrAux[n]; //Arreglo para guardar los indices por si hay colas vacias
	for(i = 0; i<n; i++) Initialize(&cajeros[i]);
	//Crear las colas de los clientes
	cola clientes[3];
	int nclientes[3] = {0};
	for(i = 0; i<3; i++) Initialize(&clientes[i]);
	
	//Inicializar la función rand
	srand(time(NULL));
	
	BorrarPantalla();
	
	for(i=1;i<=n;i++){ //Imprimir las cajas
		colocarCajas(i, calcularPosicionX(i,n), 5);
	}
	
	for(i=1;i<=3;i++){ //Imprimir las cajas
		colocarCajas(i, calcularPosicionX(i,3), 9);
	}
	
	int cajasVacias;
	//Ciclo infinito
	while (1)
	{
		EsperarMiliSeg(TIEMPO_BASE);		//Esperar el tiempo base
		tiempo++;				//Incrementar el contador de tiempo
		cajasVacias = 0;
		
		//Verificamos si los cajeros pueden atender algún cliente (que ya este formado)
		for(i = 0; i<n; i++){
			if(!Empty(&cajeros[i])){
				if(tiempo % (tiempo_atencion / 10) == 0){
					e = Dequeue(&cajeros[i]);
					limpiarLinea(calcularPosicionX(i+1, n), POS_Y_CAJAS);
					//Desencolar(&cajeros[i], calcularPosicionX(i+1, n), POS_Y_CAJAS);
					//printf("Se atendio a %d\n", e.n);
				}
			}else{ //Si hay clientes formados los mandamos a la cola
				arrAux[cajasVacias++] = i;
			}
		}
		
		//Si hay cajas vacias mandamos un cliente según la prioridad
		if (cajasVacias > 0) {
			fila = arrAux[rand() % cajasVacias]; //Fila vacia aleatoria a la que se manda un cliente
			//Verificamos si hay clientes y su prioridad
			if(!Empty(&clientes[1])){
				e = Dequeue(&clientes[1]);
				Desencolar(&clientes[1], calcularPosicionX(2,3), POS_Y_CLIENTES);
				Queue(&cajeros[fila], e);
				Encolar(&cajeros[fila], calcularPosicionX(fila+1, n), POS_Y_CAJAS);
				cliente==0;
				//printf("Se mando un usuario a %d", fila);
			}else if(!Empty(&clientes[2])){
				e = Dequeue(&clientes[2]);
				Desencolar(&clientes[2], calcularPosicionX(3,3), POS_Y_CLIENTES);
				Queue(&cajeros[fila], e);
				Encolar(&cajeros[fila], calcularPosicionX(fila+1, n), POS_Y_CAJAS);
				//printf("Se mando un C. preferente a %d", fila);
			} else if(!Empty(&clientes[0])){
				e = Dequeue(&clientes[0]);
				Desencolar(&clientes[0], calcularPosicionX(1,3), POS_Y_CLIENTES);
				Queue(&cajeros[fila], e);
				Encolar(&cajeros[fila], calcularPosicionX(fila+1, n), POS_Y_CAJAS);
				//printf("Se mando un C. del banco a %d", fila);
			}
		}
		
		//Verificamos si puede llegar algún cliente a la cola
		for(i = 0; i<3; i++){
			if(tiempo % (tiempos_cliente[i] / 10) == 0){
				cliente++;
				if(cliente > 5) cliente == 0;
				nclientes[i]++;
				char str[10];
				if(i==0) strcpy(str, "C:");
				if(i==1) strcpy(str, "U:");
				if(i==2) strcpy(str, "P:");
				
				sprintf(str, "%s%d", str, nclientes[i]);
				strcpy(e.t_cliente, str);
				Queue(&clientes[i], e);
				Encolar(&clientes[i], calcularPosicionX(i+1, 3), POS_Y_CLIENTES);
			}
		}
	}
	return 0;
}
