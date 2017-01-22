/*
Eric García de Ceca Elejoste
Práctica 2
*/

#include <iostream>
#include <locale>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <fstream>
using namespace std;

const string arch_registro = "registro.txt",
			 arch_auxiliar = "auxiliar.txt",
			 arch_reglas_PPTLS = "reglasPPTLS.txt",
			 arch_reglas_VoltDado = "reglasVD.txt",
			 user_admin = "administrador",
			 cont_neutra = "<vacio>";
const char user_bloq = '!',
		   user_nbloq = '_';
typedef enum{jugador, admin, error} tLogIn;
typedef enum{new_user, camb_cont, bloq, desbloq, act_estad} tAccReg;
typedef enum{norte, sur, este, oeste} tGiro;


//SUBFUNCIONES

//Registro

bool AbrirArchivos(ifstream &lectura, string arch_lectura, ofstream &escritura, string arch_escritura)
{
	bool devolver = true;
	lectura.open(arch_lectura);
	escritura.open(arch_escritura);

	if (!lectura.is_open()) {
		cout << "Error al abrir el archivo" << endl;
		devolver = false; }
	if (!escritura.is_open()) {
		cout << "Error al crear el archivo" << endl;
		devolver = false; }
	return devolver;
}

bool CopiarUsuarios(ifstream &lectura, ofstream &escritura, string user_limite)
{
	string user_reg, cont_reg;
	char peligroso;
	int nIngresos, nGanadas, nPerdidas , nEmpatadas, vGanadas, vPerdidas;

	lectura >> user_reg;
	while ( (user_limite == "" || user_reg != user_limite) && !lectura.eof() )
	{
		lectura >> peligroso >> cont_reg >> nIngresos >> nGanadas >> nPerdidas >> nEmpatadas >> vGanadas >> vPerdidas;
		escritura << user_reg << ' ' << peligroso << endl << cont_reg << endl
				  << nIngresos << ' ' << nGanadas << ' ' << nPerdidas << ' ' << nEmpatadas << ' ' << vGanadas << ' ' << vPerdidas << endl << endl;
		lectura >> user_reg;
	}
	return !lectura.eof();
}

bool ActReg_NewUser(string user_act, string cont_act)
{
	ifstream lectura;
	ofstream escritura;
	string user_reg, cont_reg;
	int nJugadores, nGanadas, nPerdidas , nEmpatadas, vGanadas, vPerdidas;
	bool act_ok = true;

	//1ª Copia
	act_ok = AbrirArchivos(lectura, arch_registro, escritura, arch_auxiliar);
	if (act_ok) {
		lectura >> user_reg >> cont_reg >> nJugadores >> nGanadas >> nPerdidas >> nEmpatadas >> vGanadas >> vPerdidas;
		escritura << user_reg << endl << cont_reg << endl << nJugadores+1 << ' ' 
				  << nGanadas << ' ' << nPerdidas << ' ' << nEmpatadas << ' ' << vGanadas << ' ' << vPerdidas << endl << endl;

		act_ok = !CopiarUsuarios(lectura, escritura, "");
		if (act_ok) {
			escritura << user_act << ' ' << user_nbloq << endl << cont_act << endl << "0 0 0 0 0 0" << endl << endl;

			lectura.close();
			escritura.close();

			//2ª Copia
			act_ok = AbrirArchivos(lectura, arch_auxiliar, escritura, arch_registro);
			if (act_ok) {
				lectura >> user_reg >> cont_reg >> nJugadores >> nGanadas >> nPerdidas >> nEmpatadas >> vGanadas >> vPerdidas;
				escritura << user_reg << endl << cont_reg << endl
						  << nJugadores << ' ' << nGanadas << ' ' << nPerdidas << ' ' << nEmpatadas << ' ' << vGanadas << ' ' << vPerdidas << endl << endl;
				act_ok = !CopiarUsuarios(lectura, escritura, "");

				lectura.close();
				escritura.close();
			}
		}
	}
	return act_ok;
}

bool ActReg_CambCont(string user_act, string cont_act)
{
	ifstream lectura;
	ofstream escritura;
	string user_reg, cont_reg;
	char peligroso;
	int nJugadores, nIngresos, nGanadas, nPerdidas , nEmpatadas, vGanadas, vPerdidas;
	bool act_ok = true;
	
	//1ª Copia
	act_ok = AbrirArchivos(lectura, arch_registro, escritura, arch_auxiliar);
	if (act_ok) {
		lectura >> user_reg >> cont_reg >> nJugadores >> nGanadas >> nPerdidas >> nEmpatadas >> vGanadas >> vPerdidas;
		escritura << user_reg << endl << cont_reg << endl << nJugadores << ' '
				  << nGanadas << ' ' << nPerdidas << ' ' << nEmpatadas << ' ' << vGanadas << ' ' << vPerdidas << endl << endl;
		
		act_ok = CopiarUsuarios(lectura, escritura, user_act);
		if (!act_ok) 
			cout << "El usuario no se encuentra en el registro" << endl;
		else {
			lectura >> peligroso >> cont_reg >> nIngresos >> nGanadas >> nPerdidas >> nEmpatadas >> vGanadas >> vPerdidas;
			escritura << user_act << ' ' << peligroso << endl << cont_act << endl
					  << nIngresos << ' ' << nGanadas << ' ' << nPerdidas << ' ' << nEmpatadas << ' ' << vGanadas << ' ' << vPerdidas << endl << endl;
			act_ok = !CopiarUsuarios(lectura, escritura, "");
			lectura.close();
			escritura.close();

			//2ª Copia
			act_ok = AbrirArchivos(lectura, arch_auxiliar, escritura, arch_registro);
			if (act_ok) {
				lectura >> user_reg >> cont_reg >> nJugadores >> nGanadas >> nPerdidas >> nEmpatadas >> vGanadas >> vPerdidas;
				escritura << user_reg << endl << cont_reg << endl
						  << nJugadores << ' ' << nGanadas << ' ' << nPerdidas << ' ' << nEmpatadas << ' ' << vGanadas << ' ' << vPerdidas << endl << endl;
				act_ok = !CopiarUsuarios(lectura, escritura, "");
				lectura.close();
				escritura.close();
			}
		}
	}
	return act_ok;
}

