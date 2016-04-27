#include "DungeonComunicacao\Comunicacao.h"
#include "CelulaMapa.h"
#include "Mapa.h"

Mapa::Mapa(int lin, int col){
	linhas = lin;
	colunas = col;
	celula = new CelulaMapa[lin*col];
}