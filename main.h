#include<iostream>
#include<string>
#include<windows.h>
#include<shellapi.h>
#include<tchar.h>
#include<thread>
#include<vector>
#include<ctime>
using namespace std;
#define KEY_DOWN(VK_NONAME)((GetAsyncKeyState(VK_NONAME)&0x8000)?1:0)
#define ID_TRAY_ICON 1001
#define WM_TRAY_MESSAGE (WM_APP+1)
#define push push_back
LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
void Tray();
void BanControl();
void QuickKey1();
void QuickKey2();
