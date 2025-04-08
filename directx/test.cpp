#include<iostream>
#include<Windows.h>
//Format error message
void FormatErrorMsg(DWORD errorCode)
{
	char* buf;
	FormatMessage(
		//格式设置选项以及如何解释 lpSource 参数
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		//lpSource:消息定义的位置
		nullptr,
		//dwMessageId:请求的消息的消息标识符
		errorCode,
		// dwLanguageId:所请求消息的语言标识符
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		//lpBuffer:指向缓冲区的指针
		(LPTSTR)&buf,
		//lpsize
		0,
		//Arguments
		nullptr);
	MessageBox(nullptr, buf, "error", MB_OK);
	LocalFree(buf);
}
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	//MessageBox(nullptr, "helloworld", "Mygame", MB_ABORTRETRYIGNORE && MB_ICONEXCLAMATION);
	//创建一个结构体变量
	std::string classname = "MyFirstGame";
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = classname.c_str();
	wc.lpfnWndProc = DefWindowProc;
	wc.hInstance = hInstance;
	//注册窗口(创建前， Window系统可不知道你要的是什么类型的窗口(比如标题栏上显示什么图标,鼠标形状是什么,窗口背景颜色等等).这些类型信息应在你创建前事先告诉Window系统)
	ATOM ret= RegisterClassEx(&wc);// 应用程序将字符串放在原子表中，并接收一个名为原子的 16 位整数，该整数可用于访问字符串
	if (!ret)
	{
		//DWORD本质是一个无符号的整形,unsigned long 
		DWORD errorCode=GetLastError();//返回最后错误代码值
		FormatErrorMsg(errorCode);
		return -1;
	}
	return 0;
}