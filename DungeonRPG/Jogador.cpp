#include "Jogador.h"

Jogador::Jogador(HANDLE hPipeEnviar,HANDLE hPipeReceber){
	lentidao = 5;
	saude = 10;
	autenticado = false;
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
bool Jogador::getAutenticado()
{
	return autenticado;
}
void Jogador::setHThread(HANDLE hThread)
{
	this->hThread = hThread;
}

