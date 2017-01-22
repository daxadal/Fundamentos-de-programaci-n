/*

Práctica 4
*/

#include "listaedificios.h"

bool ListaEdificiosLlena(const tListaEdificios& lista_edificios)
{
	return MaxEdif == lista_edificios.cont;
}

bool BuscarEdificio(const tListaEdificios& lista_edificios, unsigned int cod_buscado, int& pos)
{
	int ini = 0,
		fin = lista_edificios.cont - 1,
		mitad;
	bool encontrado = false;

	while ( ini<=fin && !encontrado )
	{
		mitad = (ini+fin)/2;
		if (lista_edificios.edificio[mitad].codigo == cod_buscado) 
			encontrado = true;
		else if (lista_edificios.edificio[mitad].codigo < cod_buscado) 
			ini = mitad + 1;
		else /*lista_edificios.edificio[mitad].codigo > cod_buscado*/ 
			fin = mitad - 1;
	}
	if (encontrado)
		pos = mitad;
	else
		pos = ini;

	return encontrado;
}

bool InsertarEdificio(tListaEdificios& lista_edificios, const tEdificio& edificio)
{
	bool encontrado, proceso_ok;
	int pos;
	
	encontrado = BuscarEdificio(lista_edificios, edificio.codigo, pos);
	if (!encontrado) {
		for( int i = lista_edificios.cont; i > pos; i--)
			lista_edificios.edificio[i] = lista_edificios.edificio[i-1];
		lista_edificios.edificio[pos] = edificio;
		lista_edificios.cont++;
		proceso_ok = true;
	}
	else
		proceso_ok = false;
	
	return proceso_ok;
}

bool BajaEdificio(tListaEdificios& lista_edificios, unsigned int codigo)
{
	bool encontrado, proceso_ok;
	int pos;

	encontrado = BuscarEdificio(lista_edificios, codigo, pos);
	if (encontrado && lista_edificios.edificio[pos].estado == disponible) {
		lista_edificios.edificio[pos].estado = borrado;
		proceso_ok = true;
	}
	else
		proceso_ok = false;

	return proceso_ok;
}
