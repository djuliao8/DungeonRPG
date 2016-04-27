#include "Jogo.h"
#include "Mapa.h"

void Jogo::Jogar(){
	//Fazer uma thread para receber comandos

}

bool Jogo::autenticacao(){
	tstring line;
	tfstream myfile("login.txt");
	if (myfile.good()){
		while (getline(myfile, line)) {
			if (line == BufferComandoLido[0]){
				return true;
			}
		}
		myfile.close();
	}
	return false;
}

bool Jogo::Comandos(tstring cmd){ //Este comando tem de vir da comunicação do cliente!
	bool validade = false;
	comandoLido = cmd;
	//Colocar tudo em minusculas
	for (int i = 0; i < (int)comandoLido.size(); i++)
		comandoLido[i] = tolower(comandoLido[i]);
	
	BufferComandoLido.clear();
	//Validar comando do Cliente
	if (EstadoDeJogo != LOGIN){
		//Dividir String
		itstringstream iss(comandoLido);
		while (iss){
			tstring subCom;
			iss >> subCom;
			if (subCom != TEXT(""))
				BufferComandoLido.push_back(subCom);
		}
		for (int i = 0; i < cmdValidos.size(); i++){
			if (cmdValidos[i] == BufferComandoLido[0]){
				validade = true;
				break;
			}
		}
	}
	else{
		validade = true;
		BufferComandoLido.push_back(cmd);
	}
	if (!validade)
		tcout << "Comando não é válido";
	else{
		if (EstadoDeJogo == LOGIN){
			if (autenticacao()){ //Enviar cliente a avisar que o cliente foi autenticado
				EstadoDeJogo = QUEROJOGAR;
				return true;
			}
			else return false; //Avisar cliente que a autenticacao falhou
		}
		if (EstadoDeJogo == QUEROJOGAR){
			//Tem de se colocar estados nos comandos, para que só admita certos comandos nos momentos certos do jogo
			if (BufferComandoLido[0] == TEXT("criar") && BufferComandoLido.size() == 3){ //Validar comando e número de argumentos
				if (BufferComandoLido[1] == TEXT("pre")){
					mapa = new Mapa(70, 70); //Valor pré-definido
					EstadoDeJogo = AJOGAR;
					return true;
				}
				else{
					mapa = new Mapa(stoi(TEXT("" + BufferComandoLido[1])), stoi(TEXT("" + BufferComandoLido[2]))); //stoi converte para int
					EstadoDeJogo = AJOGAR;
					return true;
				}
			} if (BufferComandoLido[0] == TEXT("juntar") && BufferComandoLido.size() == 1){
				EstadoDeJogo = 1;
				//do stuff
			}
		}
		if (EstadoDeJogo = AJOGAR){
			//... outros comandos!
		}
		
	}
	
	return false;
}


