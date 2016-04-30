#include "Util.h"
#include "Objectos.h"



//Classe que representa um jogador

class Jogador{
	int saude,lentidao;
	tstring nome;
	tstring pass;
	HANDLE hPipeEnviar;
	HANDLE hPipeReceber;
	HANDLE hThread;
	vector <Objectos *> obj;
	bool autenticado;
	int estado;

	public:
		Jogador(HANDLE hPipeEnviar,HANDLE hPipeReceber);
		HANDLE getHPipeEnviar();
		HANDLE getHPipeReceber();
		int getEstado();
		bool getAutenticado();
		void setHThread(HANDLE hThread);

};