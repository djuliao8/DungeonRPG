#include "Util.h"
#include "Objectos.h"

//Classe que representa um jogador

class Jogador{
	int saude,lentidao;
	tstring nome;
	vector <Objectos *> obj;
	public:
		Jogador(tstring n); 
};