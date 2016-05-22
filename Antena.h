/*
 * Antena.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: noe
 */

#include <string>

#include "Equipo.h"

class Antena{

private:
	std::string nombre;
	unsigned int cantidadConexiones;
	unsigned int cantidadEquiposConectados; // Falta metodos de manipulacion
	Lista<Equipo*>* equiposQueConectaron;

public:
	/*
	 * post: crea una antena inicializando nombre y cantidad de conexiones
	 * que recibe, lista vacia de equipos asociados
	 */
	Antena(std::string nombre, unsigned int conexiones);

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
	 * post: elimina los recursos utilizados
	 */
	~Antena();


};

