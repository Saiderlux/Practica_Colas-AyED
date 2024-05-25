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

	// Definir la estructura del proceso
typedef struct proceso {
    char nombre[45]; 
    char id[45]; 
    char descripcion[200];
    int tiempo_ejecucion;
} proceso;


//Definir la estructura de un nodo dinámico
typedef struct nodo
{
	proceso p;
	struct nodo *siguiente;
}nodo;

//Definir una cola 
typedef struct cola
{
	int num_elem;
	nodo *frente;
	nodo *final;
} cola;

//DECLARACIÓN DE FUNCIONES
void Initialize(cola * c);			//Inicializar cola (Initialize): Recibe una cola y la inicializa para su trabajo normal.
void Queue(cola * c, proceso p);	//Encolar (Queue): Recibe una cola y agrega un elemento al final de ella. 
proceso Dequeue(cola * c);			//Desencolar (Dequeue): Recibe una cola y remueve el elemento del frente retornándolo.
boolean Empty(cola * c);			//Es vacía (Empty): Recibe la cola y devuelve verdadero si esta esta vacía.
proceso Front(cola * c);			//Frente (Front): Recibe una cola y retorna el elemento del frente.	
proceso Final(cola * c);			//Final (Final): Recibe una cola y retorna el elemento del final.
proceso Element(cola *c, int i); 	// Recibe una cola y un número de elemento de 1 al tamaño de la cola y retorna el elemento de esa posición.
int Size(cola *c);					//Tamaño (Size): Retorna el tamaño de la cola 	
proceso Element(cola * c, int i);	//Recibe una cola y un número de elemento de 1 al tamaño de la cola y retorna el elemento de esa posición
void Destroy(cola * c);				//Eliminar cola (Destroy): Recibe una cola y la libera completamente.
