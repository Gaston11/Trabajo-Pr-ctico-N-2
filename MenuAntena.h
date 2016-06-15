/*
 * MenuAntena.h
 *
 *  Created on: 24/05/2016
 *      Author: gaston
 */
#ifndef MENUANTENA_H_INCLUDED
#define MENUANTENA_H_INCLUDED

#include "Antena.h"
#include "Equipo.h"
#include <iostream>

class MenuAntena{
	private:
		Lista<Antena*>* listaAntenas;
		Lista<Equipo*>* listaEquipos;

	public:
		/*
		 * Constructor
		 * post: crea un menu con los datos de: Listas de equipos y Lista de antenas
		 */
		MenuAntena(Lista<Antena*>* nuevaListaAntenas, Lista<Equipo*>* nuevaListaEquipos);

		/*
		 * Post: realiza el metodo que corresponda del menu
		 */
		void MenuPrincipal();

		/*
		 * post: recorre la lista antena y realiza el metodo segun corresponda la opcion
		 */
		void opcionesAntena(char opcion);

		/*
		 * Post: muestra por pantalla el numero del equipo y la cantidad indicada ( minutos o llamadas)
		 */
		void mostrarPorPantalla(Equipo* equipo, unsigned int cantidad);


		/*
		 * post: imprime por pantalla el numero de equipo que mas hablo y la cantidad de minutos. Opcion B
		 */
		void equipoQueMasHablo(Antena* antena);   // para opcion b)  realizada true, ocupado false, entrante false.

		/*
		 * post: retorna los minutos de llamadas entrante de la lista llamadas
		 */
		unsigned int contarMinutosDeLlamadaRealizada(Lista<Llamada*>* llamadas, std::string nombreAntena);

		/*
		 * post: retorna los minutos de llamadas entrante de la lista antenas utilizadas
		 */
		unsigned int contarMinutosAntena(Llamada* llamadaActual, std::string nombreAntena );

		/*
		 * post: imprime por pantalla el numero de equipo que mas llamo y la cantidad de llamadas. Opcion C
		 */
		void equipoQueMasLlamo(Antena* antena);  // para opcion c)

		/*
		 * post: devuelve true si el nombre de la antena esta en la lista de antenas utilizadas.
		 */
		bool antenaUsadaEnLlamada(Lista<AntenaUtilizada*>* antenasUtilizadas, std::string nombreAntena);

		/*
		 * post: retorna la cantidad de llamadas realizadas de la lista llamadas
		 */
		unsigned int contarLlamadasRealizadas(Lista<Llamada*>* llamadas, std::string nombreAntena);

		/*
		 * post: imprime por pantalla el numero de equipo que mas le dio ocupado al realizar llamadas
		 *  y la cantidad de veces que sucedio. Opcion D
		 */
		void equipoQueMasLeDioOcupadoAlRealizarLlamada(Antena* antena); //PREGUNTAR  para opcion d)

		/*
		 * post: retorna la cantidad de llamadas realizadas que dan ocupado de la lista llamadas
		 */
		unsigned int contarLlamadasRealizadasOcupado(Lista<Llamada*>* llamadas, std::string nombreAntena);

		/*
		 * post: imprime por pantalla el numero de equipo al que mas le llamaron y la cantidad de llamadas. Opcion E
		 */
		void equipoAlQueMasLlamaron(Antena* antena);   // para opcion e)

		/*
		 * post: retorna la cantidad de llamadas entrantes que coinciden con el nombre antena
		 */
		unsigned int contarLlamadasEntrantes(Lista<Llamada*>* llamadas, std::string nombreAntena);

		/*
		 * post: imprime por pantalla el numero de equipo que mas le hablaron y la cantidad de minutos. Opcion F
		 */
		void equipoAlQueMasLeHablaron(Antena* antena);  //para opcion f)

		/*
		 * post: retorna la cantidad deminutos de llamadas entrantes que coinciden con el nombre antena
		 */
		unsigned int contarMinutosDeLlamadasRecibidas(Lista<Llamada*>* llamadas, std::string nombreAntena);

		/*
		 * post: imprime por pantalla el numero de equipo que mas le dio ocupado al recibir llamadas
		 *  y la cantidad de veces que sucedio. Opcion G
		 */
		void equipoQueMasDioOcupadoAlLlamarlo(Antena* antena);  //PREGUNTAR   para opcion g)

		/*
		 * post: retorna la cantidad de llamadas que dieron ocupado al llamar, de la lista llamadas.
		 */
		unsigned int contarLlamadasRecibidasOcupado(Lista<Llamada*>* llamadas, std::string nombreAntena);

		/*
		 * post: compara valores enteros y cambia el valor actual y el equipo Actual en caso de que
		 *  el primero valor sea mayor al maximo actual.
		 */
		void compararValores(unsigned int nuevoValor, unsigned int &maximoActual, Equipo* equipoNuevo, Equipo* &equipoMaximo);

		/*
		 * Post: ordena la lista antena por llamadas anuladas de mayor a menor.
		 */
		void ordenarAntenaPorAnuladas();

		/*
		 * post:elimina recursos utilizados
		 */
		~MenuAntena();

};

#endif //MENUANTENA_H_INCLUDED
