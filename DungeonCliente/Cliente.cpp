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

void criarjogo() {
	Comunicacao* c = new Comunicacao();
	system("cls");
	int op = 0, tamX = 0, tamY = 0;
	tcout << "1 - Jogar com mapa pré-definido \n";
	tcout << "2 - Escolher dimensões do mapa \n";
	tcout << "3 - Sair \n";
	while (op <= 0 || op >= 4) {
		tcout << "Opção: ";
		tcin >> op;
		if (op > 0 && op < 4) {
			switch (op) {
			case 1:c->enviaComando(TEXT("criar pre"));
				break;
			case 2: tcout << "Escolha dimensões: (Minimo 70/70)\n";
				while (tamX < 70 || tamY < 70) {
					tcout << "Escreva respectivamente o tamanho X e Y: ";
					tcin >> tamX >> tamY;
				}

				c->enviaComando(TEXT("criar" + tamX + tamY));
				break;
			case 3:exit(0);
			default: exit(0);
			}
		}
	}
}

DWORD WINAPI EnviaComando(LPVOID param) {




int _tmain(int argc, LPTSTR argv[]){
	Comunicacao* c = new Comunicacao();
	utils();
	int op = 0;
	tcout <<"Dungeon RPG \n\n\n";
	tcout << "1 - Criar Jogo \n";
	tcout << "2 - Juntar a Jogo \n";
	tcout << "3 - Sair \n";
	while (op <= 0 || op >= 4){
		tcout << "Opcao: ";
		tcin >> op;
		if (op > 0 && op < 4){
			switch (op){
			case 1:criarjogo();
					break;
			case 2: c->enviaComando(TEXT("juntar"));
					break;
			case 3:exit(0);
			default: exit(0);
			}
		}
	}
	system("pause");
}
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
