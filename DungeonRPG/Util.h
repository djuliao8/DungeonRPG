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
#include <cstdlib>
#include <aclapi.h>
#include <strsafe.h>
#include <time.h>

#define TAM 1024
#define DEFAULT_MAPA 70
#define PIPE_LEITURA TEXT("\\\\.\\pipe\\PipeLeitura")//Le
#define PIPE_ESCRITA TEXT("\\\\.\\pipe\\PipeEscrita")//Escreve
#define REGISTRY_KEY TEXT("Software\\TP_SO2\\")

//Estados

#define LOGIN 0
#define QUEROJOGAR 1
#define AJOGAR 2

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


typedef struct mensagemJogo {
	bool erro;
	TCHAR cmd[TAM];
}Msg;


#endif
