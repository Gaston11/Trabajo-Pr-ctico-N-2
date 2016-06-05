/*
 * Conexion.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: noe
 */

#ifndef CONEXION_H_INCLUDED
#define CONEXION_H_INCLUDED

#include <string>

class Conexion{

private:
	std::string nombreAntena;
	bool conectado;

public:

	/*
	 * post: crea una conexion vacia
	 */
	Conexion();

	/*
	 * pre : si no esta conectado a una antena
	 * post: inicializa la conexion
	 */
	Conexion(std::string nombre);

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
	std::string obtenerNombreAntena();

	/*
	 * post: cambia el nombre de la antena a la que esta conectada
	 * y se conecta
	 */
	void cambiarNombreAntena(std::string nombre);

	/*
	 * post: elimina los recursos compartidos
	 */
	~Conexion();


};

#endif //CONEXION_H_INCLUDED