bool ActReg_Bloq(string user_act)
{
	ifstream lectura;
	ofstream escritura;
	string user_reg, cont_reg;
	char peligroso;
	int nJugadores, nIngresos, nGanadas, nPerdidas , nEmpatadas, vGanadas, vPerdidas;
	bool act_ok = true;
	
	//1ª Copia
	act_ok = AbrirArchivos(lectura, arch_registro, escritura, arch_auxiliar);
	if (act_ok) {
		lectura >> user_reg >> cont_reg >> nJugadores >> nGanadas >> nPerdidas >> nEmpatadas >> vGanadas >> vPerdidas;
		escritura << user_reg << endl << cont_reg << endl << nJugadores << ' '
				  << nGanadas << ' ' << nPerdidas << ' ' << nEmpatadas << ' ' << vGanadas << ' ' << vPerdidas << endl << endl;
		
		act_ok = CopiarUsuarios(lectura, escritura, user_act);
		if (!act_ok) 
			cout << "El usuario no se encuentra en el registro" << endl;
		else {
			lectura >> peligroso >> cont_reg >> nIngresos >> nGanadas >> nPerdidas >> nEmpatadas >> vGanadas >> vPerdidas;
			escritura << user_act << ' ' << user_bloq << endl << cont_reg << endl
					  << nIngresos << ' ' << nGanadas << ' ' << nPerdidas << ' ' << nEmpatadas << ' ' << vGanadas << ' ' << vPerdidas << endl << endl;
			act_ok = !CopiarUsuarios(lectura, escritura, "");

			lectura.close();
			escritura.close();
			
			//2ª Copia
			act_ok = AbrirArchivos(lectura, arch_auxiliar, escritura, arch_registro);
			if (act_ok) {
				lectura >> user_reg >> cont_reg >> nJugadores >> nGanadas >> nPerdidas >> nEmpatadas >> vGanadas >> vPerdidas;
				escritura << user_reg << endl << cont_reg << endl
						  << nJugadores << ' ' << nGanadas << ' ' << nPerdidas << ' ' << nEmpatadas << ' ' << vGanadas << ' ' << vPerdidas << endl << endl;
				act_ok = !CopiarUsuarios(lectura, escritura, "");

				lectura.close();
				escritura.close();
			}
		}
	}
	return act_ok;
}

bool ActReg_Desbloq(string user_act, string cont_act)
{
	ifstream lectura;
	ofstream escritura;
	string user_reg, cont_reg;
	char peligroso;
	int nJugadores, nIngresos, nGanadas, nPerdidas , nEmpatadas, vGanadas, vPerdidas;
	bool act_ok = true;
	
	//1ª Copia
	act_ok = AbrirArchivos(lectura, arch_registro, escritura, arch_auxiliar);
	if (act_ok) {
		lectura >> user_reg >> cont_reg >> nJugadores >> nGanadas >> nPerdidas >> nEmpatadas >> vGanadas >> vPerdidas;
		escritura << user_reg << endl << cont_reg << endl << nJugadores << ' '
				  << nGanadas << ' ' << nPerdidas << ' ' << nEmpatadas << ' ' << vGanadas << ' ' << vPerdidas << endl << endl;
		
		act_ok = CopiarUsuarios(lectura, escritura, user_act);
		if (!act_ok) 
			cout << "El usuario no se encuentra en el registro" << endl;
		else {
			lectura >> peligroso >> cont_reg >> nIngresos >> nGanadas >> nPerdidas >> nEmpatadas >> vGanadas >> vPerdidas;
			escritura << user_act << ' ' << user_nbloq << endl;
			if (cont_act == "")	
				escritura << cont_reg << endl;
			else
				escritura << cont_act << endl;
			escritura << nIngresos << ' ' << nGanadas << ' ' << nPerdidas << ' ' << nEmpatadas << ' ' << vGanadas << ' ' << vPerdidas << endl << endl;
			act_ok = !CopiarUsuarios(lectura, escritura, "");

			lectura.close();
			escritura.close();
			
			//2ª Copia
			act_ok = AbrirArchivos(lectura, arch_auxiliar, escritura, arch_registro);
			if (act_ok) {
				lectura >> user_reg >> cont_reg >> nJugadores >> nGanadas >> nPerdidas >> nEmpatadas >> vGanadas >> vPerdidas;
				escritura << user_reg << endl << cont_reg << endl
						  << nJugadores << ' ' << nGanadas << ' ' << nPerdidas << ' ' << nEmpatadas << ' ' << vGanadas << ' ' << vPerdidas << endl << endl;
				act_ok = !CopiarUsuarios(lectura, escritura, "");

				lectura.close();
				escritura.close();
			}
		}
	}
	return act_ok;
}

