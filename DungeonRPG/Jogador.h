#ifndef JOGADOR_HEADER
#define JOGADOR_HEADER

#include "Objectos.h"
#include "Util.h"

//Classe que representa um jogador

class Jogador{
	int saude,lentidao, posicao;
	tstring nome;
	vector <Objectos> obj;
	public:
		Jogador();
		Jogador(tstring n); 
		void addObjecto();
		void efeitosObjectos();
};

#endif