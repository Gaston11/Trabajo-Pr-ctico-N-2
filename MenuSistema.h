/*
 * MenuSistema.h
 *
 *  Created on: 31 de may. de 2016
 *      Author: noe
 */

#ifndef MENUSISTEMA_H_INCLUDED
#define MENUSISTEMA_H_INCLUDED

#include "Equipo.h"
#include <iostream>

class MenuSistema {

private:
	Lista<Equipo*>* equipos;

public:

	/*
	 * pre: recibe una lista de equipos
	 * post: inicializa la lista que se tiene por la obtenida
	 */
	MenuSistema(Lista<Equipo*>* equipos);

	/*
	 * post: muestra las opciones de menu del sistema
	 */
	void opcionesDeMenuSistema();

	/*
	 * pre: recibe una opcion de menu
	 * post: evalua si la opcion es correcta y accede a la opcion
	 */
	void opciones(char opcion);

	/*
	 * post: realiza las opciones de menu del sistema si se sale del mismo
	 * vuelve al menu principal
	 */
	void Menu();

private:
	/*
	 * post: muestra detalle entre 2 equipos, mostrando:
	 * cantidad de llamadas, antenas utilizadas, cantidad de tiempo hablado,
	 * cantidad de veces ocupado(suma de realizadas y recibidas)
	 */
	void detalleEntreEquipos();

	/*
	 * post: muestra el equipo que mas hablo, si hay mas de uno con la misma
	 * cantidad de tiempo los muestra
	 */
	void equipoQueMasHablo();

	/*
	 * post: muestra el celular que mas hablo si hay mas de uno con la misma
	 * cantidad los muestra
	 */
	void celularQueMasLlamo();

	/*
	 * post: muestra la al equipo que mas le dio ocupado sus intentos de
	 * realizar una llamda
	 */
	void equipoQueMasDioOcupado();

	/*
	 * post: muestra el/los equipos al que mas llamaron
	 */
	void equipoQueMasLlamaron();

	/*
	 * post: muestra el/los equipos que mas le hablaron
	 */
	void equipoAlQueMasHablaron();

	/*
	 * post: muestra el que equipo que mas dio ocupado
	 */
	void equipoMasOcupado();

	/*
	 * post: muestra detalles de llamadas emitidas de un equipo, a su vez
	 * devuelve la posicion de dicho equipo en la lista
	 */
	unsigned int detalleDeLlamadasEmitidas();

	/*
	 * post: muestra detalles de llamadas recibidas de un equipo, a su vez
	 * devuelve la posicion de dicho equipo en la lista
	 */
	unsigned int detalleDeLlamadasRecibidas();

	/*
	 * post: devuelve el detalle de llamadas recibidas de un equipo y
	 * realizadas de otro, a su vez muestra las antenas utilizadas durante
	 * esas llamadas
	 */
	void detalleRecibidasYRealizadas();

	/*
	 * post: muestra el detalle de todos los equipos que se encuentran
	 * en el sistema (numero y antena de la ultima conexion)
	 */
	void detalleDeEquipos();

	/*
	 * post: muestra el detalle de un equipo particular
	 */
	void detalleEquipo(Equipo* equipo);

	/*
	 * post: devuelve la cantidad de antenas que utilizo un equipo durante
	 * todas las llamdas
	 */
	unsigned int cantidadAntenasUtilizadas(Equipo* equipo);

	/*
	 * post: muestra por pantalla los nombres de las antenas utilizadas
	 * durante una llamada
	 */
	void mostrarAntenasUtilizadas(Llamada* llamada);

	/*
	 * post: muestra por pantalla el codigo/numero de todos los elementos de
	 * la lista que recibe por parametro
	 */
	void mostrarEquipos(Lista<Equipo*>* equipos);

	/*
	 * pre: recibe un equiṕo/celular
	 * post: calcula y deuelve los minutos totales de todas sus llamadas
	 */
	unsigned int calculaMinutosHablado(Equipo* equipo);

	/*
	 * post: calcula los minutos que mas le hablaron a un equipo, esto quiere
	 * decir que calcula los minutos que se realizaron en una llamada entrante
	 */
	unsigned int calcularMinutosHablaron(Equipo* equipo);

	/*
	 * post: suma los minutos de las antenas utilizadas en una llamada
	 */
	unsigned int sumarDuracion(Lista<AntenaUtilizada*>* antenas);
};

#endif //MENUSISTEMA_H_INCLUDED
