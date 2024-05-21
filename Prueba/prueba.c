/*
hay que compilar: 
gcc prueba.c TADColaDin.c formato.c presentacionWin.c/presentacionLin.c  -o a
Trate de hacerlo de forma en que todo lo relacionado a como se impriman las colas
	esten dentro de formato.c (para evitar extender el codigo)
	En formato tenemos definidas las variables para el espacio de cada fila y columna
*/

//LIBRERAS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "TADColaDin.h"
#include "formato.h"
#include "presentacion.h"

#define TIEMPO_BASE 200

int main(void)
{
	int n, i, j;
	scanf("%d",&n); //leemos el numero de cajas
	cola filas[n];
	int contador = 1;
	elemento e;
	BorrarPantalla();
	for(i=0; i<n;i++){
		scanf("%d", &j); //leemos el numero de elementos 
		Initialize(&filas[i]);
		for(;j>0;j--, contador++){
			e.n = contador;
			Queue(&filas[i], e);
			Encolar(&filas[i], i+1);
			EsperarMiliSeg(TIEMPO_BASE);
		}
		MoverCursor(0,0);
	}
	
	//Quitamos elementos para observar el correcto funcionamiento de Desencolar
	int n_eliminar;
	scanf("%d", &n_eliminar); //pedimos n elementos a eliminar
	for(i=1;i<=n_eliminar;i++){
		scanf("%d", &j);//leemos la fila en la que quitaremos un elemento 1 - n
		Dequeue(&filas[j-1]);
		Desencolar(&filas[j-1], j);
		MoverCursor(0,0);
	}
	return 0;
}
