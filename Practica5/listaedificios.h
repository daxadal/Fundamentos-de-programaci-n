/*
Pr�ctica 5
*/

#ifndef LISTAEDIFICIOS_H
#define LISTAEDIFICIOS_H

#include "edificios.h"

const unsigned int MaxEdif = 50;
typedef tEdificio *tArrayEdif[MaxEdif]; //Array de punteros (a tEdificios)

typedef struct{
	tArrayEdif edificio;
	unsigned int cont;
} tListaEdificios;

//Declaracion de subfunciones

//Inicializacion y destruccion

void Inicializar(tListaEdificios &lista_edificios);
/*Inicializa todos los punteros del array de datos din�mico a NULL*/

void Destruir(tListaEdificios &lista_edificios);
/*Destruye los datos din�micos de todos los punteros del array*/

//Gestion

bool ListaEdificiosLlena(const tListaEdificios& lista_edificios);
/*Funci�n que recibe como par�metro una lista de
edificios y devuelve un booleano indicando si esa 
lista est� llena o no*/

bool BuscarEdificio(const tListaEdificios& lista_edificios, unsigned int codigo, int& pos); 
/*Recibe una lista de edificios y un c�digo. Indica si se ha
encontrado o no un edificio con ese c�digo y, en caso afirmativo, la posici�n en
la que se encuentra. Debe estar implementado como una b�squeda binaria*/

bool InsertarEdificio(tListaEdificios& lista_edificios, const tEdificio& edificio);
/*Recibe un tEdificio y una lista de edificios. Inserta
el edificio en la lista en la posici�n que le corresponda por c�digo y devuelve la
lista actualizada y un booleano indicando si fue insertado con �xito. 
Se presupone que la lista no esta llena*/

bool BajaEdificio(tListaEdificios& lista_edificios, unsigned int codigo);
/*Recibe la lista edificios y un c�digo de edificio. Si el edificio
existe y est� disponible (no ha sido comprado), lo marca como borrado en la lista*/


#endif