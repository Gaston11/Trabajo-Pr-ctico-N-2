/*
 * Llamada.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: noe
 */


#ifndef LLAMADA_H_INCLUDED
#define LLAMADA_H_INCLUDED

#include "AntenaUtilizada.h"
#include "Lista.h"
#include "Equipo.h"

class Equipo;
class AntenaUtilizada;

class Llamada{


private:
	Equipo* equipoLlamada;
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
	Llamada( Equipo* equipoLlamada,std::string tipo);

	/*
	 * pre : si reciebe solo un equipo no recibe un tipo porque es receptor
	 * post: inicializa la llamada como entrante
	 */
	Llamada(Equipo* miequipo);

	/*
	 * post: devuelve el equipo con el que se comunico
	 */
	Equipo* obtenerCelular();

	/*
	 * post: indica si la llamada es entrante
	 */
	bool esLlamadaEntrante();

	/*
	 * post: indica si la llamada es realizada
	 */
	bool esLlamadaRealizada();

	/*
	 * post: indica si la llamada fue ocupada
	 */
	bool esOcupado();

	/*
	 * post: finaliza la llamda
	 */
	void finalizarLlamada();

	/*
	 * post: indica si la llamada finalizo
	 */
	bool estaFinalizada();

	/*
	 * pre : si la llamada fue creada
	 * post: cambia el estado de la llamada en ocupado y la finaliza
	 */
	void cambiarOcupado();

	/*
	 * post: devuelve una lista de antenas utilidas durante la llamada
	 */
	Lista<AntenaUtilizada*>* obtenerAntenasUtilizadas();

	/*
	 * post: elimina los recursos utilizados
	 */
	~Llamada();

};


# endif //LLAMADA_H_INCLUDED


