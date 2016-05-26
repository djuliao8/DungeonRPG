#ifndef JOGO_HEADER
#define JOGO_HEADER
#include "Mapa.h"
#include "Util.h"


class Jogo{
	Mapa * mapa;
	vector<Jogador> jogEmJogo;
	bool aDecorrer;
	bool jogoCriado;
	bool predefinido;

	public:
		Jogo(int lin,int col,bool pre);
		Jogo();
		void addJogador(Jogador j);
		bool removeJogador(Jogador j);
		void setADecorrer(bool aDecorrer);
		bool getJogoADecorrer();
		bool getJogoCriado();
		void setJogoCriado(bool jogoCriado);
		bool verificaJogador(Jogador j);
		int getNumJogadores();
		bool getPredefinido();
		void setPredefinido(bool predefinido);

		tstring açãoJogador(tstring movimento,Jogador j);
		tstring moveJogador(Jogador j,tstring movimento,int posX, int posY);
		tstring apanharObjecto(Jogador j);
		tstring proxMovimento(Jogador j);
		tstring posActual(Jogador j);
		tstring usarPedra(Jogador j, tstring cmd);
		tstring lutaJogador(Jogador j);
		tstring lutaEntreJogadores(Jogador j1, Jogador j2);

		bool jogadorInPos(int x, int y);
		void actualizaVector(Jogador j,int i);
		void colocaJogadores();
		void enviaMensagem(tstring msg,HANDLE hPipe);

		Jogador getJogadorByNome(Jogador j);
		Jogador getJogadorByPos(int x, int y);
		Jogador getJogadorByPosInArray(int pos);

		DWORD WINAPI terminaJogo(LPVOID param);
		void iniciaThread();
};

#endif