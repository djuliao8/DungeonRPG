#ifndef MAPA_HEADER
#define MAPA_HEADER
#include "CelulaMapa.h"

class Mapa{ //Conjunto de CelulaMapa's
	CelulaMapa *celula;
    int linhas, colunas;
	public:
		Mapa(int lin, int col);
};

#endif