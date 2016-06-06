/*
 * ParsearLinea.h
 *
 *  Created on: 22 de may. de 2016
 *      Author: noe
 */

#include <string>
#include <fstream>
#include "Antena.h"
#include "Equipo.h"

class ParsearLineas {

private:

	std::string nombre;
	Lista<Antena*>* antenas;
	Lista<Equipo*>* equipos;

public:

	/*
	 * pre : recibe nombre del archivo que se desea procesar
	 * post: recibe una linea de string y la inicializa
	 */
	ParsearLineas(std::string nombreArchivo);

	/*
	 * pre: recibe un string o linea que proviene del archivo de texto
	 * post: obtiene el primer dato de la linea, lo elimina de la misma y luego
	 * lo devuelve
	 */
	void procesarLineas();

	/*
	 * pre : una vez procesado el archivo
	 * post: devuelve un puntero a una lista de antenas
	 */
	Lista<Antena*>* obtenerAntenas();

	/*
	 * post: devuelve un puntero a una lista de equipos (todos los equipos)
	 */
	Lista<Equipo*>* obtenerEquipos();

	/*
	 * post: elimina recursos utilizados por la clase
	 */
	~ParsearLineas();

	/*
	 * pre: recibe un string o linea que proviene del archivo de texto
	 * post: obtiene el primer dato de la linea, lo elimina de la misma y luego
	 * lo devuelve
	 */
	std::string obtenerDato(std::string & linea);

	/*
	 * post: procesa lo que contiene una linea almacenando la informacion
	 * 		que corresponda
	 */
	void procesarLinea(std::string linea);

	/*
	 * pre : si los datos a almacenar pertenecen a una antena nueva
	 * post: guarda los datos de una antena
	 */
	void guardarAntena(std::string datos);

	/*
	 * pre : recibe parte de una linea que contiene datos del archivo
	 * post: segun el tipo(conectar/descoenctar, inicio/fin) almacena
	 * informacion en el equipo
	 */
	void guardarEquipo(std::string datos, std::string tipo);

	/*
	 *post: segun tipo(conectar/desconectar) almacena informacion del
	 *equipo y de la antena
	 */
	void guardarConexion(std::string datos, std::string tipo);

	/*
	 * pre : recibe por parametro una antena, busca en la lista de antenas
	 * cargadas si el nombre de alguna de las mismas es igual a la que pasa
	 * por parametro(considero que si 2 antenas tienen el mismo nombre son
	 * iguales)
	 * post: si se encuentra en la lista devuelve la posicion de la misma que
	 * va a ser mayor a cero, si no se encuentra devuelve cero
	 */
	unsigned int buscarAntena(std::string nombre);

	/*
	 * pre : recibe por parametro un numero, busca en la lista de equipos
	 * cargados si el nombre de alguno es igual a la que pasa
	 * por parametro(considero que si 2 numeros son iguales es el mismo equipo)
	 * post: si se encuentra en la lista devuelve la posicion del mismo que
	 * va a ser mayor a cero, si no se encuentra devuelve cero
	 */
	unsigned int buscarEquipo(std::string nombre);

	/*
	 * pre : recibe nombre antena, un numero y posiciones de los mismos en las listas
	 * respectivas
	 * post: evaluando la capacidad y si se encuentra el equipo o no en la lista
	 * conecta la antena en la ultima conexion del equipo
	 */
	void conectarEquipo(Antena* antena, std::string numero, unsigned int posicionEquipo, unsigned int minuto);

	/*
	 * pre : recibe un numero una posicion del equipo en la lista, los minutos y una antena
	 * post: desconecta el equipo de la ultima conexion y la llamada la antena
	 * utilizada
	 */
	void desconectarEquipo(Antena* antena, std::string numero, unsigned int posicionEquipo, unsigned int minuto);

	/*
	 * post: almacena la llamada segun el tipo(si es Inicio o fin)
	 */
	void guardarLlamada(std::string datos, std::string tipo);

	/*
	 * pre : el tipo de entrada es inicio
	 * post: guarda la antena utilizada en la llamada de los numeros Emisor
	 * y receptor almacenando el minuto de conexion de llamada
	 */
	void agregarLlamadaInicio(Equipo* equipoEmisor, Equipo* equipoReceptor, unsigned int minuto);

	/*
	 * post: finaliza las llamadas de los numeros pasado por parametro
	 */
	void finalizarLlamada(Equipo* equipoEmisor, Equipo* equipoReceptor,unsigned int minuto);

	/*
	 * pre : recibe un equipo con su llamada y los minutos en el que realizo una llamada
	 * post: guarda en llamada la antena utilizada durante una comunicacion con el minuto de
	 * conexion
	 */
	void guardarAntenaUtilizada(Equipo* equipo, unsigned int minuto, Llamada* llamada);

	/*
	 * post: finaliza la ultima antena utilizada de una comunicacion
	 */
	void finalizarAntenaUtilizada(Equipo* emisor, unsigned int minuto);

	/*
	 *post: obtiene una cadena de numeros y los convierte en un entero
	 */
	unsigned int convertir_entero(std::string cadena);

	/*
	 * post: devuelve la longitud de una cadena
	 */
	unsigned int longitud(std::string cadena);


};


