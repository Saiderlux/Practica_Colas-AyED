/*
Main de la simulación 3: 
AUTOR: 
VERSIÓN: 1.1

DESCRIPCIÓN: Simula la atención de personas en un banco, cuidando sean
	respetadas las políticas de atención del mismo y evitando que las personas
	no dejen de ser atendidas.
	
OBSERVACIONES: Se tienen tres tipos de clientes cada uno con diferente prioridad
	para ser atendidos pero hay que cuidar que siempre sean atendidos los clientes
	
COMPILACIÓN: 
Windows (en Windows Terminal):
	CHCP 65001
	gcc Banco.c formato.c presentacionWin/Lin.c TadColaDin.c -o banco
Linux:
	(chcp 65001/sudo locale-gen es_ES.UTF-8 && sudo update-locale LANG=es_ES.UTF-8)
		&& gcc Banco.c formato.c presentacion(Win/Lin).c TADColaDin.c -o banco
*/

//LIBRERAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "presentacion.h"
#include <time.h>
#include "TADColaDin.h" //Si se usa la implemtentación estática (TADColaEst.c|TADColaEstCirc.c)
#include "formato.h"

//DEFINICION DE CONSTANTES
#define TIEMPO_BASE	200 // Tiempo base en ms
#define POS_Y_CAJAS 3 // Posición en Y en la que se imprimen los cajeros
#define POS_Y_CLIENTES 12 // Posición en Y en la que se imprimen los clientes
#define TAM_MAX_X 150 // Tamaño de la pantalla en X
#define COLOR_CAJAS "\x1b[36m" // Código ANSI para color celeste
#define COLOR_RESET "\x1b[0m"  // Código ANSI para restablecer el color a blanco
#define COLOR_FILAS "\x1b[37;1m" // Color gris claro para las filas

// DECLARACIÓN DE FUNCIONES
int calcularPosicionX(int columna, int n_columnas);
int colocarCajas(int i, int x, int y);
void imprimirFila(int x, int y, int tipo_fila);

