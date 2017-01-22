/*
Práctica 5
*/

#include "archivos_bin.h"
#include "archivos_txt.h"

typedef enum{ jugador, admin, salir, sin_especificar } tLogIn;

//LogIn
tLogIn LogIn(const tListaJugadores& lista_jugadores, tNomJug& nom_jug)
{
	int intentos_rest = 3;

	tNomJug nom_intr;
	tCont contr_intr, contr_corr;
	tLogIn tipo_user = sin_especificar;
	int pos;
	
	cout << endl
		 << "Introduzca su nombre de usuario." << endl
		 << "Introduzca " << NombreSalir << " para cerrar el programa: ";
	cin >> nom_intr;
	while (tipo_user == sin_especificar) {
		if ( strcmp(NombreSalir, nom_intr) == 0 ) //El usuario desea salir
			tipo_user = salir;
		else if ( strcmp(NombreAdmin, nom_intr) == 0 ) { //El usuario es el administrador
			strcpy_s(contr_corr, ContAdmin);
			tipo_user = admin;		}
		else if ( BuscarJugador(lista_jugadores, nom_intr, pos) ) { //El usuario (jugador) está registrado
			strcpy_s(nom_jug, lista_jugadores.jugador[pos].nombre);
			strcpy_s(contr_corr, lista_jugadores.jugador[pos].contrasena);
			tipo_user = jugador;	}
		else { //El usuario (jugador) no se encuentra registrado. Volver a introducir nombre
			setColor(light_red);
			cout << "Nombre de usuario no encontrado" << endl;
			setColor(white);
			cout << "Introduzca su nombre de usuario." << endl
				 << "Introduzca " << NombreSalir << " para cerrar el programa: ";
			cin >> nom_intr;
		}
	}
	if (tipo_user != salir) { //Verificacion de contraseña (jugador/administrador)
		cout << "Introduzca su contraseña: ";
		cin >> contr_intr;
		while (tipo_user != salir && strcmp(contr_corr, contr_intr) != 0) {
			intentos_rest--;
			if (intentos_rest == 0) {
				setColor(light_red);
				cout << "Has fallado demasiadas veces. No puedes jugar" << endl;
				setColor(white);	
				tipo_user = salir;	}
			else {
				setColor(light_red);
				cout << "Contraseña incorrecta. ";
				setColor(white); 
				cout << "Te quedan " << intentos_rest << " intentos: ";
				cin >> contr_intr;	}
		}
		if (tipo_user != salir) {
			setColor(light_green);
			cout << "Login correcto. Bienvenido, " << nom_intr << endl;
			setColor(white);
		}
	}
	return tipo_user;
}

//Mensajes/Menus
void Bienvenido()
{
	setColor(light_green);
	cout << endl
		 << "===========================================" << endl
		 << "         Bienvenido a Campus Ville         " << endl
		 << "===========================================" << endl
		 << endl;
	setColor(white);
}

void MenuAdmin(unsigned short int& opcion)
{
	cout << endl
		 << " 1 - Ver el listado de edificios" << endl
		 << " 2 - Nuevo edificio" << endl
		 << " 3 - Borrar edificio" << endl
		 << " 4 - Ver el listado de jugadores" << endl
		 << " 5 - Nuevo jugador" << endl
		 << " 6 - Borrar jugador" << endl
		 << " 7 - Ejecutar un turno" << endl
		 << " 8 - Ver la clasificacion (por dinero)" << endl
		 << " 9 - Importar datos de archivo de texto" << endl
		 << "10 - Guardar copia de los datos en archivo de texto" << endl
		 << " 0 - Cerrar la sesion" << endl
		 << "Opcion: ";
	cin >> opcion;

	while(opcion > 10)
	{
		setColor(light_red);
		cout << "La opción seleccionada no es válida." << endl
			 << "Por favor, introduzca una opción permitida: ";
		setColor(white);
		cin >> opcion;
	}
}

