/*
Práctica 5
*/

#ifndef VEREDIFICIOS_H
#define VEREDIFICIOS_H

#include "listaedificios.h"

//Visualizacion - Ver edificios (general)

void VerEdif_Cabecera();
void VerEdif_Linea();
/*Cabecera y linea de la tabla de edificios*/

void VerEdif_General(const tListaEdificios& lista_edificios, bool solo_disp);
/*A partir de una lista de edificios, y usando la cabecera y linea anteriores,
muestra una tabla con todos los datos de todos los edificios (solo_disp == false),
o de los edificios que estén disponibles (solo_disp == true)*/



#endif