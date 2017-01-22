/*
Práctica 5
*/

#ifndef EDIFICIOS_H
#define EDIFICIOS_H

#include <iostream>
#include <iomanip>
#include <locale>
using namespace std;
#include "color.h"


const unsigned int SizeNomEdif = 21;
typedef char tNomEdif[SizeNomEdif];

typedef enum{disponible, comprado, borrado} tEstadoEdif; 

typedef struct {
	unsigned int codigo;
	tNomEdif nombre;
	unsigned int precio;
	int dinero;
	int prestigio;
	tEstadoEdif estado;
} tEdificio;

//Declaracion de subfunciones
tEdificio NuevoEdificio();
/*No recibe ningún valor de entrada. Pide al usuario los
datos de un edificio y devuelve como salida una estructura tEdificio
debidamente inicializada*/

void MostrarEdificio(const tEdificio& edificio, tColores color_base);
/*Dado un tEdificio muestra todos sus datos en la
consola, debidamente formateados.
Los datos se muestran como una fila de una tabla*/

#endif