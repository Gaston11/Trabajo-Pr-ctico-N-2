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
	cantidadConexiones = conexiones;
	cantidadEquiposConectados = 0;
	equiposQueConectaron = 0;
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
