/*
 * Equipo.cpp
 *
 *  Created on: 22/05/2016
 *      Author: gaston
 */

#include "Equipo.h"
#include <string>;

Equipo::Equipo(std::string numero){
	this->numero = numero;
	this->id = 0;
	this->llamadas = 0;
	this->ultimaConexionAntena = 0;   // falta metodo obtener ultima conexion
	this->llamadasEntrantes = 0;
	this->llamadasSalientes = 0;
	this->entrantesOcupado = 0;
	this->salientesOcupado = 0;
	this->llamadasAnuladas = 0; //porque la antena no tiene capacidad??
}


void Equipo::cargarId(unsigned int idNuevo){
	this->id = idNuevo;
}

std::string Equipo::obtenerNumero(){
	return this->numero;
}

void Equipo::agregarLlamadas(){
	// preguntar
}

Lista<Llamada*>* Equipo::obtenerLLamadasEquipo(){
	return this->llamadas;
}

Llamada* Equipo::obtenerUltimaLlamada(){
	return this->llamadas->obtener(llamadas->contarElementos()); // el ultimo esta en la ultima posicion

}

Conexion* Equipo::obtenerUltimaConexion(){
	return this->ultimaConexionAntena;
}

bool Equipo::estaConectado(){
	return this->ultimaConexionAntena->estaConectado();
}

bool Equipo::estaOcupado(){
	return this->llamadas->obtener(llamadas->contarElementos())->cambiarOcupado();
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

void Equipo::incrementarLlamadasAnuladas(){
	this->llamadasAnuladas++;
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

unsigned int Equipo::obtenerLlamadasAnuladas(){
	return this->llamadasAnuladas;
}
