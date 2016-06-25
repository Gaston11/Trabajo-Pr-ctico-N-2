/*
 * Llamada.cpp
 *
 *  Created on: 1 de jun. de 2016
 *      Author: noe
 */

#include "Llamada.h"
#include "Equipo.h"

Llamada::Llamada(Equipo* miEquipo, std::string tipo){

	this->antenasUtilizadas = new Lista<AntenaUtilizada*>;
	this->equipoLlamada = miEquipo;

	this->llamadaEntrante = false;
	this->llamadaRealizada = true;
	this->llamadaFinalizada = false;
	this->ocupado = false;
}

Llamada::Llamada(Equipo* miEquipo){
	this->antenasUtilizadas = new Lista<AntenaUtilizada*>;

	this->equipoLlamada= miEquipo;
	this->llamadaEntrante = true;
	this->llamadaRealizada = false;
	this->llamadaFinalizada = false;
	this->ocupado = false;
}

Equipo* Llamada::obtenerCelular(){
	return (this->equipoLlamada);
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
	return (this->antenasUtilizadas);
}

Llamada::~Llamada(){
	this->antenasUtilizadas->iniciarCursor();
	AntenaUtilizada* antena;
	while(this->antenasUtilizadas->avanzarCursor()){
		antena=this->antenasUtilizadas->obtenerCursor();
		delete(antena);
	}
	delete this->antenasUtilizadas;
}

