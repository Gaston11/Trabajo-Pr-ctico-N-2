/*
 * Antena.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: noe
 */

#ifndef ANTENA_H_INCLUDED
#define ANTENA_H_INCLUDED

#include <string>
#include "Lista.h"
#include "Equipo.h"

class Equipo;

class Antena{

private:
	std::string nombreAntena;
	unsigned int cantidadConexiones;
	unsigned int cantidadEquiposConectados;
	unsigned int cantidadLlamadasAnuladas;
	Lista<Equipo*>* equiposQueConectaron;

public:
	/*
	 * post: crea una antena inicializando nombre y cantidad de conexiones
	 * que recibe, la cantidadEquiposConectados inicializa en cero y lista vacia de equipos asociados
	 */
	Antena(std::string nombreAntena, unsigned int conexiones);

	/*
	* post: elimina los recursos utilizados
	*/
	~Antena();

	/*
	 * post: devuelve un string indicando el nombre de la antena
	 */
	std::string obtenerNombre();

	/*
	 * pre: si hubo equipos que conectaron en la antena
	 * post: devuelve la lista de equipos que se conectaron a la antena
	 */
	Lista<Equipo*>* obtenerEquiposQueConectaron();

	/*
	 * post: incrementa la cantidad de equipos conectados a la antena
	 */
	void incrementarCantidadEquiposConectados();

	/*
	 * pre: se considera llamada anulada cuando el emisor conectado a una
	 * antena llama al receptor pero el mismo no esta conectado a una antena
	 * post: incrementa la cantidad de llamadas anuladas
	 */
	void incrementarLlamadasAnuladas();

	/*
	 * pre: si algun equipo se deconecta de la antena, siendo la cantidad
	 * de equipos conectados mayor a cero
	 * post : decrementa la cantidad e equipos coenctados
	 */
	void decrementarCantidadEquiposConectados();

	/*
	 * post: indica si la antena tiene capacidad para coenctar algun
	 * equipo
	 */
	bool hayCapacidadAntena();

	/*
	 * post: retorna la cantidad de conexiones de la antena
	 */
	unsigned int retornarCantidadDeConexiones();

	/*
	 * post: retorna la cantidad de equipos conectados de la antena
	 */
	unsigned int retornarCantidadDeEquiposConectados();

	/*
	 * post: retorna la cantidad de llamadas anuladas de la antena
	 */
	unsigned int retornarCantidadDeLlamadasAnuladas();

};

#endif //ANTENA_H_INCLUDED
