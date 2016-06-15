/*
 * ParsearLineas.cpp
 *
 *  Created on: 22 de may. de 2016
 *      Author: noe
 */

#include "ParsearLineas.h"


ParsearLineas::ParsearLineas(std::string nombreArchivo){

	this->antenas = new Lista<Antena*>;
	this->equipos = new Lista<Equipo*>;

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
	unsigned int cantidadDeConexiones=this->convertir_entero(datos);

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
	unsigned int minuto=this->convertir_entero(datos);

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

		Equipo* equipo;
		if (posicionEquipo==0){

			equipo = new Equipo(numero);
			this->equipos->agregar(equipo);

		}else{
			equipo = this->equipos->obtener(posicionEquipo);
			Llamada* llamada= equipo->obtenerUltimaLlamada();
			if (!llamada->estaFinalizada()){
				AntenaUtilizada* antenaNueva= new AntenaUtilizada(antena->obtenerNombre(),minuto);
				Lista<AntenaUtilizada*>* antenas = llamada->obtenerAntenasUtilizadas();
				antenas->agregar(antenaNueva);
			}

		}
		Lista<Equipo*>* equiposQueConectaron = antena->obtenerEquiposQueConectaron();
		equiposQueConectaron->agregar(equipo);

		antena->incrementarCantidadEquiposConectados();
		Conexion* conexion = equipo->obtenerUltimaConexion();
		conexion->cambiarNombreAntena(antena->obtenerNombre());
	}
	//si no hay capacidad en antena espera hasta conetar con otra

}

void ParsearLineas::desconectarEquipo(Antena* antena, std::string numero, unsigned int posicionEquipo, unsigned int minuto){

	Equipo* equipo = this->equipos->obtener(posicionEquipo);
	Lista<Llamada*>* llamadas = equipo->obtenerLLamadasEquipo();
	llamadas->iniciarCursor();
	bool encontrado = false;
	Llamada* llamada;
	//busca en llamdas la llamada que no finalizo
	while(llamadas->avanzarCursor() && ! encontrado){
		llamada = llamadas->obtenerCursor();
		encontrado=(!llamada->estaFinalizada());
	}
	if (encontrado){
		Equipo* equipoReceptor = this->equipos->obtener(this->buscarEquipo(llamada->obtenerCelular()));
		this->finalizarLlamada(equipo,equipoReceptor,minuto);
	}
	antena->decrementarCantidadEquiposConectados();
	Conexion* ultimaConexion = equipo->obtenerUltimaConexion();
	ultimaConexion->desconectar();

}

void ParsearLineas::guardarLlamada(std::string datos, std::string tipo){

	std::string numeroEmisor = this->obtenerDato(datos);
	std::string numeroReceptor = this->obtenerDato(datos);
	unsigned int  minutos= this->convertir_entero(datos);

	Equipo* equipoEmisor = this->equipos->obtener(this->buscarEquipo(numeroEmisor));
	Equipo* equipoReceptor = this->equipos->obtener(this->buscarEquipo(numeroReceptor));

	if ((tipo == "Inicio")&&(equipoReceptor->estaConectado())){

		this->agregarLlamadaInicio(equipoEmisor, equipoReceptor, minutos);

	}else if (tipo == "Fin"){
		this->finalizarLlamada(equipoEmisor, equipoReceptor, minutos);
		Llamada* llamadaEmisor = equipoEmisor->obtenerUltimaLlamada();
		Llamada* llamadaReceptor = equipoReceptor->obtenerUltimaLlamada();
		llamadaEmisor->finalizarLlamada();
		llamadaReceptor->finalizarLlamada();

	}else{ //el receptor no esta conectado a una antena
		//la antena tiene una llamada anulada
		Conexion* conexion = equipoEmisor->obtenerUltimaConexion();
		Antena* antena = this->antenas->obtener(this->buscarAntena(conexion->obtenerNombreAntena()));
		antena->incrementarLlamadasAnuladas();
	}
}

