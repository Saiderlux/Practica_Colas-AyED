/*
Autor: 
Versión 3.0
Descripción: Cabecera de la libreria para mostrar las colas de manera más agradable para el usuario

Observaciones: La implementación solo funciona para entornos que puedan leer caracteres de utf-8
	Funciones adapatadas para la simulación 3
*/

//DEFINICIONES DE CONSTANTES
#define TRUE	1
#define FALSE	0

//DEFINICIONES DE TIPOS DE DATO

//Definir un boolean (Se modela con un "char")
typedef unsigned char boolean;


//DECLARACIÓN DE FUNCIONES
void Encolar(cola * c, int x, int y);	//Encolar : Recibe una cola y la posición en (x,y) de esa cola e imprime la cola con el nuevo elemento
void Desencolar(cola * c, int x, int y);			//Desencolar (Dequeue): Recibe una cola y la posición en (x,y) de esa cola: recorre la fila para eliminar el primer elemento
void limpiarCola(int x, int y);	//LimpiarCola: Recibe la posición en (x,y) de la cola a eliminar: Limpia en la cola mencionada
void limpiarLinea(int x, int y);	//LimpiarLinea: Recibe la posicion (x,y) y limpia en solo una linea de la cola