/*
 * MenuAntena.cpp
 *
 *  Created on: 25/05/2016
 *      Author: gaston
 */
#include "MenuAntena.h"

MenuAntena::MenuAntena(Lista<Antena*>* nuevaListaAntenas, Lista<Equipo*>* nuevaListaEquipos){
	this->listaAntenas = nuevaListaAntenas;
	this->listaEquipos = nuevaListaEquipos;
}

void MenuAntena::metodoPrincipal(char opcion){
	Antena* antenaActual;
	this->listaAntenas->iniciarCursor();
	while (this->listaAntenas->avanzarCursor()){
		antenaActual = listaAntenas->obtenerCursor();
		switch (opcion){
			case 'b' :{
						std::cout<< "Equipo que mas minutos hablo de la antena: ";    ///terminar b
						std::cout<< antenaActual->obtenerNombre()<<std::endl;
						this->equipoQueMasHablo(antenaActual);
					  }
						break;
			case 'c' :{
						std::cout<< "Equipo que mas llamo de la antena: ";    ///terminar c
						std::cout<< antenaActual->obtenerNombre()<<std::endl;
						this->equipoQueMasLlamo(antenaActual);
					  }
						break;
			case 'd' :  {
						std::cout<< "Equipo que mas dio ocupado de la antena: ";    ///terminar d
						std::cout<< antenaActual->obtenerNombre()<<std::endl;
						this->equipoQueMasLeDioOcupadoAlRealizarLlamada(antenaActual);
			  	  	  	}
						break;
			case 'e' : {
						std::cout<< "Equipo que mas llamaron de la antena: ";    ///terminar e
						std::cout<< antenaActual->obtenerNombre()<<std::endl;
						this->equipoAlQueMasLlamaron(antenaActual);
	  	  	  			}
						break;
			case 'f' : {
						std::cout<< "Equipo que mas le hablaron de la antena: ";    ///terminar f
						std::cout<< antenaActual->obtenerNombre()<<std::endl;
						this->equipoAlQueMasLeHablaron(antenaActual );
						}
						break;
			case 'g' :  {
						std::cout<< "Equipo que mas dio ocupado al llamarlo de la antena: ";    ///terminar g
						std::cout<< antenaActual->obtenerNombre()<<std::endl;
						this->equipoQueMasDioOcupadoAlLlamarlo(antenaActual);
						}
						break;
			default: std::cout<< "opcion invalida" <<std::endl;
		}
	}
}

void MenuAntena::mostrarPorPantalla(Equipo* equipo, unsigned int cantidad){
	std::cout << "Numero de equipo: ";
	std::cout << equipo->retornarNumeroEquipo();
	std::cout << "Cantidad: ";
	std::cout << cantidad<< std::endl;
	std::cout << std::endl;
}


void MenuAntena::equipoQueMasHablo(Antena* antena){   // para opcion b)  realizada true, ocupado false, entrante false.
		Equipo* equipoQueMasHablo, *equipoActual;       			// contar minutos
		Lista<Llamada*>* llamadas;
		unsigned int cantidadMinutos, cantidadMinutosDelQueMasHablo =0;
		Lista<Equipo*>* listaEquiposQueConectaron;
		listaEquiposQueConectaron = antena->obtenerEquiposQueConectaron();

		listaEquiposQueConectaron->iniciarCursor();
		while (listaEquiposQueConectaron->avanzarCursor()){
			equipoActual = listaEquiposQueConectaron->obtenerCursor();
			llamadas = equipoActual->obtenerLLamadasEquipo();
			cantidadMinutos = contarMinutosDeLlamadaEntrante(llamadas, antena->obtenerNombre());
			this->compararValores(cantidadMinutos,cantidadMinutosDelQueMasHablo,equipoActual,equipoQueMasHablo);
		}
		this-> mostrarPorPantalla (equipoQueMasHablo, cantidadMinutosDelQueMasHablo);
}

unsigned int MenuAntena::contarMinutosDeLlamadaEntrante(Lista<Llamada*>* llamadas, std::string nombreAntena){
	Llamada* llamadaActual;
	unsigned int minutos =0;

	llamadas->iniciarCursor();
	while(llamadas->avanzarCursor()){
		llamadaActual = llamadas->obtenerCursor();
		if (llamadaActual->esLlamadaRealizada() && !llamadaActual->esLlamadaEntrante() && !llamadaActual->esLlamadaOcupada())
			minutos = minutos +  this->contarMinutosAntena(llamadaActual, nombreAntena );
		}
	return minutos;
}

unsigned int MenuAntena::contarMinutosAntena(Llamada* llamadaActual, std::string nombreAntena ){
	Lista<AntenaUtilizada*>* antenasActuales;
	AntenaUtilizada* antenaActual;
	unsigned int minutos =0;

	antenasActuales = llamadaActual->obtenerAntenasUtilizadas();
	antenasActuales->iniciarCursor();
	while(antenasActuales->avanzarCursor()){
		antenaActual = antenasActuales->obtenerCursor();
		if (antenaActual->obtenerNombreAntena() == nombreAntena)
			minutos = minutos + antenaActual->duracionDeMinutosEnAntena();
	}
	return minutos;
}

