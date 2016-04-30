#include "Util.h"



#define N_MAX_LEITORES 10

HANDLE PipeLeitores[N_MAX_LEITORES];
HANDLE hPipe;
int total;
BOOL fim = FALSE;

DWORD WINAPI RecebeLeitores(LPVOID param);
DWORD WINAPI AtendeCliente(LPVOID param);


int _tmain(int argc, LPTSTR argv[]) {
	#ifdef UNICODE
		_setmode(_fileno(stdin), _O_WTEXT);
		_setmode(_fileno(stdout), _O_WTEXT);
		_setmode(_fileno(stderr), _O_WTEXT);
	#endif
	
	DWORD n;
	HANDLE hThread;
	Jogo j;

	utils();

	//Thread para novos jogadores
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecebeLeitores, NULL, 0, NULL);

	do {
		tcout << endl << TEXT("[SERVIDOR] Frase: ");
		tcin >> j.cmd;
		
		if (_tcscmp(j.cmd,TEXT("")) != 0) 
		{
			for (int i = 0; i < total; i++)
				if (!WriteFile(PipeLeitores[i], (LPCVOID)&j, sizeof(j), &n, NULL))
				{
					tcout << TEXT("[ERRO] Escrever no pipe!") << endl;
					exit(-1);
				}
		}
	}while (_tcscmp(j.cmd, TEXT("fim")) != 0);
	
	fim = TRUE;

	//Esperar a thread recebeLeitores terminar
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	exit(0);
}

DWORD WINAPI RecebeLeitores(LPVOID param) {
	HANDLE hPipe;

	while (!fim && total < N_MAX_LEITORES)
	{
		tcout << TEXT("[SERVIDOR] Vou criar pipe!") << endl;

		PipeLeitores[total] = CreateNamedPipe(PIPE_LEITURA, PIPE_ACCESS_OUTBOUND, PIPE_WAIT | PIPE_TYPE_MESSAGE
			| PIPE_READMODE_MESSAGE, N_MAX_LEITORES, TAM * sizeof(TCHAR), TAM * sizeof(TCHAR),
			1000, NULL);
		
		if (PipeLeitores[total] == INVALID_HANDLE_VALUE) 
		{
			tcout << TEXT("[ERRO] na ligação ao leitor!") << endl;
			exit(-1);
		}
		
		hPipe = CreateNamedPipe(PIPE_ESCRITA, PIPE_ACCESS_INBOUND, PIPE_WAIT | PIPE_TYPE_MESSAGE
			| PIPE_READMODE_MESSAGE, N_MAX_LEITORES, TAM * sizeof(TCHAR), TAM * sizeof(TCHAR),
			1000, NULL);
		
		if (hPipe == INVALID_HANDLE_VALUE) 
		{
			tcout << TEXT("[ERRO] na ligação ao leitor!") << endl;
			exit(-1);
		}

		tcout << TEXT("[SERVIDOR] Esperar ligação de leitor!") << endl;
		if (!ConnectNamedPipe(PipeLeitores[total], NULL)) 
		{
			tcout << TEXT("[ERRO] na ligação ao leitor!") << endl;
			exit(-1);
		}

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AtendeCliente, (LPVOID)hPipe, 0, NULL);
		total++;
	}

	for (int i = 0; i < total; i++) 
	{
		DisconnectNamedPipe(PipeLeitores[i]);
		tcout << TEXT("[SERVIDOR] Desligar pipe!") << endl;
		CloseHandle(PipeLeitores[i]);
	}
	return 0;
}

DWORD WINAPI AtendeCliente(LPVOID param) {
	HANDLE pipe = (HANDLE)param;
	Jogo j;
	DWORD n;
	int ret;

	tcout << j.cmd;
	
	while (1) 
	{
		ret = ReadFile(pipe, (LPVOID)&j, sizeof(j), &n, NULL);
		
		if (n > 0 && j.cmd != TEXT("")) 
		{
			tcout << TEXT("[SERVIDOR] Recebi - ") << j.cmd;
			
			for (int i = 0; i < total; i++) 
				WriteFile(PipeLeitores[i], (LPCVOID)&j, sizeof(j), &n, NULL);
		}
	}
	return 0;
}