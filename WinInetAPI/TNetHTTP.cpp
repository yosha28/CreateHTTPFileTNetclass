#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <WinInet.h>
#include <ShlObj.h>
#include <shlwapi.h>
#include "strutils.h"
#include "TNet.h"
#include "TNetHTTP.h"

#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "shlwapi.lib")

TNetHTTP::TNetHTTP() {
	TNet::TNet();
	setPort(INTERNET_DEFAULT_HTTP_PORT);
};

TNetHTTP::~TNetHTTP() {
	//TNet::~TNet();
};

void TNetHTTP::DownloadFile(const char *FilePath) {
	if (FileWWW()) {
		if (HttpSendRequestA(FHandleFileWWW, NULL, 0, NULL, 0))
		{
			FILE *fileHDD;
			int fileError = fopen_s(&fileHDD, FilePath, "w");
			if (0 == fileError) {
				char c;
				DWORD recBytes = 0;
				while (InternetReadFile(FHandleFileWWW, &c, 1, &recBytes)) {
					if (recBytes != 1) break;
					fprintf(fileHDD, "%c", c);
					//printf("%c", c);
				}
				fclose(fileHDD);
				
			}
			else {
				printf("I cannot to create file on HDD %s\n", FilePath);
			}
			
		}
	
	}
};