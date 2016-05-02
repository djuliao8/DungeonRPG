#include "Mapa.h"

Mapa::Mapa(int lin, int col){
	linhas = lin;
	colunas = col;
	celula = new CelulaMapa[lin*col];
	for (int i = 0; i < lin*col; i++){
		celula[i].setObjecto();
	}
}
int Mapa::getLinhas(){
	return linhas;
}

int Mapa::getColunas(){
	return colunas;
}


CelulaMapa &Mapa::getCelula(int lin, int col){
	return celula[lin * colunas + col];
}

Mapa::~Mapa(){
	delete[] celula;
}


