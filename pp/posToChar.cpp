#include "posToChar.h"

char* posToChar(int pos) {
	char *res;

	if (pos + '0' > '9') {
		res = (char *)malloc(3);
		int temp = pos / 10;
		res[0] = temp + '0';
		res[1] = (pos - temp * 10) + '0';
		res[2] = '\0';
	}
	else {
		res = (char *)malloc(2);
		res[0] = pos + '0';
		res[1] = '\0';
	}

	return res;
}