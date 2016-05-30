/*
 * ParsearLineas.cpp
 *
 *  Created on: 22 de may. de 2016
 *      Author: noe
 */

#include "ParsearLineas.h"


ParsearLineas::ParsearLineas(std::string nombreArchivo){

	this->antenas = 0;
	this->equipos = 0;

	this->nombre = nombreArchivo;
}

Lista<Antena*>* ParsearLineas::obtenerAntenas(){

	return this->antenas;
}

Lista<Equipo*>* ParsearLineas::obtenerEquipos(){

	return this->equipos;
}

void ParsearLineas::procesarLineas(){

	std::fstream archivo(this->nombre.c_str());

	std::string linea;

	while(getline(archivo,linea)){
		this->procesarLinea(linea);
	}
	archivo.close();
}

void ParsearLineas::procesarLinea(std::string linea){

	std::string tipoDeEntrada;

	tipoDeEntrada = this->obtenerDato(linea);

	if (tipoDeEntrada == "Antena"){

		this->guardarAntena(linea);

	}else{

		this->guardarEquipo(linea, tipoDeEntrada);
	}

}

void ParsearLineas::guardarAntena(std::string datos){

	//el archivo esta bien formado por ende las antenas no estan repetidas en el archivo
	std::string nombre = this->obtenerDato(datos);
	unsigned int cantidadDeConexiones = datos;

	Antena* antena = new Antena(nombre,cantidadDeConexiones);

	this->antenas->agregar(antena);
}

void ParsearLineas::guardarEquipo(std::string datos, std::string tipo){

	if ((tipo == "Conectar")||(tipo == "Desconectar")){
		this->guardarConexion(datos,tipo);
	}else{
		this->guardarLlamada(datos,tipo);
	}
}

void ParsearLineas::guardarConexion(std::string datos, std::string tipo){

	std::string numero = this->obtenerDato(datos);
	std::string nombreAntena = this->obtenerDato(datos);
	unsigned int minuto = datos;

	//posicion = 0 pos invalida (lista vacia) mayor a 0 correcto
	unsigned int posicionEquipo = this->buscarEquipo(numero);
	unsigned int posicion = this->buscarAntena(nombreAntena);
	Antena* antena = this->antenas->obtener(posicion);

	if (tipo == "Conectar"){

		this->conectarEquipo(antena, numero, posicionEquipo,minuto);

	}else{
		this->desconectarEquipo(antena, numero, posicionEquipo,minuto);
	}
}

void ParsearLineas::conectarEquipo(Antena* antena, std::string numero, unsigned int posicionEquipo, unsigned int minuto){

	if (antena->hayCapacidadAntena()){

		if (posicionEquipo==0){

			Equipo* equipo = new Equipo(numero); // pasar tipo o id

			this->equipos->agregar(equipo);

		}else{
			Equipo* equipo = this->equipos->obtener(posicionEquipo);
			Llamada* llamada= equipo->obtenerUltimaLlamada();
			if (!llamada->estaFinalizada()){
				//agregarAntena utilizada
				this->guardarAntenaUtilizada(equipo,minuto,llamada);
			}

		}
		Equipo* equipo = this->equipos->obtener(posicionEquipo);

		Lista<Equipo*>* equiposQueConectaron = antena->obtenerEquiposQueConectaron();
		equiposQueConectaron->agregar(equipo);

		antena->incrementarCantidadEquiposConectados();
		Conexion* conexion = equipo->obtenerUltimaConexion();
		conexion->cambiarNombreAntena(antena->obtenerNombre());
	}

}

void ParsearLineas::desconectarEquipo(Antena* antena, std::string numero, unsigned int posicionEquipo, unsigned int minuto){

	Equipo* equipo = this->equipos->obtener(posicionEquipo);
	Llamada* llamada = equipo->obtenerUltimaLlamada();
	if (!llamada->estaFinalizada()){
		this->finalizarAntenaUtilizada(equipo,minuto);
	}
	antena->decrementarCantidadEquiposConectados();
	Conexion* ultimaConexion = equipo->obtenerUltimaConexion();
	ultimaConexion->desconectar();


}

void ParsearLineas::guardarLlamada(std::string datos, std::string tipo){

	std::string numeroEmisor = this->obtenerDato(datos);
	std::string numeroReceptor = this->obtenerDato(datos);
	unsigned int minutos = datos;

	Equipo* equipoEmisor = this->buscarEquipo(numeroEmisor);
	Equipo* equipoReceptor = this->buscarEquipo(numeroReceptor);

	if ((tipo == "Inicio")&&(equipoReceptor->estaConectado())){
		//this->equipoReceptorConectado(numeroReceptor) me va a indicar si el receptor esta conectado a
		//alguna antena si no lo esta en la antena del emisor se suma llamada anulada
		this->agregarLlamadaInicio(equipoEmisor, equipoReceptor, minutos);

	}else if (tipo == "Fin"){
		this->finalizarLlamada(equipoEmisor, equipoReceptor, minutos);

	}else{ //el receptor no esta conectado a una antena
		//al emisor le da ocupado ?? y la antena tiene una llamada anulada
		Conexion* conexion = equipoEmisor->obtenerUltimaConexion();
		Antena* antena = this->antenas->obtener(this->buscarAntena(conexion->obtenerNombreAntena()));
		antena->incrementarLlamadasAnuladas();
	}
}