bool ActReg_ActEstad(string user_act, int nIngExtra, int pGanExtra, int pPerdExtra, int pEmpExtra, int vGanExtra, int vPerdExtra)
{
	ifstream lectura;
	ofstream escritura;
	string user_reg, cont_reg;
	char peligroso;
	int nJugadores, nIngresos, nGanadas, nPerdidas , nEmpatadas, vGanadas, vPerdidas;
	bool act_ok = true;
	
	//1ª Copia
	act_ok = AbrirArchivos(lectura, arch_registro, escritura, arch_auxiliar);
	if (act_ok) {
		lectura >> user_reg >> cont_reg >> nJugadores >> nGanadas >> nPerdidas >> nEmpatadas >> vGanadas >> vPerdidas;
		escritura << user_reg << endl << cont_reg << endl << nJugadores << ' '
				  << nGanadas+pGanExtra << ' ' << nPerdidas+pPerdExtra << ' ' << nEmpatadas+pEmpExtra << ' ' << vGanadas+vGanExtra << ' ' << vPerdidas+vPerdExtra << endl << endl;
		
		act_ok = CopiarUsuarios(lectura, escritura, user_act);
		if (!act_ok) 
			cout << "El usuario no se encuentra en el registro" << endl;
		else {
			lectura >> peligroso >> cont_reg >> nIngresos >> nGanadas >> nPerdidas >> nEmpatadas >> vGanadas >> vPerdidas;
			escritura << user_act << ' ' << peligroso << endl << cont_reg << endl
					  << nIngresos+nIngExtra << ' ' << nGanadas+pGanExtra << ' ' << nPerdidas+pPerdExtra << ' ' << nEmpatadas+pEmpExtra << ' ' << vGanadas+vGanExtra << ' ' << vPerdidas+vPerdExtra << endl << endl;
			act_ok = !CopiarUsuarios(lectura, escritura, "");

			lectura.close();
			escritura.close();
			
			//2ª Copia
			act_ok = AbrirArchivos(lectura, arch_auxiliar, escritura, arch_registro);
			if (act_ok) {
				lectura >> user_reg >> cont_reg >> nJugadores >> nGanadas >> nPerdidas >> nEmpatadas >> vGanadas >> vPerdidas;
				escritura << user_reg << endl << cont_reg << endl
						  << nJugadores << ' ' << nGanadas << ' ' << nPerdidas << ' ' << nEmpatadas << ' ' << vGanadas << ' ' << vPerdidas << endl << endl;
				act_ok = !CopiarUsuarios(lectura, escritura, "");

				lectura.close();
				escritura.close();
			}

		}
	}
	return act_ok;
}

void CabeceraTabla(bool most_bloq, bool most_cont, bool most_estad)
{
	if (most_estad) {
		cout << setw(21) << ' ';
		if (most_bloq)
			cout << setw(5) << ' ';
		if (most_cont)
			cout << setw(11) << ' ';	
		cout << "    ---Spock--- --Dado-" << endl;
	}

	cout << setw(20) << "Apodo" << ' ';
	if (most_bloq)
		cout << "Bloq" << ' ';
	if (most_cont)
		cout << setw(10) << "Contraseña" << ' ';
	if (most_estad)
		cout << "Ing Gan Per Emp Gan Per";
	cout << endl;
}

void LineaTabla(bool most_bloq, bool most_cont, bool most_estad)
{
	cout << "_____________________";
	if (most_bloq)
		cout << "_____";
	if (most_cont)
		cout << "___________";
	if (most_estad)
		cout << "_______________________";
	cout << endl;
}

void FinTabla(string user_most, bool most_bloq, bool most_estad, int contador, int nJugadores, int pGanTotal, int pPerdTotal, int pEmpTotal, int vGanTotal, int vPerdTotal)
{
	if (user_most == "")
	{
		cout << setw(13) << "Mostrando: "<< setw(3) << contador <<"/"<< setw(3) << nJugadores;
		if (most_estad)
			cout << setw(17) << ' ' << setw(4) << ' ' << setw(3) << pGanTotal << ' ' << setw(3) << pPerdTotal 
					<< ' ' << setw(3) << pEmpTotal << ' ' << setw(3) << vGanTotal << ' ' << setw(3) << vPerdTotal;
		if (most_bloq)
			cout << endl << endl << "Usuario bloqueado: " << user_bloq << endl << "Usuario no bloqueado: " << user_nbloq << endl;
	}
}

bool MostrarReg(string user_most, bool solo_bloq, bool most_bloq, bool most_cont, bool most_estad)
{
	ifstream lectura;
	string user_reg, cont_reg;
	char peligroso;
	int nJugadores, nIngresos, pGanadas, pPerdidas, pEmpatadas, vGanadas, vPerdidas, pGanTotal, pPerdTotal, pEmpTotal, vGanTotal, vPerdTotal, contador = 0;
	bool mostrar_ok;

	CabeceraTabla(most_bloq, most_cont, most_estad);
	LineaTabla(most_bloq, most_cont, most_estad);

	lectura.open(arch_registro);
	if (!lectura.is_open()) {
		cout << "Error al abrir el archivo" << endl;
		mostrar_ok = false; }
	else
	{
		lectura >> user_reg >> cont_reg >> nJugadores >> pGanTotal >> pPerdTotal >> pEmpTotal >> vGanTotal >> vPerdTotal;
		lectura >> user_reg >> peligroso >> cont_reg >> nIngresos >> pGanadas >> pPerdidas >> pEmpatadas >> vGanadas >> vPerdidas;
		while (!lectura.eof())
		{
			if ( (!solo_bloq || peligroso == user_bloq) && (user_most == "" || user_most == user_reg) )
			{
				cout << setw(20) << user_reg << ' ';
				if (most_bloq)
					cout << setw(3) << peligroso << ' ' << ' ';
				if (most_cont)
					cout << setw(10) << cont_reg << ' ';
				if (most_estad)
					cout << setw(3) << nIngresos << ' ' << setw(3) << pGanadas << ' ' << setw(3) << pPerdidas << ' ' << setw(3) << pEmpatadas << ' ' << setw(3) << vGanadas << ' ' << setw(3) << vPerdidas;
				cout << endl;
				contador++;
			}
			lectura >> user_reg >> peligroso >> cont_reg >> nIngresos >> pGanadas >> pPerdidas >> pEmpatadas >> vGanadas >> vPerdidas;
		}

		LineaTabla(most_bloq, most_cont, most_estad);
		FinTabla(user_most, most_bloq, most_estad, contador, nJugadores, pGanTotal, pPerdTotal, pEmpTotal, vGanTotal, vPerdTotal);
		cout << endl;
		lectura.close();
		mostrar_ok = true;
	}
	return mostrar_ok;
}

