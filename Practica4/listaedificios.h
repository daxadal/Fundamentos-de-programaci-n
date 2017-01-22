/*
Práctica 4
*/

#ifndef LISTAEDIFICIOS_H
#define LISTAEDIFICIOS_H

#include "edificios.h"

const unsigned int MaxEdif = 50;
typedef tEdificio tArrayEdif[MaxEdif];

typedef struct{
	tArrayEdif edificio;
	unsigned int cont;
} tListaEdificios;

//Declaracion de subfunciones

bool ListaEdificiosLlena(const tListaEdificios& lista_edificios);
/*Función que recibe como parámetro una lista de
edificios y devuelve un booleano indicando si esa 
lista está llena o no*/

bool BuscarEdificio(const tListaEdificios& lista_edificios, unsigned int codigo, int& pos); 
/*Recibe una lista de edificios y un código. Indica si se ha
encontrado o no un edificio con ese código y, en caso afirmativo, la posición en
la que se encuentra. Debe estar implementado como una búsqueda binaria*/

bool InsertarEdificio(tListaEdificios& lista_edificios, const tEdificio& edificio);
/*Recibe un tEdificio y una lista de edificios. Inserta
el edificio en la lista en la posición que le corresponda por código y devuelve la
lista actualizada y un booleano indicando si fue insertado con éxito. 
Se presupone que la lista no esta llena*/

bool BajaEdificio(tListaEdificios& lista_edificios, unsigned int codigo);
/*Recibe la lista edificios y un código de edificio. Si el edificio
existe y está disponible (no ha sido comprado), lo marca como borrado en la lista*/


#endif