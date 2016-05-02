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
	int porta; // 0- Não tem porta, 1 - Tem porta.... Se tem porta não pode ter parede!!! 
	Jogador *jogador;
	public:
		CelulaMapa();
		void setMonstro();
		void setParede();
		void setObjecto();
		void setPorta();
};

#endif