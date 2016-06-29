/*
 * Conexion.cpp
 *
 *  Created on: 22/05/2016
 *      Author: gaston
 */

#include "Conexion.h"

Conexion::Conexion(Antena* antena ){
	this->antena = antena;
	conectado = true;
}

void Conexion::conectar(){
	conectado = true;
}

void Conexion::desconectar(){
	conectado = false;
}

bool Conexion::estaConectado(){
	return (this->conectado);
}

Antena* Conexion::obtenerAntena(){
	return this->antena;
}

void Conexion::cambiarAntena(Antena* antenaNueva){
	this->antena = antenaNueva;
	this->conectar();
}

Conexion::~Conexion(){

}


