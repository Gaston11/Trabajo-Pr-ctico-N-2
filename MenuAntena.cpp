/*
 * MenuAntena.cpp
 *
 *  Created on: 25/05/2016
 *      Author: gaston
 */
#include "MenuAntena.h"

MenuAntena::MenuAntena(Lista<Antena*>* nuevaListaAntenas){
	this->listaAntenas = nuevaListaAntenas;
	this->ordenarAntenaPorAnuladas();  //// arreglar en cada metodo
}

void MenuAntena::MenuPrincipal(){
	char opcion='X';

	while (opcion != 'j') {
		std::cout << "Opciones de menu sobre antenas: " << std::endl;;

		std::cout << "a- Celular que mas hablo de cada antena." << std::endl;
		std::cout << "b- Celular que mas llamo de cada antena." << std::endl;
		std::cout << "c- Celular que mas le dio ocupado de cada antena." << std::endl;;
		std::cout << "d- Celular al que mas llamaron de cada antena." << std::endl;
		std::cout << "e- Celular al que mas le hablaron de cada antena." << std::endl;
		std::cout << "f- Celular que mas dio ocupado de cada antena." << std::endl;
		std::cout << "g- Cantidad maxima utilizada de Celulares por antena." << std::endl;
		std::cout << "h- Cantidad de llamadas anuladas por falta de Capacidad";
		std::cout << " por Antena (ordenado por cantidad descendiente)"<< std::endl;
		std::cout << "i- Detalles de Antenas." << std::endl;

		std::cout << "j- Salir." << std::endl;
		std::cout << "Ingrese opcion: " << std::endl;
		std::cin >> opcion;
		this->opcionesAntena(opcion);
	}
}

void MenuAntena::opcionesAntena(char opcion){
	Antena* antenaActual;
	this->listaAntenas->iniciarCursor();
	while (this->listaAntenas->avanzarCursor()){
		antenaActual = listaAntenas->obtenerCursor();
		switch (opcion){
			case 'a' :{
						std::cout<< "Equipo que mas minutos hablo de la antena: ";    ///
						std::cout<< antenaActual->obtenerNombre()<<std::endl;
						this->equipoQueMasHablo(antenaActual);
					  }
						break;
			case 'b' :{
						std::cout<< "Equipo que mas llamo de la antena: ";    ///
						std::cout<< antenaActual->obtenerNombre()<<std::endl;
						this->equipoQueMasLlamo(antenaActual);
					  }
						break;
			case 'c' :  {
						std::cout<< "Equipo que mas le dio ocupado de la antena: ";
						std::cout<< antenaActual->obtenerNombre()<<std::endl;
						this->equipoQueMasLeDioOcupadoAlRealizarLlamada(antenaActual);
			  	  	  	}
						break;
			case 'd' : {
						std::cout<< "Equipo que mas llamaron de la antena: ";    //
						std::cout<< antenaActual->obtenerNombre()<<std::endl;
						this->equipoAlQueMasLlamaron(antenaActual);
	  	  	  			}
						break;
			case 'e' : {
						std::cout<< "Equipo que mas minutos le hablaron de la antena: ";    //
						std::cout<< antenaActual->obtenerNombre()<<std::endl;
						this->equipoAlQueMasLeHablaron(antenaActual );
						}
						break;
			case 'f' :  {
						std::cout<< "Equipo que mas dio ocupado al llamarlo de la antena: ";    ///
						std::cout<< antenaActual->obtenerNombre()<<std::endl;
						this->equipoQueMasDioOcupadoAlLlamarlo(antenaActual);
						}
						break;
			case 'g' :	{
						std::cout<< "Cantidad maxima de celulares utilizada en la antena ";
						std::cout<< antenaActual->obtenerNombre() << ": ";
						std::cout<< antenaActual->obtenerEquiposQueConectaron()->contarElementos() <<std::endl;
						}
						break;
			case 'h' :  {
						std::cout<< "Cantidad de llamadas anuladas por falta de capacidad en la antena ";
						std::cout<< antenaActual->obtenerNombre()<< ": ";
						std::cout << antenaActual->retornarCantidadDeLlamadasAnuladas() <<std::endl;
						std::cout <<std::endl;
						}
						break;
			case 'i' :  {
						std::cout<< "Nombre antena: " << antenaActual->obtenerNombre()<< std::endl;
						std::cout<< "Cantidad maxima de celulares soportados: "<<
									antenaActual->retornarCantidadDeConexiones() << std::endl;
						std::cout<< "Cantidad maxima de celulares utilizados: "<<
								antenaActual->obtenerEquiposQueConectaron()->contarElementos() << std::endl;
						std::cout <<std::endl;
						}
						break;
			case 'j' :  // nada
						break;
			default: std::cout<< "opcion invalida" <<std::endl;
		}
	}
}

