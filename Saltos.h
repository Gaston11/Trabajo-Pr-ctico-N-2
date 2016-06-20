/*
 * Saltos.h
 *
 *  Created on: 19 de jun. de 2016
 *      Author: noe
 */

#include "Grafo.h"
#include "Equipo.h"
#include "Antena.h"
#include <iostream>


class Saltos{

private:

	Lista<Equipo*>* equipos;
	Lista<Antena*>* antenas;

	unsigned int rango;
	unsigned int matriz[50][50];

public:
	/*
	 * pre: recibe una lista de equipos
	 * post: inicializa la cantidad, de cada par de antenas, de
	 * 		saltos en 0
	 */
	Saltos(Lista<Equipo*>* equipos,Lista<Antena*>* antenas);

	/*
	 * post: elimina los recursos utilizados
	 */
	~Saltos();

	/*
	 * post: muestra por pantalla la cantidad de saltos de celulares
	 * acumulados por cada par de antenas
	 */
	void cantidadSaltos();

private:

	/*
	 * post: por cada equipo se evaluan las antenas utilizadas en las llamadas
	 */
	void contabilizarSaltos();

	/*
	 * pre: recibe una lista de llamadas
	 * post: si la llamada no dio ocupada procesa la lista de antenas
	 * utilizadas
	 */
	void procesarLlamadas(Lista<Llamada*>* llamadas);

	/*
	 * pre: recibe una lista de antenas utilizadas por un equipo
	 * post: acumula saltos y los suma segun el par de antenas
	 */
	void procesarAntenas(Lista<AntenaUtilizada*>* antenasUtilizadas);

	/*
	 * pre: recibe por parametro el nombre de una antena
	 * post: devuelve la poscion en la que se encuentra en la lista de antenas
	 * [1..cantidad de elemntos en la lista de antenas]
	 */
	unsigned int obtenerPosicionAntena(std::string nombreAntena);

	/*
	 * pre: recibe un diagrama (en la que se encuentran el orden de las
	 * conexiones de antenas durante una llamada)
	 * post: suma la cantidad de saltos segun el diagrana obtenido
	 */
	void sumarSaltos(Grafo<unsigned int>* diagrama);

};
