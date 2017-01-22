/*
Eric Garc�a de Ceca Elejoste
Pr�ctica 5
*/

#ifndef ARCHIVOS_TXT_H
#define ARCHIVOS_TXT_H

#include <fstream>
using namespace std;

#include "listajugadores.h"

const char ArchEdif[] = "edificios.txt";
const char ArchJug[] = "jugadores.txt";
const int Cent_ArchEdif = -1;
const int Cent_LisCodEdif = -1;
const char Cent_ArchJug[] = "X";

//Declaracion de subfunciones

//Inicializaci�n y carga

bool CargaEdificiosTxt(tListaEdificios& lista_edificios);
/*Recibe un par�metro del tipo tListaEdificios, en el que carga los datos de un
archivo de texto. La funci�n imprime mensajes informativos sobre el funcionamiento del
proceso. Adem�s, devuelve un booleano que indica si el proceso fue correcto*/

bool CargaJugadoresTxt(tListaJugadores& listaJugadores);
/*Recibe un par�metro del tipo tListaJugadores, en el que carga los datos de un
archivo de texto. La funci�n imprime mensajes informativos sobre el funcionamiento del
proceso. Adem�s, devuelve un booleano que indica si el proceso fue correcto*/

//Guardado

bool GuardaEdificiosTxt(const tListaEdificios& lista_edificios);
/*Recibe un par�metro del tipo tListaEdificios, cuyos datos guarda en un
archivo de texto. La funci�n imprime mensajes informativos sobre el funcionamiento del
proceso. Adem�s, devuelve un booleano que indica si el proceso fue correcto*/

bool GuardaJugadoresTxt(const tListaJugadores& listaJugadores);
/*Recibe un par�metro del tipo tListaJugadores, cuyos datos guarda en un
archivo de texto. La funci�n imprime mensajes informativos sobre el funcionamiento del
proceso. Adem�s, devuelve un booleano que indica si el proceso fue correcto*/

#endif