void MenuAntena::mostrarPorPantalla(Lista<Equipo*>* listaEquipos, unsigned int cantidad){
	if (cantidad != 0){
		Equipo* equipo;
		listaEquipos->iniciarCursor();
		while (listaEquipos->avanzarCursor()){
			equipo = listaEquipos->obtenerCursor();
			std::cout << "Numero de equipo: ";
			std::cout << equipo->obtenerNumero();
			std::cout << "  Cantidad: ";
			std::cout << cantidad<< std::endl;
		}
	}
	else
		std::cout<< "No hay Equipos que cumplan los requisitos..." << std::endl;
	std::cout << std::endl;
}


void MenuAntena::equipoQueMasHablo(Antena* antena){  //opcion a
		Equipo *equipoActual;       			// contar minutos
		Lista<Llamada*>* llamadas;
		unsigned int cantidadMinutos, cantidadMinutosDelQueMasHablo =0;
		Lista<Equipo*>* listaEquiposQueConectaron;
		Lista<Equipo*>* equiposQueMasHablaron = new Lista<Equipo*>;
		listaEquiposQueConectaron = antena->obtenerEquiposQueConectaron();

		listaEquiposQueConectaron->iniciarCursor();
		while (listaEquiposQueConectaron->avanzarCursor()){
			equipoActual = listaEquiposQueConectaron->obtenerCursor();
			llamadas = equipoActual->obtenerLLamadasEquipo();
			cantidadMinutos = contarMinutosDeLlamadaRealizada(llamadas, antena->obtenerNombre());
			this->compararValores(cantidadMinutos,cantidadMinutosDelQueMasHablo,equipoActual,equiposQueMasHablaron);
		}
		this-> mostrarPorPantalla (equiposQueMasHablaron,cantidadMinutosDelQueMasHablo);
		delete equiposQueMasHablaron;
}

unsigned int MenuAntena::contarMinutosDeLlamadaRealizada(Lista<Llamada*>* llamadas, std::string nombreAntena){
	Llamada* llamadaActual;
	unsigned int minutos =0;

	llamadas->iniciarCursor();
	while(llamadas->avanzarCursor()){
		llamadaActual = llamadas->obtenerCursor();											//VEEEER OCUPADO
		if (llamadaActual->esLlamadaRealizada() && !llamadaActual->esOcupado())
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
		if (antenaActual->obtenerAntena()->obtenerNombre() == nombreAntena)
			minutos = minutos + antenaActual->duracionDeMinutosEnAntena();
	}
	return minutos;
}

void MenuAntena::equipoQueMasLlamo(Antena* antena){    // para opcion b
	Equipo *equipoActual;
	Lista<Llamada*>* llamadas;
	unsigned int cantidadLlamadas, cantidadMaximaDeLlamadas =0;
	Lista<Equipo*>* listaEquiposQueConectaron;
	Lista<Equipo*>* equiposQueMasLlamaron = new Lista<Equipo*>;
	listaEquiposQueConectaron = antena->obtenerEquiposQueConectaron();
	listaEquiposQueConectaron->iniciarCursor();
	while (listaEquiposQueConectaron->avanzarCursor()){
		equipoActual = listaEquiposQueConectaron->obtenerCursor();
		llamadas = equipoActual->obtenerLLamadasEquipo();
		cantidadLlamadas = contarLlamadasRealizadas(llamadas, antena->obtenerNombre());
		this->compararValores(cantidadLlamadas,cantidadMaximaDeLlamadas, equipoActual, equiposQueMasLlamaron);
	}
	this->mostrarPorPantalla(equiposQueMasLlamaron, cantidadMaximaDeLlamadas );
	delete equiposQueMasLlamaron;
}