void MenuJug(unsigned short int& opcion)
{
	cout << endl
		 << "1 - Ver mis edificios" << endl
		 << "2 - Ver los edificios disponibles" << endl
		 << "3 - Comprar edificio" << endl
		 << "4 - Ver la clasificacion (por dinero)" << endl
		 << "5 - Ver la clasificacion (por prestigio)" << endl
		 << "0 - Cerrar la sesion" << endl
		 << "Opcion: ";
	cin >> opcion;

	while(opcion > 5)
	{
		setColor(light_red);
		cout << "La opción seleccionada no es válida." << endl
			 << "Por favor, introduzca una opción permitida: ";
		setColor(white);
		cin >> opcion;
	}
}

//Visualizacion - Ver clasificacion
void VerClas_Cabecera()
{
	cout << "Pos" << ' '
		 << left << setw(SizeNomJug-1) << " Nombre " << ' '
		 << setw(SizeNomEmpr-1) << "  Empresa  " << right << ' '
		 << "Credit" << ' '
		 << "Pres." << ' '
		 << "NºEdif" 
		 << endl;
}

void VerClas_Linea()
{
	cout << "____";
	for (int i=0; i < (SizeNomJug + SizeNomEmpr); i++) cout << '_';
	cout << "_______"
		 << "______"
		 << "______"
		 << endl;
}

void VerClasificacion(const tListaJugadores& lista_jugadores)
{
	cout << endl;
	VerClas_Cabecera();
	VerClas_Linea();
	for (unsigned int i=0; i<lista_jugadores.cont; i++)
		cout << setw(3) << i+1 << ' '
			 << left 
			 << setw(SizeNomJug-1) << lista_jugadores.jugador[i].nombre << ' '
			 << setw(SizeNomEmpr-1) << lista_jugadores.jugador[i].empresa << ' '
			 << right
			 << setw(6) << lista_jugadores.jugador[i].dinero << ' '
			 << setw(5) << lista_jugadores.jugador[i].prestigio << ' '
			 << setw(4) << lista_jugadores.jugador[i].comprados.cont
			 << endl;
	VerClas_Linea();
}

//Interfaces - Administrador
void Op2Admin_NuevoEdificio(tListaEdificios& lista_edificios)
{
	bool proceso_ok;
	tEdificio edificio;

	if ( ListaEdificiosLlena(lista_edificios) ) {
		setColor(light_red);
		cout << "La lista de edificios esta llena. No se ha podido insertar" << endl;
		setColor(white);		}
	else {
		edificio = NuevoEdificio();
		proceso_ok = InsertarEdificio(lista_edificios, edificio);
		if (proceso_ok) {
			setColor(light_green);
			cout << "Edificio insertado" << endl;
			setColor(white); }
		else {
			setColor(light_red);
			cout << "Ya existe un edificio con ese código" << endl;
			setColor(white);	}
	}
}

void Op3Admin_BorrarEdificio(tListaEdificios& lista_edificios)
{
	unsigned int codigo;
	bool proceso_ok;

	cout << "Introduzca el código del edificio que desea borrar: ";
	cin >> codigo;

	proceso_ok = BajaEdificio(lista_edificios, codigo);
	if (proceso_ok) {
		setColor(light_green);
		cout << "Edificio borrado" << endl;
		setColor(white); }
	else {
		setColor(light_red);
		cout << "No se ha podido borrar. El edificio no existe o ha sido comprado" << endl;
		setColor(white);	}
}

void Op4Admin_VerJugadores(const tListaJugadores& lista_jugadores, const tListaEdificios& lista_edificios)
{
	if (lista_jugadores.cont == 0)	{
		setColor(light_red);
		cout << "No se ha creado ningun jugador" << endl;
		setColor(white);			}
	else {
		for (unsigned int i=0; i< lista_jugadores.cont; i++)
		{
			cout << endl << "======================================" << endl;
			MostrarJugador(lista_jugadores.jugador[i], lista_edificios);
		}
		cout << endl << "======================================" << endl << endl;
	}
}

