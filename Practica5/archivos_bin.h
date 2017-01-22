/*
Eric García de Ceca Elejoste
Práctica 5
*/

#ifndef ARCHIVOS_BIN_H
#define ARCHIVOS_BIN_H

#include <fstream>
using namespace std;

#include "listajugadores.h"

const char ArchEdifBin[] = "edificios.dat";
const char ArchJugBin[] = "jugadores.dat";

//Declaracion de subfunciones

//Inicialización y carga

bool CargaEdificiosBin(tListaEdificios& lista_edificios);
/*Recibe un parámetro del tipo tListaEdificios, en el que carga los datos de un
archivo binario. La función imprime mensajes informativos sobre el funcionamiento del
proceso. Además, devuelve un booleano que indica si el proceso fue correcto*/

bool CargaJugadoresBin(tListaJugadores& lista_jugadores);
/*Recibe un parámetro del tipo tListaJugadores, en el que carga los datos de un
archivo binario. La función imprime mensajes informativos sobre el funcionamiento del
proceso. Además, devuelve un booleano que indica si el proceso fue correcto*/

//Guardado

bool GuardaEdificiosBin(const tListaEdificios& lista_edificios);
/*Recibe un parámetro del tipo tListaEdificios, cuyos datos guarda en un
archivo binario. La función imprime mensajes informativos sobre el funcionamiento del
proceso. Además, devuelve un booleano que indica si el proceso fue correcto*/

bool GuardaJugadoresBin(const tListaJugadores& lista_jugadores);
/*Recibe un parámetro del tipo tListaJugadores, cuyos datos guarda en un
archivo binario. La función imprime mensajes informativos sobre el funcionamiento del
proceso. Además, devuelve un booleano que indica si el proceso fue correcto*/

#endif