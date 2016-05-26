#ifndef CELULA_HEADER
#define CELULA_HEADER

#include "Util.h"
#include "Jogador.h"
#include "Objectos.h"
//Classe que representa cada Celula do Mapa

class CelulaMapa{ 
	Objectos objecto;
	int parede;// 0 - N�o tem parede, 1 - Tem parede
	int porta; // 0- N�o tem porta, 1 - Tem porta.... Se tem porta n�o pode ter parede!!! 


	public:
		CelulaMapa();
		void setParede();
		void setObjecto();
		Objectos getObjecto();
		void removeObjecto();
		void setPorta();
		int getPorta();
		bool asParede();
};

#endif