/*
Autor: 
Versión 1.0
Descripción: Cabecera de la libreria para mostrar las colas de manera más agradable para el usuario

Observaciones: La implementación solo funciona para entornos que puedan leer caracteres de utf-8
	Funciones adapatadas para la simulación 1
*/

//DEFINICIONES DE CONSTANTES
#define TRUE	1
#define FALSE	0

//DEFINICIONES DE TIPOS DE DATO

//Definir un boolean (Se modela con un "char")
typedef unsigned char boolean;


//DECLARACIÓN DE FUNCIONES
void Encolar(cola * c, int i);	//Encolar : Recibe una cola y el numero de fila de esa cola e imprime la cola con el nuevo elemento
void Desencolar(cola * c, int i);			//Desencolar: Recibe una cola y el numero de fila de esa cola: recorre la fila para eliminar el primer elemento
void limpiarCola(int i);	//LimpiarCola: Recibe el indice de la cola a eliminar: Limpia en la cola mencionada
void limpiarLinea(int x, int y);	//LimpiarLinea: Recibe la posicion (x,y) y limpia en solo una linea de la cola
void imprimirCliente(int numero, int x, int y, const char* color, const char* icono); 
	//ImprimirCliente: Recibe el número de cliente, la posición (x,y) en la que se imprimira, el color del número del cliente y el emoji que tendra ese cliente