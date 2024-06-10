/*
Main de la simulación 1: Supermercado
AUTOR: 
VERSIÓN: 1.1

DESCRIPCIÓN: Simulación de un supermercado
	Simular la atención de clientes en un supermercado, el cuál deberá
	atender al menos 100 clientes por día para no tener perdidas.
	
OBSERVACIONES: Una vez que ya se atendieron a más de 100 personas y no hay
	gente formada en las cajas puede cerrar la tienda. Mientras no se cierre
	la tienda, las personas podrán seguir llegando a las cajas.

COMPILACIÓN: 
Windows (en Windows Terminal):
	CHCP 65001
	gcc Cajeras.c formato.c presentacionWin.c TadColaDin.c -o supermercado
Linux:
	sudo locale-gen es_ES.UTF-8 && sudo update-locale LANG=es_ES.UTF-8
		&& gcc Cajeras.c formato.c presentacionLin.c TADColaDin.c -o supermercado
*/

// LIBRERÍAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TADColaDin.h"    //Si se usa la implemtentación estática (TADColaEst.c|TADColaEstCirc.c)
#include "formato.h"
#include "presentacion.h"

// DEFINICIÓN DE CONSTANTES
#define TIEMPO_BASE    200    // Tiempo base en ms
#define TAM_MAX_X    150    // Tamaño de la pantalla en X
#define Y_CAJAS    3    // Línea de las cajas
#define CLIENTES_OBJETIVO 100 // Número de clientes objetivo

// Secuencias de escape ANSI para colores
#define COLOR_RESET   "\x1b[0m"
#define COLOR_CAJAS   "\x1b[33m" // Amarillo
#define COLOR_TITULO  "\x1b[34m" // Azul
#define COLOR_CLIENTE "\x1b[32m" // Verde

// DECLARACIÓN DE FUNCIONES
int calcularPosicionX(int columna, int n_columnas);
int colocarCajas(int i, int x, int n);
void imprimirTitulo(const char *nombre);
int clientesEnColas(cola cajera[], int n);


//******************************************************************************************************
//	MAIN
//******************************************************************************************************
int main(void)
{
	BorrarPantalla();
	EsperarMiliSeg(2000);
    char nombre[100];
    int n, tiempo_cliente;
    unsigned int tiempo = 0;
    unsigned int cliente = 0;
    unsigned int clientes_atendidos = 0;
    int i, fila;
    elemento e;
    
    printf("Ingresa el nombre del supermercado: ");
    scanf("%s", nombre);
    printf("Ingresa la cantidad de cajas: ");
    scanf("%d", &n);
    
    // Variables dependientes de n
    int tiempos_atencion[n];
    // Crear n colas
    cola cajera[n];
    
    printf("Ingresa el tiempo en atender de cada caja: \n");
    for(i = 0; i < n; i++){
        printf("%d: ", i + 1);
        scanf("%d", &tiempos_atencion[i]);
        Initialize(&cajera[i]);
    }
    
    printf("Ingresa el tiempo de llegada de los clientes ms: ");
    scanf("%d", &tiempo_cliente);
    
    // Inicializar la función rand
    srand(time(NULL));
    
    BorrarPantalla();
    
    // Imprimir título
    imprimirTitulo(nombre);

    // Imprimir las cajas
    for(i = 1; i <= n; i++)
        colocarCajas(i, calcularPosicionX(i, n),0);
    

    // Ciclo principal
    while (1)
    {
        EsperarMiliSeg(TIEMPO_BASE);  // Esperar el tiempo base
        tiempo++;  // Incrementar el contador de tiempo
        
        for(i = 0; i < n; i++){
            if(tiempo % (tiempos_atencion[i] / 10) == 0){  // se divide sobre 10 ya que tiene que ser un multiplo de 10
                if (!Empty(&cajera[i])){
                    e = Dequeue(&cajera[i]);
                    Desencolar(&cajera[i], calcularPosicionX(i + 1, n));
                    clientes_atendidos++;
                }
            }
        }

       if (tiempo % (tiempo_cliente / 10) == 0) {
            cliente++;
            e.n = cliente;
            fila = rand() % n;
            Queue(&cajera[fila], e);
            Encolar(&cajera[fila], calcularPosicionX(fila + 1, n));  
        }


        // Verificar condición de término
        if (clientes_atendidos >= CLIENTES_OBJETIVO && clientesEnColas(cajera, n) == 0) {
            // Imprimir las cajas
            for(i = 1; i <= n; i++){
                colocarCajas(i, calcularPosicionX(i, n),1);
            }
            printf("\nSe han atendido a %d clientes y todas las colas están vacías. Fin del día.\n", CLIENTES_OBJETIVO);
           
            break;
        }
    }
    
	for(i = 0; i < n;i++){
		Destroy(&cajera[i]);
	}
	EsperarMiliSeg(7000);
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
void colocarCajas(int i, int x, int n);
Descripción: Imprime las cajas en la posición en x que se le indica y dependiendo de n
	imprimira el tipo de caja correspondiente
Recibe: int i (número de caja), int x (posición en x en la que se imprimira la caja),
	int n (bandera para saber que tipo de caja corresponde)
Devuelve: void
Observaciones: El usuario no debe de excederse en cajas de más de 2 digitos, así como para
	n colocar un valor valido (0: abierto, cualquier otro: cerrado)
*/
int colocarCajas(int i, int x, int n){
	char aux[20], resultado_str[3];
    sprintf(resultado_str, "%d", i);
	if(n==0){
		if(i==10)
			strcpy(aux, "🙂🟢 ");
		else
			strcpy(aux, "🙂🟢  ");
	}
    else
	{
		if(i==10)
			strcpy(aux, "😴🔴 ");
		else
			strcpy(aux, "😴🔴  ");
	}
	strcat(aux, resultado_str);
	strcat(aux, " ");
	MoverCursor(x-((int)strlen(aux)/2), Y_CAJAS-1);
	printf(COLOR_CAJAS "┌────────┐" COLOR_RESET);
	MoverCursor(x-((int)strlen(aux)/2), Y_CAJAS);
	printf(COLOR_CAJAS "│%s│" COLOR_RESET, aux);
	MoverCursor(x-((int)strlen(aux)/2), Y_CAJAS+1);
	printf(COLOR_CAJAS "└────────┘" COLOR_RESET);
    
}

/*
void imprimirTitulo(const char *nombre);
Descripción: Imprime el nombre del supermercado en la parte superior de la simulación
Recibe: const char *nombre (apuntador a el nombre del supermercado)
Devuelve: void
Observaciones: El nombre ya debe estar inicializado, la posición depende de TAM_MAX_X
	y el color en el que se imprimira depende de COLOR_TITULO
*/
void imprimirTitulo(const char *nombre) {
    int x = TAM_MAX_X / 2;
    int y = 1;  // Línea superior de la pantalla
    MoverCursor(x - ((int)strlen(nombre) / 2), y);
    printf(COLOR_TITULO "%s" COLOR_RESET, nombre);
}

/*
int clientesEnColas(cola cajera[], int n);
Descripción: Cuenta el número de clientes que hay en cada cola en ese momento
Recibe: cola cajera[] (arreglo de colas de las cajas), int n (número de cajas)
Devuelve: int (el número de clientes que hay en todas las cajas en "total")
Observaciones: El arreglo de colas ya debe estar incializada y n > 0
*/
int clientesEnColas(cola cajera[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += Size(&cajera[i]);
    }
    return total;
}