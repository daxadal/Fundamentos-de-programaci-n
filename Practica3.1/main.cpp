/*
Práctica 3
*/

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

//CONSTANTES Y TIPOS
//Constantes
const char  ChMeta = char(176),
			ChPared = char(219),
			ChLibre = ' ';
const unsigned int DIM = 20,
				   NB = 10;
const short int LIBRE = -1,
				PARED = -2,
				AGUJERO = -3;

//Tipos - Colores
typedef enum {
	black,          //  0 
	dark_blue,      //  1
	dark_green,     //  2
	dark_cyan,      //  3
	dark_red,       //  4
	dark_magenta,   //  5
	dark_yellow,    //  6
	light_gray,     //  7
	dark_gray,      //  8
	light_blue,     //  9
	light_green,    // 10
	light_cyan,     // 11
	light_red,      // 12
	light_magenta,  // 13
	light_yellow,   // 14
	white           // 15
} tColores;

//Tipos - Juego
typedef int tTablero[DIM][DIM];
/*libre =-1, pared=-2, agujero=-3, bolas=[0,NB-1]*/
typedef enum{derecha, izquierda, arriba, abajo, ninguna} tDireccion;
typedef struct {
	tTablero tablero;
	int n_bolas;
	string arch_tablero;
	tDireccion ult_direccion;
	unsigned int n_turnos;
} tJuego;
typedef bool tBolasMarcadas[NB];


//SUBFUNCIONES
//Visualizacion
void setColor(unsigned short color)                 
{                                                   
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle,color);
}

void MostrarLaberinto(const tJuego& juego)
{
	cout << endl;
	for (int i=0; i<DIM; i++) {
		for(int j=0; j<DIM; j++)
			switch (juego.tablero[i][j]) {
			case PARED: setColor(light_cyan);
						cout << ChPared << ChPared << ChPared; 
						break;
			case LIBRE: cout << ChLibre << ChLibre << ChLibre;
						break;
			case AGUJERO: setColor(light_yellow);
						  cout << ChMeta << ChMeta << ChMeta; 
						  break;
			default: setColor(white);
					 cout << '(' << juego.tablero[i][j] << ')';
		}
		cout << endl;
	}
	setColor(white);
	cout << "Movimientos realizados: " << juego.n_turnos << endl;
}

void Menu(char& opcion)
{
	cout << endl << "________________________________" << endl
		 << "W - Inclinar hacia arriba" << endl
		 << "S - Inclinar hacia abajo" << endl 
		 << "A - Inclinar hacia la izquierda" << endl
		 << "D - Inclinar hacia la derecha" << endl
		 << "1 - Reiniciar el tablero" << endl
		 << "2 - Cargar nuevo tablero" << endl
		 << "0 - Salir" << endl
		 << "Opcion: ";
	cin >> opcion;
	while (	opcion != 'W' && opcion != 'S' && opcion != 'A' && opcion != 'D' 
		 && opcion != 'w' && opcion != 's' && opcion != 'a' && opcion != 'd'
		 && opcion != '1' && opcion != '2' && opcion != '0')
	{
		setColor(light_red);
		cout << "La opcion seleccionada no es valida." << endl
			 << "Introduzca una opcion permitida: ";
		setColor(white);
		cin >> opcion;
	}
}

void Enhorabuena(unsigned int turnos)
{
	setColor(light_green);
	cout << endl
		 << "---------------------------------------------" << endl
		 << "                = ENHORABUENA =              " << endl
		 << "Has resuelto el laberinto en " << turnos << " movimientos!" << endl
		 << "---------------------------------------------" << endl;
	setColor(white);
}

//Inicializacion y carga
void Inicializar(tBolasMarcadas& marcador, bool valor)
{
	for (int i=0; i<NB; i++)
		marcador[i] = valor;
}

void IniciaJuego(tJuego& juego, string arch)
{
	juego.n_turnos = 0;
	juego.ult_direccion = ninguna;
	juego.arch_tablero = arch;
}

void PedirArchivo(tJuego& juego, string arch_defecto)
{
	string arch;
	cout << "Introduzca el nombre del archivo (sin la extension '.txt')" << endl
		 << "Intro para abrir el archivo por defecto (" << arch_defecto << "): ";
	cin.sync();
	getline(cin, arch);

	if (arch == "")
		IniciaJuego(juego, arch_defecto);
	else 
		IniciaJuego(juego, arch +".txt");
}

