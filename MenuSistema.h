/*
 * MenuSistema.h
 *
 *  Created on: 31 de may. de 2016
 *      Author: noe
 */

#ifndef MENUSISTEMA_H_INCLUDED
#define MENUSISTEMA_H_INCLUDED

#include "Equipo.h"

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
	 * post: muestra detalles de llamadas emitidas de un equipo
	 */
	void detalleDeLlamadasEmitidas();

	/*
	 * post: muestra detalles de llamadas realizadas de un equipo
	 */
	void detalleDeLlamadasRealizadas();

	/*
	 * post: muestra el detalle de todos los equipos que se encuentran
	 * en el sistema (numero y antena de la ultima conexion)
	 */
	void detalleDeEquipos();

};

#endif //MENUSISTEMA_H_INCLUDED
