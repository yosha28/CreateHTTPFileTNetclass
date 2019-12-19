#ifndef TNET_H
#define TNET_H
class TNet;

typedef void(*OnTNetError)(TNet *Sender);


class TNet {
private:
	char *FUrlPath;
	char *FUserName;
	char *FPassword;
	char *FHost;
	int FPort;

public:
	TNet();
	virtual ~TNet();
	void getHost(char **Host);
	void setHost(const char *Value);
	int getPort();
	void setPort(const int Value);
	void getUrlPath(char **UrlPath);
	void setUrlPath(const char *Value);
	void getUserName(char **UserName);
	void setUserName(const char *UserName);
	void getPassword(char **Password);
	void setPassword(const char *Value);
	bool Internet();
	void InternetClose();
	bool Connected();
	void ConnectClose();
	bool FileWWW();
	void FileWWWClose();
	virtual void DownloadFile(const char *FilePath);
	OnTNetError OnNoInternet;
	OnTNetError OnNoConnect;
	OnTNetError OnNoFileFound;

protected:
	
	HINTERNET FHandleInet;
	HINTERNET FHandleConnection;
	HINTERNET FHandleFileWWW;
	virtual void  DoOnNoInternet();
	virtual void DoOnNoConnect();
	virtual void DoOnNoFileFound();

};

#endif