void MenuAntena::equipoQueMasLlamo(Antena* antena){    // para opcion c
	Equipo* equipoQueMasLlamo, *equipoActual;
	Lista<Llamada*>* llamadas;
	unsigned int cantidadLlamadas, cantidadMaximaDeLlamadas =0;
	Lista<Equipo*>* listaEquiposQueConectaron;

	listaEquiposQueConectaron = antena->obtenerEquiposQueConectaron();
	listaEquiposQueConectaron->iniciarCursor();
	while (listaEquiposQueConectaron->avanzarCursor()){
		equipoActual = listaEquiposQueConectaron->obtenerCursor();
		llamadas = equipoActual->obtenerLLamadasEquipo();
		cantidadLlamadas = contarLlamadasRealizadas(llamadas, antena->obtenerNombre());
		this->compararValores(cantidadLlamadas,cantidadMaximaDeLlamadas, equipoActual, equipoQueMasLlamo);
	}
	this->mostrarPorPantalla(equipoQueMasLlamo, cantidadMaximaDeLlamadas );
}

unsigned int MenuAntena::contarLlamadasRealizadas(Lista<Llamada*>* llamadas, std::string nombreAntena){
	Llamada* llamadaActual;
	unsigned int cantidadLlamadas = 0;

	llamadas->iniciarCursor();
	while(llamadas->avanzarCursor()){
		llamadaActual = llamadas->obtenerCursor();
		if (llamadaActual->esLlamadaRealizada() && !llamadaActual->esLlamadaEntrante() && !llamadaActual->esLlamadaOcupada()
			 && this->antenaUsadaEnLlamada(llamadaActual->obtenerAntenasUtilizadas(), nombreAntena ) )
				cantidadLlamadas++;
	}
	return cantidadLlamadas;
}

bool MenuAntena::antenaUsadaEnLlamada(Lista<AntenaUtilizada*>* antenasUtilizadas, std::string nombreAntena){//buscar Antena
	AntenaUtilizada* antenaActual;
	bool antenaEncontrada = false;

	antenasUtilizadas->iniciarCursor();
	while(antenasUtilizadas->avanzarCursor() && !antenaEncontrada){
		antenaActual = antenasUtilizadas->obtenerCursor();
		if (antenaActual->obtenerNombreAntena() == nombreAntena)
			antenaEncontrada = true;
	}
	return antenaEncontrada;
}

void MenuAntena::equipoQueMasLeDioOcupadoAlRealizarLlamada(Antena* antena){ //PREGUNTAR  para opcion d)
	Equipo* equipoQueMasLlamo, *equipoActual;
	Lista<Llamada*>* llamadas;
	unsigned int cantidadLlamadasOcupado, cantidadMaximaDeLlamadasOcupado =0;
	Lista<Equipo*>* listaEquiposQueConectaron;

	listaEquiposQueConectaron = antena->obtenerEquiposQueConectaron();
	listaEquiposQueConectaron->iniciarCursor();
	while (listaEquiposQueConectaron->avanzarCursor()){
		equipoActual = listaEquiposQueConectaron->obtenerCursor();
		llamadas = equipoActual->obtenerLLamadasEquipo();
		cantidadLlamadasOcupado = contarLlamadasRealizadasOcupado(llamadas, antena->obtenerNombre());
		this->compararValores(cantidadLlamadasOcupado, cantidadMaximaDeLlamadasOcupado,equipoActual, equipoQueMasLlamo);
	}
	this->mostrarPorPantalla(equipoQueMasLlamo, cantidadMaximaDeLlamadasOcupado );
}

unsigned int MenuAntena::contarLlamadasRealizadasOcupado(Lista<Llamada*>* llamadas, std::string nombreAntena){
	Llamada* llamadaActual;
	unsigned int cantidadLlamadasOcupado = 0;

	llamadas->iniciarCursor();
	while(llamadas->avanzarCursor()){
		llamadaActual = llamadas->obtenerCursor();
		if (llamadaActual->esLlamadaRealizada() && !llamadaActual->esLlamadaEntrante() && llamadaActual->esLlamadaOcupada()
			 && this->antenaUsadaEnLlamada(llamadaActual->obtenerAntenasUtilizadas(), nombreAntena ) )
				cantidadLlamadasOcupado++;
		}
	return cantidadLlamadasOcupado;

}

void MenuAntena::equipoAlQueMasLlamaron(Antena* antena){       // para opcion e)  cantidad llamadas
	Equipo* equipoQueMasLlamaron, *equipoActual;
	Lista<Llamada*>* llamadas;
	unsigned int cantidadLlamadas, cantidadMaximaDeLlamadas =0;
	Lista<Equipo*>* listaEquiposQueConectaron;

	listaEquiposQueConectaron = antena->obtenerEquiposQueConectaron();
	listaEquiposQueConectaron->iniciarCursor();
	while (listaEquiposQueConectaron->avanzarCursor()){
		equipoActual = listaEquiposQueConectaron->obtenerCursor();
		llamadas = equipoActual->obtenerLLamadasEquipo();
		cantidadLlamadas = contarLlamadasEntrantes(llamadas, antena->obtenerNombre());
		this->compararValores(cantidadLlamadas,cantidadMaximaDeLlamadas,equipoActual,equipoQueMasLlamaron);
	}
	this->mostrarPorPantalla(equipoQueMasLlamaron, cantidadMaximaDeLlamadas);
}

