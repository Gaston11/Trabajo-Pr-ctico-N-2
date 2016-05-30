/*
 * Antena.cpp
 *
 *  Created on: 22/05/2016
 *      Author: gaston
 */
#include "Antena.h"
#include "Lista.h"

Antena::Antena(std::string nombreAntena, unsigned int conexiones){
	this-> nombreAntena = nombreAntena;
	this->cantidadConexiones = conexiones;
	this->cantidadEquiposConectados = 0;
	this->cantidadLlamadasAnuladas = 0;
	this->equiposQueConectaron = 0;
}

Antena::~Antena(){
	//nada
}

std::string Antena::obtenerNombre(){
	return this->nombreAntena;
}

void  Antena::agregarEquipoQueConecto(Equipo* equipo){
	this->equiposQueConectaron->agregar(equipo);

}

Lista<Equipo*>* Antena::obtenerEquiposQueConectaron(){
	return equiposQueConectaron;
}

void Antena::incrementarCantidadEquiposConectados(){
	this->cantidadEquiposConectados++;
}

void Antena::incrementarLlamadasAnuladas(){
	this->cantidadLlamadasAnuladas++;
}

void Antena::decrementarCantidadEquiposConectados(){
	if (this->cantidadEquiposConectados > 0)
		this->cantidadEquiposConectados --;
}

bool Antena::hayCapacidadAntena(){
	return (this->cantidadEquiposConectados  <  this->cantidadConexiones);
}

unsigned int Antena::retornarCantidadDeConexiones(){
	return this->cantidadConexiones;
}

unsigned int Antena::retornarCantidadDeEquiposConectados(){
	return this->cantidadEquiposConectados;
}

unsigned int Antena::retornarCantidadDeLlamadasAnuladas(){
	return this->cantidadLlamadasAnuladas;
}
