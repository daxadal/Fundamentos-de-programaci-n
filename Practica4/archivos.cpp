/*
Práctica 4
*/

#include "archivos.h"

//SUBFUNCIONES
//Inicialización y carga
bool CargaEdificios(tListaEdificios& lista_edificios)
{
	bool carga_ok = true;
	ifstream lectura;
	char basura;

	unsigned int codigo;
	tNomEdif nombre;
	unsigned int precio;
	int dinero;
	int prestigio;
	unsigned int estado;

	cout << "Cargando edificios...";
	lectura.open(ArchEdif);
	if (!lectura.is_open()) {
		setColor(light_red);
		cout << "Error al abrir el archivo" << endl;
		setColor(white);
		carga_ok = false;	}
	else
	{
		lista_edificios.cont = 0;
		lectura >> codigo;
		while (codigo != Cent_ArchEdif)
		{
			//Leer resto de datos de edificio
			lectura.get(basura);
			lectura.getline(nombre, SizeNomEdif);
			lectura >> precio >> dinero >> prestigio >> estado;

			//Cargar en la lista
			lista_edificios.edificio[ lista_edificios.cont ].codigo = codigo;
			strcpy_s(lista_edificios.edificio[ lista_edificios.cont ].nombre, nombre);
			lista_edificios.edificio[ lista_edificios.cont ].precio = precio;
			lista_edificios.edificio[ lista_edificios.cont ].dinero = dinero;
			lista_edificios.edificio[ lista_edificios.cont ].prestigio = prestigio;
			lista_edificios.edificio[ lista_edificios.cont ].estado = tEstadoEdif(estado);

			lista_edificios.cont++;
			lectura >> codigo;
		}
	}

	if(carga_ok) {
		setColor(light_green);
		cout << "Edificios cargados" << endl;
		setColor(white);
	}
	return carga_ok;
}

void CargaCodEdif(ifstream& lectura, tListaJugadores& lista_jugadores)
{
	int codigo;
	unsigned int cont = 0;

	lectura >> codigo;
	while (codigo != Cent_LisCodEdif)
	{
		lista_jugadores.jugador[ lista_jugadores.cont ].comprados.cod_edif[cont] = codigo;
		cont++;
		lectura >> codigo;
	}
	lista_jugadores.jugador[ lista_jugadores.cont ].comprados.cont = cont;
}

bool CargaJugadores(tListaJugadores& lista_jugadores)
{
	bool carga_ok = true;
	ifstream lectura;
	char basura;

	tNomJug nombre;
	tCont contrasena;
	tNomEmpr empresa;
	int dinero;
	int prestigio;

	cout << "Cargando jugadores...";
	lectura.open(ArchJug);
	if (!lectura.is_open()) {
		setColor(light_red);
		cout << "Error al abrir el archivo" << endl;
		setColor(white);
		carga_ok = false;	}
	else
	{
		lista_jugadores.cont = 0;
		lectura >> nombre;
		while (strcmp(nombre, Cent_ArchJug) != 0)
		{
			//Leer resto de datos de jugador
			lectura >> contrasena;
			lectura.get(basura);
			lectura.getline(empresa, SizeNomEmpr);
			lectura >> dinero >> prestigio;

			//Cargar en la lista
			strcpy_s(lista_jugadores.jugador[ lista_jugadores.cont ].nombre, nombre);
			strcpy_s(lista_jugadores.jugador[ lista_jugadores.cont ].contrasena, contrasena);
			strcpy_s(lista_jugadores.jugador[ lista_jugadores.cont ].empresa, empresa);
			lista_jugadores.jugador[ lista_jugadores.cont ].dinero = dinero;
			lista_jugadores.jugador[ lista_jugadores.cont ].prestigio = prestigio;

			//Leer y cargar edificios comprados del jugador
			CargaCodEdif(lectura, lista_jugadores);

			lista_jugadores.cont++;
			lectura >> nombre;
		}
	}

	if(carga_ok) {
		setColor(light_green);
		cout << "Jugadores cargados" << endl;
		setColor(white);
	}
	return carga_ok;
}

//Guardado
bool GuardaEdificios(const tListaEdificios& lista_edificios)
{
	bool carga_ok = true;
	ofstream escritura;

	cout << "Guardando edificios...";
	escritura.open(ArchEdif);
	if (!escritura.is_open()) {
		setColor(light_red);
		cout << "Error al abrir el archivo" << endl;
		setColor(white);
		carga_ok = false;	}
	else {
		for(unsigned int i=0; i<lista_edificios.cont; i++)
			escritura << lista_edificios.edificio[i].codigo << endl
					  << lista_edificios.edificio[i].nombre << endl
					  << lista_edificios.edificio[i].precio << endl
					  << lista_edificios.edificio[i].dinero << endl
					  << lista_edificios.edificio[i].prestigio << endl
					  << lista_edificios.edificio[i].estado << endl
					  << endl;
		escritura << Cent_ArchEdif;
	}

	if(carga_ok) {
		setColor(light_green);
		cout << "Edificios guardados" << endl;
		setColor(white);
	}
	return carga_ok;
}

bool GuardaJugadores(const tListaJugadores& lista_jugadores)
{
	bool carga_ok = true;
	ofstream escritura;

	cout << "Guardando jugadores...";
	escritura.open(ArchJug);
	if (!escritura.is_open()) {
		setColor(light_red);
		cout << "Error al abrir el archivo" << endl;
		setColor(white);
		carga_ok = false;	}
	else {
		for(unsigned int i=0; i<lista_jugadores.cont; i++) {
			escritura << lista_jugadores.jugador[i].nombre << endl
					  << lista_jugadores.jugador[i].contrasena << endl
					  << lista_jugadores.jugador[i].empresa << endl
					  << lista_jugadores.jugador[i].dinero << endl
					  << lista_jugadores.jugador[i].prestigio << endl
					  << endl;
			for (unsigned int j=0; j<lista_jugadores.jugador[i].comprados.cont; j++)
				escritura << lista_jugadores.jugador[i].comprados.cod_edif[j] << endl;
			escritura << Cent_LisCodEdif << endl
					  << endl;
		}
		escritura << Cent_ArchJug;
	}
	
	if(carga_ok) {
		setColor(light_green);
		cout << "Jugadores guardados" << endl;
		setColor(white);
	}
	return carga_ok;
}