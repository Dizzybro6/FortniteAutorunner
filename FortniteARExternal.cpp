// FortniteARExternal.cpp : Defines the entry point for the console application.
//

#define WINVER 0x0500

#include "stdafx.h"
#include <Windows.h>
#include <Psapi.h>
#include <tchar.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <iostream>
using namespace std;

HANDLE OpenProcessByName(LPCTSTR Name, DWORD dwAccess)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pe;
		ZeroMemory(&pe, sizeof(PROCESSENTRY32));
		pe.dwSize = sizeof(PROCESSENTRY32);
		Process32First(hSnap, &pe);
		do
		{
			if (!lstrcmpi(pe.szExeFile, Name))
			{
				return OpenProcess(dwAccess, 0, pe.th32ProcessID);
			}
		} while (Process32Next(hSnap, &pe));

	}
	return INVALID_HANDLE_VALUE;
}

void eProc(DWORD procId)
{
	TCHAR szProcName[MAX_PATH] = TEXT("<unknown>");
	
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, procId);	 

	//get process name
	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;
		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcName, sizeof(szProcName) / sizeof(TCHAR));
		}
	}

	_tprintf(TEXT("%s (PID: %u)\n"), szProcName, procId);
	CloseHandle(hProcess);
}

int main()
{
	cout << "Connors Fortnite Autorunner." << endl;
	cout << "-----------------------------" << endl;
	//cout << "Current processes running:" << endl;
	/*
	DWORD aProcessess[1024], cbNeeded, cProcesses;
	unsigned int i;

	if (!EnumProcesses(aProcessess, sizeof(aProcessess), &cbNeeded))
	{
		return 1;
	}

	cProcesses = cbNeeded / sizeof(DWORD);
	for (int i = 0; i < cProcesses; i++)
	{
		if (aProcessess[i] != 0)
		{
			eProc(aProcessess[i]);
		}
	}
	*/

	//HANDLE hWnd = OpenProcessByName(L"notepad.exe", PROCESS_VM_READ);
	//cout << "Handle: " << hWnd << endl;
	//CloseHandle(hWnd);

	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.dwFlags = 0;
	ip.ki.dwFlags = 0x57;
	//0x57 - W Key;

	bool isRunning = false;

	while (!GetAsyncKeyState(VK_SPACE))
	{
		if (GetAsyncKeyState(VK_SHIFT))
		{
			//cout << "Autorun key pressed." << endl;
			if (isRunning)
			{
				isRunning = false;
				//cout << "\tisRunning: false" << endl;
			}
			else {
				isRunning = true;
				//cout << "\tisRunning: true" << endl;
			}
		}

		if (isRunning)
		{
			/*SendInput(1, &ip, sizeof(INPUT));
			ip.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &ip, sizeof(INPUT));
			*/
			keybd_event(VK_SHIFT, 0, 0, 0);
			keybd_event(0x57, 0, 0, 0);
			
			//keybd_event(0x57, 0, KEYEVENTF_KEYUP, 0);
			//keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
			//keybd_event(0x57, 0, KEYEVENTF_KEYUP, 0);
			//cout << "\tAuto running." << endl;
		}
		else {
			//cout << "\tStopped auto running." << endl;
		}

		//cout << "Checking autorun key" << endl;
		Sleep(100);
	}
	cout << "Autorunner exited." << endl;
	

	//cin.get();

    return 0;
}

