#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <WinInet.h>
#include <ShlObj.h>
#include <shlwapi.h>
#include "strutils.h"
#include "TNet.h"

#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "shlwapi.lib")

TNet::TNet() {
	FHost = (char *)malloc(defaultBufferSize * sizeof(char));
	FPort = 0;
	FUrlPath = (char *)malloc(defaultBufferSize * sizeof(char));
	FUserName = (char *)malloc(defaultBufferSize * sizeof(char));
	FPassword = (char *)malloc(defaultBufferSize * sizeof(char));
	nullstr(FHost);
	nullstr(FUrlPath);
	nullstr(FUserName);
	nullstr(FUserName);
	FHandleInet = NULL;
	FHandleConnection = NULL;
	FHandleFileWWW = NULL;

	OnNoInternet = NULL;
	OnNoConnect = NULL;
	OnNoFileFound = NULL;
};

TNet::~TNet() {
	FileWWWClose();
	ConnectClose();
	InternetClose();
	free(FPassword);
	free(FUserName);
	free(FUrlPath);
	free(FHost);
};

void TNet::getHost(char **Host) {
	strcpy_s(*Host, defaultBufferSize, FHost);

};

void TNet::setHost(const char *Value) {
	nullstr(FHost);
	strcpy_s(FHost, defaultBufferSize, Value);
};

int TNet::getPort() {
	return FPort;
};

void TNet::setPort(const int Value) {
	FPort = Value;
};

void TNet::getUrlPath(char **UrlPath) {
	strcpy_s(*UrlPath, defaultBufferSize, FUrlPath);
};

void TNet::setUrlPath(const char *Value) {
	nullstr(FUrlPath);
	strcpy_s(FUrlPath, defaultBufferSize, Value);
};

void TNet::getUserName(char **UserName) {
	strcpy_s(*UserName, defaultBufferSize, FUserName);
};

void TNet::setUserName(const char *Value) {
	nullstr(FUserName);
	strcpy_s(FUserName, defaultBufferSize, Value);
};

void TNet::getPassword(char **Password) {
	strcpy_s(*Password, defaultBufferSize, FPassword);
};

void TNet::setPassword(const char *Value) {
	nullstr(FPassword);
	strcpy_s(FPassword, defaultBufferSize, Value);
};

bool TNet::Internet() {
	if (NULL == FHandleInet) {
		FHandleInet = InternetOpenA("HTTPGET", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
		if (NULL == FHandleInet) DoOnNoInternet();
	}
	return (NULL != FHandleInet);
};

void  TNet::InternetClose() {
	if (NULL != FHandleInet) {
		InternetCloseHandle(FHandleInet);
		FHandleInet = NULL;
	}
};

bool TNet::Connected() {
	if (NULL == FHandleConnection) {
		if (Internet()) {
			FHandleConnection = InternetConnectA(FHandleInet, FHost, FPort, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
			if (NULL == FHandleConnection) DoOnNoConnect();
		}
	}
	return (NULL != FHandleConnection);
};

void  TNet::ConnectClose() {
	if (NULL != FHandleConnection) {
		InternetCloseHandle(FHandleConnection);
		FHandleConnection = NULL;
	}
};

bool  TNet::FileWWW() {
	if (NULL == FHandleFileWWW) {
		if (Connected()) {
			FHandleFileWWW = HttpOpenRequestA(FHandleConnection, NULL, FUrlPath, "HTTP/1.1\0", NULL, NULL,
				INTERNET_FLAG_RELOAD | INTERNET_FLAG_EXISTING_CONNECT, 0);
		}
		if (NULL == FHandleFileWWW) DoOnNoFileFound();
	}
	return (NULL != FHandleFileWWW);
};

void  TNet::FileWWWClose() {
	if (NULL != FHandleFileWWW) {
		InternetCloseHandle(FHandleFileWWW);
		FHandleFileWWW = NULL;
	}
};

void  TNet::DownloadFile(const char *FilePath) {
	printf("abstract method of class TNet\n");
}
void  TNet::DoOnNoInternet()
{
	if (NULL != OnNoInternet)
	{
		OnNoInternet(this);
	}

}
void  TNet::DoOnNoConnect()
{
	if (NULL != OnNoConnect)
	{
		OnNoConnect(this);
	}

}
void TNet::DoOnNoFileFound()
{
	if (NULL != OnNoFileFound)
	{
		OnNoFileFound(this);
	}

}
;
