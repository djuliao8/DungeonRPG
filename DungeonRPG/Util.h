#include <iostream>
#include <string>
#include <tchar.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

using namespace std;

#ifdef UNICODE
#define tstring wstring
#define tcout  wcout
#define tcin wcin
#else
#define tstring string 
#define tcout cout
#define tcin cin
#endif

void utils(){
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif
}
