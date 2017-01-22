/*
Práctica 4
*/

#ifndef LISTAJUGADORES_H
#define LISTAJUGADORES_H

#include "jugadores.h"

const int MaxJug = 20;
typedef tJugador tArrJug[MaxJug];

typedef struct{
	tArrJug jugador;
	unsigned int cont;
}tListaJugadores;

//Declaracion de subfunciones

bool ListaJugadoresLlena(tListaJugadores lista_jugadores);
/*Función que recibe como parámetro una lista de
jugadores y devuelve un booleano indicando si la lista está llena o no*/

bool BuscarJugador(const tListaJugadores& lista_jugadores, const tNomJug nombre, int& pos);
/*Recibe como entrada una lista de jugadores y un nombre
de usuario. Devuelve un booleano indicando si se ha encontrado el jugador o
no y, en caso afirmativo, la posición en la que se encuentra el jugador*/

bool InsertarJugador(tListaJugadores& lista_jugadores, const tJugador& jugador);
/*Recibe una variable de tipo tJugador y una lista de
jugadores. Inserta el jugador al final de la lista de jugadores y un booleano indicando si fue insertado con éxito. 
Se presupone que la lista no esta llena*/

bool BajaJugador(tNomJug nombre_jug, tListaJugadores& lista_jugadores, tListaEdificios& lista_edificios);
/*Recibe un nombre de usuario, la lista de jugadores y la lista
de edificios. Busca al jugador en la lista y lo elimina completamente*/

void OrdenarJug_PorDinero(tListaJugadores& lista_jugadores);

void OrdenarJug_PorPrestigio(tListaJugadores& lista_jugadores);

#endif