void Op5Admin_NuevoJugador(tListaJugadores& lista_jugadores)
{
	bool proceso_ok;
	tJugador jugador;

	if ( ListaJugadoresLlena(lista_jugadores) ) {
		Redimensionar(lista_jugadores);
		cout << "La lista de jugadores estaba llena. Se ha añadido un 50% más de capacidad" << endl;
	}
	
	jugador = NuevoJugador();
	proceso_ok = InsertarJugador(lista_jugadores, jugador);
	if (proceso_ok) {
		setColor(light_green);
		cout << "Jugador insertado" << endl;
		setColor(white); }
	else {
		setColor(light_red);
		cout << "Ya existe un jugador con ese nombre" << endl;
		setColor(white);	}
	
}

void Op6Admin_BorrarJugador(tListaJugadores& lista_jugadores, tListaEdificios& lista_edificios)
{
	bool proceso_ok;
	tNomJug nombre;

	cout << "Introduzca el nombre del jugador que desea borrar: ";
	cin >> nombre;

	proceso_ok = BajaJugador(nombre, lista_jugadores, lista_edificios);
	if(proceso_ok) {
		setColor(light_green);
		cout << "Jugador borrado" << endl;
		setColor(white); }
	else {
		setColor(light_red);
		cout << "No existe un jugador con ese nombre" << endl;
		setColor(white);	}
	}

void Op7Admin_EjecutarTurno(tListaJugadores& lista_jugadores, tListaEdificios& lista_edificios)
{
	int pos_edif;
	
	cout << "Ejecutando turno..." << endl;
	setColor(light_gray);

	for (unsigned int i=0; i<lista_jugadores.cont; i++) //Para cada jugador, ...
	{
		cout << "Procesando jugador: " << lista_jugadores.jugador[i].nombre << endl;

		for (unsigned int j=0; j<lista_jugadores.jugador[i].comprados.cont; j++) { //... por cada edificio que haya comprado ...
			BuscarEdificio(lista_edificios, lista_jugadores.jugador[i].comprados.cod_edif[j], pos_edif);
			lista_jugadores.jugador[i].dinero += lista_edificios.edificio[pos_edif]->dinero;		//... se le ingresa los beneficios del edificio ...
			lista_jugadores.jugador[i].prestigio += lista_edificios.edificio[pos_edif]->prestigio;	//... y se le añade el prestigio del edificio

			cout << " - " << left << setw(SizeNomEdif) << lista_edificios.edificio[pos_edif]->nombre << right
				 << " (Ingresos: " << showpos << setw(4) << lista_edificios.edificio[pos_edif]->dinero 
				 << " Prestigio: " << setw(4) << lista_edificios.edificio[pos_edif]->prestigio << noshowpos << ")" << endl;
		}
		cout << endl;
	}
	setColor(light_green);
	cout << "Turno ejecutado" << endl << endl;
	setColor(white);
}

void InterfazAdmin(tListaEdificios& lista_edificios, tListaJugadores& lista_jugadores)
{
	unsigned short int opcion;

	MenuAdmin(opcion);
	while (opcion != 0)
	{
		switch (opcion) {
			case 1: VerEdif_General(lista_edificios, false); break;
			case 2: Op2Admin_NuevoEdificio(lista_edificios); break;
			case 3: Op3Admin_BorrarEdificio(lista_edificios); break;
			case 4: Op4Admin_VerJugadores(lista_jugadores, lista_edificios); break;
			case 5: Op5Admin_NuevoJugador(lista_jugadores); break;
			case 6: Op6Admin_BorrarJugador(lista_jugadores, lista_edificios); break;
			case 7: Op7Admin_EjecutarTurno(lista_jugadores, lista_edificios); break;
			case 8: OrdenarJug_PorDinero(lista_jugadores);
					VerClasificacion(lista_jugadores);
					break;
			case 9: CargaEdificiosTxt(lista_edificios);
					CargaJugadoresTxt(lista_jugadores);
					break;
			case 10: GuardaEdificiosTxt(lista_edificios);
					GuardaJugadoresTxt(lista_jugadores);
					break;
		}
		MenuAdmin(opcion);
	}
}

