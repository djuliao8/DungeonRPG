#ifndef UTIL_H
#define UTIL_H

#pragma once

#include <iostream>
#include <string>
#include <tchar.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

#define TAM 1024
#define PIPE_LEITURA TEXT("\\\\.\\pipe\\PipeLeitura")//Le
#define PIPE_ESCRITA TEXT("\\\\.\\pipe\\PipeEscrita")//Escreve

using namespace std;

#ifdef UNICODE
#define tstring wstring
#define tcout  wcout
#define tcerr wcerr
#define tcin wcin
#else
#define tstring string 
#define tcout cout
#define tcin cin
#define tcerr cerr
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
