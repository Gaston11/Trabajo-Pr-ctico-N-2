/*
 * AntenaUtilizada.cpp
 *
 *  Created on: 22/05/2016
 *      Author: gaston
 */
#include "AntenaUtilizada.h"

AntenaUtilizada::AntenaUtilizada(Antena* antena, unsigned int minuto){
	this->antena = antena;
	minutoIniciado = minuto;
	minutoFinalizado = 0;
}

Antena* AntenaUtilizada::obtenerAntena(){
	return this->antena;
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

AntenaUtilizada::~AntenaUtilizada(){

}


