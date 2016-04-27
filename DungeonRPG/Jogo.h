#include "Util.h"
#include "Mapa.h"

#define LOGIN 0
#define QUEROJOGAR 1
#define AJOGAR 2
class Jogo{
	Mapa *mapa;
	vector<tstring> cmdValidos = {TEXT("criar"), TEXT("juntar")}; //Irá ter mais
	tstring comandoLido;
	vector<tstring> BufferComandoLido; 
	int EstadoDeJogo;
	public:
		void Jogar();
		bool Comandos(tstring cmd);		
};