//LogIn
bool ComprobarString(string str_introd, bool is_cont)
{
	bool str_ok = true;

	if (is_cont)
		if (str_introd.length()<8 || str_introd.length()>10)
			str_ok = false;

	for (unsigned int i=0; str_ok && i < str_introd.length(); i++)
		if (isspace(str_introd[i]))
			str_ok = false;

	return str_ok;
}

void CrearRegistro()
{
	ofstream escritura;
	string cont_introd;

	cout << "No se encuentra el registro. Se procedera a crear uno nuevo." << endl
		 << "Por favor, introduzca su nombre: ";
	cin >> cont_introd;

	escritura.open(arch_registro);
	if (!escritura.is_open())
		cout << "No se puede crear el archivo." << endl;
	else
	{
		escritura << user_admin << endl << cont_introd << endl << "0 0 0 0 0 0" << endl << endl;
		escritura.close();
		cout << "Se ha registrado como Administrador." << endl
			 << "Usuario: " << user_admin << endl
			 << "Contraseña: " << cont_introd << endl;
	}
}

tLogIn PedirContraseña(tLogIn tipo_user, string user_reg, string cont_reg)
{
	unsigned short int cont_intentos = 2;
	string cont_introd;
	bool salir = false;

	cout << "Por favor, introduzca la contraseña: ";
	cin >> cont_introd;
	while (!salir)
	{
		if (cont_intentos == 0 ) {
			cout << "Has fallado demasiadas veces. No puedes entrar" << endl;
			if (tipo_user == jugador)
				ActReg_Bloq(user_reg);
			tipo_user = error;
			salir = true; }

		else if (cont_introd == cont_reg) {
			cout << "Contraseña correcta. Bienvenido, " << user_reg << endl;
			salir = true; }

		else {
			cout << "Contraseña incorrecta. Le quedan " << cont_intentos << " intentos: ";
			cin >> cont_introd;
			cont_intentos--; }
	}
	return tipo_user;
}

tLogIn NuevaContraseña(tAccReg tipo_acc, string user_introd)
{
	string cont_introd;
	bool str_ok, act_ok;
	tLogIn devolver;

	if (tipo_acc == new_user)
		cout << "Su usuario no se encuentra registrado." << endl;
	else if (tipo_acc == camb_cont)
		cout << "Su usuario ha sido recientemente desbloqueado." << endl;
	cout << "Por favor, escoja una contraseña: ";
	cin.sync();
	getline(cin, cont_introd);
	str_ok = ComprobarString(cont_introd, true);
	while (!str_ok)
	{
		cout << "La contraseña debe tener entre 8 y 10 caracteres y no puede contener blancos." << endl
			 << "Por favor, introduzca otra: ";
		cin.sync();
		getline(cin, cont_introd);
		str_ok = ComprobarString(cont_introd, true);
	}
	if (tipo_acc == new_user)
		act_ok = ActReg_NewUser(user_introd, cont_introd);
	else if (tipo_acc == camb_cont)
		act_ok = ActReg_CambCont(user_introd, cont_introd);
	if (act_ok)
		devolver = jugador;
	else
		devolver = error;
	return devolver;

}

void LogIn(tLogIn& logIn, string& user_reg)
{
	ifstream lectura;
	char peligroso;
	int nJugadores, nIngresos, pGanadas, pPerdidas , pEmpatadas, vGanadas, vPerdidas;
	string cont_reg, user_introd;
	bool str_ok,
		 salir = false;

	lectura.open(arch_registro);
	if  ( !lectura.is_open() ) { //No se puede abrir. Crear administrador
		CrearRegistro();
		logIn = admin;
		user_reg = user_admin; }
	else {
		cout << "Por favor, introduzca su apodo: ";
		cin.sync();
		getline(cin, user_introd);
		str_ok = ComprobarString(user_introd, false);
		while (!str_ok)
		{
			cout << "El apodo no puede tener blancos. Por favor, introduzca otro: ";
			cin.sync();
			getline(cin, user_introd);
			str_ok = ComprobarString(user_introd, false);
		}
		lectura >> user_reg >> cont_reg >> nJugadores >> pGanadas >> pPerdidas >> pEmpatadas >> vGanadas >> vPerdidas;
		if (user_reg == user_introd) //Usuario encontrado (administrador)
			logIn = PedirContraseña(admin, user_admin, cont_reg);
		else {
			lectura >> user_reg >> peligroso >> cont_reg >> nIngresos >> pGanadas >> pPerdidas >> pEmpatadas >> vGanadas >> vPerdidas;
			while (!salir) {
				if (lectura.eof()) { //Usuario no encontrado. Actualizar registro
					logIn = NuevaContraseña(new_user, user_introd);
					user_reg = user_introd;
					salir = true; }

				else if (user_reg == user_introd) { //Usuario encontrado (jugador)
					if (peligroso == user_bloq) {
						cout << "Tu usuario se encuentra bloqueado. No puedes jugar." << endl;
						logIn = error; }
					else if (cont_reg == cont_neutra) 
						logIn = NuevaContraseña(camb_cont, user_introd);
					else
						logIn = PedirContraseña(jugador, user_reg, cont_reg);
					salir = true;
				}

				else //Leer siguiente
					lectura >> user_reg >> peligroso >> cont_reg >> nIngresos >> pGanadas >> pPerdidas >> pEmpatadas >> vGanadas >> vPerdidas;
			}
		}
	}
}

