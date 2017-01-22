/*
Práctica 5
*/

#include "listaedificios.h"

//Inicializacion y destruccion
void Inicializar(tListaEdificios &lista_edificios)
{
	for (int i=0; i < MaxEdif; i++)
		lista_edificios.edificio[i] = NULL;
}

void Destruir(tListaEdificios &lista_edificios)
{
	for (int i=0; i < MaxEdif; i++)
		delete lista_edificios.edificio[i];
}


//Gestion
bool ListaEdificiosLlena(const tListaEdificios& lista_edificios)
{
	return MaxEdif == lista_edificios.cont;
}

bool BuscarEdificio_Rec(int ini, int fin, const tListaEdificios& lista_edificios, unsigned int cod_buscado, int& pos)
{
	int mitad = (ini+fin)/2;
	bool encontrado;

	if (ini>fin) {
		encontrado = false;
		pos = ini; }
	else if (lista_edificios.edificio[mitad]->codigo == cod_buscado) {
		encontrado = true;
		pos = mitad; }
	else if (lista_edificios.edificio[mitad]->codigo < cod_buscado) 
		encontrado = BuscarEdificio_Rec(mitad+1, fin, lista_edificios, cod_buscado, pos);
	else /*lista_edificios.edificio[mitad]->codigo > cod_buscado*/ 
		encontrado = BuscarEdificio_Rec(ini, mitad-1, lista_edificios, cod_buscado, pos);

	return encontrado;
}

bool BuscarEdificio(const tListaEdificios& lista_edificios, unsigned int cod_buscado, int& pos)
{
	int ini = 0,
		fin = lista_edificios.cont - 1;
	bool encontrado;
	encontrado = BuscarEdificio_Rec(ini, fin, lista_edificios, cod_buscado, pos);

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
		lista_edificios.edificio[pos] = new tEdificio;
		*lista_edificios.edificio[pos] = edificio;
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
	if (encontrado && lista_edificios.edificio[pos]->estado == disponible) {
		lista_edificios.edificio[pos]->estado = borrado;
		proceso_ok = true;
	}
	else
		proceso_ok = false;

	return proceso_ok;
}
