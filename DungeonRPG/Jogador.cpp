#include "Jogador.h"

Jogador::Jogador(HANDLE hPipeEnviar, HANDLE hPipeReceber) {
	lentidao = 5;
	saude = 10;
	estado = LOGIN;
	this->hPipeEnviar = hPipeEnviar;
	this->hPipeReceber = hPipeReceber;
	obj.clear();
}

HANDLE Jogador::getHPipeEnviar()
{
	return hPipeEnviar;
}
HANDLE Jogador::getHPipeReceber()
{
	return hPipeReceber;
}
int Jogador::getEstado()
{
	return estado;
}
void Jogador::setEstado(int estado)
{
	this->estado = estado;
}
tstring Jogador::getNome()
{
	return nome;
}
void Jogador::setNome(tstring nome)
{
	this->nome = nome;
}
void Jogador::setPass(tstring pass)
{
	this->pass = pass;
}
void Jogador::setHThread(HANDLE hThread)
{
	this->hThread = hThread;
}

void Jogador::addObjecto(){ //No máximo 15 pedras
}


void Jogador::efeitosObjectos(){
	/*for (int i = 0; i < obj.size(); i++){
		if (obj[i].getNomeObjecto() == TEXT("Rebuçado de Cafeína")){
			obj.pop_back();
			lentidao -= 2;
		}
		if (obj[i].getNomeObjecto() == TEXT("Vitaminas") && saude < 20){
				obj.pop_back();
				saude++;
		}else{
			if (obj[i].getNomeObjecto() == TEXT("Vitaminas") && saude >= 20)
				obj.pop_back();
			}
		if (obj[i].getNomeObjecto() == TEXT("Garrafa de OrangeBull") && saude < 20){
			obj.pop_back();
			saude += 3;
		}
		else{
			if (obj[i].getNomeObjecto() == TEXT("Garrafa de OrangeBull") && saude >= 20)
				obj.pop_back();
		}	
	}*/
}
