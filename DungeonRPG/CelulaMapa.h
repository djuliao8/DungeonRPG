#ifndef CELULA_HEADER
#define CELULA_HEADER

#include "Util.h"
#include "Jogador.h"
#include "Monstro.h"
#include "Objectos.h"
//Classe que representa cada Celula do Mapa

class CelulaMapa{ 
	Monstro *monstro;
	Objectos *objecto;
	int parede;// 0 - Não tem parede, 1 - Tem parede
	Jogador *jogador;
	public:
		CelulaMapa();
};

#endif