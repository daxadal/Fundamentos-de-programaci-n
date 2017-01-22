/*
Práctica 5
*/

#include "jugadores.h"

bool TieneEspacios(tNomJug cadena)
{
	bool devolver = false;
	int i=0;

	while (cadena[i] != '\0' && !devolver)
		if (cadena[i] == ' ')
			devolver = true;
		else
			i++;

	return devolver;
}

tJugador NuevoJugador()
{
	tNomJug nombre;
	tCont contrasena;
	tNomEmpr empresa;
	const int dinero = 3000;
	const int prestigio = 0;
	const unsigned int cont_comprados = 0;
	tJugador jugador;

	//Introduccion de datos
	cout << endl
		 << "Introduzca nombre de usuario (max. " << SizeNomJug-1 << " carácteres): ";
	cin.sync();
	cin.getline(nombre, SizeNomJug);
	while (strcmp(nombre, NombreAdmin) == 0 || strcmp(nombre, NombreSalir) == 0 || TieneEspacios(nombre) )
	{
		setColor(light_red);
		cout << "El nombre no puede contener espacios" << endl
			 << "Los nombres '" << NombreAdmin << "' y '" << NombreSalir << "' no estan permitidos" << endl
			 << "Introduzca otro nombre: ";
		setColor(white);
		cin.sync();
		cin.getline(nombre, SizeNomJug);
	}

	cout << "Introduzca contraseña (max. " << SizeContr-1 << " carácteres): ";
	cin.sync();
	cin.getline(contrasena, SizeContr);
	while ( TieneEspacios(contrasena) )
	{
		setColor(light_red);
		cout << "la contraseña no puede contener espacios" << endl
			 << "Introduzca otra contraseña: ";
		setColor(white);
		cin.sync();
		cin.getline(contrasena, SizeContr);
	}

	cout << "Introduzca nombre de empresa (max. " << SizeNomEmpr-1 << " carácteres): ";
	cin.sync();
	cin.getline(empresa, SizeNomEmpr);
	cin.sync();

	//Generar jugador
	strcpy_s(jugador.nombre, nombre);
	strcpy_s(jugador.contrasena, contrasena);
	strcpy_s(jugador.empresa, empresa);
	jugador.dinero = dinero;
	jugador.prestigio = prestigio;
	jugador.comprados.cont = cont_comprados;
	
	return jugador;
}

void MostrarJugador(const tJugador& jugador, const tListaEdificios& lista_edificios)
{
	//Cabecera
	cout << left 
		 << setw(SizeNomJug-1) << " Nombre " << ' '
		 << setw(SizeContr-1) << "Contraseña" << ' '
		 << setw(SizeNomEmpr-1) << "  Empresa  " << ' '
		 << right
		 << setw(6) << "Credit" << ' '
		 << setw(5) << "Pres."
		 << endl;

	//Línea
	for (int i=0; i< (SizeNomJug + SizeContr + SizeNomEmpr + 6+1 + 5); i++) cout << '_';
	cout << endl;
	
	//Datos
	cout << left 
		 << setw(SizeNomJug-1) << jugador.nombre << ' '
		 << setw(SizeContr-1) << jugador.contrasena << ' '
		 << setw(SizeNomEmpr-1) << jugador.empresa << ' '
		 << right
		 << setw(6) << jugador.dinero << ' '
		 << setw(5) << jugador.prestigio
		 << endl;
	
	//Edificios
	setColor(light_gray);
	cout << endl << "Edificios comprados:" << jugador.comprados.cont << endl;
	if (jugador.comprados.cont != 0 ) VerEdif_Jugador(lista_edificios, jugador, light_gray);
	setColor(white);
}

void VerEdif_Jugador(const tListaEdificios& lista_edificios, const tJugador& jugador, tColores color_base)
{
	int pos_edif;
	cout << endl;
	setColor(color_base);
	VerEdif_Cabecera();
	VerEdif_Linea();

	
	for (unsigned int i=0; i < jugador.comprados.cont; i++)
	{
		BuscarEdificio(lista_edificios, jugador.comprados.cod_edif[i], pos_edif);
		MostrarEdificio(*lista_edificios.edificio[pos_edif], color_base);
	}
	VerEdif_Linea();
	cout << "Mostrando: "<< setw(3) << jugador.comprados.cont << endl
		 << endl;
	setColor(white);
}

bool ListaCompradosLlena(tJugador jugador)
{
	return MaxEdifComp == jugador.comprados.cont;
}

bool BuscarCodEdif(const tLisCodEdif& lista_cod_edif, unsigned int cod_buscado, int& pos)
{
	int ini = 0,
		fin = lista_cod_edif.cont - 1,
		mitad;
	bool encontrado = false;

	while ( ini<=fin && !encontrado )
	{
		mitad = (ini+fin)/2;
		if (lista_cod_edif.cod_edif[mitad] == cod_buscado) 
			encontrado = true;
		else if (lista_cod_edif.cod_edif[mitad] < cod_buscado) 
			ini = mitad + 1;
		else /*lista_cod_edif.cod_edif[mitad] > cod_buscado*/ 
			fin = mitad - 1;
	}
	if (encontrado)
		pos = mitad;
	else
		pos = ini;

	return encontrado;
}

bool InsertarCodEdif(tLisCodEdif& lista_cod_edif, unsigned int cod_edif)
{
	bool encontrado, proceso_ok;
	int pos;
	
	encontrado = BuscarCodEdif(lista_cod_edif, cod_edif, pos);
	if (!encontrado) {
		for( int i = lista_cod_edif.cont; i > pos; i--)
			lista_cod_edif.cod_edif[i] = lista_cod_edif.cod_edif[i-1];
		lista_cod_edif.cod_edif[pos] = cod_edif;
		lista_cod_edif.cont++;
		proceso_ok = true;
	}
	else
		proceso_ok = false;
	
	return proceso_ok;
}

int ComprarEdificio(tJugador& jugador, unsigned int cod_edif, tListaEdificios& lista_edificios)
{
	int proceso_ok;
	/*comprado = 0, no encontrado = 1, no disponible = 2, sin dinero = 3*/
	bool encontrado;
	int pos;

	encontrado = BuscarEdificio(lista_edificios, cod_edif, pos);
	if ( !encontrado ) proceso_ok = 1;		//No encontrado
	else if( lista_edificios.edificio[pos]->estado != disponible ) proceso_ok = 2;	//No disponible
	else if ( jugador.dinero < (int) lista_edificios.edificio[pos]->precio ) proceso_ok = 3;	//Sin dinero
	else {
		jugador.dinero -= lista_edificios.edificio[pos]->precio;
		lista_edificios.edificio[pos]->estado = comprado;
		InsertarCodEdif(jugador.comprados, cod_edif); //Insertar en lista de edificios comprados
		proceso_ok = 0;	//Edificio comprado
	}

	return proceso_ok;		
}
