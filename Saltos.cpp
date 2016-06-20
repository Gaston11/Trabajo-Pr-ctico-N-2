/*
 * Saltos.cpp
 *
 *  Created on: 19 de jun. de 2016
 *      Author: noe
 */

#include "Saltos.h"

Saltos::Saltos(Lista<Equipo*>* equipos, Lista<Antena*>* antenas){

	this->equipos = equipos;
	this->antenas = antenas;
	this->rango = this->equipos->contarElementos();

	for (unsigned int i=0; i<this->rango; i++){
		for(unsigned int j=0; j<this->rango; j++){
			this->matriz[i][j]=0;
		}
	}
}

void Saltos::cantidadSaltos(){
	//contabilizar la cantidad de saltos con los equipos
	this->contabilizarSaltos();

	std::cout<<"Cantidad de saltos por cada par de antenas: "<<std::endl;
	for (unsigned int fila=0;fila<this->rango;fila++){
		for (unsigned int columna=fila+1; columna<this->rango;columna++){

			std::cout << this->antenas->obtener(fila+1)->obtenerNombre();
			std::cout << " - ";
			std::cout << this->antenas->obtener(columna+1)->obtenerNombre();
			std::cout << " ";
			std::cout << this->matriz[fila][columna];
			std::cout << " saltos "<<std::endl;
		}

	}
}

void Saltos::contabilizarSaltos(){
	this->equipos->iniciarCursor();
	Lista<Llamada*>* llamadas;
	while(this->equipos->avanzarCursor()){
		llamadas=this->equipos->obtenerCursor()->obtenerLLamadasEquipo();
		this->procesarLlamadas(llamadas);

	}
}

void Saltos::procesarLlamadas(Lista<Llamada*>* llamadas){
	llamadas->iniciarCursor();
	Llamada* llamada;
	Lista<AntenaUtilizada*>* antenasUtilizadas;
	while(llamadas->avanzarCursor()){
		llamada=llamadas->obtenerCursor();
		if (!llamada->esOcupado()){
			antenasUtilizadas = llamada->obtenerAntenasUtilizadas();
			this->procesarAntenas(antenasUtilizadas);
		}
	}
}

void Saltos::procesarAntenas(Lista<AntenaUtilizada*>* antenasUtilizadas){
	antenasUtilizadas->iniciarCursor();
	AntenaUtilizada* antena;

	Grafo<unsigned int>* diagrama = new Grafo<unsigned int>;
	unsigned int verticeIni=0,verticeFin=0,pos;

	while(antenasUtilizadas->avanzarCursor()){
		antena=antenasUtilizadas->obtenerCursor();
		pos=this->obtenerPosicionAntena(antena->obtenerNombreAntena());

		if(!verticeIni){
			verticeIni=pos;
			diagrama->agregarVertice(verticeIni);
		}
		else if(!verticeFin){
			verticeFin=pos;
			diagrama->agregarVertice(verticeFin);
			diagrama->agregarArista(verticeIni,verticeFin);
		}
		else if(verticeIni==pos){
			verticeIni=verticeFin;
			verticeFin=pos;

		}else{
			verticeIni=verticeFin;
			verticeFin=pos;
			diagrama->agregarVertice(verticeFin);
			diagrama->agregarArista(verticeIni,verticeFin);
		}
	}
	this->sumarSaltos(diagrama);
	delete diagrama;
}

unsigned int Saltos::obtenerPosicionAntena(std::string nombre){
	unsigned int pos=0;
	this->antenas->iniciarCursor();
	bool encontrado=false;

	while(this->antenas->avanzarCursor() && ! encontrado){
		pos++;
		encontrado=(this->antenas->obtenerCursor()->obtenerNombre()==nombre);
	}
	return pos;
}

void Saltos::sumarSaltos(Grafo<unsigned int>* diagrama){
	Lista<Lista<unsigned int>*>* aristas=diagrama->obtenerAristas();
	Lista<unsigned int>* vertices=diagrama->obtenerVertices();
	Lista<unsigned int>* arista;
	unsigned int fila,columna;

	aristas->iniciarCursor();
	vertices->iniciarCursor();

	while(aristas->avanzarCursor() && vertices->avanzarCursor()){
		fila=vertices->obtenerCursor();
		arista=aristas->obtenerCursor();

		while(arista->avanzarCursor()){
			columna=arista->obtenerCursor();
			if(fila<columna){this->matriz[fila-1][columna-1]++;}
			else{this->matriz[columna-1][fila-1]++;}
		}
	}

}

Saltos::~Saltos(){

}
