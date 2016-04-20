#ifndef COMUNICACAO_H
#define COMUNICACAO_H

#include "DungeonRPG\Util.h"


class Comunicacao
{
	static const tstring NamedPipeEscrita;
	static const tstring NamedPipeLeitura;

	void terminaComunicacao();
	HANDLE hServerPipeEscrita;
	HANDLE hServerPipeLeitura;
public:

	Comunicacao();
	~Comunicacao();
	bool enviaComando(tstring linhaComando);
	tstring recebeComando();
};


#endif