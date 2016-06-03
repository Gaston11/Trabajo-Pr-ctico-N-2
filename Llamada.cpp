/*
 * Llamada.cpp
 *
 *  Created on: 1 de jun. de 2016
 *      Author: noe
 */

#include "Llamada.h"
#include "Equipo.h"

Llamada::Llamada(Equipo* equipo, std::string tipo){
	this->antenasUtilizadas = 0;
	this->celular = equipo;

	this->llamadaEntrante = true;
	this->llamadaRealizada = false;
	this->llamadaFinalizada = false;
	this->ocupado = false;
}

Llamada::Llamada(Equipo* equipo){
	this->antenasUtilizadas = 0;
	this->celular = equipo;

	this->llamadaEntrante = false;
	this->llamadaRealizada = true;
	this->llamadaFinalizada = false;
	this->ocupado = false;
}

std::string Llamada::obtenerCelular(){
	return this->celular->obtenerNumero();
}

bool Llamada::esLlamadaEntrante(){
	return (this->llamadaEntrante);
}

bool Llamada::esLlamadaRealizada(){
	return (this->llamadaRealizada);
}

bool Llamada::esOcupado(){
	return (this->ocupado);
}

void Llamada::finalizarLlamada(){
	this->llamadaFinalizada = true;
}

bool Llamada::estaFinalizada(){
	return (this->llamadaFinalizada);
}

void Llamada::cambiarOcupado(){
	this->ocupado = true;
}

Lista<AntenaUtilizada*>* Llamada::obtenerAntenasUtilizadas(){
	return this->antenasUtilizadas;
}

Llamada::~Llamada(){
	this->antenasUtilizadas->iniciarCursor();
	while(this->antenasUtilizadas->avanzarCursor()){
		delete(this->antenasUtilizadas->obtenerCursor());
	}
}

