#ifndef JOGADOR_HEADER
#define JOGADOR_HEADER

#include "Util.h"
#include "Objectos.h"



//Classe que representa um jogador

class Jogador {
	int saude, lentidao;
	int posX, posY;
	tstring nome;
	tstring pass;
	HANDLE hPipeEnviar;
	HANDLE hPipeReceber;
	vector <Objectos> pedras;
	int estado;
	bool pedra;
	bool erro;
public:
	Jogador(HANDLE hPipeEnviar, HANDLE hPipeReceber);
	Jogador();

	HANDLE getHPipeEnviar();
	HANDLE getHPipeReceber();
	int getEstado();
	void setEstado(int estado);
	bool getErro();
	tstring getNome();
	tstring getPass();
	void setPass(tstring pass);
	void setNome(tstring nome);
	int getVida();
	bool isMorto();
	
	void setPedra(bool pedra);
	bool getPedra();
	void sofreDano(int dano);

	void usarVitaminas();
	void usarRebucado();
	void usarRedbull();

	bool addPedra(Objectos pedra);
	int numPedras();
	bool removePedra();

	void setPosX(int posX);
	void setPosY(int posY);
	int getPosX();
	int getPosY();
};

#endif