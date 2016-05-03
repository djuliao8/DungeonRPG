#ifndef JOGADOR_HEADER
#define JOGADOR_HEADER

#include "Objectos.h"
#include "Util.h"



//Classe que representa um jogador

class Jogador{
	int saude,lentidao;
	tstring nome;
	tstring pass;
	HANDLE hPipeEnviar;
	HANDLE hPipeReceber;
	HANDLE hThread;
	vector <Objectos *> obj;
	bool autenticado;
	int estado;

	public:
		Jogador(HANDLE hPipeEnviar,HANDLE hPipeReceber);
		HANDLE getHPipeEnviar();
		HANDLE getHPipeReceber();
		int getEstado();
		bool getAutenticado();
		void setHThread(HANDLE hThread);

};

#endif