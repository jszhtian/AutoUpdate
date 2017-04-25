// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#pragma comment(lib, "wininet.lib")

void LpDownloadToMem(_In_ const wchar_t *Url,_Out_ byte* Buffer,_In_ int sizeofbuffer)
{
	memset(Buffer, 0, sizeof(byte)*sizeofbuffer);
	ULONG Number = 1;
	HINTERNET hSession = InternetOpenW(L"HTTPDOWNLOAD", INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
	if (hSession !=NULL)
	{
		HINTERNET hInternetHandle = InternetOpenUrlW(hSession, Url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
		if (hInternetHandle!=NULL)
		{
			while (Number>0)
			{
				InternetReadFile(hInternetHandle, Buffer, sizeofbuffer - 1, &Number);
			}
		}
		InternetCloseHandle(hInternetHandle);
		hInternetHandle = NULL;
	}
	InternetCloseHandle(hSession);
	hSession = NULL;
}

int main()
{
	byte* Buffer = new byte[1024];
	LpDownloadToMem(L"https://raw.githubusercontent.com/jszhtian/AutoUpdate/master/Check.txt",Buffer,1024);

	std::cout << "Get!" << std::endl;
    return 0;
}

