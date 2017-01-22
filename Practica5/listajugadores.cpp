/*
Práctica 5
*/

#include "listajugadores.h"

bool ListaJugadoresLlena(const tListaJugadores& lista_jugadores)
{
	return lista_jugadores.capacidad == lista_jugadores.cont;
}

void Redimensionar(tListaJugadores &lista_jugadores)
{
	int nueva_capac = (lista_jugadores.capacidad *3)/2 +1; //Calcular nueva capacidad
	lista_jugadores.capacidad = nueva_capac; //Actualizar capacidad

	tJugador *array_jug_aux = new tJugador[nueva_capac]; //Crear array con la nueva capacidad

	for (unsigned int i=0; i < lista_jugadores.cont; i++) //Copia todos los datos al nuevo array
		array_jug_aux[i] = lista_jugadores.jugador[i];

	delete [] lista_jugadores.jugador; //Borra el antiguo array
	lista_jugadores.jugador = array_jug_aux; //Liga el nuevo array a la lista
	
}

bool BuscarJugador(const tListaJugadores &lista_jugadores, const tNomJug nombre, int& pos)
{
	bool encontrado = false;
	unsigned int i=0;
	while (i<lista_jugadores.cont && !encontrado)
		if (strcmp( lista_jugadores.jugador[i].nombre, nombre) == 0) {
			encontrado = true;
			pos = i;	}
		else
			i++;
	return encontrado;
}

bool InsertarJugador(tListaJugadores &lista_jugadores, const tJugador& jugador)
{
	bool encontrado, proceso_ok;
	int pos;
	
	encontrado = BuscarJugador(lista_jugadores, jugador.nombre, pos);
	if (!encontrado) {
		lista_jugadores.jugador[ lista_jugadores.cont ] = jugador;
		lista_jugadores.cont++;
		proceso_ok = true;
	}
	else
		proceso_ok = false;
	
	return proceso_ok;
}

bool BajaJugador(tNomJug nombre_jug, tListaJugadores &lista_jugadores, tListaEdificios& lista_edificios)
{
	bool proceso_ok;
	int pos, pos_edif;

	proceso_ok = BuscarJugador(lista_jugadores, nombre_jug, pos);
	if (proceso_ok) {
		for (unsigned int i=0; i < lista_jugadores.jugador[pos].comprados.cont; i++) //Vender edificios
		{
			BuscarEdificio(lista_edificios, lista_jugadores.jugador[pos].comprados.cod_edif[i], pos_edif);
			lista_edificios.edificio[pos_edif]->estado = disponible;
		}
		lista_jugadores.jugador[pos] = lista_jugadores.jugador[ lista_jugadores.cont -1 ]; //Copiar ultimo jugador sobre el que queremos borrar
		lista_jugadores.cont--;
	}
	return proceso_ok;
}

void OrdenarJug_PorDinero_interno(tListaJugadores &lista_jugadores, unsigned int i)
{
	unsigned int j=i;
	tJugador tmp_jugador;
	while (j>0 && lista_jugadores.jugador[j-1].dinero < lista_jugadores.jugador[j].dinero)
	{
		tmp_jugador = lista_jugadores.jugador[j-1];
		lista_jugadores.jugador[j-1] = lista_jugadores.jugador[j];
		lista_jugadores.jugador[j] = tmp_jugador;
		j--;
	}
}

void OrdenarJug_PorDinero(tListaJugadores &lista_jugadores)
{
	for (unsigned int i=1; i < lista_jugadores.cont; i++)
		OrdenarJug_PorDinero_interno(lista_jugadores, i);
}

void OrdenarJug_PorPrestigio_interno(tListaJugadores &lista_jugadores, unsigned int i)
{
	unsigned int j=i;
	tJugador tmp_jugador;
	while (j>0 && lista_jugadores.jugador[j-1].prestigio < lista_jugadores.jugador[j].prestigio)
	{
		tmp_jugador = lista_jugadores.jugador[j-1];
		lista_jugadores.jugador[j-1] = lista_jugadores.jugador[j];
		lista_jugadores.jugador[j] = tmp_jugador;
		j--;
	}
}

void OrdenarJug_PorPrestigio(tListaJugadores &lista_jugadores)
{
	for (unsigned int i=1; i < lista_jugadores.cont; i++)
		OrdenarJug_PorPrestigio_interno(lista_jugadores, i);
}

