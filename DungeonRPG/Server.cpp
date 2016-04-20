#include "Util.h"


int _tmain(int argc, LPTSTR argv[]){
	utils();
	TCHAR buf[256];
	HANDLE hpipe;
	int i = 0;
	BOOL ret;
	DWORD n;
	tcout << TEXT("[SERVIDOR]Esperar pelo pipe \'") << PIPE_NAME << TEXT("\'(WaitNamedPipe)\n");
	if (!WaitNamedPipe(PIPE_NAME, NMPWAIT_WAIT_FOREVER)) {
		tcout << TEXT("[ERRO] Ligar ao pipe \'") << PIPE_NAME << TEXT("\'... (WaitNamedPipe)\n");
		exit(-1);
	}

	tcout << TEXT("[SERVIDOR] Ligação ao escritor... (CreateFile)\n");
	hpipe = CreateFile(PIPE_NAME, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hpipe == NULL) {
		tcerr << TEXT("[ERRO] Ligar ao pipe \'") << PIPE_NAME << TEXT("\'... (CreateFile)\n");
		exit(-1);
	}
	tcout << TEXT("[SERVIDOR]Liguei-me...\n");
	while (1) {
		ret = ReadFile(hpipe, buf, sizeof(buf), &n, NULL);
		buf[n / sizeof(TCHAR)] = '\0';
		if (!ret || !n)
			break;
		tcout << TEXT("[SERVIDOR] Recebi ") << n << TEXT(" bytes: \'") << buf << TEXT("\'... (ReadFile)\n");
	}
	CloseHandle(hpipe);
	Sleep(200);
	return 0;
}