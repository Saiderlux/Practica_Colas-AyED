/*
Ejecucion:
gcc Cajeras.c formato.c presentacionWin/Lin.c TadColaDin.c -o cajeras

Ya funciona(en teoria), solo falta la condición de término, solo que
	no entiendo si cuando llegue a minimo 100 personas dejaran de llegar
	personas o ya después de las 100 personas esperemos hasta que esten vacias las colas
	y terminamos el "dia"
	
Otra cosa esto es solo la logica de como podría funcionar solo faltaría que se vea bien
*/

// LIBRERAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include "TADCola/TADColaEst.h"     //Si se usa la implemtentación dinámica (TADColaDin.c)
#include "TADColaDin.h"    //Si se usa la implemtentación estática (TADColaEst.c|TADColaEstCirc.c)
#include "formato.h"
#include "presentacion.h"

// DEFINICION DE CONSTANTES
#define TIEMPO_BASE    200    // Tiempo base en ms
#define TAM_MAX_X    100    // Tamaño de la pantalla en X
#define Y_CAJAS    3    // Línea de las cajas
#define CLIENTES_OBJETIVO 100 // Número de clientes objetivo

// Secuencias de escape ANSI para colores
#define COLOR_RESET   "\x1b[0m"
#define COLOR_CAJAS   "\x1b[33m" // Amarillo
#define COLOR_TITULO  "\x1b[34m" // Azul
#define COLOR_CLIENTE "\x1b[32m" // Verde

// DEFINICION DE FUNCIONES
int calcularPosicionX(int columna, int n_columnas);
int colocarCajas(int i, int x);
void imprimirTitulo(const char *nombre);
void imprimirClientes(cola cajera[], int n);
int clientesEnColas(cola cajera[], int n);

int main(void)
{
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
    for(i = 1; i <= n; i++){
        colocarCajas(i, calcularPosicionX(i, n));
    }

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

        if (tiempo % (tiempo_cliente / 10) == 0 && cliente < CLIENTES_OBJETIVO){
            cliente++;  // Incrementar el numero de clientes
            e.n = cliente;  // Dar el numero que identifica al cliente
            fila = rand() % n;  // Escoger la fila para formarse aleatoriamente
            Queue(&cajera[fila], e);  // Formarse en la fila seleccionada
            Encolar(&cajera[fila], calcularPosicionX(fila + 1, n));
        }

        // Verificar condición de término
        if (clientes_atendidos >= CLIENTES_OBJETIVO && clientesEnColas(cajera, n) == 0) {
            printf("\nSe han atendido a %d clientes y todas las colas están vacías. Fin del día.\n", CLIENTES_OBJETIVO);
            break;
        }
    }
    
    return 0;
}

int calcularPosicionX(int columna, int n_columnas) {
    // Calcular el ancho de cada columna
    int ancho_columna = TAM_MAX_X / (n_columnas + 1);
    // Calcular la posición x de la columna específica
    int posicion_x = ancho_columna * columna;
    
    return posicion_x;
}

int colocarCajas(int i, int x){
    char aux[20], resultado_str[2];
    sprintf(resultado_str, "%d", i);
    strcpy(aux, "[ ");
    strcat(aux, resultado_str);
    strcat(aux, " ]");
    MoverCursor(x - ((int)strlen(aux) / 2), Y_CAJAS);
    printf(COLOR_CAJAS "%s" COLOR_RESET, aux);
}

void imprimirTitulo(const char *nombre) {
    int x = TAM_MAX_X / 2;
    int y = 1;  // Línea superior de la pantalla
    MoverCursor(x - ((int)strlen(nombre) / 2), y);
    printf(COLOR_TITULO "%s" COLOR_RESET, nombre);
}

void imprimirClientes(cola cajera[], int n) {
    for (int i = 0; i < n; i++) {
        int x = calcularPosicionX(i + 1, n);
        int y = Y_CAJAS + 2;
        nodo *temp = cajera[i].frente;
        while (temp != NULL) {
            char cliente_str[3];
            sprintf(cliente_str, "%d", temp->e.n);
            MoverCursor(x, y);
            printf(COLOR_CLIENTE "%s" COLOR_RESET, cliente_str);
            y++;
            temp = temp->siguiente;
        }
    }
}

int clientesEnColas(cola cajera[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += Size(&cajera[i]);
    }
    return total;
}
