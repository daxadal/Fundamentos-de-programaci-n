/*
Práctica 5
*/

#include "veredificios.h"

//Visualizacion - Ver edificios (general)
void VerEdif_Cabecera()
{
	cout << setw(4) << "Cod." << ' '
		 << left << setw(SizeNomEdif-1) << "   Edificio   " << right << ' '
		 << setw(4) << "Prec" << ' '
		 << setw(4) << "Ingr" << ' '
		 << setw(4) << "Pres" << ' '
		 << setw(4) << "Est." 
		 << endl;
}

void VerEdif_Linea()
{
	cout << "_____________________________";
	for (int i=0; i<SizeNomEdif-1; i++) cout << '_';
	cout << endl;
}

void VerEdif_General(const tListaEdificios& lista_edificios, bool solo_disp)
{
	unsigned int cont = 0;

	if (lista_edificios.cont == 0)	{
		setColor(light_red);
		cout << "No se ha creado ningun edificio" << endl;
		setColor(white);			}
	else {
		cout << endl;
		VerEdif_Cabecera();
		VerEdif_Linea();
		for (unsigned int i=0; i<lista_edificios.cont; i++)
			if (!solo_disp || lista_edificios.edificio[i]->estado == disponible) {
				MostrarEdificio( *lista_edificios.edificio[i], white );
				cont++;	}
		VerEdif_Linea();
		cout << "Mostrando: "<< setw(3) << cont <<"/"<< setw(3) << lista_edificios.cont << endl
			 << endl;
	}
}


