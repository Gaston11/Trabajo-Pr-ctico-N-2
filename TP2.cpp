/*
 * TP2.cpp
 *
 *  Created on: 9 de may. de 2016
 *      Author: noe
 */

#include <iostream>

using namespace std;

void opcionesDeMenu(){

	std::cout << " TELEFONIA CELULAR V2.0: " << std::endl;

	std::cout << "Opciones de menu :" << std::endl;

	std::cout << "1- Sistema (informacion sobre todos los celulares)" << std::endl;
	std::cout << "2- Antena (informacion de cada antena)" << std::endl;
	std::cout << "3- Salir. " <<std::endl;

}

void opcionesDeMenuSistema(){

	std::cout << "Opciones de menu sobre equipos: " << std::endl;

	std::cout << "a- Detalle de llamadas entre celular X al celular Y." << std::endl;
	std::cout << "b- Celular que mas hablo." << std::endl;
	std::cout << "c- Celular que mas llamo." << std::endl;
	std::cout << "d- Celular que mas le dio ocupado." << std::endl;
	std::cout << "e- Celular al que mas llamaron." << std::endl;
	std::cout << "f- Celular al que mas le hablaron." << std::endl;
	std::cout << "g- Celular que mas dio ocupado." << std::endl;
	std::cout << "h- Detalle de llamadas emitidas por celular X." << std::endl;
	std::cout << "i- Detalle de llamadas recibidas por el celular Y." << std::endl;
	std::cout << "j- Detalle de llamdas recibidas por el celular X y ";
	std::cout << "realizadas por el celular Y. " << std::endl;
	std::cout << "k- Detalle de Celulares. " << std::endl;
	std::cout << "l- Salir." << std::endl;

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

	char opcion;

	// mostrar menu
	cin >> opcion;

	while (opcion != 'e'){

		switch (opcion){

		case 'a':
			break;
		case 'b':
			break;
		case 'c':
			break;
		case 'e':
			break;
		default:
			break;

		}
	}


	return 0;
}



