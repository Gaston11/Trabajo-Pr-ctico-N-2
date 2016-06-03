/*
 * TP2.cpp
 *
 *  Created on: 9 de may. de 2016
 *      Author: noe
 */

#include <iostream>
#include <fstream>

#include "ParsearLinea.h"
#include "MenuAntena.h"

using namespace std;

void opcionesDeMenu(){

	std::cout << " TELEFONIA CELULAR V2.0: " << std::endl;

	std::cout << "Opciones de menu :" << std::endl;

	std::cout << "1- Sistema (informacion sobre todos los celulares)" << std::endl;
	std::cout << "2- Antena (informacion de cada antena)" << std::endl;
	std::cout << "3- Salir. " <<std::endl;

}

void opcionesDeMenuAntenas(){

	std::cout << "Opciones de menu sobre antenas: " << std::cout;

	std::cout << "a- Celular que mas hablo de cada antena." << std::cout;
	std::cout << "b- Celular que mas llamo de cada antena." << std::cout;
	std::cout << "c- Celular que mas le dio ocupado de cada antena." << std::cout;
	std::cout << "d- Celular al que mas llamaron de cada antena." << std::cout;
	std::cout << "e- Celular al que mas le hablaron de cada antena." << std::cout;
	std::cout << "f- Celular que mas dio ocupado de cada antena." << std::cout;
	std::cout << "g- Cantidad maxima utilizada de Celulares por antena." << std::cout;
	std::cout << "h- Cantidad de llamadas anuladas por falta de Capacidad";
	std::cout << " por Antena (ordenado por cantidad descendiente)"<< std::cout;
	std::cout << "i- Detalles de Antenas." << std::cout;

	std::cout << "j- Salir." << std::cout;

}

int main(){

	string nombreArchivo;

	cout << "Ingrese el nombre del archivo: ";
	cin >> nombreArchivo;

	//procesar archivo
	ParsearLineas archivo(nombreArchivo);

	Lista<Equipo*>* equipos = archivo.obtenerEquipos;
	Lista<Antena*>* antenas = archivo.obtenerAntenas();
	MenuAntena menuAntena(antenas,equipos); // AGREGADOO

	char opcion;

	// mostrar menu
	opcionesDeMenu();
	cin >> opcion;

	while (opcion != '3'){

		switch (opcion){

		case '1':
			//MENU DE LOS EQUIPOS
			break;
		case '2':
			//MENU DE LAS ANTENAS
			opcionesDeMenuAntenas();
			cin >> opcion;
			menuAntena.MenuPrincipal(opcion);   ///AGREGADO

			break;
		case '3':
			break;
		default:
			cout<<"Opcion invalida. Ingreselo nuevamente: ";
			cin >>opcion;
			break;

		}
	}


	return 0;
}
