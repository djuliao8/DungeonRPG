#include "Monstro.h"

Monstro::Monstro(){
	tipo = rand() % 1;
	if (tipo == 0){ //Distraído
		saude = 5;
		lentidao = 3;
	}
	else{ //Bully
		saude = 15;
		lentidao = 7;
	}
}

