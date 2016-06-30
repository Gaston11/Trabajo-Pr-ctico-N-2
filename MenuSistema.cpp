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

	case 'a':
		this->detalleEntreEquipos();
		break;

	case 'b':
		this->equipoQueMasHablo();
		break;

	case 'c':
		this->celularQueMasLlamo();
		break;

	case 'd':
		this->equipoQueMasDioOcupado();
		break;

	case 'e':
		this->equipoQueMasLlamaron();
		break;

	case 'f':
		this->equipoAlQueMasHablaron();
		break;

	case 'g':
		this->equipoMasOcupado();
		break;

	case 'h':
		this->detalleDeLlamadasEmitidas();
		break;

	case 'i':
		this->detalleDeLlamadasRecibidas();
		break;

	case 'j':
		this->detalleRecibidasYRealizadas();
		break;

	case 'k':
		this->detalleDeEquipos();
		break;

	case 'l':
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

	while(opcion != 'l'){
		this->opciones(opcion);

		if (opcion != 'l'){
			this->opcionesDeMenuSistema();
			std::cin >> opcion;
		}
	}
}

MenuSistema::~MenuSistema(){

}

void MenuSistema::detalleEntreEquipos(){

	unsigned int equipo1, equipo2;
	std::cout << "Detalle de llamadas entre 2 celulares ingreselo por orden ";
	std::cout << "si no lo sabe puede ir a la opcion de menu k: ";
	std::cin >> equipo1;
	std::cin >>equipo2;

	this->detalleEquipo(this->equipos->obtener(equipo1),this->equipos->obtener(equipo2));

}

void MenuSistema::detalleEquipo(Equipo* equipoEmisor, Equipo* equipoReceptor){

	Lista<Llamada*>* llamadasEmisor;
	Llamada* llamadaEmisor;
	unsigned int cantidadLlamadas =0;
	unsigned int cantidadMinutos =0;
	unsigned int cantidadOcupado =0;
	std::cout<<"Equipo Emisor: ";
	std::cout<<equipoEmisor->obtenerNumero()<<std::endl;

	std::cout << "Equipo Receptor: ";
	std::cout << equipoReceptor->obtenerNumero()<< std::endl;
	llamadasEmisor = equipoEmisor->obtenerLLamadasEquipo();
	llamadasEmisor->iniciarCursor();
	while(llamadasEmisor->avanzarCursor()){
		llamadaEmisor = llamadasEmisor->obtenerCursor();
		if (llamadaEmisor->obtenerCelular()->obtenerNumero() == equipoReceptor->obtenerNumero()  &&
					llamadaEmisor->esLlamadaRealizada() && !llamadaEmisor->esOcupado() ){
			cantidadLlamadas++;
			this->mostrarAntenasUtilizadas(llamadaEmisor);
			cantidadMinutos += this->sumarDuracion(llamadaEmisor->obtenerAntenasUtilizadas());
		}
		else if( llamadaEmisor->obtenerCelular()->obtenerNumero() == equipoReceptor->obtenerNumero()  &&
					llamadaEmisor->esLlamadaRealizada() && llamadaEmisor->esOcupado()){
			cantidadOcupado++;
		}
	}
	std::cout << "Cantidad de llamadas : ";
	std::cout<< cantidadLlamadas << std::endl;
	std::cout << "Cantidad de tiempo hablado: ";
	std::cout<< cantidadMinutos<<std::endl;
	std::cout << "Cantidad de veces ocupado totales: ";
	std::cout << cantidadOcupado<<std::endl;


}

void MenuSistema::detalleEquipo(Equipo* equipo){

	std::cout << "Cantidad de llamadas totales: ";
	std::cout << equipo->obtenerLlamadasEntrantes() + equipo->obtenerLlamadasSalientes()<<std::endl;

	std::cout << "Cantidad de tiempo hablado: ";
	std::cout<< this->calculaMinutosHablado(equipo)<<std::endl;

	std::cout << "Cantidad de veces ocupado totales: ";
	std::cout << equipo->obtenerLlamadasEntranteOcupado()+equipo->obtenerLlamadasSalienteOcupado()<<std::endl;

}

