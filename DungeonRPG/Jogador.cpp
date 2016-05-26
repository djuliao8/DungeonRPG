#include "Jogador.h"

Jogador::Jogador(HANDLE hPipeEnviar, HANDLE hPipeReceber) {
	lentidao = 5;
	saude = 10;
	estado = LOGIN;
	pedra = false;
	this->hPipeEnviar = hPipeEnviar;
	this->hPipeReceber = hPipeReceber;
	pedras.clear();
	erro = false;
}

Jogador::Jogador()
{
	erro = true;
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
bool Jogador::getErro()
{
	return erro;
}
tstring Jogador::getNome()
{
	return nome;
}
tstring Jogador::getPass()
{
	return pass;
}
void Jogador::setNome(tstring nome)
{
	this->nome = nome;
}
void Jogador::setPass(tstring pass)
{
	this->pass = pass;
}

bool Jogador::addPedra(Objectos objecto)
{ //No máximo 15 pedras
	if (numPedras() <= 15) {
		pedras.push_back(objecto);
		return true;
	}
	return false;
}

bool Jogador::getPedra()
{
	return pedra;
}

void Jogador::setPedra(bool pedra)
{
	this->pedra = pedra;
}

int Jogador::numPedras()
{
	return (int)pedras.size();
}

bool Jogador::removePedra()
{
	if (numPedras() > 0)
	{
		pedras.pop_back();
		return true;
	}
	return false;
}

void Jogador::usarRebucado()
{

}

void Jogador::usarRedbull() 
{
	saude += 3;
}

void Jogador::usarVitaminas()
{
	saude += 1;
}

void Jogador::setPosX(int posX) 
{
	this->posX = posX;
}

void Jogador::setPosY(int posY) 
{
	this->posY = posY;
}

int Jogador::getPosX() 
{
	return posX;
}

int Jogador::getPosY() 
{
	return posY;
}

void Jogador::sofreDano(int dano)
{
	saude -= dano;
}

int Jogador::getVida()
{
	if (saude < 0)
		return 0;
	return saude;
}

bool Jogador::isMorto()
{
	if (saude <= 0)
		return true;
	return false;
}


