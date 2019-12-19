#ifndef TNETHTTP_H
#define TNETHTTP_H

#include "TNet.h"

class TNetHTTP : public TNet {
private:

public:
	TNetHTTP();
	virtual ~TNetHTTP();

	virtual void DownloadFile(const char *FilePath);
};

#endif