#include "CelulaMapa.h"


CelulaMapa::CelulaMapa(){	
	objecto = nullptr;
	jogador = nullptr;
}


void CelulaMapa::setParede(){
	parede = 1;
}

void CelulaMapa::setPorta(){
	porta = 1;
}

void CelulaMapa::setObjecto(){
	int aux = rand() % 15;
	if (aux == 0)
		objecto = new Objectos();
}

int CelulaMapa::getPorta(){
	return porta;
}

int CelulaMapa::getParede(){
	return parede;
}

void CelulaMapa::setJogador(){
	jogador = new Jogador();
}

