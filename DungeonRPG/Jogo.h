#ifndef JOGO_HEADER
#define JOGO_HEADER
#include "Mapa.h"

//Máquina de Estados
#define LOGIN 0
#define QUEROJOGAR 1
#define AJOGAR 2

class Jogo{
	Mapa *mapa;
	static const vector<tstring> cmdValidos; 
	tstring comandoLido;
	vector<tstring> BufferComandoLido; 
	int EstadoDeJogo = LOGIN;
	public:
		void Jogar();
		bool Comandos(tstring cmd);
		bool Autenticacao();
};

#endif