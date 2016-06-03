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

void Conexion::desconectar(){
	conectado = false;
}

bool Conexion::estaConectado(){
	return (this->conectado);
}

std::string Conexion::obtenerNombreAntena(){
	return this->nombreAntena;
}

void Conexion::cambiarNombreAntena(std::string nombre){
	this->nombreAntena = nombre;
}


