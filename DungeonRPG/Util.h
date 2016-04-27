#ifndef UTIL_H
#define UTIL_H

#pragma once

#include <iostream>
#include <string>
#include <tchar.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <vector>
#include <sstream>
#include <fstream>

#define TAM 1024
#define PIPE_LEITURA TEXT("\\\\.\\pipe\\PipeLeitura")//Le
#define PIPE_ESCRITA TEXT("\\\\.\\pipe\\PipeEscrita")//Escreve

using namespace std;

#ifdef UNICODE
#define tcout wcout
#define tcin wcin
#define tos wotstringstream
#define tfstream wifstream
#define tstring wstring
#define otstringstream wostringstream
#define itstringstream wistringstream
#define to_tstring to_wstring
#define tstringstream wstringstream
#else
#define tcout cout
#define tcin cin
#define tos otstringstream
#define tfstream ifstream
#define tstring string
#define otstringstream ostringstream
#define itstringstream istringstream
#define to_tstring to_string
#define tstringstream stringstream
#endif
void utils() {
#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
	_setmode(_fileno(stderr), _O_WTEXT);
#endif
}

typedef struct Jogos {
	TCHAR cmd[TAM];
}Jogo;

#endif