void ParsearLineas::agregarLlamadaInicio(Equipo* equipoEmisor, Equipo* equipoReceptor, unsigned int minuto){

	//falta agregar las llamadas a los equipos si no ver si es conveniente
	//equipoEmisor->agregarLlamadas(equipoReceptor,"Inicio");
	//equipoReceptor->agregarLlamadas(equipoEmisor);

	Llamada* llamadaEmisor = new Llamada(equipoEmisor,"Inicio");
	Llamada* llamadaReceptor = new Llamada(equipoReceptor);

	this->guardarAntenaUtilizada(equipoEmisor, minuto, llamadaEmisor);
	this->guardarAntenaUtilizada(equipoReceptor, minuto, llamadaReceptor);

	if (!equipoReceptor->estaOcupado()){
		//incrementa el contador de los equipos en llamdas
		equipoEmisor->incrementarLlamadasSalientes();
		equipoReceptor->incrementarLlamadasEntrantes();

	}else{
		equipoEmisor->incrementarSalientesOcupado();
		equipoReceptor->incrementarEntrantesOcupado();
		llamadaEmisor->cambiarOcupado();//Indica que la llamada es saliente y dio ocupado
		llamadaReceptor->cambiarOcupado();
	}


}

void ParsearLineas::guardarAntenaUtilizada(Equipo* equipo, unsigned int minuto, Llamada* llamada){

	Conexion* ultimaAntena = equipo->obtenerUltimaConexion();
	//metodo de equipo;

	Lista<AntenaUtilizada*>* antenasUtilizadas = llamada->obtenerAntenasUtilizadas();
	//AntenaUtilizada* antena = new AntenaUtilizada(ultimaAntena->obtenerNombreAntena(),minuto);
	//antenasUtilizadas->agregar(antena);

}

void ParsearLineas::finalizarLlamada(Equipo* equipoEmisor, Equipo* equipoReceptor,unsigned int minuto){

	this->finalizarAntenaUtilizada(equipoEmisor,minuto);

	this->finalizarAntenaUtilizada(equipoReceptor,minuto);

}

void ParsearLineas::finalizarAntenaUtilizada(Equipo* emisor, unsigned int minuto){

	Lista<Llamada*>* llamadas = emisor->obtenerLLamadasEquipo();

	llamadas->iniciarCursor();
	bool encontrado = false;
	Llamada* llamada;
	while ((llamadas->avanzarCursor())&&!(encontrado)){
		llamada = llamadas->obtenerCursor();
		encontrado = (!llamada->estaFinalizada());
		//metodos de la clase llamada
	}
	//ir a la ultima antena utilizada y agregar minutos de finalizacion
	Lista<AntenaUtilizada*>* antenasUtilizadas = llamada->obtenerAntenasUtilizadas();
	AntenaUtilizada* ultimaAntenaLlamada = antenasUtilizadas->obtener(antenasUtilizadas->contarElementos());

	//obtiene el ultimo elemento de la antena utilizada
	ultimaAntenaLlamada->finAntenaUtilizada(minuto);
}

std::string ParsearLineas::obtenerDato(std::string & linea){
	unsigned int posicion;
	std::string dato;

	posicion = linea.find(" ");
	dato = linea.substr(0,posicion);
	linea = linea.erase(0,posicion+1);

	return dato;
}

unsigned int ParsearLineas::buscarAntena(std::string nombre){

	this->antenas->iniciarCursor();
	bool encontrado = false;
	Antena* antena;
	unsigned int pos=0;

	while(this->antenas->avanzarCursor()&&!(encontrado)){
		antena = this->antenas->obtenerCursor();
		encontrado = (antena->obtenerNombre() == nombre);
		pos += 1;
	}
	return pos;
}

unsigned int ParsearLineas::buscarEquipo(std::string numero){

	this->equipos->iniciarCursor();
	bool encontrado=false;
	Equipo* equipo;
	unsigned int pos=0;

	while(this->equipos->avanzarCursor()&&!encontrado){
		equipo=this->equipos->obtenerCursor();
		encontrado = (equipo->obtenerNumero()==numero);
		pos+=1;
	}
	return pos;
}
