/*
 * AntenaUtilizada.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: noe
 */

#include <string>

class AntenaUtilizada {

private:
	std::string nombre;//o puntero a antena ???
	unsigned int minutoIniciado;
	unsigned int minutoFinalizado;

public:
	/*
	 * post: inicia la antena utilizada durante una llamada y el tiempo
	 * en el que inicio
	 */
	AntenaUtilizada(std::string nombre, unsigned int minuto);

	/*
	 * pre: cuando finaliza la conexion en esta antena
	 * post: guarda el minuto en que se finalizo
	 */
	void finAntenaUtilizada(unsigned int minutoFinal);

	/*
	 * post: devuelve la cantidad de minutos que estuvo conectado en
	 * la antena realizando la llamada
	 */
	unsigned int duracionDeMinutosEnAntena();

};

