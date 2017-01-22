/*
Práctica 1. Versión release mejorada.
- Cálculo de ganador mediante módulos
- Lectura/Escritura sin centinela y sin copia
- Contraseñas entre 8 y 10 caracteres
*/

#include <iostream>
#include <locale>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

//SUBFUNCIONES
bool LogIn() 
{
	string user_introd, user_reg, cont_introd, cont_reg;
	bool user_ok = false,
		 logIn_ok = true;
	ifstream lectura;
	ofstream escritura;
	unsigned short int cont_intentos = 3;
	const string arch_registro = "registro.txt",
				 arch_auxiliar = "auxiliar.txt",
				 cont_bloqueado = "usuario_peligroso",
				 cont_desbloqueado = "cont_sin_definir";

	cout << "Por favor, introduce tu apodo: ";
	cin >> user_introd;

	lectura.open(arch_registro);
	if (!lectura.is_open()) 
	{
		cout << "Error al abrir el archivo" << endl;
		logIn_ok = false;
	}
	else while (!user_ok)
	{
		lectura >> user_reg >> cont_reg;
		if (user_reg == user_introd) //Usuario encontrado
		{
			cout << "Por favor, introduce la contraseña: ";
			cin >> cont_introd;
			while (cont_reg != cont_introd && logIn_ok) //Contraseña incorrecta
			{
				cont_intentos--;
				if (cont_intentos == 0) {
					cout << "Lo siento, pero has fallado demasiadas veces. No puedes jugar" << endl;
					logIn_ok = false;
					user_ok = true; }
				else {
					cout << "Contraseña incorrecta. Te quedan " << cont_intentos << " intentos: ";
					cin >> cont_introd; }
			}
			if (cont_reg == cont_introd)
			{
				user_ok = true;
				lectura.close();
				cout << "Tu sesión ha sido iniciada correctamente. Bienvenido, " << user_introd << endl;
			}
		}
		else if ( lectura.eof() ) //Usuario no encontrado. Demanda una contraseña y el programa procede a actualizar la lista
		{
			cout << "Tu usuario no se encuentra registrado. Escoja una contraseña: ";
			cin >> cont_introd;
			while ( cont_introd.length()<8 || cont_introd.length()>10)
			{
				cout << "La contraseña debe tener entre 8 y 10 caracteres, y no puede tener blancos." << endl
					 << "Por favor, escoja otra contraseña: ";
				cin >> cont_introd;
			}
			lectura.close();
			escritura.open(arch_registro, ios::app);
			if ( !escritura.is_open() ) //Comprueba que el archivo se ha abierto correctamente
			{
				cout << "Error al abrir el archivo" << endl;
				logIn_ok = false;
				user_ok = true;
			}
			else 
			{
				escritura << user_introd << endl << cont_introd << endl; //Añade el nuevo usuario y contraseña
				escritura.close();
				user_ok = true;
				cout << "Tu usuario ha sido añadido correctamente. Bienvenido, " << user_introd << endl;
			}
		}
	}
	
	return logIn_ok;
}

void MenuPrincipal()
{
	cout << "1 - Jugar una partida" << endl
		 << "2 - Ver instrucciones" << endl
		 << "0 - Salir" << endl
		 << "Opción: ";
}

bool MostrarReglas()
{	
	bool reglas_ok = true;
	const string arch_reglas = "reglas.txt";
	ifstream lectura;
	string regla;

	lectura.open(arch_reglas);
	if (!lectura.is_open()) //Comprueba que el archivo se han abierto correctamente
	{
		cout << "Error al abrir el archivo" << endl;
		reglas_ok = false; 
	}
	else
	{
		getline(lectura, regla);
		while ( !lectura.eof() )
		{
			cout << regla << endl;
			getline(lectura, regla);
		}
		lectura.close();
	}
	return reglas_ok;
}

