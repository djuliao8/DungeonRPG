#ifndef JOGADOR_HEADER
#define JOGADOR_HEADER

#include "Objectos.h"
#include "Util.h"

//Classe que representa um jogador

class Jogador{
	int saude,lentidao;
	tstring nome;
	vector <Objectos *> obj;
	public:
		Jogador(tstring n); 
};

#endif