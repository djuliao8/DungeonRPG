#ifndef COMUNICACAO_H
#define COMUNICACAO_H

#include "DungeonRPG\Util.h"


class Comunicacao
{
	static const tstring NamedPipeEscrita;
	static const tstring NamedPipeLeitura;

	void terminaCliente();
	HANDLE hServerPipeEscrita;
	HANDLE hServerPipeLeitura;
public:
	static const tstring getNomeNamedPipeEscrita();
	static const tstring getNomeNamedPipeLeitura();

	Comunicacao();
	~Comunicacao();
	bool enviaComando(tstring linhaComando);
	bool recebeMensagem(ptrMensagemJogo & mJ);
};


#endif