#ifndef MONSTRO_HEADER
#define MONSTRO_HEADER

#include <iostream>
#include <string>
#include <tchar.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
//Classe que representa cada monstro

class Monstro{
	int tipo; // 0 - Distraído, 1 - Bully
	int saude, lentidao;
	public:
		Monstro();
};

#endif