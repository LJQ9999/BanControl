#include "main.h"
HWND hwnd=NULL;
extern HWND hwnd2;
extern bool Switch_BC,Switch_Hide;
void Tray(){
    WNDCLASSEX wc={sizeof(WNDCLASSEX),CS_CLASSDC,WindowProc,0L,0L,GetModuleHandle(NULL),NULL,NULL,NULL,NULL,_T("TrayApp"),NULL };
    RegisterClassEx(&wc);
    hwnd=CreateWindow(wc.lpszClassName,_T("Tray App"),WS_OVERLAPPEDWINDOW,0,0,0,0,NULL,NULL,wc.hInstance,NULL);
    ShowWindow(hwnd,SW_HIDE);
    UpdateWindow(hwnd);
    NOTIFYICONDATA nid={0};
    nid.cbSize=sizeof(NOTIFYICONDATA);
    nid.hWnd=hwnd;
    nid.uID=ID_TRAY_ICON;
    nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;
    nid.uCallbackMessage=WM_TRAY_MESSAGE;
    nid.hIcon=LoadIcon(NULL,IDI_APPLICATION);
    lstrcpyn(nid.szTip,_T ("ÍÑ¿ØÆ÷"),ARRAYSIZE(nid.szTip));
    Shell_NotifyIcon(NIM_ADD, &nid);
    MSG msg;
    while(GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
	}
    Shell_NotifyIcon(NIM_DELETE, &nid);
    return ;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    switch(uMsg){
        case WM_TRAY_MESSAGE:
            if(lParam==WM_RBUTTONUP){
                HMENU hMenu=CreatePopupMenu();
                AppendMenu(hMenu,MF_STRING,1,_T("ÍË³ö"));
                if(Switch_BC)AppendMenu(hMenu,MF_STRING,2,_T("ÔÝÍ£"));
                else AppendMenu(hMenu,MF_STRING,3,_T("¼ÌÐø"));
                if(Switch_Hide)AppendMenu(hMenu, MF_STRING,4,_T("ÏÔÊ¾UI"));
                else AppendMenu(hMenu,MF_STRING,5,_T("Òþ²ØUI"));
                POINT pt;
                GetCursorPos(&pt);
                SetForegroundWindow(hwnd);
                TrackPopupMenu(hMenu,TPM_BOTTOMALIGN|TPM_LEFTALIGN,pt.x,pt.y,0,hwnd,NULL);
                DestroyMenu(hMenu);
            }
            break;
            
        case WM_COMMAND:
            if(wParam==1)PostQuitMessage(0);
            if(wParam==2)Switch_BC=0;
			if(wParam==3)Switch_BC=1;
			if(wParam==4){
				if(hwnd2)ShowWindow(hwnd2,SW_SHOW);
            	Switch_Hide=0;
			}
			if(wParam==5){
				if(hwnd2)ShowWindow(hwnd2,SW_HIDE);
				Switch_Hide=1;            	
			}
            break;
            
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
            
        default:
            return DefWindowProc(hwnd,uMsg,wParam,lParam);
    }
    return 0;
}
