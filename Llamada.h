/*
 * Llamada.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: noe
 */


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
	 *
	 */
	Llamada(); //recibe un equipo y tipo de llamda

	/*
	 * post: devuelve una lista de antenas utilidas durante la llamada
	 */
	Lista<AntenaUtilizada*>* obtenerAntenasUtilizadas();

};


