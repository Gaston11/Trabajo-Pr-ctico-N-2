/*
 * MenuSistema.cpp
 *
 *  Created on: 31 de may. de 2016
 *      Author: noe
 */

#include "MenuSistema.h"

MenuSistema::MenuSistema(Lista<Equipo*>* equipos){

	this->equipos = equipos;
}

void MenuSistema::opcionesDeMenuSistema(){

	std::cout << "Opciones de menu sobre equipos: " << std::endl;

	std::cout << "a- Detalle de llamadas entre celular X al celular Y." << std::endl;
	std::cout << "b- Celular que mas hablo." << std::endl;
	std::cout << "c- Celular que mas llamo." << std::endl;
	std::cout << "d- Celular que mas le dio ocupado." << std::endl;
	std::cout << "e- Celular al que mas llamaron." << std::endl;
	std::cout << "f- Celular al que mas le hablaron." << std::endl;
	std::cout << "g- Celular que mas dio ocupado." << std::endl;
	std::cout << "h- Detalle de llamadas emitidas por celular X." << std::endl;
	std::cout << "i- Detalle de llamadas recibidas por el celular Y." << std::endl;
	std::cout << "j- Detalle de llamdas recibidas por el celular X y ";
	std::cout << "realizadas por el celular Y. " << std::endl;
	std::cout << "k- Detalle de Celulares. " << std::endl;
	std::cout << "l- Salir." << std::endl;

}

void MenuSistema::opciones(char opcion){

	switch (opcion){

	case "a":
		this->detalleEntreEquipos();
		break;

	case "b":
		this->equipoQueMasHablo();
		break;

	case "c":
		this->celularQueMasLlamo();
		break;

	case "d":
		this->equipoQueMasDioOcupado();
		break;

	case "e":
		this->equipoQueMasLlamaron();
		break;

	case "f":
		this->equipoAlQueMasHablaron();
		break;

	case "g":
		this->equipoMasOcupado();
		break;

	case "h":
		this->detalleDeLlamadasEmitidas();
		break;

	case "i":
		this->detalleDeLlamadasRealizadas();
		break;

	case "j":


	case "k":
		this->detalleDeEquipos();
		break;

	case "l":
		break;

	default:
		std::cout << "Opcion Incorrecta. Ingresela nuevamente" << std::endl;
		break;

	}

}

void MenuSistema::Menu(){

	char opcion;

	this->opcionesDeMenuSistema();
	std::cin >> opcion;

	while(opcion != "l"){
		this->opciones(opcion);

		if (opcion != "l"){
			this->opcionesDeMenuSistema();
			std::cin >> opcion;
		}
	}
}

void MenuSistema::detalleEntreEquipos(){

}

void MenuSistema::equipoQueMasHablo(){
	this->equipos->iniciarCursor();
	Equipo* equipo;
	unsigned int cantidadMinutos=0, minutosMaximos=0;
	while (this->equipos->avanzarCursor()){
		equipo=this->equipos->obtenerCursor();
		//cantidadMinutos=this->calcularMinutosHablado();
		if(){

		}
	}
}

void MenuSistema::celularQueMasLlamo(){
	this->equipos->iniciarCursor();
	Equipo* equipo;
	Lista<Equipo*>* equiposQueMasLlamaron;
	unsigned int cantidad=0;
	while(this->equipos->avanzarCursor()){
		equipo=this->equipos->obtenerCursor();
		if (equipo->obtenerLlamadasSalientes()>cantidad){
			//this->borrarLista(equiposQueMasLlamaron);
			equiposQueMasLlamaron->agregar(equipo);
			cantidad = equipo->obtenerLlamadasSalientes();
		}else if(equipo->obtenerLlamadasSalientes()==cantidad){
			equiposQueMasLlamaron->agregar(equipo);
		}
	}
	//this->MostrarEquipos(equiposQueMasLlamaron);
}

void MenuSistema::detalleDeEquipos(){

	this->equipos->iniciarCursor();
	Equipo* equipo; unsigned int i = 0;
	std::cout << "Detalle de todos los celulares: " << std::endl;
	std::cout << "(unidad / numero / antena de la ultima conexion)"<<std::endl;
	while(this->equipos->avanzarCursor()){
		i++;
		equipo=this->equipos->obtenerCursor();
		std::cout << i,"- ", equipo->obtenerNumero(), " - ";
		std::cout << equipo->obtenerUltimaConexion()->obtenerNombreAntena() << std::endl;
	}
	//esperar al ingreso de una tecla?
}

void MenuSistema::detalleDeLlamadasEmitidas(){

	std::string numero;
	std::cout << "Ingrese el numero del equipo: ";
	std::cin >> numero;

	//Equipo* equipo = this->buscarEquipo(numero); //ver si este metodo se puede usar
	//o ver si se recibe el id o unidad por posicion de la lista

	std::cout << "Detalle de llamadas emitidas: " << std::endl;

	//lista<Llamada*>* llamadas = equipo->obtenerLlamadas();
	//llamadas->iniciarCursor();
	//Llamada* llamada;
	//while(llamadas->avanzarCursor()){
		//llamada->llamadas->obtenerCursor();
		//if (llamada->esLlamadaRealizada()) && !(llamada->esOcupado()){


	//}

}
