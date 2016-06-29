/*
 * Conexion.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: noe
 */

#ifndef CONEXION_H_INCLUDED
#define CONEXION_H_INCLUDED

#include "Antena.h"

class Antena;

class Conexion{

private:
	Antena* antena;
	bool conectado;

public:

	/*
	 * pre : si no esta conectado a una antena
	 * post: inicializa la conexion
	 */
	Conexion(Antena* antena);

	/*
	 * post: conecta la antena
	 */
	void conectar();

	/*
	 * post: desconecta la antena al equipo
	 */
	void desconectar();

	/*
	 * post: indica si la conexion esta conectada a una antena
	 */
	bool estaConectado();

	/*
	 * post: devuelve el nombre de la antena
	 */
	Antena* obtenerAntena();

	/*
	 * post: cambia el nombre de la antena a la que esta conectada
	 * y se conecta
	 */
	void cambiarAntena(Antena* nuevaAntena);

	/*
	 * post: elimina los recursos compartidos
	 */
	~Conexion();


};

#endif //CONEXION_H_INCLUDED
