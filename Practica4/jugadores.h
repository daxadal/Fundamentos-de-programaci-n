/*
Práctica 4
*/

#ifndef JUGADORES_H
#define JUGADORES_H

#include "veredificios.h"

const char NombreAdmin[] = "admin";
const char ContAdmin[] = "12345";
const char NombreSalir[] = "salir";

const unsigned int SizeNomJug = 11;
typedef char tNomJug[SizeNomJug];

const unsigned int SizeContr = 11;
typedef char tCont[SizeContr];

const unsigned int SizeNomEmpr = 21;
typedef char tNomEmpr[SizeNomEmpr];

const unsigned int MaxEdifComp = 20;
typedef unsigned int tArrCodEdif[MaxEdifComp];
typedef struct{
	tArrCodEdif cod_edif;
	unsigned int cont;
} tLisCodEdif;

typedef struct{
	tNomJug nombre;
	tCont contrasena;
	tNomEmpr empresa;
	int dinero;
	int prestigio;
	tLisCodEdif comprados;
}tJugador;


//Declaracion de subfunciones

tJugador NuevoJugador();
/*Lee los datos de un jugador, inicializa su lista de edificios
comprados como vacía, el dinero a 3.000 créditos y los puntos de prestigio a 0.
Devuelve la estructura tJugador debidamente inicializada*/

void VerEdif_Jugador(const tListaEdificios& lista_edificios, const tJugador& jugador, tColores color_base);
/*A partir de una lista de edificios y un jugador , y usando la cabecera y linea anteriores,
muestra una tabla con todos los datos de todos los edificios 
que el jugador ha comprado. La variable color_base escoge el color
en el que se mostrará la tabla*/

void MostrarJugador (const tJugador& jugador, const tListaEdificios& lista_edificios);
/*Dado un tJugador y la lista de edificios, muestra en la
consola los datos del jugador y los datos básicos de todos sus edificios
(nombre, dinero y prestigio por turno).*/

bool ListaCompradosLlena(tJugador jugador); 
/*Recibe como entrada un tJugador y devuelve un
booleano indicando si su lista de edificios comprados está llena*/

int ComprarEdificio(tJugador& jugador, unsigned int cod_edif, tListaEdificios& lista_edificios);
/*Recibe como entrada un tJugador, un código de
edificio y la lista completa de edificios. Si se puede hacer la compra (el edificio
existe, está disponible y hay dinero suficiente) realiza la compra y añade el
código de edificio a la lista de edificios del jugador*/

#endif