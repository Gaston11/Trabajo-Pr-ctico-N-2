/*
 * AntenaUtilizada.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: noe
 */
#ifndef ANTENAUTILIZADA_H_INCLUDED
#define ANTENAUTILIZADA_H_INCLUDED


#include "Antena.h"

class Antena;

class AntenaUtilizada {

private:
	Antena* antena;
	unsigned int minutoIniciado;
	unsigned int minutoFinalizado;

public:
	/*
	 * post: inicia la antena utilizada durante una llamada y el tiempo
	 * en el que inicio
	 */
	AntenaUtilizada(Antena* antena, unsigned int minuto);

	/*
	 * post: devuelve la antena utilizada
	 */
	Antena* obtenerAntena();

	/*
	 * pre: cuando finaliza la conexion en esta antena
	 * post: guarda el minuto en que se finalizo
	 */
	void finAntenaUtilizada(unsigned int minutoFinal);

	/* pre: minutoFinal > minutoIniciado
	 * post: devuelve la cantidad de minutos que estuvo conectado en
	 * la antena realizando la llamada
	 */
	unsigned int duracionDeMinutosEnAntena();

	/*
	 * post: elimina los recursos compartidos
	 */
	~AntenaUtilizada();
};

#endif //ANTENAUTILIZADA_H_INCLUDED