void MenuSistema::equipoQueMasHablo(){
	this->equipos->iniciarCursor();
	Equipo* equipo;
	Lista<Equipo*>* equiposMaximos = new Lista<Equipo*>;
	unsigned int cantidadMinutos=0, minutosMaximos=0;

	while (this->equipos->avanzarCursor()){
		equipo=this->equipos->obtenerCursor();
		cantidadMinutos=this->calculaMinutosHablo(equipo);

		if(cantidadMinutos > minutosMaximos){
			this->removerLista(equiposMaximos);
			equiposMaximos->agregar(equipo);
			minutosMaximos=cantidadMinutos;
		}else if(cantidadMinutos == minutosMaximos){
			equiposMaximos->agregar(equipo);
		}
	}
	std::cout<<"Equipo/s que mas hablo: "<<std::endl;
	std::cout<<"Cantidad de minutos: ";
	std::cout<< minutosMaximos<<std::endl;
	this->mostrarEquipos(equiposMaximos);

	this->removerLista(equiposMaximos);
	delete equiposMaximos;
}

unsigned int MenuSistema::calculaMinutosHablo(Equipo* equipo){
	Lista<Llamada*>* llamadas = equipo->obtenerLLamadasEquipo();
	llamadas->iniciarCursor();
	Llamada* llamada; Lista<AntenaUtilizada*>* antenas;
	unsigned int cantidad=0;

	while(llamadas->avanzarCursor()){
		llamada = llamadas->obtenerCursor();
		if (llamada->esLlamadaRealizada() && !llamada->esOcupado()){
			antenas=llamada->obtenerAntenasUtilizadas();
			cantidad+=this->sumarDuracion(antenas);
		}

	}
		return cantidad;
}

void MenuSistema::celularQueMasLlamo(){
	this->equipos->iniciarCursor();
	Equipo* equipo;
	Lista<Equipo*>* equiposQueMasLlamaron = new Lista<Equipo*>;
	unsigned int cantidad=0;

	while(this->equipos->avanzarCursor()){
		equipo=this->equipos->obtenerCursor();

		if (equipo->obtenerLlamadasSalientes()>cantidad){
			this->removerLista(equiposQueMasLlamaron);
			equiposQueMasLlamaron->agregar(equipo);
			cantidad = equipo->obtenerLlamadasSalientes();
		}else if(equipo->obtenerLlamadasSalientes()==cantidad){
			equiposQueMasLlamaron->agregar(equipo);
		}
	}
	std::cout<<"Equipo/s que mas llamo: "<<std::endl;
	std::cout<<"Cantidad: ";
	std::cout<< cantidad<<std::endl;

	if (cantidad>0){
	this->mostrarEquipos(equiposQueMasLlamaron);
	}else{std::cout << "No existen Equipos que que mas llamaron"<< std::endl;}

	this->removerLista(equiposQueMasLlamaron);
	delete equiposQueMasLlamaron;
}

void MenuSistema::equipoQueMasDioOcupado(){

	this->equipos->iniciarCursor();
	Equipo* equipo;
	Lista<Equipo*>* equiposMasDioOcupado = new Lista<Equipo*>;
	unsigned int maximoSalienteOcupado=0;

	while(this->equipos->avanzarCursor()){
		equipo=this->equipos->obtenerCursor();

		if(equipo->obtenerLlamadasSalienteOcupado()>maximoSalienteOcupado){
			this->removerLista(equiposMasDioOcupado);
			equiposMasDioOcupado->agregar(equipo);
			maximoSalienteOcupado=equipo->obtenerLlamadasSalienteOcupado();
		}else if(equipo->obtenerLlamadasSalienteOcupado()==maximoSalienteOcupado){
			equiposMasDioOcupado->agregar(equipo);

		}
	}
	std::cout<<"Equipo/s que mas dio ocupado en sus intentos de llamadas: "<<std::endl;
	std::cout<<"Cantidad de veces: ";
	std::cout<< maximoSalienteOcupado<<std::endl;
	if (maximoSalienteOcupado>0){
		this->mostrarEquipos(equiposMasDioOcupado);
	}else{std::cout << "No existen equipos que cumplan con estas caracteristicas"<<std::endl;}

	this->removerLista(equiposMasDioOcupado);
	delete equiposMasDioOcupado;
}

