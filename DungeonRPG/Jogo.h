#include "DungeonComunicacao\Comunicacao.h"
#include "Mapa.h"


class Jogo{
	Mapa *mapa;
	vector<tstring> cmdValidos = {TEXT("criar"), TEXT("juntar")}; //Ir� ter mais
	tstring comandoLido;
	vector<tstring> BufferComandoLido;
	int EstadoDeJogo = 0; // 0 - Ainda n�o come�ou, 1 - J� foi criado ou j� se juntou a um jogo 
	public:
		void Jogar();
		bool Comandos(tstring cmd);		
};