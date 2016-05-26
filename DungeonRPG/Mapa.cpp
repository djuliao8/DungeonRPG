#include "Mapa.h"

//Classe Mapa

Mapa::Mapa(int lin, int col,bool pre) 
{
	linhas = lin;
	colunas = col;
	celula = new CelulaMapa[lin * col];
	for (int i = 0; i < lin; i++) 
	{		
		for (int j = 0; j < col; j++) 
		{
			if (i == 0 || j == 0 || i == (lin - 1) || j == (col - 1))
				getCelula(i,j).setParede();
		}
	}
	if (pre)
		mapaPredefinido();
	else
		mapaRandom();

	mostraMapa();
}
void Mapa::mostraMapa()
{
	for (int i = 0; i < linhas;i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			if (getCelula(i, j).asParede())
				tcout << TEXT("1");
			else
				tcout << TEXT("0");
		}
	}
}

int Mapa::getLinhas() 
{
	return linhas;
}

void Mapa::mapaPredefinido() 
{ //Função que cria um mapa pré-definido
	for (int i = 0; i < linhas; i++) 
	{
		for (int j = 0; j < colunas; j++) 
		{
			if (!getCelula(i, j).asParede())
			{
				if(i % 2 == 0 && j % 3 == 0)
					getCelula(i, j).setParede();
				getCelula(i, j).setObjecto();
			}
		}
	}
}

void Mapa::mapaRandom()
{
	/*for (int i = 1; i < linhas - 1; i++)
	{
		for (int j = 1; j < colunas - 1; j++)
		{
			if (celula[i][j].getParede() == 0)
			{

			}
		}
	}*/
}

bool Mapa:: verificaParede(int x, int y)
{
	return getCelula(x, y).asParede();
}

int Mapa::getColunas() 
{
	return colunas;
}

Objectos Mapa::getObjecto(int x,int y)
{
	return getCelula(x, y).getObjecto();
}

void Mapa::removeObjecto(int x, int y)
{
	getCelula(x, y).removeObjecto();
}

CelulaMapa &Mapa::getCelula(int lin, int col) 
{
	return celula[lin * colunas + col];
}

Mapa::~Mapa() 
{
	delete[] celula;
}



