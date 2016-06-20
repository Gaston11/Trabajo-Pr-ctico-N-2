/*
 * Grafo.h
 *
 *  Created on: 17 de jun. de 2016
 *      Author: noe
 */

#include "Lista.h"

template <class T> class Grafo{
	//nodos que son los vertices en este caso antenas
	//conjunto de aristas
private:
	Lista<T>* vertices;
	Lista<Lista<T>*>* aristas;//(Lista de listas)(con ceros y unos para indicar si hay una arista)
	//en la diagonal hay ceros

public:
	/*
	 * post: crea un grafo vacio
	 */
	Grafo();

	/*
	 * post: elimina todos los recursos utilizados
	 */
	~Grafo();

	/*
	 * pre: el vertice ingresado no esta dado de alta
	 * post: ingresa el vertice al final de los agregados
	 */
	void agregarVertice(T vertice);

	/*
	 * pre: recibe 2 vertices existente, la arista no esta dada de alta
	 * post: agrega la arista
	 */
	void agregarArista(T verticeInicial, T verticeFinal);

	/*
	 * pre: el vertice no tiene asociado ninguna arista
	 * post: elimina el vertice del sistema
	 */
	void eliminarVertice(T vertice);

	/*
	 * pre: los vertices existen
	 * post: elimina la arista asociada a los vertices pasados por parametro
	 */
	void eliminarArista(T verticeInicial, T verticeFinal);

	/*
	 * pre: vertices existentes
	 * post: indica si la arista asociada a los vertices existe
	 */
	bool existeArista(T verticeInicial, T verticeFinal);

	/*
	 * post: indica si el vertice existe
	 */
	bool existeVertice(T vertice);

	/*
	 * pre vertice existente
	 * post: indica si el vertice pertenece alguna arista, es decir
	 * si posee algun verice aldyacente
	 */
	bool existenAristasAsociadas(T vertice);

	/*
	 * post: devuelve una lista de listas de las aristas de un grafo
	 */
	Lista<Lista<T>*>* obtenerAristas();

	/*
	 * post: devuelve una lista de los vertices asociados al grafo
	 */
	Lista<T>* obtenerVertices();

	/*
	 *
	 */
	//recorrido

private:

	/*
	 * post: devuelve la posicion en la que se encuentra en vertice [1 - cantidad de vertices],
	 *  si no existe devuelve una posicion invalida que es igual a cero
	 */
	unsigned int obtenerPosicionVertice(T vertice);

	//crear la matriz de adyacencia
};

template <class T>
Grafo<T>::Grafo(){
	this->vertices = new Lista<T>;
	this->aristas = new Lista<Lista<T>*>; //ver si va el puntero dentro
}

template <class T>
Grafo<T>::~Grafo(){
	delete(this->vertices);
	//ver como eliminar aristas
	this->aristas->iniciarCursor();
	while (this->aristas->avanzarCursor()){
		delete(this->aristas->obtenerCursor());
	}
}

template <class T>
void Grafo<T>::agregarVertice(T vertice){

	if (!this->existeVertice(vertice)){
		Lista<T>* arista=new Lista<T>;
		this->vertices->agregar(vertice);
		this->aristas->agregar(arista);
	}
}

template <class T>
void Grafo<T>::agregarArista(T verticeInicial, T verticeFinal){
	unsigned int posicionInicial;

	if(this->existeVertice(verticeInicial) && this->existeVertice(verticeFinal)){
		posicionInicial = this->obtenerPosicionVertice(verticeInicial);
		this->aristas->obtener(posicionInicial)->agregar(verticeFinal); //agregar posicion O vertice ??

	}

}

template <class T>
void Grafo<T>::eliminarArista(T verticeInicial, T verticeFinal){

	unsigned int pos=0, posicionInicial = this->obtenerPosicionVertice(verticeInicial);
	Lista<T>* vecinos = this->aristas->obtener(posicionInicial);
	vecinos->iniciarCursor();
	bool encontrado = false;
	while(vecinos->avanzarCursor() && ! encontrado){
		pos++;
		encontrado=(vecinos->obtenerCursor()==verticeFinal);
	}
	if (encontrado){
		vecinos->remover(pos);
	}
}

template <class T>
void Grafo<T>::eliminarVertice(T vertice){
	if (!this->existenAristasAsociadas(vertice)){
		unsigned int posicion = this->obtenerPosicionVertice(vertice);
		this->vertices->remover(posicion);
		this->aristas->remover(posicion);
	}
}

template <class T>
bool Grafo<T>::existeVertice(T vertice){
	unsigned int encontrado = this->obtenerPosicionVertice(vertice);
	return encontrado;
}

template <class T>
bool Grafo<T>::existeArista(T verticeInicial, T verticeFinal){

	unsigned int pos=0,posicion = this->obtenerPosicionVertice(verticeInicial);
	Lista<T>* vecinos = this->aristas->obtener(posicion);
	vecinos->iniciarCursor();
	bool encontrado=false;
	while(vecinos->avanzarCursor() && ! encontrado){
		encontrado=(vecinos->obtenerCursor()==verticeFinal);
	}
	return encontrado;
}

template <class T>
bool Grafo<T>::existenAristasAsociadas(T vertice){
	unsigned int posicion = this->obtenerPosicionVertice(vertice);
	return(this->aristas->obtener(posicion)->contarElementos());
}

template <class T>
Lista<Lista<T>*>* Grafo<T>::obtenerAristas(){
	return this->aristas;
}

template <class T>
Lista<T>* Grafo<T>::obtenerVertices(){
	return this->vertices;
}

template <class T>
unsigned int Grafo<T>::obtenerPosicionVertice(T vertice){
	this->vertices->iniciarCursor();
	bool encontrado = false;
	unsigned int i =0;
	while(this->vertices->avanzarCursor() && ! encontrado){
		i++;
		encontrado=(this->vertices->obtenerCursor() == vertice);

	}
	if (!encontrado){
		i=0;
	}
	return i;
}
