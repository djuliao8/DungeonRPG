#include "Util.h"
#include "Jogador.h"

#define N_MAX_LEITORES 10

vector<Jogador> jogadores;
int total;
BOOL fim = FALSE;

DWORD WINAPI RecebeJogadores(LPVOID param);
DWORD WINAPI AtendeCliente(LPVOID param);
Jogador * getJogadorByPipe(HANDLE hPipe);

Msg errorMsg(TCHAR * error)
{
	Msg msg;
	msg.erro = true;
	wcscpy_s(msg.cmd, error);
	return msg;
}

bool autenticaUser(TCHAR * user) {
	tstring line;
	tfstream myfile("login.txt");

	if (myfile.good())
	{
		while (getline(myfile, line))
		{
			if (_tcscmp(line.c_str(), user) == 0)
				return true;
		}
		myfile.close();
	}
	return false;
}

//Recebe comando
TCHAR * recebeMensagem(HANDLE hPipe)
{
	TCHAR cmd[TAM];
	DWORD n;

	ReadFile(hPipe, cmd, 1024 * sizeof(TCHAR), &n, NULL);
	cmd[n / sizeof(TCHAR)] = '\0';

	if (n > 0) {
		tcout << cmd;
		return cmd;
	}
	return TEXT("Erro!");
}

bool validaComando(tstring cmd)
{
	const vector<tstring> cmdValidos = { TEXT("criar"), TEXT("juntar"),TEXT("login") };

	for (int i = 0; i < (int)cmdValidos.size(); i++)
		if (cmdValidos[i] == cmd)
			return true;
	return false;
}

Jogador * getJogadorByPipe(HANDLE hPipe)
{
	for (int i = 0; i < (int)jogadores.size(); i++)
	{
		if (jogadores[i].getHPipeReceber() == hPipe)
			return &jogadores[i];
	}

	return nullptr;
}

Msg executaComando(TCHAR * cmd, Jogador * jogador) { //Este comando tem de vir da comunicação do cliente!
	TCHAR aux[TAM] = TEXT("");
	vector<tstring> BufferComandoLido;
	Msg msg;

	//Colocar tudo em minusculas
	for (int i = 0; i < (int)_tcslen(cmd); i++)
		cmd[i] = tolower(cmd[i]);

	//Separa a string
	tstring comandoLido = cmd;

	itstringstream iss(comandoLido);
	while (iss)
	{
		tstring subCom;
		iss >> subCom;
		if (subCom != TEXT(""))
			BufferComandoLido.push_back(subCom);
	}

	//Valida comando do Cliente
	if (validaComando(BufferComandoLido[0]))
	{
		//Estado login
		if (jogador->getEstado() == LOGIN)
		{
			if (BufferComandoLido[0] == TEXT("login") && BufferComandoLido.size() == 3)
			{
				wcscat_s(aux, BufferComandoLido[1].c_str());
				wcscat_s(aux, TEXT(":"));
				wcscat_s(aux, BufferComandoLido[2].c_str());

				if (autenticaUser(aux))
				{
					jogador->setNome(BufferComandoLido[1]);
					jogador->setPass(BufferComandoLido[2]);
					jogador->setEstado(QUEROJOGAR);
					msg = errorMsg(TEXT(" Login efectuado com sucesso!"));
					return msg;
				}
				else
				{
					msg = errorMsg(TEXT(" Login sem sucesso! Username ou password errada!"));
					return msg;
				}

			}
			else
			{
				msg = errorMsg(TEXT("Comando mal construído ou não aceite!"));
				return msg;
			}
		}
		else if (jogador->getEstado() == QUEROJOGAR)
		{
			/*if (BufferComandoLido[0] == TEXT("criar") && BufferComandoLido.size() == 3) { //Validar comando e número de argumentos
			if (BufferComandoLido[1] == TEXT("pre")) {
			mapa = new Mapa(70, 70); //Valor pré-definido
			}
			else {
			mapa = new Mapa(stoi(TEXT("" + BufferComandoLido[1])), stoi(TEXT("" + BufferComandoLido[2]))); //stoi converte para int
			}
			} if (BufferComandoLido[0] == TEXT("juntar") && BufferComandoLido.size() == 1) {

			}*/

		}

		else if (jogador->getEstado() == AJOGAR)
		{

		}
	}
	else
	{
		wcscat_s(aux, BufferComandoLido[0].c_str());
		wcscat_s(aux, TEXT(" - O comando é inválido!"));
		msg = errorMsg(aux);
	}

	return msg;
}

void enviaMensagem(Msg msg, HANDLE hPipeEnviar)
{
	if (hPipeEnviar == NULL)
		return;

	DWORD n;
	WriteFile(hPipeEnviar, &msg, sizeof(msg), &n, NULL);
}



DWORD WINAPI AtendeCliente(LPVOID param) {
	TCHAR cmd[TAM];
	HANDLE hPipe = (HANDLE)param;
	Jogador * j = getJogadorByPipe(hPipe);

	//j->setHThread(GetCurrentThread());

	do {

		//Recebe mensagem cliente
		wcscpy_s(cmd, recebeMensagem(j->getHPipeReceber()));

		//Verifica / executa comando
		Msg msg = executaComando(cmd, j);

		//Envi resposta
		enviaMensagem(msg, j->getHPipeEnviar());

	} while (_tcscmp(cmd, TEXT("sair")) != 0);

	return 0;
}



DWORD WINAPI RecebeJogadores(LPVOID param) {
	HANDLE hPipeEnviar, hPipeReceber;

	while (!fim && jogadores.size() < N_MAX_LEITORES)
	{
		tcout << TEXT("[SERVIDOR] Cria pipes!") << endl;

		hPipeEnviar = CreateNamedPipe(PIPE_LEITURA, PIPE_ACCESS_OUTBOUND, PIPE_WAIT | PIPE_TYPE_MESSAGE
			| PIPE_READMODE_MESSAGE, N_MAX_LEITORES, TAM * sizeof(TCHAR), TAM * sizeof(TCHAR),
			1000, NULL);

		hPipeReceber = CreateNamedPipe(PIPE_ESCRITA, PIPE_ACCESS_INBOUND, PIPE_WAIT | PIPE_TYPE_MESSAGE
			| PIPE_READMODE_MESSAGE, N_MAX_LEITORES, TAM * sizeof(TCHAR), TAM * sizeof(TCHAR),
			1000, NULL);

		tcout << TEXT("[SERVIDOR] Esperar ligação do jogador!") << endl;
		if (!ConnectNamedPipe(hPipeEnviar, NULL))
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

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AtendeCliente, (LPVOID)hPipeReceber, 0, NULL);
	}


	return 0;
}

int _tmain(int argc, LPTSTR argv[]) {
	HANDLE hThread;

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif

	//Thread para novos jogadores
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecebeJogadores, NULL, 0, NULL);
	//Esperar a thread recebeJogadores terminar
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	exit(0);
}