bool CargaFila(int i, ifstream& lectura, tJuego& juego, tBolasMarcadas& marcador)
{
	bool carga_ok = true;
	int j=0;
	while(j<DIM && carga_ok)
	{
		lectura >> juego.tablero[i][j];
		if ( juego.tablero[i][j] < -3 || juego.n_bolas <= juego.tablero[i][j]) { //Compobar valor en intervalo [-3, n-1]
			setColor(light_red);
			cout << "Error: Valor leido no valido" << endl;
			setColor(white);
			carga_ok = false;	}

		else if (0 <= juego.tablero[i][j]) //Comprobar bolas no repetidas
			if (marcador[juego.tablero[i][j]]) {
				setColor(light_red);
				cout << "Error: Bola " << juego.tablero[i][j] << " repetida" << endl;
				setColor(white);
				carga_ok = false;	}
			else
				marcador[juego.tablero[i][j]] = true;
		j++;
	}
	return carga_ok;
}

bool CargaTablero(ifstream& lectura, tJuego& juego, tBolasMarcadas& marcador)
{
	bool carga_ok = true;
	int i=0;

	while(i<DIM && carga_ok) {
		carga_ok = CargaFila(i, lectura, juego, marcador); //Comprueba las columnas de la fila i
		i++; }

	return carga_ok;
}

bool ComprobarBolas(tBolasMarcadas marcador, int n_bolas) //Comprueba que no falten bolas
{
	bool comp_ok = true;
	int i=0;

	while(comp_ok && i<n_bolas)
	{
		if (!marcador[i])	 {
			setColor(light_red);
			cout << "Error: Falta la bola numero " << i << endl;
			setColor(white);
			comp_ok = false; }
		i++;
	}

	return comp_ok;
}

bool ValidarFronteras(const tJuego& juego)
{
	bool val_ok = true;
	int i;

	//Comprobar primera fila (0)
	i=0;
	while (val_ok && i<DIM) { 
		if (juego.tablero[0][i] != PARED) val_ok = false;
		i++;	  }

	//Comprobar última fila (DIM-1)
	i=0;
	while (val_ok && i<DIM) { 
		if (juego.tablero[DIM-1][i] != PARED) val_ok = false;
		i++;	  }

	//Comprobar primera columna (0)
	i=1;
	while (val_ok && i<DIM-1) { 
		if (juego.tablero[i][0] != PARED) val_ok = false;
		i++;	  }

	//Comprobar última columna (DIM-1)
	i=1;
	while (val_ok && i<DIM-1) { 
		if (juego.tablero[i][DIM-1] != PARED) val_ok = false;
		i++;	  }

	if(!val_ok) {
		setColor(light_red);
		cout << "Error: El tablero no esta rodeado de paredes" << endl;
		setColor(white); }
	return val_ok;
}

bool CargaJuego(tJuego& juego)
{
	ifstream lectura;
	string comentario;
	bool carga_ok = true;
	tBolasMarcadas marcador;
	Inicializar(marcador, false); //Inicializa comprobador de bolas

	lectura.open(juego.arch_tablero);
	if ( !lectura.is_open() ) {
		setColor(light_red);
		cout << "Error al abrir el archivo" << endl;
		setColor(white);
		carga_ok = false;	  }
	else 
	{
		lectura >> comentario;
		lectura >> juego.n_bolas;
		if ( juego.n_bolas > NB ) { //Comprobar nº correcto de bolas
			setColor(light_red);
			cout << "Error: Numero de bolas no valido" << endl;
			setColor(white);
			carga_ok = false;	  }
		else {
			lectura >> comentario;
			carga_ok = CargaTablero(lectura, juego, marcador); //Además comprueba valores correctos y bolas no repetidas
			if(carga_ok) carga_ok = ComprobarBolas(marcador, juego.n_bolas); //Comprobar que no faltan bolas
			if(carga_ok) carga_ok = ValidarFronteras(juego); //Comprobar escenario rodeado de paredes
		}
	}
	return carga_ok;
}

//Lógica del juego
void DesplazaBola(tJuego& juego, int fila, int col, tDireccion direccion, bool& terminado)
{
	bool bola_movida = false;
	int bola = juego.tablero[fila][col];

	juego.tablero[fila][col] = LIBRE;

	switch (direccion) {
	case arriba:	while (!bola_movida)
				 		if (juego.tablero[fila-1][col] == LIBRE || juego.tablero[fila-1][col] == AGUJERO) fila--;
						else {
							if (juego.tablero[fila][col] == AGUJERO) terminado = true;
							juego.tablero[fila][col] = bola;
							bola_movida = true; }
					break;

	case abajo:		while (!bola_movida)
				 		if (juego.tablero[fila+1][col] == LIBRE || juego.tablero[fila+1][col] == AGUJERO) fila++;
						else {
							if (juego.tablero[fila][col] == AGUJERO) terminado = true;
							juego.tablero[fila][col] = bola;
							bola_movida = true; }
					break;

	case izquierda:	while (!bola_movida)
				 		if (juego.tablero[fila][col-1] == LIBRE || juego.tablero[fila][col-1] == AGUJERO) col--;
						else {
							if (juego.tablero[fila][col] == AGUJERO) terminado = true;
							juego.tablero[fila][col] = bola;
							bola_movida = true; }
					break;

	case derecha:	while (!bola_movida)
				 		if (juego.tablero[fila][col+1] == LIBRE || juego.tablero[fila][col+1] == AGUJERO) col++;
						else {
							if (juego.tablero[fila][col] == AGUJERO) terminado = true;
							juego.tablero[fila][col] = bola;
							bola_movida = true; }
					break;
	}
}

