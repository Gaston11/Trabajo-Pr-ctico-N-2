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
	void agregarEquipoQueConecto(Equipo* equipo);

	/*
	 * pre: si hubo equipos que conectaron en la antena
	 * post: devuelve la lista de equipos que se conectaron a la antena
	 */
	Lista<Equipo*>* obtenerEquiposQueConectaron();

};

#endif //ANTENA_H_INCLUDED