void ParsearLineas::agregarLlamadaInicio(Equipo* equipoEmisor, Equipo* equipoReceptor, unsigned int minuto){

	Llamada* llamadaEmisor = new Llamada(equipoEmisor->obtenerNumero(),"Inicio");
	Llamada* llamadaReceptor = new Llamada(equipoReceptor->obtenerNumero());

	this->guardarAntenaUtilizada(equipoEmisor, minuto, llamadaEmisor);
	this->guardarAntenaUtilizada(equipoReceptor, minuto, llamadaReceptor);

	if (equipoReceptor->estaOcupado()&&(equipoReceptor->obtenerUltimaLlamada()->obtenerCelular()==equipoEmisor->obtenerNumero())){
		//incrementa el contador de los equipos en llamdas
		equipoEmisor->incrementarLlamadasSalientes();
		equipoReceptor->incrementarLlamadasEntrantes();

	}else{
		equipoEmisor->incrementarSalientesOcupado();
		equipoReceptor->incrementarEntrantesOcupado();
		llamadaEmisor->cambiarOcupado();//Indica que la llamada es saliente y dio ocupado
		llamadaReceptor->cambiarOcupado();
	}

	Lista<Llamada*>* llamadasEmisor = equipoEmisor->obtenerLLamadasEquipo();
	Lista<Llamada*>* llamadasReceptor = equipoReceptor->obtenerLLamadasEquipo();
	llamadasEmisor->agregar(llamadaEmisor);
	llamadasReceptor->agregar(llamadaReceptor);
}

void ParsearLineas::guardarAntenaUtilizada(Equipo* equipo, unsigned int minuto, Llamada* llamada){

	Lista<AntenaUtilizada*>* antenasUtilizadas = llamada->obtenerAntenasUtilizadas();
	Conexion* ultimaAntena = equipo->obtenerUltimaConexion();
	AntenaUtilizada* antena = new AntenaUtilizada((ultimaAntena->obtenerNombreAntena()),minuto);
	antenasUtilizadas->agregar(antena);

}

void ParsearLineas::finalizarLlamada(Equipo* equipoEmisor, Equipo* equipoReceptor,unsigned int minuto){

	this->finalizarAntenaUtilizada(equipoEmisor,minuto);

	this->finalizarAntenaUtilizada(equipoReceptor,minuto);

}

void ParsearLineas::finalizarAntenaUtilizada(Equipo* equipo, unsigned int minuto){


	Llamada* llamada = equipo->obtenerUltimaLlamada();
	//ir a la ultima antena utilizada y agregar minutos de finalizacion
	Lista<AntenaUtilizada*>* antenasUtilizadas = (llamada->obtenerAntenasUtilizadas());
	AntenaUtilizada* ultimaAntenaLlamada = (antenasUtilizadas->obtener(antenasUtilizadas->contarElementos()));

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

unsigned int ParsearLineas::buscarEquipo(std::string numero){

	this->equipos->iniciarCursor();
	bool encontrado=false;
	Equipo* equipo;
	unsigned int pos=0;

	while(this->equipos->avanzarCursor()&&!encontrado){
		equipo=this->equipos->obtenerCursor();
		encontrado = ((equipo->obtenerNumero())==numero);
		pos+=1;
	}
	if (!(encontrado)){
			pos=0;
	}
	return pos;
}
unsigned int ParsearLineas::buscarAntena(std::string nombre){

	this->antenas->iniciarCursor();
	bool encontrado = false;
	Antena* antena;
	unsigned int pos=0;

	while(this->antenas->avanzarCursor()&&!(encontrado)){
		antena = this->antenas->obtenerCursor();
		encontrado = ((antena->obtenerNombre()) == nombre);
		pos += 1;
	}
	if (!(encontrado)){ //si no fue encontrado
		pos=0;
	}
	return pos;
}

ParsearLineas::~ParsearLineas(){
	this->antenas->iniciarCursor();
	this->equipos->iniciarCursor();
	while(this->antenas->avanzarCursor()){
		delete this->antenas->obtenerCursor();
	}
	while(this->equipos->avanzarCursor()){
		delete this->equipos->obtenerCursor();
	}
	delete this->antenas;
	delete this->equipos;

}

unsigned int ParsearLineas::longitud(std::string cadena)
{
  unsigned int  valor = 0;
  unsigned int i;

  for(i=0; cadena[ i ]!='\0'; i++)
     valor++;

  return valor;
}

unsigned int ParsearLineas::convertir_entero(std::string cadena)
{
  unsigned int potencias[5]={1,10,100,1000};
  int i;
  unsigned int valor = 0;
  unsigned int lon = longitud(cadena);

  for(i=lon-1; i>=0; i--)
     valor += (cadena[ i ]-'0') * potencias[ lon-i-1 ];

  return valor;
}