//Menus
void MenuPrincipal()
{
	cout << "1 - Jugar a Piedra-Papel-Tijera-Lagarto-Spock" << endl
		 << "2 - Ver instrucciones de Piedra-Papel-Tijera-Lagarto-Spock" << endl
		 << "3 - Jugar a Voltear el Dado" << endl
		 << "4 - Ver instrucciones de Voltear el Dado" << endl
		 << "5 - Ver estadísticas" << endl
		 << "0 - Salir" << endl
		 << "Opción: ";
}

void MenuAdmin()
{
	cout << "1 - Ver registro completo" << endl
		 << "2 - Ver usuarios bloqueados" << endl
		 << "3 - Cambiar contraseña" << endl
		 << "4 - Bloquear usuario" << endl
		 << "5 - Desbloquear usuario" << endl
		 << "0 - Salir" << endl
		 << "Opción: ";
}

void MenuDesbloqAdmin()
{
	cout << "¿Qué desea hacer?" << endl
		 << "1 - Desbloquear y reestablecer contraseña anterior" << endl
		 << "2 - Desbloquear y cambiar contraseña" << endl
		 << "3 - Desbloquear y permitir al usuario escoger nueva contraseña" << endl
		 << "Opción: ";
}

void MenuDificultadDado()
{
	cout << "Elige la dificultad de la máquina:" << endl
		 << "1 - Fácil" << endl
		 << "2 - Media" << endl
		 << "3 - Difícil" << endl
		 << "Opción:";
}

void CabeceraPortal()
{
	cout << endl
		 << "+--------------------------------------+" << endl
		 << "|    BIENVENIDO AL PORTAL DE JUEGOS    |" << endl
		 << "+--------------------------------------+" << endl
		 << endl;
}

void CabeceraPPTLS()
{
	cout << endl
		 << "  Piedra - Papel - Tijera - Lagarto - Spock  " << endl
		 << "_____________________________________________" << endl
		 << endl;
}

void CabeceraVoltDado()
{
	cout << endl
		 << "       Voltear el dado       " << endl
		 << "_____________________________" << endl
		 << endl;
}

void CabeceraInstrucciones()
{
	cout << endl
		 << "       Instrucciones       " << endl
		 << "___________________________" << endl
		 << endl;
}

void CierreJugador(int pGanadas, int pPerdidas, int pEmpatadas, int vGanadas, int vPerdidas)
{
	cout << endl
		 << "Piedra-Papel-Tijera-Lagarto-Spock" << endl
		 << "Partidas jugadas: " << pGanadas + pPerdidas + pEmpatadas << endl
		 << "Partidas ganadas: " << pGanadas << endl
		 << "Partidas perdidas: " << pPerdidas << endl
		 << "Partidas empatadas: " << pEmpatadas << endl << endl
		 << "Voltear el dado" << endl
		 << "Partidas jugadas: " << vGanadas + vPerdidas << endl
		 << "Partidas ganadas: " << vGanadas << endl
		 << "Partidas perdidas: " << vPerdidas << endl
		 << "Hasta pronto!" << endl;
}

