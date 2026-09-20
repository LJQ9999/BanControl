#include "main.h"
void HideWindow(){
	HWND hwnd=GetForegroundWindow();
	if(hwnd)ShowWindow(hwnd,SW_HIDE);
	return ;
}
