/*
 * Equipo.cpp
 *
 *  Created on: 22/05/2016
 *      Author: gaston
 */

#include "Equipo.h"

Equipo::Equipo(std::string numero){
	this->numero = numero;
	this->llamadas = new Lista<Llamada*>;
	this->ultimaConexionAntena = new Conexion();

	this->llamadasEntrantes = 0;
	this->llamadasSalientes = 0;
	this->entrantesOcupado = 0;
	this->salientesOcupado = 0;
}


std::string Equipo::obtenerNumero(){
	return this->numero;
}

Lista<Llamada*>* Equipo::obtenerLLamadasEquipo(){
	return this->llamadas;
}

Llamada* Equipo::obtenerUltimaLlamada(){
	this->llamadas->iniciarCursor(); // el ultimo esta en la ultima posicion
	bool encontrado=false;
	Llamada* llamada;
	while(this->llamadas->avanzarCursor() && !encontrado){
		llamada=this->llamadas->obtenerCursor();
		encontrado=(!llamada->estaFinalizada());
	}
	return llamada;

}

Conexion* Equipo::obtenerUltimaConexion(){
	return this->ultimaConexionAntena;
}

bool Equipo::estaConectado(){
	return this->ultimaConexionAntena->estaConectado();
}

bool Equipo::estaOcupado(){
	return (!this->obtenerUltimaLlamada()->estaFinalizada());
}

void Equipo::incrementarLlamadasSalientes(){
	this->llamadasSalientes++;
}

void Equipo::incrementarLlamadasEntrantes(){
	this->llamadasEntrantes++;
}

void Equipo::incrementarSalientesOcupado(){
	this->salientesOcupado++;
}

void Equipo::incrementarEntrantesOcupado(){
	this->entrantesOcupado++;
}

unsigned int Equipo::obtenerLlamadasEntrantes(){
	return this->llamadasEntrantes;
}

unsigned int Equipo::obtenerLlamadasSalientes(){
	return this->llamadasSalientes;
}

unsigned int Equipo::obtenerLlamadasSalienteOcupado(){
	return this->salientesOcupado;
}

unsigned int Equipo::obtenerLlamadasEntranteOcupado(){
	return this->entrantesOcupado;
}

Equipo::~Equipo(){
	this->llamadas->iniciarCursor();
	while(this->llamadas->avanzarCursor()){
		delete this->llamadas->obtenerCursor();
	}
	delete (this->llamadas);
	delete (this->ultimaConexionAntena);
}
