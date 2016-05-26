#include "Util.h"
#include "Jogador.h"
#include "Jogo.h"

#define N_MAX_LEITORES 10

HANDLE hMutex = NULL;
vector<Jogador> jogadores;
Jogo j;
BOOL fim = FALSE;

DWORD WINAPI RecebeJogadores(LPVOID param);
DWORD WINAPI AtendeCliente(LPVOID param);
Jogador getJogadorByPipe(HANDLE hPipe);

void actualizaVector(Jogador j, int i)
{
	int pos = -1;
	for (int i = 0; i < (int)jogadores.size(); i++)
	{
		if (jogadores[i].getHPipeReceber() == j.getHPipeReceber())
			pos = i;
	}

	if (pos != -1)
	{
		jogadores.erase(jogadores.begin() + pos);
		jogadores.insert(jogadores.begin() + i, j);
	}
}

void actualizaInfoServer()
{
	for (int i = 0; i < (int)j.getNumJogadores();i++)
	{
		actualizaVector(j.getJogadorByPosInArray(i), 0);
	}

	for (int i = 0; i < (int)jogadores.size();i++)
	{
		if (jogadores[i].getEstado() == AJOGAR && !j.verificaJogador(jogadores[i]))
		{
			jogadores[i].setEstado(QUEROJOGAR);
			actualizaVector(jogadores[i],0);
		}
	}
}

DWORD WINAPI terminaJogo(LPVOID param)
{
	do
	{
		Sleep(300);
	} while (j.getNumJogadores() > 1);

	Jogador jogador = j.getJogadorByPosInArray(0);
	j.enviaMensagem(TEXT("Ganhou o jogo!"), jogador.getHPipeEnviar());

	for (int i = 0; i < (int)jogadores.size();i++)
	{
		jogadores[i].setEstado(QUEROJOGAR);
		actualizaVector(jogadores[i],i);
	}

	j = Jogo();

	return 0;
}

void iniciaThreadFimJogo()
{
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)terminaJogo, NULL, 0, NULL);
}

void actualizaInfoJogo()
{
	for (int i = 0; i < (int)jogadores.size();i++)
	{
		if (j.verificaJogador(jogadores[i]))
			j.actualizaVector(jogadores[i], 0);
	}
}