void MenuSistema::equipoAlQueMasHablaron(){

	this->equipos->iniciarCursor();
	Equipo* equipo; Lista<Equipo*>* equiposAlQueMasHablaron = new Lista<Equipo*>;
	unsigned int cantidadMinutosHablaron=0, maximoMinutosHablaron=0;

	while(this->equipos->avanzarCursor()){
		equipo=this->equipos->obtenerCursor();
		cantidadMinutosHablaron = this->calcularMinutosHablaron(equipo);

		if(cantidadMinutosHablaron > maximoMinutosHablaron){
			this->removerLista(equiposAlQueMasHablaron);
			equiposAlQueMasHablaron->agregar(equipo);
			maximoMinutosHablaron=cantidadMinutosHablaron;
		}else if(cantidadMinutosHablaron == maximoMinutosHablaron){
			equiposAlQueMasHablaron->agregar(equipo);
		}
	}
	std::cout << "Equipo/s que mas hablaron: "<<std::endl;
	std::cout << "Cantidad de minutos: ";
	std::cout << maximoMinutosHablaron << std::endl;

	if (maximoMinutosHablaron>0){
		this->mostrarEquipos(equiposAlQueMasHablaron);
	}else{std::cout << "No existen equipos que cumplan estas caracteristicas"<<std::endl;}

	this->removerLista(equiposAlQueMasHablaron);
	delete equiposAlQueMasHablaron;
}

void MenuSistema::equipoMasOcupado(){

	this->equipos->iniciarCursor();
	Equipo* equipo; Lista<Equipo*>* equiposMasOcupado = new Lista<Equipo*>;
	unsigned int maximoOcupado=0;

	while(this->equipos->avanzarCursor()){
		equipo=this->equipos->obtenerCursor();

		if(equipo->obtenerLlamadasEntranteOcupado()>maximoOcupado){

			this->removerLista(equiposMasOcupado);
			equiposMasOcupado->agregar(equipo);
			maximoOcupado=equipo->obtenerLlamadasEntranteOcupado();
		}else if(equipo->obtenerLlamadasEntranteOcupado()== maximoOcupado){
			equiposMasOcupado->agregar(equipo);
		}
	}
	std::cout << "Equipo/s que estuvo mas ocupado: " << std::endl;
	std::cout << "Cantidad de veces: ";
	std::cout << maximoOcupado << std::endl;

	if (maximoOcupado>0){
	this->mostrarEquipos(equiposMasOcupado);
	}else{std::cout << "No existen equipos con estas caracteristicas"<<std::endl;}

	this->removerLista(equiposMasOcupado);
	delete equiposMasOcupado;
}

void MenuSistema::equipoQueMasLlamaron(){

	this->equipos->iniciarCursor();
	Equipo* equipo;
	Lista<Equipo*>* equiposMasLlamaron = new Lista<Equipo*>;
	unsigned int maximaEntrante=0;

	while(this->equipos->avanzarCursor()){
		equipo=this->equipos->obtenerCursor();

		if (equipo->obtenerLlamadasEntrantes()>maximaEntrante){
			this->removerLista(equiposMasLlamaron);
			equiposMasLlamaron->agregar(equipo);
			maximaEntrante = equipo->obtenerLlamadasEntrantes();
		}else if(equipo->obtenerLlamadasEntrantes()==maximaEntrante){
			equiposMasLlamaron->agregar(equipo);
		}
	}
	std::cout << "Equipo/s que mas llamada/s recibio: " << std::endl;
	std::cout << "Cantidad de llamadas: " ;
	std::cout << maximaEntrante << std::endl;

	if(maximaEntrante >0){
		this->mostrarEquipos(equiposMasLlamaron);
	}else{std::cout << "No existen equipos con estas caracteristicas"<<std::endl;}

	this->removerLista(equiposMasLlamaron);
	delete equiposMasLlamaron;
}

void MenuSistema::detalleDeEquipos(){

	this->equipos->iniciarCursor();
	Equipo* equipo; unsigned int i = 0;
	std::cout << "Detalle de todos los celulares: " << std::endl;
	std::cout << "(unidad / numero / antena de la ultima conexion)"<<std::endl;
	while(this->equipos->avanzarCursor()){
		i++;
		equipo=this->equipos->obtenerCursor();
		std::cout << i;
		std::cout << "- ";
		std::cout<<equipo->obtenerNumero();
		std::cout<< " - ";
		std::cout << equipo->obtenerUltimaConexion()->obtenerAntena()->obtenerNombre() << std::endl;
	}
}

