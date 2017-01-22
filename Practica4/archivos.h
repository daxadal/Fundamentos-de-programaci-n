/*
Pr�ctica 4
*/

#ifndef ARCHIVOS_H
#define ARCHIVOS_H

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

bool CargaEdificios(tListaEdificios& lista_edificios);
/*Recibe un par�metro del tipo tListaEdificios, en el que carga los datos de un
archivo. La funci�n imprime mensajes informativos sobre el funcionamiento del
proceso. Adem�s, devuelve un booleano que indica si el proceso fue correcto*/

bool CargaJugadores(tListaJugadores& listaJugadores);
/*Recibe un par�metro del tipo tListaJugadores, en el que carga los datos de un
archivo. La funci�n imprime mensajes informativos sobre el funcionamiento del
proceso. Adem�s, devuelve un booleano que indica si el proceso fue correcto*/

//Guardado

bool GuardaEdificios(const tListaEdificios& lista_edificios);
/*Recibe un par�metro del tipo tListaEdificios, cuyos datos guarda en un
archivo. La funci�n imprime mensajes informativos sobre el funcionamiento del
proceso. Adem�s, devuelve un booleano que indica si el proceso fue correcto*/

bool GuardaJugadores(const tListaJugadores& listaJugadores);

#endif