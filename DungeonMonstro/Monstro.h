#ifndef MONSTRO_HEADER
#define MONSTRO_HEADER

#include "MemoriaPartilhada.h"


//Número máximo de monstros no labirinto
#define N_MAX 100

//Classe que representa o Monstro

class Monstro{
	int lentidao;
	int tipo; // 0 - Distraido, 1 - Bully
	int posX, posY;
	HANDLE hMapFile;

	public:
		Monstro();
		~Monstro();
};
#endif