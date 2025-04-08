#include<iostream>
#include<Windows.h>
//Format error message
void FormatErrorMsg(DWORD errorCode)
{
	char* buf;
	FormatMessage(
		//��ʽ����ѡ���Լ���ν��� lpSource ����
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		//lpSource:��Ϣ�����λ��
		nullptr,
		//dwMessageId:�������Ϣ����Ϣ��ʶ��
		errorCode,
		// dwLanguageId:��������Ϣ�����Ա�ʶ��
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		//lpBuffer:ָ�򻺳�����ָ��
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
	//����һ���ṹ�����
	std::string classname = "MyFirstGame";
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = classname.c_str();
	wc.lpfnWndProc = DefWindowProc;
	wc.hInstance = hInstance;
	//ע�ᴰ��(����ǰ�� Windowϵͳ�ɲ�֪����Ҫ����ʲô���͵Ĵ���(�������������ʾʲôͼ��,�����״��ʲô,���ڱ�����ɫ�ȵ�).��Щ������ϢӦ���㴴��ǰ���ȸ���Windowϵͳ)
	ATOM ret= RegisterClassEx(&wc);// Ӧ�ó����ַ�������ԭ�ӱ��У�������һ����Ϊԭ�ӵ� 16 λ�����������������ڷ����ַ���
	if (!ret)
	{
		//DWORD������һ���޷��ŵ�����,unsigned long 
		DWORD errorCode=GetLastError();//�������������ֵ
		FormatErrorMsg(errorCode);
		return -1;
	}
	return 0;
}