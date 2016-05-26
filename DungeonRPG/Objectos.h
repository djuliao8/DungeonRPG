#ifndef OBJECTOS_HEADER
#define OBJECTOS_HEADER

#include "Util.h"
//Classe que representa cada objecto

class Objectos{
	tstring nome;
	public:
		Objectos();
		Objectos(tstring nome);
		tstring getNomeObjecto();
};

#endif