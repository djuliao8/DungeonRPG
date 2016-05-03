#include "Util.h"
#include "Jogador.h"



#define N_MAX_LEITORES 10

vector<Jogador> jogadores;
int total;
BOOL fim = FALSE;

DWORD WINAPI RecebeLeitores(LPVOID param);
DWORD WINAPI AtendeCliente(LPVOID param);


int _tmain(int argc, LPTSTR argv[]) {
	HANDLE hThread;

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	//Thread para novos jogadores
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecebeLeitores, NULL, 0, NULL);

		
	fim = TRUE;

	//Esperar a thread recebeLeitores terminar
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	exit(0);
}

DWORD WINAPI RecebeLeitores(LPVOID param) {
	HANDLE hPipeEnviar, hPipeReceber;

	while (!fim && jogadores.size() < N_MAX_LEITORES)
	{
		tcout << TEXT("[SERVIDOR] Vou criar pipe!") << endl;

		hPipeEnviar = CreateNamedPipe(PIPE_LEITURA, PIPE_ACCESS_OUTBOUND, PIPE_WAIT | PIPE_TYPE_MESSAGE
			| PIPE_READMODE_MESSAGE, N_MAX_LEITORES, TAM * sizeof(TCHAR), TAM * sizeof(TCHAR),
			1000, NULL);
		
		tcout << TEXT("[SERVIDOR] Esperar ligação de leitor!") << endl;
		if (!ConnectNamedPipe(hPipeEnviar, NULL))
		{
			tcout << TEXT("[ERRO] na ligação ao leitor!") << endl;
			exit(-1);
		}
		
		hPipeReceber = CreateNamedPipe(PIPE_ESCRITA, PIPE_ACCESS_INBOUND, PIPE_WAIT | PIPE_TYPE_MESSAGE
			| PIPE_READMODE_MESSAGE, N_MAX_LEITORES, TAM * sizeof(TCHAR), TAM * sizeof(TCHAR),
			1000, NULL);
		
		tcout << TEXT("[SERVIDOR] Esperar ligação de leitor!") << endl;
		if (!ConnectNamedPipe(hPipeReceber, NULL))
		{
			tcout << TEXT("[ERRO] na ligação ao leitor!") << endl;
			exit(-1);
		}

		if (hPipeReceber == INVALID_HANDLE_VALUE || hPipeEnviar == INVALID_HANDLE_VALUE)
		{
			tcout << TEXT("[ERRO] na ligação ao leitor!") << endl;
			exit(-1);
		}

		jogadores.push_back(Jogador(hPipeEnviar, hPipeReceber));

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AtendeCliente, (LPVOID)hPipeReceber,0, NULL);
	}


	return 0;
}

bool autenticaUser(TCHAR * user) {
	tstring line;
	tfstream myfile("login.txt");

	if (myfile.good()) 
	{
		while (getline(myfile, line)) 
	{
			if (_tcscmp(line.c_str(),user) == 0)
				return true;	
		}
		myfile.close();		
	}
	return false;
	}


TCHAR * recebeComando(HANDLE hPipe) {
	TCHAR cmd[TAM];
	DWORD n;

	ReadFile(hPipe, cmd, 1024 * sizeof(TCHAR), &n, NULL);

	if (n > 0 && cmd != TEXT(""))
		return cmd;
	return TEXT("Erro!");
}

DWORD WINAPI AtendeCliente(LPVOID param) {
	
	HANDLE hPipeReceber = (HANDLE)param;

	DWORD nBytes;
	TCHAR cmd[TAM];
	
	getJogadorByPipe(hPipeReceber)->setHThread(GetCurrentThread());

	do {
		ReadFile(hPipeReceber,cmd, 1024, &nBytes, NULL);
	
		cmd[nBytes / sizeof(TCHAR)] = '\0';
		
	} while ();
			
	return 0;
		}

Jogador * getJogadorByPipe(HANDLE hPipe) {
	for (int i = 0; i < (int)jogadores.size(); i++)
	{
		if (jogadores[i].getHPipeReceber() == hPipe)
			return &jogadores[i];
	}

	return nullptr;
}