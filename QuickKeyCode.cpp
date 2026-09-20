#include "main.h"
extern HWND hwnd2;
extern bool Switch_BC,Notice_exit,Switch_Hide;
extern vector<int>QuickKey_value,Hide_value,Exit_value;
void QuickKey1(){
	while(true){
		if(Notice_exit)break;
		bool QuickKey_flag=1;
		for(int i=0;i<QuickKey_value.size();i++)if(!KEY_DOWN(QuickKey_value[i]))QuickKey_flag=0;
		if(QuickKey_value.size()&&QuickKey_flag){
			if(Switch_BC)Switch_BC=0;
			else Switch_BC=1;
			Sleep(200); 
		}
		bool Hide_flag=1;
		for(int i=0;i<Hide_value.size();i++)if(!KEY_DOWN(Hide_value[i]))Hide_flag=0;
		if(Hide_value.size()&&Hide_flag){
			if(Switch_Hide){
				if(hwnd2)ShowWindow(hwnd2,SW_SHOW);
    	       	Switch_Hide=0;
			}
			else{
				if(hwnd2)ShowWindow(hwnd2,SW_HIDE);
				Switch_Hide=1;            	
			} 
			Sleep(200); 
		}
		bool Exit_flag=1;
		for(int i=0;i<Exit_value.size();i++)if(!KEY_DOWN(Exit_value[i]))Exit_flag=0;
		if(Exit_value.size()&&Exit_flag)exit(0);
		Sleep(10); 
	}
	return ;
}
void QuickKey2(){
	extern string QuickMouse;
	if(QuickMouse.size()==0)return ;
	bool flag;int cnt=QuickMouse.length()-1;vector<int>vis(QuickMouse.length(),-1); 
	while(true){
		if(Notice_exit)break;
		if(KEY_DOWN(1)){vis[(++cnt)%QuickMouse.length()]=1;Sleep(200);flag=1;}
		if(KEY_DOWN(2)){vis[(++cnt)%QuickMouse.length()]=0;Sleep(200);flag=1;}
		for(int i=0;i<QuickMouse.size();i++)if(vis[(cnt+i+1)%QuickMouse.length()]!=(QuickMouse[i]=='L'?1:0))flag=0;
		if(flag){
			if(Switch_BC)Switch_BC=0;
			else Switch_BC=1;
			flag=0;
		}
		Sleep(10);
	}
	return ;
}