unsigned int MenuAntena::contarLlamadasEntrantes(Lista<Llamada*>* llamadas, std::string nombreAntena){
	Llamada* llamadaActual;
	unsigned int cantidadLlamadas = 0;

	llamadas->iniciarCursor();
	while(llamadas->avanzarCursor()){
		llamadaActual = llamadas->obtenerCursor();
		if ( llamadaActual->esLlamadaRealizada() && llamadaActual->esLlamadaEntrante() && !llamadaActual->esLlamadaOcupada()
					&&  this-> antenaUsadaEnLlamada(llamadaActual->obtenerAntenasUtilizadas(), nombreAntena))
			cantidadLlamadas++;
		}
	return cantidadLlamadas;
}

void MenuAntena::equipoAlQueMasLeHablaron(Antena* antena ){  //para opcion f)
	Equipo* equipoQueMasLeHablaron, *equipoActual;
	Lista<Llamada*>* llamadas;
	unsigned int cantidadMinutos, cantidadMinutosDelQueMasLeHablaron=0;
	Lista<Equipo*>* listaEquiposQueConectaron;

	listaEquiposQueConectaron = antena->obtenerEquiposQueConectaron();
	listaEquiposQueConectaron->iniciarCursor();
	while (listaEquiposQueConectaron->avanzarCursor()){
		equipoActual = listaEquiposQueConectaron->obtenerCursor();
		llamadas = equipoActual->obtenerLLamadasEquipo();
		cantidadMinutos = contarMinutosDeLlamadasRecibidas(llamadas, antena->obtenerNombre());
		this->compararValores(cantidadMinutos, cantidadMinutosDelQueMasLeHablaron,equipoActual,equipoQueMasLeHablaron);

	}
	this->mostrarPorPantalla(equipoQueMasLeHablaron, cantidadMinutosDelQueMasLeHablaron);
}

unsigned int MenuAntena::contarMinutosDeLlamadasRecibidas(Lista<Llamada*>* llamadas, std::string nombreAntena){
	Llamada* llamadaActual;
	unsigned int minutos =0;

	llamadas->iniciarCursor();
	while(llamadas->avanzarCursor()){
		llamadaActual = llamadas->obtenerCursor();
		if (llamadaActual->esLlamadaRealizada() && !llamadaActual->esLlamadaEntrante() && !llamadaActual->esLlamadaOcupada())
			minutos = minutos +  this->contarMinutosAntena(llamadaActual, nombreAntena);
		}
		return minutos;
}

void MenuAntena::equipoQueMasDioOcupadoAlLlamarlo(Antena* antena){  //PREGUNTAR   para opcion g)
	Equipo* equipoQueMasLlamo, *equipoActual;
	Lista<Llamada*>* llamadas;
	unsigned int cantidadLlamadasOcupado, cantidadMaximaDeLlamadasOcupado =0;
	Lista<Equipo*>* listaEquiposQueConectaron;

	listaEquiposQueConectaron = antena->obtenerEquiposQueConectaron();
	listaEquiposQueConectaron->iniciarCursor();
	while (listaEquiposQueConectaron->avanzarCursor()){
		equipoActual = listaEquiposQueConectaron->obtenerCursor();
		llamadas = equipoActual->obtenerLLamadasEquipo();
		cantidadLlamadasOcupado = this->contarLlamadasRecibidasOcupado(llamadas,antena->obtenerNombre());
		this->compararValores(cantidadLlamadasOcupado,cantidadMaximaDeLlamadasOcupado,equipoActual, equipoQueMasLlamo);
	}
	this->mostrarPorPantalla(equipoQueMasLlamo, cantidadMaximaDeLlamadasOcupado );
}

unsigned int MenuAntena::contarLlamadasRecibidasOcupado(Lista<Llamada*>* llamadas, std::string nombreAntena){
	Llamada* llamadaActual;
	unsigned int cantidadLlamadasOcupado = 0;

	llamadas->iniciarCursor();
	while(llamadas->avanzarCursor()){
		llamadaActual = llamadas->obtenerCursor();
		if (llamadaActual->esLlamadaRealizada() && llamadaActual->esLlamadaEntrante() && llamadaActual->esLlamadaOcupada()
			 && this->antenaUsadaEnLlamada(llamadaActual->obtenerAntenasUtilizadas(), nombreAntena ) )
				cantidadLlamadasOcupado++;
		}
	return cantidadLlamadasOcupado;

}

void MenuAntena::compararValores(unsigned int nuevoValor,unsigned int &maximoActual,Equipo* equipoNuevo, Equipo* &equipoMaximo){
	if (nuevoValor > maximoActual){
		maximoActual = nuevoValor;
		equipoMaximo = equipoNuevo;
	}
}


