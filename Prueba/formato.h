/*
LIBRERIA: Cabecera de el TAD COLA DINÁMICA
AUTOR: Edgardo Adrián Franco Martínez (C) Noviembre 2022
VERSIÓN: 1.7

DESCRIPCIÓN: TAD cola o Queue.
Estructura de datos en la que se cumple:
Los elementos se insertan en un extremo (el posterior) y 
la supresiones tienen lugar en el otro extremo (frente).

OBSERVACIONES: Hablamos de una Estructura de datos dinámica 
cuando se le asigna memoria a medida que es necesitada, 
durante la ejecución del programa. 
 
*/

//DEFINICIONES DE CONSTANTES
#define TRUE	1
#define FALSE	0

//DEFINICIONES DE TIPOS DE DATO

//Definir un boolean (Se modela con un "char")
typedef unsigned char boolean;


//DECLARACIÓN DE FUNCIONES
void Encolar(cola * c, int i);	//Encolar : Recibe una cola y el numero de fila de esa cola e imprime la cola con el nuevo elemento
void Desencolar(cola * c, int i);			//Desencolar (Dequeue): Recibe una cola y el numero de fila de esa cola: recorre la fila para eliminar el primer elemento
void limpiarCola(int i);	//Recibe el indice de la cola a eliminar: Limpia en la cola mencionada
void limpiarLinea(int x, int y);	//Recibe la posicion (x,y) y limpia en solo una linea de la cola
void imprimirFilas(cola cajera[], int n);
void imprimirFilasInicio(cola cajera[], int n);