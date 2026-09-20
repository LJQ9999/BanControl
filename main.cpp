#include "main.h"
using namespace std;
extern bool Switch_BC,Notice_exit,Switch_Hide,flag_bagin;
extern vector<int>QuickKey_value,Hide_value,Exit_value;
extern string QuickMouse;
HWND hwnd2=GetForegroundWindow();
void ClearScreen(){
	HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord={0,0};
	DWORD count;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut,&csbi);
	FillConsoleOutputCharacter(hStdOut,' ',csbi.dwSize.X*csbi.dwSize.Y,coord,&count);
	SetConsoleCursorPosition(hStdOut,coord);
}
void set(vector<int>&q){
	int last_num=-1,last_F=-1,last_letter=-1,last_Shift=0,last_Ctrl=0,last_Alt=0;
	int flag_num=-1,flag_F=-1,flag_letter=-1,flag_Shift=0,flag_Ctrl=0,flag_Alt=0;
	int num=0;
	while(!KEY_DOWN(13)){
		if(KEY_DOWN(17))flag_Ctrl=1;
		if(KEY_DOWN(16))flag_Shift=1;
		if(KEY_DOWN(18))flag_Alt=1;
		for(int i=48;i<58;i++){
			if(KEY_DOWN(i)){
				flag_num=i;
				break;
			}
		}
		for(int i=112;i<124;i++){
			if(KEY_DOWN(i)){
				flag_F=i;
				break;
			}
		}
		for(int i=65;i<91;i++){
			if(KEY_DOWN(i)){
				flag_letter=i;
				break;
			}
		}
		if(flag_num!=last_num||flag_Shift!=last_Shift||flag_Ctrl!=last_Ctrl||flag_Alt!=last_Alt||flag_F!=last_F||flag_letter!=last_letter){
			if(!KEY_DOWN(17))flag_Ctrl=0;
			if(!KEY_DOWN(16))flag_Shift=0;
			if(!KEY_DOWN(18))flag_Alt=0;
			if(flag_num!=-1&&!KEY_DOWN(flag_num))flag_num=-1;
			if(flag_F!=-1&&!KEY_DOWN(flag_F))flag_F=-1;
			if(flag_letter!=-1&&!KEY_DOWN(flag_letter))flag_letter=-1;
			last_num=flag_num,last_F=flag_F,last_letter=flag_letter,last_Shift=flag_Shift,last_Ctrl=flag_Ctrl,last_Alt=flag_Alt;
			for(int i=0;i<num;i++)cout<<"\b";
			for(int i=0;i<num;i++)cout<<" ";
			for(int i=0;i<num;i++)cout<<"\b";
			num=0;
			if(flag_Ctrl)cout<<"Ctrl ",num+=5;
			if(flag_Shift)cout<<"Shift ",num+=6;
			if(flag_Alt)cout<<"Alt ",num+=4;
			if(flag_num!=-1)cout<<flag_num-48<<" ",num++;
			if(flag_F!=-1)cout<<"F"<<flag_F-111<<" ",num+=(flag_F>120?4:3);
			if(flag_letter!=-1)cout<<char(flag_letter),num++;
		}
		Sleep(10);
	}
	if(flag_Ctrl)q.push(17);
	if(flag_Shift)q.push(16);
	if(flag_Alt)q.push(18);
	if(flag_num!=-1)q.push(flag_num);
	if(flag_F!=-1)q.push(flag_F);
	if(flag_letter!=-1)q.push(flag_letter);
	return ;
} 
signed main(){
	freopen("setting","r",stdin);
	cin>>flag_bagin;
	if(!flag_bagin){
		string Setting;
		cout<<"初次使用,开始配置：\n";
		cout<<"启动时开始脱控[Y/N]?\n";
		bool flag=0;
		while(!KEY_DOWN(13)){
			if(KEY_DOWN(89)){
				if(flag)cout<<"\b \b";
				cout<<"Y";flag=1;Switch_BC=1;
			}
			if(KEY_DOWN(78)){
				if(flag)cout<<"\b \b";
				cout<<"N";flag=1;Switch_BC=0;
			}
			Sleep(10);
		}
		Sleep(200);
		cout<<"\n启动时隐藏[Y/N]?\n";
		flag=0;
		while(!KEY_DOWN(13)){
			if(KEY_DOWN(89)){
				if(flag)cout<<"\b \b";
				cout<<"Y";flag=1;Switch_Hide=1;
			}
			if(KEY_DOWN(78)){
				if(flag)cout<<"\b \b";
				cout<<"N";flag=1;Switch_Hide=0;
			}
			Sleep(10);
		}
		Sleep(200);
		cout<<"\n配置脱控快捷键:\n";
		set(QuickKey_value);
		cout<<"\n配置显示\\隐藏快捷键:\n";Sleep(200);
		set(Hide_value);
		cout<<"\n配置退出快捷键:\n";Sleep(200);
		set(Exit_value);
		cout<<"\n配置鼠标脱控暗号\n";Sleep(200);
		vector<bool>QuickMouse_value;
		while(!KEY_DOWN(13)){
			if(KEY_DOWN(76)){cout<<"L";Sleep(100);QuickMouse_value.push(1);}
			if(KEY_DOWN(82)){cout<<"R";Sleep(100);QuickMouse_value.push(0);}
			if(KEY_DOWN(8)){
				cout<<"\b \b";Sleep(200);
				if(QuickMouse_value.size())QuickMouse_value.erase(QuickMouse_value.end());
			}
			Sleep(10);
		}
		for(int i=0;i<QuickMouse_value.size();i++){
			if(QuickMouse_value[i])QuickMouse+="L";
			else QuickMouse+="R";
		}
		cout<<"\n设置完成,保存设置中...\n";
		freopen("setting","w",stdout);
		cout<<"1\n";
		cout<<Switch_BC<<"\n";
		cout<<Switch_Hide<<"\n";
		cout<<QuickKey_value.size()<<" ";for(int i=0;i<QuickKey_value.size();i++)cout<<QuickKey_value[i]<<" ";cout<<"\n";
		cout<<Hide_value.size()<<" ";for(int i=0;i<Hide_value.size();i++)cout<<Hide_value[i]<<" ";cout<<"\n";
		cout<<Exit_value.size()<<" ";for(int i=0;i<Hide_value.size();i++)cout<<Exit_value[i]<<" ";cout<<"\n";
		cout<<QuickMouse.length()<<" "<<QuickMouse;
		Sleep(800);
		freopen("CON","w",stdout);
		cout<<"设置完成,按Enter继续\n";
		Sleep(200); 
		while(!KEY_DOWN(13))Sleep(10);
	}
	if(flag_bagin){
		int len;
		cin>>Switch_BC;
		cin>>Switch_Hide;
		cin>>len;if(len)for(int i=0,input;i<len;i++)cin>>input,QuickKey_value.push(input);
		cin>>len;if(len)for(int i=0,input;i<len;i++)cin>>input,Hide_value.push(input);
		cin>>len;if(len)for(int i=0,input;i<len;i++)cin>>input,Exit_value.push(input);
		cin>>len;if(len)cin>>QuickMouse;
	}
	ClearScreen();
	if(Switch_Hide&&hwnd2)ShowWindow(hwnd2,SW_HIDE);
	thread BanControl_P(BanControl),QuickKey1_P(QuickKey1),QuickKey2_P(QuickKey2),Tray_P(Tray);
	Tray_P.join();Notice_exit=1;BanControl_P.join(),QuickKey1_P.join(),QuickKey2_P.join();
	return 0;
}
