/*
 * AntenaUtilizada.cpp
 *
 *  Created on: 22/05/2016
 *      Author: gaston
 */
#include "AntenaUtilizada.h"

AntenaUtilizada::AntenaUtilizada(std::string nombreAntena, unsigned int minuto){
	this->nombreAntena = nombreAntena;
	minutoIniciado = minuto;
	minutoFinalizado = 0;
}

void AntenaUtilizada::finAntenaUtilizada(unsigned int minutoFinal){
	minutoFinalizado = minutoFinal;
}

unsigned int AntenaUtilizada::duracionDeMinutosEnAntena(){
	if ( minutoFinalizado > minutoIniciado )
		return (minutoFinalizado - minutoIniciado);
		else
			return 0;
}




