#include "Util.h"

int _tmain(int argc, LPTSTR argv[]){
	utils();
	HANDLE hpipe;
	tstring buf;
	hpipe = CreateNamedPipe(PIPE_NAME, PIPE_ACCESS_DUPLEX, PIPE_WAIT | PIPE_TYPE_MESSAGE| PIPE_READMODE_MESSAGE, 1, sizeof(buf), sizeof(buf), 1000, NULL);
	if (hpipe == INVALID_HANDLE_VALUE){
		_tperror(TEXT("Erro na ligação ao Servidor"));
		exit(-1);
	}
	while (1){
		tcout << TEXT("[CLIENTE] Esperar ligação de um leitor... (ConnectNamedPipe)\n");

		if (!ConnectNamedPipe(hpipe, NULL)){
			tcerr << TEXT("Erro na ligação ao leitor!");
			exit(-1);
		}
		do{
			tcout << TEXT("[CLIENTE] Frase: ");
			getline(tcin, buf);
			if (!WriteFile(hpipe, buf.c_str(), buf.length()*sizeof(TCHAR), &n, NULL)) {
				tcerr << TEXT("[ERRO] Escrever no pipe... (WriteFile)\n");
				exit(-1);
			}
			tcout << TEXT("[CLIENTE] Enviei ") << n << TEXT(" bytes ao leitor... (WriteFile)\n");
		} while (buf != TEXT("fim"));

		tcout << TEXT("[CLIENTE]Vou desligar o pipe(DisconnectNamedPipe/CloseHandle)\n");
		if (!DisconnectNamedPipe(hpipe)){
			tcerr << TEXT("Erro ao desligar o pipe!");
			exit(-1);
		}
	}
	Sleep(2000);
	tcout << TEXT("[CLIENTE] Vou desligar o pipe... (CloseHandle)\n");
	CloseHandle(hpipe);
	exit(0);
}