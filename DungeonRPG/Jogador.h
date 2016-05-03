#ifndef JOGADOR_HEADER
#define JOGADOR_HEADER

#include "Util.h"
#include "Objectos.h"



//Classe que representa um jogador

class Jogador {
	int saude, lentidao;
	tstring nome;
	tstring pass;
	HANDLE hPipeEnviar;
	HANDLE hPipeReceber;
	HANDLE hThread;
	vector <Objectos *> obj;
	int estado;

public:
	Jogador(HANDLE hPipeEnviar, HANDLE hPipeReceber);
	HANDLE getHPipeEnviar();
	HANDLE getHPipeReceber();
	int getEstado();
	void setEstado(int estado);
	tstring getNome();
	void setPass(tstring pass);
	void setNome(tstring nome);
	void setHThread(HANDLE hThread);
	void addObjecto();
	void efeitosObjectos();
};

#endif