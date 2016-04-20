#include "Comunicacao.h"

const tstring Comunicacao::NamedPipeEscrita = TEXT("\\\\.\\pipe\\PIPE_ESCRITA");
const tstring Comunicacao::NamedPipeLeitura = TEXT("\\\\.\\pipe\\PIPE_LEITURA");

Comunicacao::Comunicacao()
{
	hServerPipeEscrita = NULL;
	hServerPipeLeitura = NULL;

	if (!WaitNamedPipe(NamedPipeEscrita.c_str(), NMPWAIT_WAIT_FOREVER))
	{
		
	}

	hServerPipeEscrita = CreateFile(NamedPipeEscrita.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);




}

void Comunicacao::terminaCliente()
{
	if (hServerPipeEscrita != NULL)
		CloseHandle(hServerPipeEscrita);

	if (hServerPipeLeitura != NULL)
		CloseHandle(hServerPipeLeitura);
}
