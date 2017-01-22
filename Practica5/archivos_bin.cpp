/*
Eric García de Ceca Elejoste
Práctica 5
*/

#include "archivos_bin.h"

//SUBFUNCIONES
//Inicialización y carga

bool CargaEdificiosBin(tListaEdificios& lista_edificios)
{
	const int SIZE = sizeof(tEdificio);
	int n_bytes;
	bool carga_ok = true;
	fstream lectura;

	cout << "Cargando edificios...";
	lectura.open(ArchEdifBin, ios::in | ios::binary);
	if (!lectura.is_open()) {
		setColor(light_red);
		cout << "Error al abrir el archivo" << endl;
		setColor(white);
		carga_ok = false;	}
	else
	{
		lectura.seekg( 0, ios::end);
		n_bytes = lectura.tellg();
		lista_edificios.cont = n_bytes / SIZE; //Calcular nº de datos

		lectura.seekg( 0, ios::beg);
		for (unsigned int i=0; i < lista_edificios.cont; i++) {//Cargar datos
			lista_edificios.edificio[i] = new tEdificio; //Crear dato
			lectura.read( (char*) lista_edificios.edificio[i], SIZE);
		}
	}

	if(carga_ok) {
		lectura.close();
		setColor(light_green);
		cout << "Edificios cargados" << endl;
		setColor(white);
	}
	return carga_ok;
}

bool CargaJugadoresBin(tListaJugadores& lista_jugadores)
{
	const int SIZE = sizeof(tJugador);
	int n_bytes;
	bool carga_ok = true;
	fstream lectura;

	cout << "Cargando jugadores...";
	lectura.open(ArchJugBin, ios::in | ios::binary);
	if (!lectura.is_open()) {
		setColor(light_red);
		cout << "Error al abrir el archivo" << endl;
		setColor(white);
		carga_ok = false;	}
	else
	{
		lectura.seekg( 0, ios::end);
		n_bytes = lectura.tellg();
		lista_jugadores.cont = n_bytes / SIZE; //Calcular nº de datos

		lista_jugadores.capacidad = (lista_jugadores.cont /10 + 1) *10; //Calcular capacidad (cont redondeado hacia arriba)
		lista_jugadores.jugador = new tJugador[ lista_jugadores.capacidad ]; //Crear array de jugadores

		lectura.seekg( 0, ios::beg);
		for (unsigned int i=0; i < lista_jugadores.cont; i++) //Cargar datos
			lectura.read( (char*) &lista_jugadores.jugador[i], SIZE);
	}

	if(carga_ok) {
		lectura.close();
		setColor(light_green);
		cout << "Jugadores cargados" << endl;
		setColor(white);
	}
	return carga_ok;
}

//Guardado

bool GuardaEdificiosBin(const tListaEdificios& lista_edificios)
{
	const int SIZE = sizeof(tEdificio);
	bool carga_ok = true;
	fstream escritura;

	cout << "Guardando edificios...";
	escritura.open(ArchEdifBin, ios::out | ios::binary);
	if (!escritura.is_open()) {
		setColor(light_red);
		cout << "Error al abrir el archivo" << endl;
		setColor(white);
		carga_ok = false;	}

	else for (unsigned int i=0; i < lista_edificios.cont; i++)
			escritura.write( (char *) lista_edificios.edificio[i], SIZE);

	if(carga_ok) {
		escritura.close();
		setColor(light_green);
		cout << "Edificios guardados" << endl;
		setColor(white);
	}
	return carga_ok;
}

bool GuardaJugadoresBin(const tListaJugadores& lista_jugadores)
{
	const int SIZE = sizeof(tJugador);
	bool carga_ok = true;
	fstream escritura;

	cout << "Guardando jugadores...";
	escritura.open(ArchJugBin, ios::out | ios::binary);
	if (!escritura.is_open()) {
		setColor(light_red);
		cout << "Error al abrir el archivo" << endl;
		setColor(white);
		carga_ok = false;	}

	else for (unsigned int i=0; i < lista_jugadores.cont; i++)
			escritura.write( (char *) &lista_jugadores.jugador[i], SIZE);

	if(carga_ok) {
		escritura.close();
		setColor(light_green);
		cout << "Edificios guardados" << endl;
		setColor(white);
	}
	return carga_ok;
}