/*
 * Equipo.h
 *
 *  Created on: 20 de may. de 2016
 *      Author: noe
 */


#ifndef EQUIPO_H_INCLUDED
#define EQUIPO_H_INCLUDED


#include <string>

#include "Conexion.h"
#include "Llamada.h"

class Equipo{

private:
	std::string numero;
	Lista<Llamada*>* llamadas;
	Conexion* ultimaConexionAntena;

	unsigned int llamadasEntrantes;
	unsigned int llamadasSalientes;
	unsigned int entrantesOcupado;
	unsigned int salientesOcupado;


public:

	/*
	 * post: Inicializa al equipo con numero
	 */
	Equipo(std::string numero);

	/*
	 * post: devuelve el numero del equipo celular
	 */
	std::string obtenerNumero();

	/*
	 *
	 */
	void agregarLlamadas();

	/*
	 * post: devuelve la lista de todas las llamadas asociada al equipo
	 */
	Lista<Llamada*>* obtenerLLamadasEquipo();

	/*
	 * pre : si la lista de llamadas no esta vacia
	 * post: devuelve la ultima llamada de equipo que no esta finalizada
	 */
	Llamada* obtenerUltimaLlamada();

	/*
	 * pre : el equipo ya esta conectado a una antena
	 * post: devuelve la conexion del equipo
	 */
	Conexion* obtenerUltimaConexion();

	/*
	 * post: indica si el equipo esta conectado a una antena
	 */
	bool estaConectado();

	/*
	 * post: indica si un equipo esta ocupado en otra comunicacion
	 */
	bool estaOcupado();

	/*
	 * post: incrementa en 1 si el equipo realizo una llamada
	 */
	void incrementarLlamadasSalientes();

	/*
	 * post: incrementa en uno si el equipo recibio una llamada
	 */
	void incrementarLlamadasEntrantes();

	/*
	 * post: incrementa en uno si al realizar una llamada al equipo le dio
	 * ocupado
	 */
	void incrementarSalientesOcupado();

	/*
	 * post: incrementa en uno si dio ocupado
	 */
	void incrementarEntrantesOcupado();

	/*
	 * post: incrementa en uno si al equipo se le anulo la llamada
	 */
	void incrementarLlamadasAnuladas();

	/*
	 * post: devuelve la cantidad de llamadas que recibio el equipo
	 */
	unsigned int obtenerLlamadasEntrantes();

	/*
	 * post: devuelve la cantidad de llamadas que realizo el equipo
	 */
	unsigned int obtenerLlamadasSalientes();

	/*
	 * post: devuelve la cantidad de llamadas que le dio ocupado
	 */
	unsigned int obtenerLlamadasSalienteOcupado();

	/*
	 * post: devuelve la cantidad de llamadas que dio ocupado
	 */
	unsigned int obtenerLlamadasEntranteOcupado();



};


#endif //EQUIPO_H_INCLUDED
