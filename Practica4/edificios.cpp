/*
Pr�ctica 4
*/

#include "edificios.h"

//SUBFUNCIONES
tEdificio NuevoEdificio()
{
	const unsigned int CodigoMax = 10000;	
	unsigned int codigo;
	tNomEdif nombre;
	unsigned int precio;
	int dinero;
	int prestigio;
	const tEstadoEdif estado = disponible;
	tEdificio edificio;

	//Introducci�n de datos
	cout << endl
		 << "Introduzca c�digo del edificio: ";
	cin >> codigo;
	while (codigo >= CodigoMax) {
		setColor(light_red);
		cout << "El c�digo debe ser un entero positivo menor que " << CodigoMax << endl
			 << "Introduzca un c�digo v�lido: ";
		setColor(white);
		cin.sync();
		cin >> codigo;
	}
	cout << "Introduzca nombre del edificio (max. " << SizeNomEdif-1 << " car�cteres): ";
	cin.sync();
	cin.getline(nombre, SizeNomEdif);
	cout << "Introduzca precio del edificio: ";
	cin.sync();
	cin >> precio;
	cout << "Introduzca el dinero que genera: ";
	cin >> dinero;
	cout << "Introduzca el prestigio que genera: ";
	cin >> prestigio;

	//Generar edificio
	edificio.codigo = codigo;
	strcpy_s(edificio.nombre, nombre);
	edificio.precio = precio;
	edificio.dinero = dinero;
	edificio.prestigio = prestigio;
	edificio.estado = estado;

	return edificio;
}

void MostrarEdificio(const tEdificio& edificio, tColores color_base)
{
	cout << setw(4) << edificio.codigo << ' '
		 << left << setw(SizeNomEdif-1) << edificio.nombre << right << ' '
	 	 << setw(4) << edificio.precio << ' '
		 << setw(4) << edificio.dinero << ' '
		 << setw(4) << edificio.prestigio << ' ';
	switch(edificio.estado) {
	case disponible:	setColor(light_green);
						cout << "Disp";
						setColor(color_base);
						break;

	case comprado:		setColor(light_yellow);
						cout << "Comp";
						setColor(color_base);
						break;

	case borrado:		setColor(light_red);
						cout << "Borr";
						setColor(color_base);
						break;
	}
	cout << endl;
}