void InclinaTablero(tJuego& juego, tDireccion direccion, bool& terminado)
{
	switch (direccion) {
		case arriba:	for (int i=0; i<DIM; i++)
						 for (int j=0; j<DIM; j++)
							 if (0 <= juego.tablero[i][j] && juego.tablero[i][j] <= juego.n_bolas-1)
								 DesplazaBola(juego, i, j, direccion, terminado);
						break;

		case abajo:		for (int i=DIM-1; 0<=i; i--)
						 for (int j=0; j<DIM; j++)
							 if (0 <= juego.tablero[i][j] && juego.tablero[i][j] <= juego.n_bolas-1)
								 DesplazaBola(juego, i, j, direccion, terminado);
						break;

		case izquierda: for (int i=0; i<DIM; i++)
						 for (int j=0; j<DIM; j++)
							 if (0 <= juego.tablero[i][j] && juego.tablero[i][j] <= juego.n_bolas-1)
								 DesplazaBola(juego, i, j, direccion, terminado);
						break;

		case derecha:	for (int i=0; i<DIM; i++)
						 for (int j=DIM-1; 0<=j; j--)
							 if (0 <= juego.tablero[i][j] && juego.tablero[i][j] <= juego.n_bolas-1)
								 DesplazaBola(juego, i, j, direccion, terminado);
						break;
	}
	juego.ult_direccion = direccion;
	juego.n_turnos++;
}

//PROGRAMA PRINCIPAL
int main ()
{
	SetConsoleOutputCP(850);
	tJuego juego;
	bool carga_ok,
		 terminado = false;
	char opcion;
	const string arch_defecto = "lab1.txt";
	char fin;
	setColor(white);

	PedirArchivo(juego, arch_defecto);
	carga_ok = CargaJuego(juego);
	if (carga_ok) 
	{
		MostrarLaberinto(juego);
		Menu(opcion);
		while (opcion != '0' && !terminado)
		{
			switch (opcion) {
				case 'W': 
				case 'w': if (!carga_ok) {
							setColor(light_red);
							cout << "No hay un archivo cargado" << endl;
							setColor(white);				 }
						  else if (juego.ult_direccion == arriba) {
							setColor(light_red);
							cout << "Ya has movido en esa direccion" << endl;
							setColor(white);				 }
						  else 
							  InclinaTablero(juego, arriba, terminado);
						  break;
				case 'S': 
				case 's': if (!carga_ok) {
							setColor(light_red);
							cout << "No hay un archivo cargado" << endl;
							setColor(white);				 }
						  else if (juego.ult_direccion == abajo) {
							setColor(light_red);
							cout << "Ya has movido en esa direccion" << endl;
							setColor(white);				 }
						  else 
							  InclinaTablero(juego, abajo, terminado);
						  break;
				case 'A': 
				case 'a': if (!carga_ok) {
							setColor(light_red);
							cout << "No hay un archivo cargado" << endl;
							setColor(white);				 }
						  else if (juego.ult_direccion == izquierda) {
							setColor(light_red);
							cout << "Ya has movido en esa direccion" << endl;
							setColor(white);				 }
						  else 
							  InclinaTablero(juego, izquierda, terminado);
						  break;
				case 'D': 
				case 'd': if (!carga_ok) {
							setColor(light_red);
							cout << "No hay un archivo cargado" << endl;
							setColor(white);				 }
						  else if (juego.ult_direccion == derecha) {
							setColor(light_red);
							cout << "Ya has movido en esa direccion" << endl;
							setColor(white);				 }
						  else 
							  InclinaTablero(juego, derecha, terminado);
						  break;

				case '1': IniciaJuego(juego, juego.arch_tablero);
						  carga_ok = CargaJuego(juego);
						  break;
				case '2': PedirArchivo(juego, arch_defecto);
						  carga_ok = CargaJuego(juego);
						  break;
			}
			if (carga_ok) MostrarLaberinto(juego);
			if (!terminado) Menu(opcion);
		}
		if (terminado) Enhorabuena(juego.n_turnos);
	}
	cout << endl << "(Pulsa Intro para salir)";
	cin.sync();
	cin.get(fin);
	return 0;
}