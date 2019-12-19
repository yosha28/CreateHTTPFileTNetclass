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

void onNoInet(TNet *Sender)
{
	printf("No internet\n");
}
void onNoConnect(TNet *Sender)
{
	char *buff = (char*)malloc(defaultBufferSize * sizeof(char));
	nullstr(buff);
	Sender->getHost(&buff);
	printf("I cannot to connect to host %s\n", buff);
	free(buff);

}
void onNoFileFound(TNet *Sender)
{
	char *buff = (char*)malloc(defaultBufferSize * sizeof(char));
	char *bufff = (char*)malloc(defaultBufferSize * sizeof(char));
	nullstr(buff);
	nullstr(bufff);
	Sender->getUrlPath(&buff);
	Sender->getHost(&bufff);
	printf("I find file on http:// %s %s\n", bufff, buff);
	free(buff);
	free(bufff);
}

int main() {
	
		char *filePath = (char *)malloc(defaultBufferSize * sizeof(char));
		nullstr(filePath);
		SHGetFolderPathA(0, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, filePath);
		PathAppendA(filePath, "goo000000gle.com.0001.html");

		TNetHTTP *Downloader = new TNetHTTP();
		Downloader->setHost("www.gooo000oogle.com");
		Downloader->setUrlPath("/");
		Downloader->OnNoInternet = &onNoInet;
		Downloader->OnNoConnect = &onNoConnect;
		Downloader->OnNoFileFound = &onNoFileFound;

		Downloader->DownloadFile(filePath);
	
	delete Downloader;
	free(filePath);
}
