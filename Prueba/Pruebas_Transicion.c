//Compilar: gcc Pruebas_Transicion.c presentacion(Win/Lin).c -o prueba

//LIBRERAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "presentacion.h"


// Función de transición de esquina a esquina
void Transicion() {
    int tamX = 150;
    int tamY = 30;
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
}

// Función de transición de izquierda a derecha
void OtraTransicion(){
	int tamX = 150, tamY = 30;
	for(int x = 0; x < tamX; x++){
		for(int y = 0; y < tamY; y++){
			MoverCursor(x,y);
			printf("*");
		}
		EsperarMiliSeg(5);
	}
}
int main(void)
{
	Transicion();
	BorrarPantalla();
	OtraTransicion();
	BorrarPantalla();
	return 0;
}