//******************************************************************************************************
//	MAIN
//******************************************************************************************************
int main(void)
{
	BorrarPantalla();
	EsperarMiliSeg(2000);
	int n, tiempo_atencion, tiempos_cliente[3];
	unsigned int tiempo = 0;
	unsigned int cliente = 0, contador2= 0;
	int i, j,fila, bandera=0, bandera2 = 0;
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
		imprimirFila(calcularPosicionX(1, 3), POS_Y_CLIENTES, 0); // Clientes del banco
		imprimirFila(calcularPosicionX(2, 3), POS_Y_CLIENTES, 1); // Usuarios del banco
		imprimirFila(calcularPosicionX(3, 3), POS_Y_CLIENTES, 2); // Clientes preferentes
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
			if(!Empty(&cajeros[i])){//si estan ocupada la caja
				if(tiempo % (tiempo_atencion / 10) == 0){// si ya paso el tiempo de atencion, se remueve a la persona que se estaba atendiendo
					e = Dequeue(&cajeros[i]);
					limpiarLinea(calcularPosicionX(i+1, n), POS_Y_CAJAS);
					//Desencolar(&cajeros[i], calcularPosicionX(i+1, n), POS_Y_CAJAS);
					//printf("Se atendio a %d\n", e.n);
				}
			}else{ // si hay cajas vacias, debemos saber cuantas y cuales
				arrAux[cajasVacias++] = i;// para saber cuantas, nos ayudamos de "cajasVacias";  para saber cuales, del arreglo arrAux 
				//para saber especificamente cuales cajas estan vacías, las guardamos de acuerdo con su índice i;
			}
		}
		
		//Si hay cajas vacias mandamos un cliente según la prioridad
		if (cajasVacias > 0) {
			fila = arrAux[rand() % cajasVacias]; //Fila vacia aleatoria a la que se manda un cliente// elije aleatoriamente entre la cantidad de cajas vacias. Despues, accede a la posicion de esta para saber cual es esa caja (el indice i guardado) 
			//Verificamos si hay clientes y su prioridad
			if(!Empty(&clientes[0]) && ((bandera==0 && bandera2==1) || Empty(&clientes[2]))){//clientes
				e = Dequeue(&clientes[0]);
				Desencolar(&clientes[0], calcularPosicionX(1,3), POS_Y_CLIENTES);
				Queue(&cajeros[fila], e);
				Encolar(&cajeros[fila], calcularPosicionX(fila+1, n), POS_Y_CAJAS);
				contador2=0;
				bandera2=0;
				if((cliente++)==5)
					bandera=1;
			}
			else if(!Empty(&clientes[2]) && bandera==0){//preferentes
				e = Dequeue(&clientes[2]);
				Desencolar(&clientes[2], calcularPosicionX(3,3), POS_Y_CLIENTES);
				Queue(&cajeros[fila], e);
				Encolar(&cajeros[fila], calcularPosicionX(fila+1, n), POS_Y_CAJAS);
				if((cliente++)==5)
					bandera=1;
				if((contador2++)==3) bandera2=1;
			} 
			 else if(!Empty(&clientes[1]) && ( bandera==1 || ( Empty(&clientes[0]) && Empty(&clientes[2] ) ))){//usuarios
				e = Dequeue(&clientes[1]);
				Desencolar(&clientes[1], calcularPosicionX(2,3), POS_Y_CLIENTES);
				Queue(&cajeros[fila], e);
				Encolar(&cajeros[fila], calcularPosicionX(fila+1, n), POS_Y_CAJAS);
				bandera=0;
				cliente=0;
			}
			
		}
		
		//Verificamos si puede llegar algún cliente a la cola
		for(i = 0; i<3; i++){
			if(tiempo % (tiempos_cliente[i] / 10) == 0){
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

//******************************************************************************************************
//	FUNCIONES
//******************************************************************************************************
/*
void calcularPosicionX(int columna, int n_columnas);
Descripción: Retornar la posición en la que debe colocarse cada cola
	según la cantidad de cajas
Recibe: int columna(número de caja a retornar su pos), int n_columnas (número de cajas)
Devuelve: void
Observaciones: El usuario no se debe de exceder del número de cajas y debe considerar
	el TAM_MAX_X que es la anchura del programa
*/
int calcularPosicionX(int columna, int n_columnas) {
    // Calcular el ancho de cada columna
    int ancho_columna = TAM_MAX_X / (n_columnas + 1);
    // Calcular la posición x de la columna específica
    int posicion_x = ancho_columna * columna;
    
    return posicion_x;
}

/*
void colocarCajas(int i, int x, int y);
Descripción: Imprime la caja i en la posición (x,y)
Recibe: int i (número de caja), int x (posición en x en la que se imprimira la caja),
	int y (posición en Y en la que se imprimira la caja)
Devuelve: void
Observaciones: El usuario no debe de excederse en cajas de más de 2 digitos
	Realmente se imprime en y-1, debido a que se considera que en esa posición empiezan
	las colas 
*/
int colocarCajas(int i, int x, int y) {
    char aux[20];
    sprintf(aux, "🟢👨‍💼%d", i);
    MoverCursor(x - ((int)strlen(aux) / 2), y);
    printf(COLOR_CAJAS "┌────────┐" COLOR_RESET);
    MoverCursor(x - ((int)strlen(aux) / 2), y + 1);
    printf(COLOR_CAJAS "│%s│" COLOR_RESET, aux);
    MoverCursor(x - ((int)strlen(aux) / 2), y + 2);
    printf(COLOR_CAJAS "└────────┘" COLOR_RESET);
}



void imprimirFila(int x, int y, int tipo_fila) {
    char fila[30]; // Aumentar el tamaño del arreglo
    char emoji[5]; // Aumentar el tamaño del arreglo

    switch (tipo_fila) {
        case 0:
            strncpy(emoji, "💼", sizeof(emoji)); // Utilizar strncpy para evitar desbordamiento
            strncpy(fila, "Clientes del banco", sizeof(fila));
            break;
        case 1:
            strncpy(emoji, "👤", sizeof(emoji));
            strncpy(fila, "Usuarios del banco", sizeof(fila));
            break;
        case 2:
            strncpy(emoji, "👑", sizeof(emoji));
            strncpy(fila, "Clientes preferentes", sizeof(fila));
            break;
    }

    MoverCursor(x - strlen(fila) / 2, y);
    printf(COLOR_FILAS "╔═");
    printf("%-*s", strlen(fila) + 2, "");
    printf(" ═╗" COLOR_RESET);

    MoverCursor(x - strlen(fila) / 2, y + 1);
    printf(COLOR_FILAS "║" COLOR_RESET " %s %s" COLOR_FILAS " ║" COLOR_RESET, emoji, fila);

    MoverCursor(x - strlen(fila) / 2, y + 2);
    printf(COLOR_FILAS "╚═");
    printf("%-*s", strlen(fila) + 2, "");
    printf(" ═╝" COLOR_RESET);
}