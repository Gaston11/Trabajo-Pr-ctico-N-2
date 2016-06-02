/*
 * Conexion.cpp
 *
 *  Created on: 22/05/2016
 *      Author: gaston
 */

#include "Conexion.h"

Conexion::Conexion(){
	conectado = false;
}

Conexion::Conexion(std::string nombreAntena ){
	this->nombreAntena = nombreAntena;
	conectado = true;
}

void Conexion::conectar(){
	conectado = true;
}

bool Conexion::estaConectado(){
	return this->conectado;
}

void Conexion::desconectar(){
	conectado = false;
}

std::string Conexion::obtenerNombreAntena(){
	return this->nombreAntena;
}