unsigned int MenuAntena::contarLlamadasRealizadas(Lista<Llamada*>* llamadas, std::string nombreAntena){
	Llamada* llamadaActual;
	unsigned int cantidadLlamadas = 0;

	llamadas->iniciarCursor();
	while(llamadas->avanzarCursor()){
		llamadaActual = llamadas->obtenerCursor();
		if (llamadaActual->esLlamadaRealizada() && !llamadaActual->esOcupado()
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
		if (antenaActual->obtenerAntena()->obtenerNombre() == nombreAntena)
			antenaEncontrada = true;
	}
	return antenaEncontrada;
}

void MenuAntena::equipoQueMasLeDioOcupadoAlRealizarLlamada(Antena* antena){  //  para opcion c) FALTA CHEQUEAR
	Equipo *equipoActual;
	Lista<Llamada*>* llamadas;
	unsigned int cantidadLlamadasOcupado, cantidadMaximaDeLlamadasOcupado =0;
	Lista<Equipo*>* listaEquiposQueConectaron;
	Lista<Equipo*>* equiposMasOcupadosAlRealizarLlamada = new Lista<Equipo*>;
	listaEquiposQueConectaron = antena->obtenerEquiposQueConectaron();
	listaEquiposQueConectaron->iniciarCursor();
	while (listaEquiposQueConectaron->avanzarCursor()){
		equipoActual = listaEquiposQueConectaron->obtenerCursor();
		llamadas = equipoActual->obtenerLLamadasEquipo();
		cantidadLlamadasOcupado = contarLlamadasRealizadasOcupado(llamadas, antena->obtenerNombre());
		this->compararValores(cantidadLlamadasOcupado, cantidadMaximaDeLlamadasOcupado,equipoActual, equiposMasOcupadosAlRealizarLlamada);
	}
	this->mostrarPorPantalla(equiposMasOcupadosAlRealizarLlamada, cantidadMaximaDeLlamadasOcupado );
	delete equiposMasOcupadosAlRealizarLlamada;
}

unsigned int MenuAntena::contarLlamadasRealizadasOcupado(Lista<Llamada*>* llamadas, std::string nombreAntena){
	Llamada* llamadaActual;
	unsigned int cantidadLlamadasOcupado = 0;

	llamadas->iniciarCursor();
	while(llamadas->avanzarCursor()){
		llamadaActual = llamadas->obtenerCursor();
		if (llamadaActual->esLlamadaRealizada() && llamadaActual->esOcupado()
			 && this->antenaUsadaEnLlamada(llamadaActual->obtenerAntenasUtilizadas(), nombreAntena ) )
				cantidadLlamadasOcupado++;
		}
	return cantidadLlamadasOcupado;

}

void MenuAntena::equipoAlQueMasLlamaron(Antena* antena){       // para opcion D)  cantidad llamadas
	Equipo *equipoActual;
	Lista<Llamada*>* llamadas;
	unsigned int cantidadLlamadas, cantidadMaximaDeLlamadas =0;
	Lista<Equipo*>* listaEquiposQueConectaron;
	Lista<Equipo*>* equiposQueMasLlamaron = new Lista<Equipo*>;
	listaEquiposQueConectaron = antena->obtenerEquiposQueConectaron();
	listaEquiposQueConectaron->iniciarCursor();
	while (listaEquiposQueConectaron->avanzarCursor()){
		equipoActual = listaEquiposQueConectaron->obtenerCursor();
		llamadas = equipoActual->obtenerLLamadasEquipo();
		cantidadLlamadas = contarLlamadasEntrantes(llamadas, antena->obtenerNombre());
		this->compararValores(cantidadLlamadas,cantidadMaximaDeLlamadas,equipoActual, equiposQueMasLlamaron);
	}
	this->mostrarPorPantalla(equiposQueMasLlamaron, cantidadMaximaDeLlamadas);
	delete equiposQueMasLlamaron;
}

unsigned int MenuAntena::contarLlamadasEntrantes(Lista<Llamada*>* llamadas, std::string nombreAntena){
	Llamada* llamadaActual;
	unsigned int cantidadLlamadas = 0;

	llamadas->iniciarCursor();
	while(llamadas->avanzarCursor()){
		llamadaActual = llamadas->obtenerCursor();
		if ( llamadaActual->esLlamadaEntrante() && !llamadaActual->esOcupado()
					&&  this-> antenaUsadaEnLlamada(llamadaActual->obtenerAntenasUtilizadas(), nombreAntena))
			cantidadLlamadas++;
		}
	return cantidadLlamadas;
}

void MenuAntena::equipoAlQueMasLeHablaron(Antena* antena ){  //para opcion e)
	Equipo *equipoActual;
	Lista<Llamada*>* llamadas;
	unsigned int cantidadMinutos, cantidadMinutosDelQueMasLeHablaron=0;
	Lista<Equipo*>* listaEquiposQueConectaron;
	Lista<Equipo*>* equiposQueMasLeHablaron = new Lista<Equipo*>;
	listaEquiposQueConectaron = antena->obtenerEquiposQueConectaron();
	listaEquiposQueConectaron->iniciarCursor();
	while (listaEquiposQueConectaron->avanzarCursor()){
		equipoActual = listaEquiposQueConectaron->obtenerCursor();
		llamadas = equipoActual->obtenerLLamadasEquipo();
		cantidadMinutos = contarMinutosDeLlamadasRecibidas(llamadas, antena->obtenerNombre());
		this->compararValores(cantidadMinutos, cantidadMinutosDelQueMasLeHablaron,equipoActual, equiposQueMasLeHablaron);
	}
	this->mostrarPorPantalla(equiposQueMasLeHablaron, cantidadMinutosDelQueMasLeHablaron);
	delete equiposQueMasLeHablaron;
}

unsigned int MenuAntena::contarMinutosDeLlamadasRecibidas(Lista<Llamada*>* llamadas, std::string nombreAntena){
	Llamada* llamadaActual;
	unsigned int minutos =0;

	llamadas->iniciarCursor();
	while(llamadas->avanzarCursor()){
		llamadaActual = llamadas->obtenerCursor();
		if (llamadaActual->esLlamadaEntrante() && !llamadaActual->esOcupado())
			minutos = minutos +  this->contarMinutosAntena(llamadaActual, nombreAntena);
		}
		return minutos;
}

void MenuAntena::equipoQueMasDioOcupadoAlLlamarlo(Antena* antena){  //FALTA CHEQUEAR   para opcion f)
	Equipo *equipoActual;
	Lista<Llamada*>* llamadas;
	unsigned int cantidadLlamadasOcupado, cantidadMaximaDeLlamadasOcupado =0;
	Lista<Equipo*>* listaEquiposQueConectaron;
	Lista<Equipo*>* equiposQueMasDieronOcupadoAlLlamarlos = new Lista<Equipo*>;
	listaEquiposQueConectaron = antena->obtenerEquiposQueConectaron();
	listaEquiposQueConectaron->iniciarCursor();
	while (listaEquiposQueConectaron->avanzarCursor()){
		equipoActual = listaEquiposQueConectaron->obtenerCursor();
		llamadas = equipoActual->obtenerLLamadasEquipo();
		cantidadLlamadasOcupado = this->contarLlamadasRecibidasOcupado(llamadas,antena->obtenerNombre());
		this->compararValores(cantidadLlamadasOcupado,cantidadMaximaDeLlamadasOcupado,equipoActual, equiposQueMasDieronOcupadoAlLlamarlos);
	}
	this->mostrarPorPantalla(equiposQueMasDieronOcupadoAlLlamarlos, cantidadMaximaDeLlamadasOcupado );
	delete equiposQueMasDieronOcupadoAlLlamarlos;
}

unsigned int MenuAntena::contarLlamadasRecibidasOcupado(Lista<Llamada*>* llamadas, std::string nombreAntena){
	Llamada* llamadaActual;
	unsigned int cantidadLlamadasOcupado = 0;

	llamadas->iniciarCursor();
	while(llamadas->avanzarCursor()){
		llamadaActual = llamadas->obtenerCursor();
		if (llamadaActual->esLlamadaEntrante() && llamadaActual->esOcupado()
			 && this->antenaUsadaEnLlamada(llamadaActual->obtenerAntenasUtilizadas(), nombreAntena ) )
				cantidadLlamadasOcupado++;
		}
	return cantidadLlamadasOcupado;

}

void MenuAntena::compararValores(unsigned int nuevoValor,unsigned int &maximoActual,Equipo* equipoNuevo, Lista<Equipo*>* listaEquipos){

	if (nuevoValor > maximoActual){
		maximoActual = nuevoValor;
		while (!listaEquipos->estaVacia())
			listaEquipos->remover(1);
		listaEquipos->agregar(equipoNuevo);
	}else
		if(nuevoValor == maximoActual){
			listaEquipos->agregar(equipoNuevo);
		}
}

void MenuAntena::ordenarAntenaPorAnuladas(){
	//metodo burbujeo
	Antena* antena1, * antena2;
	for(unsigned int contador1 =1; contador1 <= this->listaAntenas->contarElementos() - 1 ; contador1++){
		for (unsigned int contador2 =1; contador2 <= this->listaAntenas->contarElementos() - contador1 ; contador2++){
			antena1 = listaAntenas->obtener(contador2);
			antena2 = listaAntenas->obtener(contador2 + 1);
			if (antena1->retornarCantidadDeLlamadasAnuladas() < antena2->retornarCantidadDeLlamadasAnuladas()){
				listaAntenas->asignar(antena1,contador2 + 1);
				listaAntenas->asignar(antena2, contador2);
			}
		}
	}
}

MenuAntena::~MenuAntena(){

}