unsigned int MenuSistema::detalleDeLlamadasRecibidas(){

	unsigned int posicion;
	std::cout << "Ingrese el numero/posicion del equipo en la lista de detalles: ";
	std::cin >> posicion;

	Equipo* equipo = this->equipos->obtener(posicion);

	std::cout << "Detalle de llamadas recibidas por el numero: ";

	Lista<Llamada*>* llamadas = equipo->obtenerLLamadasEquipo();
	llamadas->iniciarCursor();
	Llamada* llamada;
	std::cout << equipo->obtenerNumero() << std::endl;
	while(llamadas->avanzarCursor()){
		llamada = llamadas->obtenerCursor();
		if (llamada->esLlamadaEntrante() && !llamada->esOcupado()){
			std::cout << llamada->obtenerCelular()->obtenerNumero() << std::endl;
			std::cout << "Antenas Utilizadas: " << std::endl;
			this->mostrarAntenasUtilizadas(llamada);
		}

	}
	return posicion;

}

unsigned int MenuSistema::detalleDeLlamadasEmitidas(){

	unsigned int posicion;
	std::cout << "Ingrese el numero/posicion del equipo en la lista de detalles: ";
	std::cin >> posicion;

	Equipo* equipo = this->equipos->obtener(posicion);

	std::cout << "Detalle de llamadas realizadas por el numero: ";

	Lista<Llamada*>* llamadas = equipo->obtenerLLamadasEquipo();
	llamadas->iniciarCursor();
	Llamada* llamada;
	std::cout << equipo->obtenerNumero() << std::endl;
	while(llamadas->avanzarCursor()){
		llamada = llamadas->obtenerCursor();
		if (llamada->esLlamadaRealizada() && ! llamada->esOcupado()){
			std::cout << llamada->obtenerCelular()->obtenerNumero() << std::endl;
			std::cout << "Antenas Utilizadas: " << std::endl;
			this->mostrarAntenasUtilizadas(llamada);
		}

	}
	return posicion;
}

void MenuSistema::detalleRecibidasYRealizadas(){
	unsigned int posicion = this->detalleDeLlamadasRecibidas();

	this->detalleEquipo(this->equipos->obtener(posicion));

	posicion = this->detalleDeLlamadasEmitidas();

	this->detalleEquipo(this->equipos->obtener(posicion));
}

void MenuSistema::mostrarAntenasUtilizadas(Llamada* llamada){
	Lista<AntenaUtilizada*>* antenas = llamada->obtenerAntenasUtilizadas();
	antenas->iniciarCursor();

	std::cout << "Antenas Utilizadas: " << std::endl;
	while(antenas->avanzarCursor()){
		std::cout<<antenas->obtenerCursor()->obtenerAntena()->obtenerNombre()<<std::endl;
	}

}

void MenuSistema::mostrarEquipos(Lista<Equipo*>* equiposAMostrar){

	equiposAMostrar->iniciarCursor();
	while(equiposAMostrar->avanzarCursor()){
		std::cout << equiposAMostrar->obtenerCursor()->obtenerNumero() << std::endl;
	}
}

unsigned int MenuSistema::calculaMinutosHablado(Equipo* equipo){

	Lista<Llamada*>* llamadas = equipo->obtenerLLamadasEquipo();
	llamadas->iniciarCursor();
	Llamada* llamada; Lista<AntenaUtilizada*>* antenas;
	unsigned int cantidad=0;

	while(llamadas->avanzarCursor()){
		llamada = llamadas->obtenerCursor();
		if (!llamada->esOcupado()){
			antenas=llamada->obtenerAntenasUtilizadas();
			cantidad+=this->sumarDuracion(antenas);
		}

	}
	return cantidad;
}

unsigned int MenuSistema::calcularMinutosHablaron(Equipo* equipo){

	Lista<Llamada*>* llamadas = equipo->obtenerLLamadasEquipo();
	llamadas->iniciarCursor();
	Llamada* llamada; Lista<AntenaUtilizada*>* antenas;
	unsigned int minutos=0;

	while(llamadas->avanzarCursor()){
		llamada=llamadas->obtenerCursor();

		if (llamada->esLlamadaEntrante() && ! llamada->esOcupado()){
			antenas=llamada->obtenerAntenasUtilizadas();
			minutos+=this->sumarDuracion(antenas);
		}
	}
	return minutos;
}

unsigned int MenuSistema::sumarDuracion(Lista<AntenaUtilizada*>* antenas){
	antenas->iniciarCursor();
	unsigned int minutos=0;
	AntenaUtilizada* antena;

	while(antenas->avanzarCursor()){
		antena=antenas->obtenerCursor();
		minutos+=antena->duracionDeMinutosEnAntena();
	}
	return minutos;
}

void MenuSistema::removerLista(Lista<Equipo*>* equipos){
	while(!equipos->estaVacia()){
		equipos->remover(1);
	}
}