unsigned short int EleccionUser()
{
	unsigned short int jug_user;
	string eleccion;
	bool elec_ok;

	cout << "Elige tu jugada (piedra, papel, tijera, lagarto, spock): ";
	cin >> eleccion;
	elec_ok = false;
	while (!elec_ok)
	{
		if (eleccion == "piedra") {  
			jug_user = 0;
			elec_ok = true; }
		else if (eleccion == "papel") {	
			jug_user = 1;
			elec_ok = true; }
		else if (eleccion == "tijera") {	
			jug_user = 2;
			elec_ok = true;	}
		else if (eleccion == "lagarto") {	
			jug_user = 4;
			elec_ok = true;	}
		else if (eleccion == "spock") {	
			jug_user = 3;
			elec_ok = true;	}
		else {
			cout << "Jugada no válida. Introduzca una jugada permitida: ";
			cin >> eleccion; }
	}
	return jug_user;
}

void CalculoGanador(unsigned short int jug_comp, unsigned short int jug_user, unsigned int& pGanadas, unsigned int& pPerdidas, unsigned int& pEmpatadas)
{
	switch ( (5+jug_user - jug_comp) %5 ) {
		case 0: cout << "Empate!"   << endl; pEmpatadas++; break;
		case 3:
		case 1: cout << "Tu ganas!" << endl; pGanadas++;   break;
		case 2:
		case 4: cout << "Yo gano!"  << endl; pPerdidas++;  break;
	}
}

void MostrarJugadas(unsigned short int jug_comp, unsigned short int jug_user)
{
	cout << "Mi elección: ";
		switch (jug_comp) {
			case 0: cout << "piedra";  break;
			case 1: cout << "papel";   break;
			case 2: cout << "tijera";  break;
			case 4: cout << "lagarto"; break;
			case 3: cout << "spock";   break;
		}
		cout << endl << "Tu elección: ";
		switch (jug_user) {
			case 0: cout << "piedra";  break;
			case 1: cout << "papel";   break;
			case 2: cout << "tijera";  break;
			case 4: cout << "lagarto"; break;
			case 3: cout << "spock";   break;
		}
}


//PROGRAMA PRINCIPAL
int main ()
{
	setlocale(LC_ALL,"");
	//Declaracion de variables
	unsigned short int jug_comp, jug_user;
	/*piedra=0, papel=1, tijera=2, spock=3, lagarto=4 */
	unsigned int pGanadas = 0,
				 pEmpatadas = 0,
				 pPerdidas = 0;
	unsigned short int opcion;
	bool logIn_ok, reglas_ok = true;
	srand(time(NULL));
	
	//Introducción
	cout << "Piedra-Papel-Tijera-Lagarto-Spock" << endl;

	//Log in
	logIn_ok = LogIn();
	if (logIn_ok)
	{

	//Menú principal
	MenuPrincipal();
	cin >> opcion;

	while (opcion != 0 && reglas_ok)
	{
		//Opciones no válidas
		while (opcion >= 3)
		{
			cout << "Opción no válida. Introduzca una opción permitida: ";
			cin >> opcion;
		}
	
		//Mostrar reglas
		if (opcion == 2) 
			reglas_ok = MostrarReglas();
	
		//Jugar una partida
		else if (opcion == 1)
		{
			//Eleccion del ordenador
			jug_comp = rand()%5;
			cout << "He elegido mi jugada" << endl;

			jug_user = EleccionUser(); //Elección del usuario
			
			//Evaluación del ganador
			CalculoGanador(jug_comp, jug_user, pGanadas, pPerdidas, pEmpatadas);
			MostrarJugadas(jug_comp, jug_user); //El ordenador muestra las elecciones
		}
		//Jugar otra partida/Salir
		if (reglas_ok) {
			cout << endl << "......................." << endl;
			MenuPrincipal();
			cin >> opcion; }
	}

	//Fin del programa
	cout << "Partidas jugadas: " << pGanadas + pPerdidas + pEmpatadas << endl
		 << "Partidas ganadas: " << pGanadas << endl
		 << "Partidas perdidas: " << pPerdidas << endl
		 << "Partidas empatadas: " << pEmpatadas << endl
		 << "Hasta pronto!" << endl;
	}
	return 0;
}