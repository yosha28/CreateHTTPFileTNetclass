#include "pch.h"
#include "strutils.h"

void nullstr(char *str, const int len) {
	char *wrk = str;
	for (int i = 0; i < len; i++) {
		*wrk = 0;
		wrk++;
	}
};
