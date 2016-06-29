/*
 * ParsearLineas.cpp
 *
 *  Created on: 25 de jun. de 2016
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

			equipo = new Equipo(numero, antena);
			this->equipos->agregar(equipo);

		}else{
			equipo = this->equipos->obtener(posicionEquipo);
			Llamada* llamada= equipo->obtenerUltimaLlamada();
			if (!llamada->estaFinalizada()){
				AntenaUtilizada* antenaNueva= new AntenaUtilizada(antena,minuto);
				Lista<AntenaUtilizada*>* antenas = llamada->obtenerAntenasUtilizadas();
				antenas->agregar(antenaNueva);
			}
			Conexion* conexion = equipo->obtenerUltimaConexion();
			conexion->cambiarAntena(antena);

		}
		Lista<Equipo*>* equiposQueConectaron = antena->obtenerEquiposQueConectaron();
		equiposQueConectaron->agregar(equipo);

		antena->incrementarCantidadEquiposConectados();
	}
	//si no hay capacidad en antena espera hasta conetar con otra

}

void ParsearLineas::desconectarEquipo(Antena* antena, std::string numero, unsigned int posicionEquipo, unsigned int minuto){

	Equipo* equipo = this->equipos->obtener(posicionEquipo);
	Llamada* llamada = equipo->obtenerUltimaLlamada();

	if (!llamada->estaFinalizada()){
		this->finalizarAntenaUtilizada(llamada,minuto);
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
		std::cout << "el equipo receptor esta conectado INicia llamda"<<std::endl;
		std::cout << numeroEmisor<<std::endl;
		std::cout << numeroReceptor<<std::endl;
		this->agregarLlamadaInicio(equipoEmisor, equipoReceptor, minutos);

	}else if (tipo == "Fin"){
		//finaliza las antenas utilizadas
		std::cout << "Finalizar LLamada de :";
		std::cout << "Numero Emisor/receptor: ";
		std::cout << numeroEmisor << std::endl;
		std::cout << numeroReceptor << std::endl;
		this->finalizarLlamada(equipoEmisor, equipoReceptor, minutos);
		//luego finaliza las llamadas


	}else{ //el receptor no esta conectado a una antena
		//la antena tiene una llamada anulada
		std::cout<<"el recpetor no esta conectado a una antena"<<std::endl;
		std::cout << "Incrementa llamdas anuladas de la antena del emisor"<< std::endl;

		Lista<Llamada*>* llamadas = equipoEmisor->obtenerLLamadasEquipo();
		Llamada* llamada = new Llamada(equipoReceptor, "Inicio");
		llamadas->agregar(llamada);
		Conexion* conexion = equipoEmisor->obtenerUltimaConexion();
		conexion->obtenerAntena()->incrementarLlamadasAnuladas();
	}
}

void ParsearLineas::agregarLlamadaInicio(Equipo* equipoEmisor, Equipo* equipoReceptor, unsigned int minuto){

	Llamada* llamadaEmisor = new Llamada(equipoReceptor,"Inicio");
	Llamada* llamadaReceptor = new Llamada(equipoEmisor);
	std::cout <<"Se crearon llamadas, llamada del emisor a :";
	std::cout << llamadaEmisor->obtenerCelular()->obtenerNumero()<<std::endl;
	std::cout << llamadaReceptor->obtenerCelular()->obtenerNumero()<<std::endl;

	this->guardarAntenaUtilizada(equipoEmisor, minuto, llamadaEmisor);
	this->guardarAntenaUtilizada(equipoReceptor, minuto, llamadaReceptor);

	//if (equipoReceptor->estaOcupado() && equipoReceptor->obtenerUltimaLlamada()->obtenerCelular()==equipoEmisor){
	if (!equipoReceptor->estaOcupado()){
		//incrementa el contador de los equipos en llamdas
		std::cout << "el equipo receptor no esta ocupado"<<std::endl;
		std::cout << "Incremento salientes y entrantes"<<std::endl;
		equipoEmisor->incrementarLlamadasSalientes();
		equipoReceptor->incrementarLlamadasEntrantes();

	}else{
		std::cout << "el equipo esta ocupado"<< std::endl;
		std::cout << "Incrementa llamadas Ocupados"<<std::endl;
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
	AntenaUtilizada* antena = new AntenaUtilizada(ultimaAntena->obtenerAntena(),minuto);
	antenasUtilizadas->agregar(antena);

}

void ParsearLineas::finalizarLlamada(Equipo* equipoEmisor, Equipo* equipoReceptor,unsigned int minuto){

	std::cout << "Obtiene las ultimas llamadas"<< std::endl;//borrar
	Llamada* llamadaEmisor = equipoEmisor->obtenerUltimaLlamada();
	Llamada* llamadaReceptor = equipoReceptor->obtenerUltimaLlamada();

	if (llamadaEmisor->obtenerCelular()!=llamadaReceptor->obtenerCelular()){
		std::cout << "La ultima llamada no es la correcta..."<<std::endl; //borrar
		std::cout << "Busca la llamada correspondiente.."; // borrar
		llamadaEmisor=this->buscarLlamada(equipoEmisor,equipoReceptor);
		llamadaReceptor=this->buscarLlamada(equipoReceptor,equipoEmisor);
		this->finalizarAntenaUtilizada(llamadaEmisor,minuto);
		this->finalizarAntenaUtilizada(llamadaReceptor,minuto);
	}

	std::cout<<"Finaliza las llamadas"<<std::endl; //borrar
	llamadaEmisor->finalizarLlamada();
	llamadaReceptor->finalizarLlamada();

}

void ParsearLineas::finalizarAntenaUtilizada(Llamada* llamada, unsigned int minuto){


	std::cout << "Obtiene la ultima llamada de equipo: ";//borrar

	//Llamada* llamada = equipo->obtenerUltimaLlamada();

	//ver si la llamada del emisor no condice con el receptor
	//falla para finalizar

	std::cout<<"Con el equipo :"; //borrar
	std::cout << llamada->obtenerCelular()->obtenerNumero()<<std::endl;
	//ir a la ultima antena utilizada y agregar minutos de finalizacion
	Lista<AntenaUtilizada*>* antenasUtilizadas = llamada->obtenerAntenasUtilizadas();
	AntenaUtilizada* ultimaAntenaLlamada = antenasUtilizadas->obtener(antenasUtilizadas->contarElementos());

	//obtiene el ultimo elemento de la antena utilizada
	ultimaAntenaLlamada->finAntenaUtilizada(minuto);
	std::cout<<"finaliza la antena utilizada"<<std::endl;
}

Llamada* ParsearLineas::buscarLlamada(Equipo* emisor, Equipo* receptor){
	Lista<Llamada*>* llamadas = emisor->obtenerLLamadasEquipo();
	Llamada* llamada;
	llamadas->iniciarCursor();
	bool encontrado=false;
	while(llamadas->avanzarCursor() && ! encontrado){
		llamada=llamadas->obtenerCursor();
		if(!llamada->estaFinalizada()){
			encontrado=(llamada->obtenerCelular()==receptor);
		}
	}
	return llamada;
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
		encontrado = ( nombre == antena->obtenerNombre());
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
	std::cout << "Destructor ParsearLineas"<<std::endl;

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
