/*
 * Conexion.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: noe
 */

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
	 * post: devuelve el nombre de la antena
	 */
	std::string obtenerNombreAntena();


};

