/*
 * Llamada.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: noe
 */
#ifndef LLAMADA_H_INCLUDED
#define LLAMADA_H_INCLUDED

#include "AntenaUtilizada.h"

class Llamada{

#include "Equipo.h"

private:

	Equipo* celular;
	Lista<AntenaUtilizada*>* antenasUtilizadas;

	bool llamadaRealizada;
	bool llamadaEntrante;
	bool ocupado;
	bool llamadaFinalizada;

public:

	/*
	 * pre : recibe un equipo y un tipo
	 * post: si el equipo es emisor tipo = "Inicio" entonces inicializa la
	 * llamada como saliente
	 */
	Llamada(Equipo* equipo, std::string tipo); //recibe un equipo y tipo de llamda

	/*
	 * pre : si reciebe solo un equipo no recibe un tipo porque es receptor
	 * post: inicializa la llamada como entrante
	 */
	Llamada(Equipo* equipo);

	/*
	 * post: indica si la llamada finalizo
	 */
	bool estaFinalizada();

	/*
	 * pre : si la llamada fue creada
	 * post: cambia el estado de la llamada en ocupado
	 */
	void cambiarOcupado();

	/*
	 * post: devuelve una lista de antenas utilidas durante la llamada
	 */
	Lista<AntenaUtilizada*>* obtenerAntenasUtilizadas();

};

# endif //LLAMADA_H_INCLUDED
