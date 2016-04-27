#include "DungeonRPG\Util.h"

DWORD WINAPI EnviaComando(LPVOID param);
DWORD WINAPI RecebeComando(LPVOID param);

int _tmain(int argc, LPTSTR argv[]){

	HANDLE hPipeLeitura, hPipeEscrita;
	HANDLE hThreadRecebe, hThreadEnvia;
	DWORD n;
	Jogo j;

	utils();

	tcout << TEXT("[CLIENTE] Esperar pelo pipe!") << endl;
	if (!WaitNamedPipe(PIPE_LEITURA, NMPWAIT_WAIT_FOREVER)) 
	{
		tcout << TEXT("[ERRO] Ligar ao pipe!") << endl;
		exit(-1);
	}

	tcout << TEXT("[CLIENTE] Ligação ao servidor!") << endl;

	hPipeLeitura = CreateFile(PIPE_LEITURA, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPipeLeitura == NULL) 
	{
		tcout << TEXT("[ERRO] Ligar ao pipe!") << endl;
		exit(-1);
	}

	hPipeEscrita = CreateFile(PIPE_ESCRITA, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPipeEscrita == NULL) 
	{
		tcout << TEXT("[ERRO] Ligar ao pipe!") << endl;
		exit(-1);
	}

	//Thread que envia e recebe dados
	hThreadEnvia = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)EnviaComando, (LPVOID)hPipeEscrita, 0, NULL);
	hThreadRecebe = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecebeComando, (LPVOID)hPipeLeitura, 0, NULL);

	tcout << TEXT("[CLIENTE] Liguei-me!") << endl;


	WaitForSingleObject(hThreadEnvia, INFINITE);
	WaitForSingleObject(hThreadRecebe, INFINITE);

	CloseHandle(hPipeEscrita);
	CloseHandle(hPipeLeitura);

	

	Sleep(200);
	return 0;
}

//Envia comandos

DWORD WINAPI EnviaComando(LPVOID param) {

	HANDLE pipe = (HANDLE)param;
	DWORD n;
	Jogo j;

	while (1)
	{
		tcout << TEXT("\n[CLIENTE] Frase: ");
		tcin >> j.cmd;
		WriteFile(pipe, (LPCVOID)&j, sizeof(j), &n, NULL);
	}
	return 0;
}

//Recebe comando

DWORD WINAPI RecebeComando(LPVOID param) {

	HANDLE pipe = (HANDLE)param;
	DWORD n;
	BOOL ret;
	Jogo j;

	while (1)
	{
		ret = ReadFile(pipe, (LPVOID)&j, sizeof(j), &n, NULL);
		if (n > 0)
		{
			if (!ret || !n)
				break;
			tcout << TEXT("[CLIENTE] Recebi - ") << j.cmd;
		}
	}

	return 0;
}
