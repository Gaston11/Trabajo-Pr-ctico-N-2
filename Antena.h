/*
 * Antena.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: noe
 */
#ifndef ANTENA_H_INCLUDED
#define ANTENA_H_INCLUDED

#include "Lista.h"
#include <string>

#include "Equipo.h"

class Antena{

private:
	std::string nombreAntena;
	unsigned int cantidadConexiones;
	unsigned int cantidadEquiposConectados; // Falta metodos de manipulacion
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
	 * post: agrega el equipo que se conecto a la antena a la lista
	 * equiposQueConectaron
	 */
	//void agregarEquipoQueConecto(Equipo* equipo);

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

};

#endif //ANTENA_H_INCLUDED
