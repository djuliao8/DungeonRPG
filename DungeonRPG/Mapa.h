#include "DungeonComunicacao\Comunicacao.h"
#include "CelulaMapa.h"

class Mapa{ //Conjunto de CelulaMapa's
	CelulaMapa *celula;
    int linhas, colunas;
	public:
		Mapa(int lin, int col);
};