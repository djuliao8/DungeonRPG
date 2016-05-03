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

void Mapa::colocaJogadorRandom(){
	int posicao;
	do{
		posicao = rand() % (linhas*colunas);
	} while (celula[posicao].getParede() == 1 || celula[posicao].getPorta() == 1);
	celula[posicao].setJogador();
}

Mapa::~Mapa(){
	delete[] celula;
}


