#include "main.h" 
extern bool Notice_exit,Switch_BC;
void BanControl(){
	while(true){
		if(Notice_exit)break;
		if(Switch_BC){
			system("taskkill /f /im StudentClient.exe");
			system("taskkill /f /im screenclient_win7.exe");
			Sleep(300);
		}
		Sleep(10);
	}
	return ;
}
