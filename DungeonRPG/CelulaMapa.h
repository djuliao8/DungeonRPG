#include "Util.h"
#include "Monstro.h"
#include "Objectos.h"
#include "Jogador.h"

//Classe que representa cada Celula do Mapa

class CelulaMapa{ 
	Monstro *monstro;
	Objectos *objecto;
	int parede;// 0 - Não tem parede, 1 - Tem parede
	Jogador *jogador;
	public:
		CelulaMapa();
};