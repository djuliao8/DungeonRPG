#include "DungeonComunicacao\Comunicacao.h"
#include "Jogo.h"
#include "Mapa.h"

void Jogo::Jogar(){
	//Fazer uma thread para receber comandos

}

bool Jogo::Comandos(tstring cmd){ //Este comando tem de vir da comunicação do cliente!
	bool validade = false;
	comandoLido = cmd;
	//Colocar tudo em minusculas
	for (int i = 0; i < (int)comandoLido.size(); i++)
		comandoLido[i] = tolower(comandoLido[i]);
	//Dividir String
	itstringstream iss(comandoLido);
	BufferComandoLido.clear();
	while (iss){
		tstring subCom;
		iss >> subCom;
		if (subCom != TEXT(""))
			BufferComandoLido.push_back(subCom);
	}
	//Validar comando do Cliente
	for (int i = 0; i < cmdValidos.size(); i++){
		if (cmdValidos[i] == BufferComandoLido[0]){
			validade = true;
			break;
		}
	}
	if (!validade)
		tcout << "Comando não é válido";
	else{
		if (EstadoDeJogo == 0){
			//Tem de se colocar estados nos comandos, para que só admita certos comandos nos momentos certos do jogo
			if (BufferComandoLido[0] == TEXT("criar") && BufferComandoLido.size() == 3){ //Validar comando e número de argumentos
				if (BufferComandoLido[1] == TEXT("pre")){
					mapa = new Mapa(70, 70); //Valor pré-definido
					EstadoDeJogo = 1;
					return true;
				}
				else{
					mapa = new Mapa(stoi(TEXT("" + BufferComandoLido[1])), stoi(TEXT("" + BufferComandoLido[2]))); //stoi converte para int
					EstadoDeJogo = 1;
					return true;
				}
			} if (BufferComandoLido[0] == TEXT("juntar") && BufferComandoLido.size() == 1){
				EstadoDeJogo = 1;
				//do stuff
			}
		}
		//... outros comandos!
	}
	
	return false;
}


