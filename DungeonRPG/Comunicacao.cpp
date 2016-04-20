#include "Comunicacao.h"

const tstring Comunicacao::NamedPipeEscrita = TEXT("\\\\.\\pipe\\PIPE_ESCRITA");
const tstring Comunicacao::NamedPipeLeitura = TEXT("\\\\.\\pipe\\PIPE_LEITURA");

Comunicacao::Comunicacao()
{
	hServerPipeEscrita = NULL;
	hServerPipeLeitura = NULL;

	if (!WaitNamedPipe(NamedPipeEscrita.c_str(), NMPWAIT_WAIT_FOREVER))
	{
		tcout << TEXT("[ERRO] Ligar ao pipe de escrita!");
		terminaComunicacao();
	}
	hServerPipeEscrita = CreateFile(NamedPipeEscrita.c_str(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (!WaitNamedPipe(NamedPipeLeitura.c_str(), NMPWAIT_WAIT_FOREVER))
	{
		tcout << TEXT("[ERRO] Ligar ao pipe de leitura!");
		terminaComunicacao();
	}
	hServerPipeLeitura = CreateFile(NamedPipeLeitura.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hServerPipeEscrita == NULL || hServerPipeLeitura == NULL)
	{
		terminaComunicacao();
	}

	DWORD dwMode = PIPE_READMODE_MESSAGE;

	if (!SetNamedPipeHandleState(hServerPipeEscrita, &dwMode, NULL, NULL))
	{
		terminaComunicacao();
	}

	tcout << TEXT("[INFO] Comunicacao ligada!");

}

Comunicacao::~Comunicacao()
{
	terminaComunicacao();
}

bool Comunicacao::enviaComando(tstring linhaComando)
{
	if (hServerPipeEscrita == NULL)
		return false;

	DWORD nBytesWrite;

	if (!WriteFile(hServerPipeEscrita, linhaComando.c_str(), linhaComando.size() * sizeof(TCHAR), &nBytesWrite, NULL))
		return false;

	return true;
}

tstring Comunicacao::recebeComando() 
{
	tstring comando = TEXT("");
	DWORD nBytesRead;

	if (hServerPipeLeitura == NULL)
		return comando;

	ReadFile(hServerPipeLeitura, &comando, sizeof(tstring), &nBytesRead, NULL);

	return comando;
}



void Comunicacao::terminaComunicacao()
{
	if (hServerPipeEscrita != NULL)
		CloseHandle(hServerPipeEscrita);

	if (hServerPipeLeitura != NULL)
		CloseHandle(hServerPipeLeitura);
}
