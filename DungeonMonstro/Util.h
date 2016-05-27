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

#endif