//Reglas
bool MostrarReglas(string archivo)
{	
	bool reglas_ok = true;
	ifstream lectura;
	string regla;

	lectura.open(archivo);
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

//Voltear el dado
void MostrarDado(short int cara_sup, short int cara_front, short int cara_lat, int contador)
{
	cout << "  ___ " << endl
		 << " / " << cara_sup << " /|" << endl
		 << "·---·" << cara_lat << "|" << "          " << "Contador: " << contador << endl
		 << "| " << cara_front << " |/" << endl
		 << "·---·" << endl;
}

void GirarDado(tGiro giro, short int& cara_sup, short int& cara_front, short int& cara_lat)
{
	short int aux;
	switch (giro) {
		case norte:
			aux = cara_sup;
			cara_sup = cara_front;
			cara_front = 7-aux;
			break;
		case sur:
			aux = cara_front;
			cara_front = cara_sup;
			cara_sup = 7-aux;
			break;
		case este:
			aux = cara_lat;
			cara_lat = cara_sup;
			cara_sup = 7-aux;
			break;
		case oeste:
			aux = cara_sup;
			cara_sup = cara_lat;
			cara_lat = 7-aux;
			break;
	}
}

void TurnoUser(short int& cara_sup, short int& cara_front, short int& cara_lat, int& contador, bool &salir)
{
	char opcion;
	do{
		cout << "Te toca" << endl << "Introduce el giro mediante un punto cardinal (N,S,E,O) " << endl
			 << "Introduce 1 para ver instrucciones" << endl
			 << "Introduce 0 para salir: ";

	cin >> opcion;
		while (opcion != 'N' && opcion != 'S' && opcion != 'E' && opcion != 'O' &&
			   opcion != 'n' && opcion != 's' && opcion != 'e' && opcion != 'o' && opcion != '1' && opcion != '0')
		{
			cout << "Opción no válida. Introduzca una opción permitida: ";
			cin >> opcion;
		}
		if (opcion == '1') {
			cout << endl;
			CabeceraInstrucciones();
			MostrarReglas(arch_reglas_VoltDado);
			cout << endl;}
	} while (opcion == '1');

	switch (opcion) {
		case 'n':
		case 'N': cout << "Has elegido norte" << endl; GirarDado(norte, cara_sup, cara_front, cara_lat); break;
		case 's':
		case 'S': cout << "Has elegido sur" << endl; GirarDado(sur, cara_sup, cara_front, cara_lat); break;
		case 'e':
		case 'E': cout << "Has elegido este" << endl; GirarDado(este, cara_sup, cara_front, cara_lat); break;
		case 'o':
		case 'O': cout << "Has elegido oeste" << endl; GirarDado(oeste, cara_sup, cara_front, cara_lat); break;
		case '0': salir = true; break;
	}
	contador += cara_sup;
}

void TurnoCompFacil(short int& cara_sup, short int& cara_front, short int& cara_lat, int& contador)
{
	cout << "Me toca" << endl;
	switch (rand()%4) {
		case 0: cout << "He elegido norte" << endl;
				GirarDado(norte, cara_sup, cara_front, cara_lat);
				break;

		case 1: cout << "He elegido sur" << endl;
				GirarDado(sur, cara_sup, cara_front, cara_lat);
				break;

		case 2: cout << "He elegido este" << endl;
				GirarDado(este, cara_sup, cara_front, cara_lat);
				break;

		case 3: cout << "He elegido oeste" << endl;
				GirarDado(oeste, cara_sup, cara_front, cara_lat);
				break;
	}
	contador += cara_sup;
}

void TurnoCompMedia(short int& cara_sup, short int& cara_front, short int& cara_lat, int& contador)
{
	cout << "Me toca" << endl;
	if (cara_sup == 1 || cara_sup == 6)
		if (cara_front == 2) {
			cout << "He elegido norte" << endl;
			GirarDado(norte, cara_sup, cara_front, cara_lat); }
		else if (cara_front == 5) {
			cout << "He elegido sur" << endl;
			GirarDado(sur, cara_sup, cara_front, cara_lat); }
		else if (cara_lat == 2) {
			cout << "He elegido oeste" << endl;
			GirarDado(oeste, cara_sup, cara_front, cara_lat); }
		else /*(cara_lat == 5)*/ {
			cout << "He elegido este" << endl;
			GirarDado(este, cara_sup, cara_front, cara_lat); }
	else
		if (cara_front == 1) {
			cout << "He elegido norte" << endl;
			GirarDado(norte, cara_sup, cara_front, cara_lat); }
		else if (cara_front == 6) {
			cout << "He elegido sur" << endl;
			GirarDado(sur, cara_sup, cara_front, cara_lat); }
		else if (cara_lat == 1) {
			cout << "He elegido oeste" << endl;
			GirarDado(oeste, cara_sup, cara_front, cara_lat); }
		else /*(cara_lat == 6)*/ {
			cout << "He elegido este" << endl;
			GirarDado(este, cara_sup, cara_front, cara_lat); }

	contador += cara_sup;
}

bool EstudiarCaso(short int posicion, short int modulo, short int dejar_cara, short int& cara_sup, short int& cara_front, short int& cara_lat, int& contador)
{
	bool he_girado = false;
	if (modulo != 0 && contador+posicion<50)
	{
		if ( (contador+cara_front) % modulo == posicion && (dejar_cara == 0 || cara_front==dejar_cara || cara_front==(7-dejar_cara)) ) {
			cout << "He elegido norte" << endl;
			GirarDado(norte, cara_sup, cara_front, cara_lat);
			he_girado = true; }
		else if ( (contador+(7-cara_front)) % modulo == posicion && (dejar_cara == 0 || cara_front==dejar_cara || cara_front==(7-dejar_cara)) ) {
			cout << "He elegido sur" << endl;
			GirarDado(sur, cara_sup, cara_front, cara_lat);
			he_girado = true; }
		else if ( (contador+cara_lat) % modulo == posicion && (dejar_cara == 0 || cara_lat==dejar_cara || cara_lat==(7-dejar_cara)) ) {
			cout << "He elegido oeste" << endl;
			GirarDado(oeste, cara_sup, cara_front, cara_lat);
			he_girado = true; }
		else if ( (contador+(7-cara_lat)) % modulo == posicion && (dejar_cara == 0 || cara_lat==dejar_cara || cara_lat==(7-dejar_cara)) ) {
			cout << "He elegido este" << endl;
			GirarDado(este, cara_sup, cara_front, cara_lat);
			he_girado = true; }
	}
	else if (modulo == 0)
	{
		if ( contador+cara_front == posicion && (dejar_cara == 0 || cara_front==dejar_cara || cara_front==(7-dejar_cara)) ) {
			cout << "He elegido norte" << endl;
			GirarDado(norte, cara_sup, cara_front, cara_lat);
			he_girado = true; }
		else if ( contador+(7-cara_front) == posicion && (dejar_cara == 0 || cara_front==dejar_cara || cara_front==(7-dejar_cara)) ) {
			cout << "He elegido sur" << endl;
			GirarDado(sur, cara_sup, cara_front, cara_lat);
			he_girado = true; }
		else if ( contador+cara_lat == posicion && (dejar_cara == 0 || cara_lat==dejar_cara || cara_lat==(7-dejar_cara)) ) {
			cout << "He elegido oeste" << endl;
			GirarDado(oeste, cara_sup, cara_front, cara_lat);
			he_girado = true; }
		else if ( contador+(7-cara_lat) == posicion && (dejar_cara == 0 || cara_lat==dejar_cara || cara_lat==(7-dejar_cara)) ) {
			cout << "He elegido este" << endl;
			GirarDado(este, cara_sup, cara_front, cara_lat);
			he_girado = true; }
	}
	return he_girado;
}

void TurnoCompDificil(short int& cara_sup, short int& cara_front, short int& cara_lat, int& contador)
{
	bool he_girado = false;
	cout << "Me toca" << endl;
	
	//Ir a posicion ganadora (4 mod9)
	he_girado = EstudiarCaso(4, 9, 0, cara_sup, cara_front, cara_lat, contador);

	//Ir a posicion semiganadora (8 mod9 dejando 2 ó 5)
	if (!he_girado) {
		he_girado = EstudiarCaso(8, 9, 2, cara_sup, cara_front, cara_lat, contador);

	//Ir a posicion semiganadora (0,1,5 mod9 dejando 3 ó 4)
	if (!he_girado) {
		he_girado = EstudiarCaso(0, 9, 3, cara_sup, cara_front, cara_lat, contador);
	if (!he_girado) {
		he_girado = EstudiarCaso(1, 9, 3, cara_sup, cara_front, cara_lat, contador);
	if (!he_girado) {
		he_girado = EstudiarCaso(5, 9, 3, cara_sup, cara_front, cara_lat, contador);

	//Ir a posicion semiganadora (48 dejando 1 ó 6)
	if (!he_girado) {
		he_girado = EstudiarCaso(48, 0, 1, cara_sup, cara_front, cara_lat, contador);

	//Ir a posicion perdidora (2,3,6,7 mod9)
	if (!he_girado) {
		switch (rand()%4) {
			case 0: cout << "He elegido norte" << endl;
					GirarDado(norte, cara_sup, cara_front, cara_lat);
					break;
			case 1: cout << "He elegido sur" << endl;
					GirarDado(sur, cara_sup, cara_front, cara_lat);
					break;
			case 2: cout << "He elegido este" << endl;
					GirarDado(este, cara_sup, cara_front, cara_lat);
					break;
			case 3: cout << "He elegido oeste" << endl;
					GirarDado(oeste, cara_sup, cara_front, cara_lat);
					break;
		}
	}}}}}}
	contador += cara_sup;
}

void PartidaDado(unsigned short int dificultad, short int& cara_sup, short int& cara_front, short int& cara_lat, int& contador, bool& turno_user, bool& salir)
{
	switch (dificultad) {
	case 1: //Fácil
		while (contador<50 && !salir) {
			if (turno_user) {
				TurnoUser(cara_sup, cara_front, cara_lat, contador, salir);
				MostrarDado(cara_sup, cara_front, cara_lat, contador);
				turno_user = false; }
			else {
				TurnoCompFacil(cara_sup, cara_front, cara_lat, contador);
				MostrarDado(cara_sup, cara_front, cara_lat, contador);
				turno_user = true; }
			cout << endl; }
		break;

	case 2: //Media
		while (contador<50 && !salir) {
			if (turno_user) {
				TurnoUser(cara_sup, cara_front, cara_lat, contador, salir);
				MostrarDado(cara_sup, cara_front, cara_lat, contador);
				turno_user = false; }
			else {
				TurnoCompMedia(cara_sup, cara_front, cara_lat, contador);
				MostrarDado(cara_sup, cara_front, cara_lat, contador);
				turno_user = true; }
			cout << endl; }
		break;

	case 3: //Difícil
		while (contador<50 && !salir) {
			if (turno_user) {
				TurnoUser(cara_sup, cara_front, cara_lat, contador, salir);
				MostrarDado(cara_sup, cara_front, cara_lat, contador);
				turno_user = false; }
			else {
				TurnoCompDificil(cara_sup, cara_front, cara_lat, contador);
				MostrarDado(cara_sup, cara_front, cara_lat, contador);
				turno_user = true; }
			cout << endl; }
		break;
	}
}

void JugarDado(int& vGanadas, int& vPerdidas)
{
	short int cara_sup, cara_front, cara_lat;
	unsigned short int dificultad;
	int contador;
	bool turno_user, salir = false;

	MenuDificultadDado();
	cin >> dificultad;
	while (dificultad > 3) {
		cout << "Opción no válida. Introduzca una opción permitida: ";
		cin >> dificultad; }

	//Lanza dado y elige turno
	cara_sup = rand()%6 +1;
	if (cara_sup == 1 || cara_sup == 6) {
		cara_front = 2;
		cara_lat = 3; }
	else if (cara_sup == 2 || cara_sup == 5) {
		cara_front = 1;
		cara_lat = 3; }
	else { //cara_sup == 3 || cara_sup == 4
		cara_front = 1;
		cara_lat = 2; }

	if (rand()%2 == 0) turno_user = true;
	else turno_user = false;

	contador = cara_sup;
	cout << "Dado lanzado" << endl;
	MostrarDado(cara_sup, cara_front, cara_lat, contador);

	PartidaDado(dificultad, cara_sup, cara_front, cara_lat, contador, turno_user, salir);

	if (!salir) {
		if (turno_user) {
			cout << "Has ganado!" << endl;
			vGanadas++; }
		else {
			cout << "Has perdido!" << endl;
			vPerdidas++; }
	}
}

//Piedra-Papel-Tijera-Lagarto-Spock
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

void CalculoGanador(unsigned short int jug_comp, unsigned short int jug_user, int& pGanadas, int& pPerdidas, int& pEmpatadas)
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

void JugarPPTLS(int& pGanadas, int& pPerdidas, int& pEmpatadas)
{
	unsigned short int jug_comp, jug_user;
	/*piedra=0, papel=1, tijera=2, spock=3, lagarto=4 */

	jug_comp = rand()%5;
	cout << "He elegido mi jugada" << endl; //Eleccion del ordenador
	jug_user = EleccionUser(); //Elección del usuario
	CalculoGanador(jug_comp, jug_user, pGanadas, pPerdidas, pEmpatadas); //Evaluación del ganador
	MostrarJugadas(jug_comp, jug_user); //El ordenador muestra las elecciones
}

//Interfaces
void InterfazUser(string user) 
{
	int pGanadas = 0,
		pEmpatadas = 0,
		pPerdidas = 0,
		vGanadas = 0,
		vPerdidas = 0;
	unsigned short int opcion;
	bool lectura_ok = true;
	srand(time(NULL));
	
	//Menú principal
	CabeceraPortal();
	MenuPrincipal();
	cin >> opcion;

	while (opcion != 0) {
		while (opcion >= 6){
			cout << "Opción no válida. Introduzca una opción permitida: ";
			cin >> opcion; }
	
		switch (opcion) {
			case 1: CabeceraPPTLS();
					JugarPPTLS(pGanadas, pPerdidas, pEmpatadas);
					break;

			case 2: CabeceraInstrucciones();
					lectura_ok = MostrarReglas(arch_reglas_PPTLS);
					break;

			case 3: CabeceraVoltDado();
					JugarDado(vGanadas, vPerdidas);
					break;

			case 4: CabeceraInstrucciones();
					lectura_ok = MostrarReglas(arch_reglas_VoltDado);
					break;

			case 5: lectura_ok = MostrarReg(user, false, false, false, true);
					cout << endl << "Las estadísticas corresponden a la última vez que se cerró el programa" << endl;
					break;
		}
		cout << endl << "......................." << endl;
		MenuPrincipal();
		cin >> opcion; 
	}
	lectura_ok = ActReg_ActEstad(user, 1, pGanadas, pPerdidas, pEmpatadas, vGanadas, vPerdidas);
	CierreJugador(pGanadas, pPerdidas, pEmpatadas, vGanadas, vPerdidas);
}

void CambiarCont()
{
	bool str_ok, lectura_ok;
	string user, cont;
	
	cout << "Introduzca el apodo del usuario: ";
	cin >> user;
	cout << "Introduzca la nueva contraseña: ";
	cin.sync();
	getline(cin, cont);
	str_ok = ComprobarString(cont, true);
	while (!str_ok)
	{
		cout << "La contraseña debe tener entre 8 y 10 caracteres y no puede contener blancos." << endl
				<< "Por favor, introduzca otra: ";
		cin.sync();
		getline(cin, cont);
		str_ok = ComprobarString(cont, true);
	}
	lectura_ok = ActReg_CambCont(user, cont);
	if (lectura_ok)
		cout << "Contraseña cambiada" << endl;
}

void DesbloqUser()
{
	unsigned short int opcion_cont;
	bool str_ok, lectura_ok;
	string user, cont;

	cout << "Introduzca el apodo del usuario: ";
	cin >> user;
	MenuDesbloqAdmin();
	cin >> opcion_cont;
	while (opcion_cont < 1 || 3 < opcion_cont) {
		cout << "Opción no válida. Introduzca una opción permitida: ";
		cin >> opcion_cont; }
	switch (opcion_cont) {
		case 1:
			lectura_ok = ActReg_Desbloq(user, "");
			break;
		case 2:
			cout << "Escoja una nueva contraseña: ";
			cin.sync();
			getline(cin, cont);
			str_ok = ComprobarString(cont, true);
			while (!str_ok)
			{
				cout << "La contraseña debe tener entre 8 y 10 caracteres y no puede contener blancos." << endl
						<< "Por favor, introduzca otra: ";
				cin.sync();
				getline(cin, cont);
				str_ok = ComprobarString(cont, true);
			}
			lectura_ok = ActReg_Desbloq(user, cont);
			break;
		case 3:
			lectura_ok = ActReg_Desbloq(user, cont_neutra);
			break;
	}
	if (lectura_ok)
		cout << "Usuario desbloqueado" << endl;
}

void InterfazAdmin()
{
	unsigned short int opcion;
	bool lectura_ok = true;
	string user, cont;

	MenuAdmin();
	cin >> opcion;
	cout << endl;

	while (opcion != 0) {
		while (opcion > 5) {
			cout << "Opción no válida. Introduzca una opción permitida: ";
			cin >> opcion; }
		
		switch (opcion) {
			case 1:	lectura_ok = MostrarReg("", false, true, true, true); break;
			case 2: lectura_ok = MostrarReg("", true, true, false, false); break;
			case 3: CambiarCont(); break;

			case 4:
				cout << "Introduzca el apodo del usuario: ";
				cin >> user;
				lectura_ok = ActReg_Bloq(user);
				if (lectura_ok)
					cout << "Usuario bloqueado" << endl;
				break;

			case 5: DesbloqUser(); break;
		}
		cout << endl << "......................." << endl;
		MenuAdmin();
		cin >> opcion;
		cout << endl;
	}
}


//PROGRAMA PRINCIPAL
int main ()
{
	setlocale(LC_ALL,"");
	tLogIn tipo_user;
	string apodo_user;
	char fin;
	
	LogIn(tipo_user, apodo_user);
	switch (tipo_user) {
		case jugador: 
			InterfazUser(apodo_user);
			break;
		case admin:   
			InterfazAdmin();
			break;
	}
	
	cout << endl << "(Pulsa Intro para salir)";
	cin.sync();
	cin.get(fin);
	return 0;
}