#ifndef MAPA_HEADER
#define MAPA_HEADER
#include "CelulaMapa.h"

class Mapa { //Conjunto de CelulaMapa's
	CelulaMapa *celula;
	int linhas, colunas;
public:
	Mapa(int lin, int col,bool pre);
	int getColunas();
	int getLinhas();
	void mapaPredefinido();
	void mapaRandom();
	CelulaMapa &getCelula(int lin, int col);
	bool verificaParede(int x, int y);
	~Mapa();
	void mostraMapa();
	Objectos getObjecto(int x,int y);
	void removeObjecto(int x,int y);
};

#endif