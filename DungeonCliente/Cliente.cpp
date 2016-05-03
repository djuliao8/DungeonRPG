#include "Util.h"


HANDLE hPipeLeitura, hPipeEscrita;
HANDLE hThreadRecebe;
HANDLE hMutex;
bool threadActiva = true;
bool modoScroll = false;

void iniciaPipes();
void intro();
bool enviaComando(TCHAR * cmd);
DWORD WINAPI RecebeMensagem(LPVOID param);

int _tmain(int argc, LPTSTR argv[]) {
	tstring cmd;
	TCHAR tcmd[TAM];
	TCHAR tecla;

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	//Cria mutex
	hMutex = CreateMutex(NULL, FALSE, NULL);

	//Inicia o pipe de escrita e leitura 
	iniciaPipes();

	// Inicia a thread para receber
	hThreadRecebe = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecebeMensagem, (LPVOID)hPipeLeitura, 0, NULL);

	//Apresenta mensagem do jogo
	intro();

	do
	{
		//if (!modoScroll)
		//{
			fflush(stdin);
			getline(tcin, cmd);

			if (cmd == TEXT("scroll"))
			{
				modoScroll = true;
				cmd = TEXT("scroll 0 0");
			}
		/*}
		else
		{
			tecla = c.getch();

			if (tolower(tecla) == TEXT('c'))
			{
				modoScroll = false;
			}

			switch (tecla)
			{
			case c.CIMA: cmd = TEXT("scroll -1 0"); break;
			case c.BAIXO: cmd = TEXT("scroll 1 0"); break;
			case c.DIREITA: cmd = TEXT("scroll 0 1"); break;
			case c.ESQUERDA: cmd = TEXT("scroll 0 -1"); break;
			default: cmd = TEXT("scroll 0 0");
			}
		}
		*/

		//Para passar de string para TCHAR
		_tcscpy(tcmd, cmd.c_str());

		//Envia comando, se falhar sai
		enviaComando(tcmd);

	} while (cmd != TEXT("sair"));

	threadActiva = false;
	
	CloseHandle(hPipeEscrita);
	CloseHandle(hPipeLeitura);

	Sleep(200);
	return 0;
}

void intro() 
{
	tcout << TEXT("\n\n\t\t Dungeon RPG - Trabalho de SO2 \n\n\n");
	tcout << TEXT("\t Trabalho realizado por: \n\n");
	tcout << TEXT("\t\t David Julião - 21230100 \n");
	tcout << TEXT("\t\t Luís Antunes - 21230122 \n\n\n");
	tcout << TEXT("[CLIENTE] Comando > ");
}

void iniciaPipes() 
{

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

	tcout << TEXT("[CLIENTE] Liguei-me!") << endl;
}

//Envia comando

bool enviaComando(TCHAR *cmd) 
{
	if (hPipeEscrita == NULL)
		return false;

	DWORD n;
	if (!WriteFile(hPipeEscrita, cmd, _tcslen(cmd) * sizeof(TCHAR), &n, NULL))
		return false;
	return true;
}


//Recebe comando

DWORD WINAPI RecebeMensagem(LPVOID param) {
	DWORD n;
	Msg msg;

	while (threadActiva)
	{
		ReadFile((HANDLE)param, (LPVOID)&msg, sizeof(msg), &n, NULL);
		
		//FALTA GERIR A INFORMAÇÂO RECEBIDA

		tcout << TEXT("[CLIENTE] Recebi - ") << msg.cmd << endl;
		tcout << TEXT("[CLIENTE] Comando > ");
	}

	return 0;
}
