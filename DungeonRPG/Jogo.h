#include "DungeonComunicacao\Comunicacao.h"
#include "Mapa.h"


class Jogo{
	Mapa *mapa;
	vector<tstring> cmdValidos = {TEXT("criar"), TEXT("juntar")}; //Irá ter mais
	tstring comandoLido;
	vector<tstring> BufferComandoLido;
	int EstadoDeJogo = 0; // 0 - Ainda não começou, 1 - Já foi criado ou já se juntou a um jogo 
	public:
		void Jogar();
		bool Comandos(tstring cmd);		
};