bool addJogador(tstring user,tstring pass)
{
	HKEY key;
	DWORD keyDword;
	TCHAR keyName[TAM] = REGISTRY_KEY;
	wcscat_s(keyName, user.c_str());

	if (RegCreateKeyEx(HKEY_CURRENT_USER, keyName, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, &keyDword) != ERROR_SUCCESS) {
		tcout << TEXT("Erro ao criar/abrir chave!");
		return false;
	}
	RegSetValueEx(key, TEXT("Nome"), 0, REG_SZ, (LPBYTE)user.c_str(), _tcslen(user.c_str())*sizeof(TCHAR));
	RegSetValueEx(key, TEXT("Pass"), 0, REG_SZ, (LPBYTE)pass.c_str(), _tcslen(pass.c_str())*sizeof(TCHAR));
	return true;
}
bool autenticaUser(tstring user, tstring pass)
{
	TCHAR key[TAM] = REGISTRY_KEY,password[TAM];
	HKEY hKey;
	DWORD size;

	wcscat_s(key, user.c_str());
	if (RegOpenKeyEx(HKEY_CURRENT_USER, key, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
	{
		RegQueryValueEx(hKey, TEXT("Pass"), NULL, NULL, (LPBYTE)password, &size);
		if (_tcscmp(password, pass.c_str()) == 0)
			return true;
		return false;
	}
	else
		return false;
}
bool verificaNome(tstring user)
{
	TCHAR key[TAM] = REGISTRY_KEY;
	HKEY hKey;

	wcscat_s(key, user.c_str());
	if (RegOpenKeyEx(HKEY_CURRENT_USER, key, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
		return false;
	return true;
}



void enviaMensagem(Msg msg, HANDLE hPipeEnviar)
{
	if (hPipeEnviar == NULL)
		return;

	DWORD n;
	WriteFile(hPipeEnviar, &msg, sizeof(msg), &n, NULL);
}

Msg errorMsg(TCHAR * error)
{
	Msg msg;
	msg.erro = true;
	wcsncpy_s(msg.cmd, error,_TRUNCATE);
	return msg;
}

//Envia mensagem para todos os jogadores que estão a jogar
void enviaMensagemParaTodos(TCHAR * aux,Jogador jogador)
{
	//Envia mensagem a todos os jogadores em queue
	for (int i = 0; i < (int)jogadores.size();i++)
	{
		if (j.verificaJogador(jogadores[i]) && jogadores[i].getNome() != jogador.getNome())
			enviaMensagem(errorMsg(aux), jogadores[i].getHPipeEnviar());
	}
}

void removeJogador(Jogador jogador) {
	int pos = -1;

	for (int i = 0; i < (int)jogadores.size(); i++)
	{
		if (jogadores[i].getNome() == jogador.getNome())
		{
			pos = i;
			CloseHandle(jogador.getHPipeEnviar());
			CloseHandle(jogador.getHPipeReceber());
		}
	}

	if (pos != -1)
	{
		jogadores.erase(jogadores.begin() + pos);
	}
}

void terminaJogador(Jogador jogador)
{
	int pos = -1;
	TCHAR aux[TAM] = TEXT("O jogador ");

	if (j.getJogoCriado() && !j.getJogoADecorrer())
	{
		//Remove jogador do jogo
		if (j.removeJogador(jogador))
		{
			//Envia mensagem
			if (j.getNumJogadores() > 0) 
			{
				//Cria mensagem a avisar de saida do jogo
				wcscat_s(aux, jogador.getNome().c_str());
				wcscat_s(aux, TEXT(" saiu do lobby!"));

				enviaMensagemParaTodos(aux,jogador);
			}
			else
			{
				//Faz reset ao jogo
				j = Jogo();
			}
		}		
	}
	else if (j.getJogoCriado() && j.getJogoADecorrer())
	{
		if (j.removeJogador(jogador))
		{
			if (j.getNumJogadores() > 1)
			{
				wcscat_s(aux, jogador.getNome().c_str());
				wcscat_s(aux, TEXT(" saiu do jogo!"));
				
				enviaMensagemParaTodos(aux, jogador);
			}
		}
	}
	removeJogador(jogador);
}

bool verificaLogado(tstring user) 
{
	for (int i = 0; i < (int)jogadores.size();i++)
	{
		if (jogadores[i].getNome() == user)
			return true;
	}
	return false;
}

void limpaJogador(Jogador jogador)
{
	int pos = -1;
	for (int i = 0; i < (int)jogadores.size();i++)
	{
		if (jogador.getHPipeReceber() == jogadores[i].getHPipeReceber())
			pos = i;
	}
	if (pos != -1)
	{
		jogador.setNome(TEXT(""));
		jogador.setPass(TEXT(""));
		jogador.setEstado(LOGIN);
		actualizaVector(jogador, 0);
	}
}
//Recebe comando
TCHAR * recebeMensagem(HANDLE hPipe)
{
	TCHAR cmd[TAM];
	DWORD n;

	if (!ReadFile(hPipe, cmd, 1024 * sizeof(TCHAR), &n, NULL))
	{
		Jogador j = getJogadorByPipe(hPipe);
		terminaJogador(j);
		return TEXT("thread");
	}
	cmd[n / sizeof(TCHAR)] = '\0';

	if (n > 0) {
		tcout << TEXT("[SERVIDOR] Comando: ") << cmd << endl;
		return cmd;
	}
	return TEXT("Erro!");
}

bool validaComando(tstring cmd)
{
	const vector<tstring> cmdValidos = { TEXT("criar"), TEXT("juntar"),TEXT("login"),TEXT("registo"),TEXT("começar"),TEXT("mover"),TEXT("pos"),TEXT("pedra"),TEXT("logout"),TEXT("sair")};

	for (int i = 0; i < (int)cmdValidos.size(); i++)
		if (cmdValidos[i] == cmd)
			return true;
	return false;
}


Jogador getJogadorByPipe(HANDLE hPipe)
{
	for (int i = 0; i < (int)jogadores.size(); i++)
	{
		if (jogadores[i].getHPipeReceber() == hPipe)
			return jogadores[i];
	}

	return Jogador();
}

Msg executaComando(TCHAR * cmd, Jogador jogador) { //Este comando tem de vir da comunicação do cliente!
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
		if (BufferComandoLido[0] == TEXT("sair"))
		{
			msg = errorMsg(TEXT("Irá sair do jogo!"));
			return msg;
		}
	
		//Estado login
		if (jogador.getEstado() == LOGIN)
		{
			if (BufferComandoLido[0] == TEXT("login") && BufferComandoLido.size() == 3)
			{

				if (autenticaUser(BufferComandoLido[1], BufferComandoLido[2]))
				{
					if (!verificaLogado(BufferComandoLido[1]))
					{
						jogador.setNome(BufferComandoLido[1]);
						jogador.setPass(BufferComandoLido[2]);
						jogador.setEstado(QUEROJOGAR);

						actualizaVector(jogador,0);

						msg = errorMsg(TEXT(" Login efectuado com sucesso!"));
						return msg;
					}
					else
					{
						msg = errorMsg(TEXT(" Login sem sucesso!Jogador já ligado!"));
						return msg;
					}
				}
				else
				{
					msg = errorMsg(TEXT(" Login sem sucesso! Username ou password errada!"));
					return msg;
				}

			}
			else if(BufferComandoLido[0] == TEXT("registo") && BufferComandoLido.size() == 3)
			{
				if (verificaNome(BufferComandoLido[1]))
				{
					if (addJogador(BufferComandoLido[1], BufferComandoLido[2]))
					{
						msg = errorMsg(TEXT("Registo feito com sucesso!"));
						return msg;
					}
					else
					{
						msg = errorMsg(TEXT("Registo não sucedido!"));
						return msg;
					}
				}
				else
				{
					msg = errorMsg(TEXT("Username já existente!"));
					return msg;
				}
			}
			else
			{
				msg = errorMsg(TEXT("Comando mal construído ou não aceite!"));
				return msg;
			}
		}
		else if (jogador.getEstado() == QUEROJOGAR)
		{
			if (BufferComandoLido[0] == TEXT("criar") && (BufferComandoLido.size() == 2 || BufferComandoLido.size() == 3))
			{
				if (!j.getJogoCriado())
				{
					if (BufferComandoLido[1] == TEXT("pre") && BufferComandoLido.size() == 2)
					{
						//Cria jogo
						j = Jogo(DEFAULT_MAPA, DEFAULT_MAPA,true);
						//Adiciona jogador que o criou ao jogo
						j.addJogador(jogador);
						j.setPredefinido(true);

						msg = errorMsg(TEXT("Jogo criado com dimensões default!"));
						return msg;
					}
					else if (BufferComandoLido.size() == 3)
					{
						int lin = stoi(TEXT("" + BufferComandoLido[1]));
						int col = stoi(TEXT("" + BufferComandoLido[2]));

						if (lin > 70 && col > 70 && lin < 150 && col < 150)
						{
							j = Jogo(lin, col,false);
							j.addJogador(jogador);
							j.setPredefinido(false);

							msg = errorMsg(TEXT("Jogo criado!"));
							return msg;
						}
						else
						{
							msg = errorMsg(TEXT("Dimensões do mapa erradas!"));
							return msg;
						}
					}
					else 
					{
						msg = errorMsg(TEXT("Comando mal construído!"));
						return msg;
					}
				}
				else
				{
					msg = errorMsg(TEXT("Jogo já criado! Só se pode juntar!"));
					return msg;
				}
			} 
			else if (BufferComandoLido[0] == TEXT("juntar") && BufferComandoLido.size() == 1)
			{
				if (!j.getJogoADecorrer())
				{
					if (j.getJogoCriado())
					{
						if (!j.verificaJogador(jogador))
						{
							j.addJogador(jogador);

							wcscpy_s(aux, TEXT("O jogador "));
							wcscat_s(aux, jogador.getNome().c_str());
							wcscat_s(aux, TEXT(" juntou-se ao jogo!"));

							for (int i = 0; i < (int)jogadores.size();i++)
							{
								if (j.verificaJogador(jogadores[i]))
								{	
									if (jogadores[i].getNome() != jogador.getNome())
										enviaMensagem(errorMsg(aux), jogadores[i].getHPipeEnviar());
								}
							}

							msg = errorMsg(TEXT("Juntou-se ao jogo com sucesso!"));
							return msg;
						}
						else
						{
							msg = errorMsg(TEXT("Não se pode Juntar! Já está no jogo!"));
							return msg;
						}
					}
					else
					{
						msg = errorMsg(TEXT("Não se pode Juntar! Necessário criar jogo!"));
						return msg;
					}
				}
				else
				{
					msg = errorMsg(TEXT("Não se pode juntar! Jogo já a decorrer!"));
					return msg;
				}
			}
			else if (BufferComandoLido[0] == TEXT("começar") && BufferComandoLido.size() == 1)
			{
				if (j.getJogoCriado() && !j.getJogoADecorrer())
				{
					if (j.verificaJogador(jogador))
					{
						if (j.getNumJogadores() >= 2)
						{
							iniciaThreadFimJogo();

							for (int i = 0; i < (int)jogadores.size();i++) 
							{
								if (j.verificaJogador(jogadores[i]))
								{
									jogadores[i].setEstado(AJOGAR);
									actualizaVector(jogadores[i],i);
								}
							}
							actualizaInfoJogo();

							enviaMensagemParaTodos(TEXT("Jogo iniciado!"), jogador);
							
							j.setADecorrer(true);
							j.colocaJogadores();							

							actualizaInfoServer();

							msg = errorMsg(TEXT("Jogo iniciado!"));
							return msg;
						}
						else
						{
							j = Jogo();
							msg = errorMsg(TEXT("Jogo não iniciado! Não havia pelo menos 2 jogadores!"));
							return msg;
						}
					}
					else
					{
						msg = errorMsg(TEXT("Não está no jogo! Junte-se primeiro!"));
						return msg;
					}
				}
				else
				{
					msg = errorMsg(TEXT("Jogo não criado ou já a decorrer!"));
					return msg;
				}
			}
			else if (BufferComandoLido[0] == TEXT("logout") && BufferComandoLido.size() == 1)
			{
				if (j.getJogoCriado() && !j.getJogoADecorrer())
				{
					//Remove jogador do jogo
					if (j.removeJogador(jogador))
					{
						//Envia mensagem
						if (j.getNumJogadores() > 0)
						{
							//Cria mensagem a avisar de saida do jogo
							wcscat_s(aux, jogador.getNome().c_str());
							wcscat_s(aux, TEXT(" saiu do lobby!"));

							enviaMensagemParaTodos(aux, jogador);
						}
						else
						{
							//Faz reset ao jogo
							j = Jogo();
						}
					}
				}
				limpaJogador(jogador);
				msg = errorMsg(TEXT("Logout efectuado com sucesso!"));
				return msg;
			}
			else
			{
				msg = errorMsg(TEXT("Comando mal construído ou não aceite!"));
				return msg;
			}
		}
		else if (jogador.getEstado() == AJOGAR)
		{
			if (BufferComandoLido[0] == TEXT("mover") && BufferComandoLido.size() == 2)
			{
				tstring x = j.açãoJogador(BufferComandoLido[1], jogador);
				wcscpy_s(aux, x.c_str());
				msg = errorMsg(aux);
				actualizaInfoServer();
				return msg;
			}
			if (BufferComandoLido[0] == TEXT("pos") && BufferComandoLido.size() == 1)
			{
				tstring x = j.posActual(jogador);
				wcscpy_s(aux, x.c_str());
				msg = errorMsg(aux);
				return msg;
			}
			if (BufferComandoLido[0] == TEXT("pedra") && BufferComandoLido.size() == 2)
			{
				tstring x = j.usarPedra(jogador,BufferComandoLido[1]);
				wcscpy_s(aux, x.c_str());
				msg = errorMsg(aux);
				actualizaInfoServer();
				return msg;
			}
			else
			{
				msg = errorMsg(TEXT("Comando mal construído ou não aceite!"));
				return msg;
			}
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





DWORD WINAPI AtendeCliente(LPVOID param) {
	TCHAR cmd[TAM];
	HANDLE hPipe = (HANDLE)param;
	Jogador jogador = getJogadorByPipe(hPipe);

	do {
		
		//Recebe mensagem cliente
		wcscpy_s(cmd, recebeMensagem(jogador.getHPipeReceber()));

		jogador = getJogadorByPipe(hPipe);

		//Termina thread
		if (_tcscmp(cmd, TEXT("thread")) == 0)
			return 0;
		WaitForSingleObject(hMutex, INFINITE);
		//Verifica / executa comando
		Msg msg = executaComando(cmd, jogador);
		
		//Envia resposta
		enviaMensagem(msg, jogador.getHPipeEnviar());

		ReleaseMutex(hMutex);

	} while (_tcscmp(cmd, TEXT("sair")) != 0);

	terminaJogador(jogador);

	return 0;
}



DWORD WINAPI RecebeJogadores(LPVOID param) {
	HANDLE hPipeEnviar, hPipeReceber;

	hMutex = CreateMutex(NULL, FALSE, NULL);

	//Segurança - Colocar qualquer jogador com permissões apenas para escrita e leitura
	SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
	PSID everyone_sid = NULL;
	AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &everyone_sid);

	EXPLICIT_ACCESS ea;
	ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));
	ea.grfAccessPermissions = SPECIFIC_RIGHTS_ALL | STANDARD_RIGHTS_ALL;
	ea.grfAccessMode = SET_ACCESS;
	ea.grfInheritance = NO_INHERITANCE;
	ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
	ea.Trustee.ptstrName = (LPWSTR)everyone_sid;

	PACL acl = NULL;
	SetEntriesInAcl(1, &ea, NULL, &acl);

	PSECURITY_DESCRIPTOR sd = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR,
		SECURITY_DESCRIPTOR_MIN_LENGTH);
	InitializeSecurityDescriptor(sd, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(sd, TRUE, acl, FALSE);

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = sd;
	sa.bInheritHandle = FALSE;


	while (!fim && jogadores.size() < N_MAX_LEITORES)
	{
		tcout << TEXT("[SERVIDOR] Cria pipes!") << endl;

		hPipeEnviar = CreateNamedPipe(PIPE_LEITURA, PIPE_ACCESS_OUTBOUND, PIPE_WAIT | PIPE_TYPE_MESSAGE
			| PIPE_READMODE_MESSAGE, N_MAX_LEITORES, TAM * sizeof(TCHAR), TAM * sizeof(TCHAR),
			1000, &sa);

		hPipeReceber = CreateNamedPipe(PIPE_ESCRITA, PIPE_ACCESS_INBOUND, PIPE_WAIT | PIPE_TYPE_MESSAGE
			| PIPE_READMODE_MESSAGE, N_MAX_LEITORES, TAM * sizeof(TCHAR), TAM * sizeof(TCHAR),
			1000, &sa);

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