//Interfaces - Jugador
void Op3Jug_ComprarEdificio(tNomJug nom_jug, tListaJugadores& lista_jugadores, tListaEdificios& lista_edificios)
{
	unsigned int codigo;
	int proceso_ok;
	/*comprado = 0, no encontrado = 1, no disponible = 2, sin dinero = 3*/
	int pos;

	BuscarJugador(lista_jugadores, nom_jug, pos);

	cout << endl
		 << "(Dinero Disponible: " << lista_jugadores.jugador[pos].dinero << " Créditos)" << endl << endl
		 << "Introduzca el código del edificio que desea comprar: ";
	cin >> codigo;

	proceso_ok = ComprarEdificio(lista_jugadores.jugador[pos], codigo, lista_edificios);

	switch (proceso_ok) {
	case 0:	setColor(light_green);
			cout << "Edificio comprado" << endl;
			setColor(white); 
			break;
	case 1: setColor(light_red);
			cout << "No se ha podido comprar. El edificio no existe" << endl;
			setColor(white);
			break;
	case 2:	setColor(light_red);
			cout << "No se ha podido comprar. El edificio no está disponible" << endl;
			setColor(white);
			break;
	case 3:	setColor(light_red);
			cout << "No se ha podido comprar. No tienes dinero suficiente" << endl;
			setColor(white);
			break;
	}
}

void InterfazJug(tListaEdificios& lista_edificios, tListaJugadores& lista_jugadores, tNomJug nom_jug)
{
	unsigned short int opcion;
	int pos_jug;

	MenuJug(opcion);
	while (opcion != 0)
	{
		switch (opcion) {
			case 1: BuscarJugador(lista_jugadores, nom_jug, pos_jug);
					if (lista_jugadores.jugador[pos_jug].comprados.cont != 0 )
						VerEdif_Jugador(lista_edificios, lista_jugadores.jugador[pos_jug], white);
					else  {
						setColor(light_red);
						cout << "No posees ningún edificio" << endl;
						setColor(white);	}
					break;
			case 2: VerEdif_General(lista_edificios, true); break;
			case 3: Op3Jug_ComprarEdificio(nom_jug, lista_jugadores, lista_edificios); break;
			case 4: OrdenarJug_PorDinero(lista_jugadores);
					VerClasificacion(lista_jugadores);
					break;
			case 5: OrdenarJug_PorPrestigio(lista_jugadores);
					VerClasificacion(lista_jugadores);
					break;
		}
		MenuJug(opcion);
	}
}

//PROGRAMA PRINCIPAL
int main()
{
	setlocale(LC_ALL,"");
	char fin;
	tListaEdificios lista_edificios;
	tListaJugadores lista_jugadores;
	tLogIn tipo_jug;
	tNomJug nom_jug;
	bool carga_ok;

	Inicializar(lista_edificios);
	lista_jugadores.jugador = NULL;
	setColor(white); //Inicializar parámetros

	//Carga de datos
	carga_ok = CargaEdificiosBin(lista_edificios);
	if(!carga_ok) {
		cout << "Generando nueva lista de edificios...";
		lista_edificios.cont = 0;
		setColor(light_green);
		cout << "Lista de edificios generada" << endl;
		setColor(white);
	}
	carga_ok = CargaJugadoresBin(lista_jugadores);
	if(!carga_ok) {
		cout << "Generando nueva lista de jugadores...";
		lista_jugadores.jugador = new tJugador[MaxJugIni];
		lista_jugadores.capacidad = MaxJugIni;
		lista_jugadores.cont = 0;
		setColor(light_green);
		cout << "Lista de jugadores generada" << endl;
		setColor(white);
	}

	//Desarrollo del programa
	Bienvenido();
	tipo_jug = LogIn(lista_jugadores, nom_jug);
	while (tipo_jug != salir) {
		switch (tipo_jug) {
			case admin: InterfazAdmin(lista_edificios, lista_jugadores); break;
			case jugador: InterfazJug(lista_edificios, lista_jugadores, nom_jug); break;
		}
		tipo_jug = LogIn(lista_jugadores, nom_jug);	
	}

	//Guardado de datos y destruccion de arrays dinámicos
	cout << endl;
	GuardaEdificiosBin(lista_edificios);
	Destruir(lista_edificios);
	GuardaJugadoresBin(lista_jugadores);
	delete [] lista_jugadores.jugador;

	cout << endl << "(Pulsa Intro para salir)";
	cin.sync();
	cin.get(fin);
	return 0;
}