/* 
Práctica 1. Versión release básica.
- Tipo enumerado
- Comprobación de casos
*/

#include <iostream>
#include <locale>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

typedef enum{piedra, papel, tijera, lagarto, spock} tJugadas;

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
				 centinela = "XXX";

	cout << "Por favor, introduce tu apodo: ";
	cin >> user_introd;
	while (user_introd == centinela)
	{
		cout << "El apodo " << centinela << " no es válido. Por favor, introduce otro: ";
		cin >> user_introd;
	}

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
					user_ok = true;}
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
		else if (user_reg == centinela) //Usuario no encontrado. Demanda una contraseña y el programa procede a actualizar la lista
		{
			cout << "Tu usuario no se encuentra registrado. Escoja una contraseña: ";
			cin >> cont_introd;
			while (cont_introd == centinela)
			{
				cout << "La contraseña " << centinela << " no es válida. Por favor, introduce otra: ";
				cin >> user_introd;
			}

			lectura.close(); //Cierra la lectura
			lectura.open(arch_registro);
			escritura.open(arch_auxiliar); //Prepara el proceso de copia
			if (!lectura.is_open() || !escritura.is_open()) //Comprueba que los archivos se han abierto correctamente
			{
				cout << "Error al abrir el archivo" << endl;
				logIn_ok = false;
				user_ok = true; 
			}
			else {
			lectura >> user_reg >> cont_reg;
			while (user_reg != centinela) //Copia todos los usuarios/contraseñas ya existentes
			{
				escritura << user_reg << endl << cont_reg << endl;
				lectura >> user_reg >> cont_reg;
			}
			escritura << user_introd << endl << cont_introd << endl << "XXX"; //Añade el nuevo usuario y contraseña, y el centinela
			lectura.close();
			escritura.close();
			//Copia en sentido inverso
			lectura.open(arch_auxiliar);
			escritura.open(arch_registro); //Prepara el proceso de copia
			if (!lectura.is_open() || !escritura.is_open()) //Comprueba que los archivos se han abierto correctamente
			{
				cout << "Error al abrir el archivo" << endl;
				logIn_ok = false;
				user_ok = true; 
			}
			else {
			lectura >> user_reg >> cont_reg;
			while (user_reg != centinela) //Copia todos los usuarios/contraseñas ya existentes
			{
				
				escritura << user_reg << endl << cont_reg << endl;
				lectura >> user_reg >> cont_reg;
			}
			escritura << centinela; //añade el centinela
			user_ok = true;
			cout << "Tu usuario ha sido añadido correctamente. Bienvenido, " << user_introd << endl;
			lectura.close();
			escritura.close();
			}}
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
	const string arch_reglas = "reglas.txt",
				 centinela = "XXX";
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
		while (regla != centinela)
		{
			cout << regla << endl;
			getline(lectura, regla);
		}
		lectura.close();
	}
	return reglas_ok;
}

tJugadas EleccionUser()
{
	tJugadas jug_user;
	string eleccion;
	bool elec_ok;

	cout << "Elige tu jugada (piedra, papel, tijera, lagarto, spock): ";
	cin >> eleccion;
	elec_ok = false;
	while (!elec_ok)
	{
		if (eleccion == "piedra") {  
			jug_user = piedra;
			elec_ok = true; }
		else if (eleccion == "papel") {	
			jug_user = papel;
			elec_ok = true; }
		else if (eleccion == "tijera") {	
			jug_user = tijera;
			elec_ok = true;	}
		else if (eleccion == "lagarto") {	
			jug_user = lagarto;
			elec_ok = true;	}
		else if (eleccion == "spock") {	
			jug_user = spock;
			elec_ok = true;	}
		else {
			cout << "Jugada no válida. Introduzca una jugada permitida: ";
			cin >> eleccion; }
	}
	return jug_user;
}

void CalculoGanador(tJugadas jug_comp, tJugadas jug_user, unsigned int& pGanadas, unsigned int& pPerdidas, unsigned int& pEmpatadas)
{
	//Evaluación del ganador. Las jugadas del ordenador están ordenadas segun convenga
	if (jug_user == piedra)
	{
		switch (jug_comp) {
			case piedra:  cout << "Empate!"   << endl; pEmpatadas++; break;
			case papel:
			case spock:   cout << "Yo gano!"  << endl; pPerdidas++;  break;
			case tijera:
			case lagarto: cout << "Tu ganas!" << endl; pGanadas++;   break;
		}
	}
	else if (jug_user == papel)
	{
		switch (jug_comp) {
			case papel:   cout << "Empate!"   << endl; pEmpatadas++; break;
			case tijera:
			case lagarto: cout << "Yo gano!"  << endl; pPerdidas++;  break;
			case piedra:
			case spock:   cout << "Tu ganas!" << endl; pGanadas++;   break;
		}
	}
	else if (jug_user == tijera)
	{
		switch (jug_comp) {
			case tijera:  cout << "Empate!"   << endl; pEmpatadas++; break;
			case piedra:
			case spock:   cout << "Yo gano!"  << endl; pPerdidas++;  break;
			case papel:
			case lagarto: cout << "Tu ganas!" << endl; pGanadas++;   break;
		}
	}
	else if (jug_user == lagarto)
	{
		switch (jug_comp) {
			case lagarto: cout << "Empate!"   << endl; pEmpatadas++; break;
			case piedra:
			case tijera:  cout << "Yo gano!"  << endl; pPerdidas++;  break;
			case spock:
			case papel:   cout << "Tu ganas!" << endl; pGanadas++;   break;
		}
	}
	else if (jug_user == spock)
	{
		switch (jug_comp) {
			case spock:   cout << "Empate!"   << endl; pEmpatadas++; break;
			case papel:
			case lagarto: cout << "Yo gano!"  << endl; pPerdidas++;  break;
			case tijera:
			case piedra:  cout << "Tu ganas!" << endl; pGanadas++;   break;
		}
	}
}

void MostrarJugadas(tJugadas jug_comp, tJugadas jug_user)
{
	cout << "Mi elección: ";
		switch (jug_comp) {
			case piedra:  cout << "piedra";  break;
			case papel:   cout << "papel";   break;
			case tijera:  cout << "tijera";  break;
			case lagarto: cout << "lagarto"; break;
			case spock:   cout << "spock";   break;
		}
		cout << endl << "Tu elección: ";
		switch (jug_user) {
			case piedra:  cout << "piedra";  break;
			case papel:   cout << "papel";   break;
			case tijera:  cout << "tijera";  break;
			case lagarto: cout << "lagarto"; break;
			case spock:   cout << "spock";   break;
		}
}


//PROGRAMA PRINCIPAL
int main ()
{
	setlocale(LC_ALL,"");
	//Declaracion de variables
	tJugadas jug_comp, jug_user;
	unsigned short int opcion;
	bool logIn_ok, reglas_ok = true;
	unsigned int pGanadas = 0,
			 pEmpatadas = 0,
			 pPerdidas = 0;
	srand(time(NULL));
	
	//Introducción
	cout << "Piedra-Papel-Tijera-Lagarto-Spock" << endl;

	//Log in
	logIn_ok = LogIn();
	if (logIn_ok) 
	{ /*Ejecuta el programa*/

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
			switch (rand()%5) {
				case 0: jug_comp = piedra;  break;
				case 1: jug_comp = papel;   break;
				case 2: jug_comp = tijera;  break;
				case 3: jug_comp = lagarto; break;
				case 4: jug_comp = spock;   break;
			}
			cout << "He elegido mi jugada" << endl;

			jug_user = EleccionUser(); //Elección del usuario
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