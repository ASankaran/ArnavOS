#include "string.h"

int cmpstr(unsigned char str1[], unsigned char str2[]) {
	int i = 0;
	if (strlen(str1) != strlen(str2)) {
		return 0;
	}
	while (str1[i] != '\0') {
		if (str1[i] != str2[i]) {
			return 0;
		}
		i++;
	}
	return 1;
}

int strlen(unsigned char str[]) {
	int i = 0;
	while (str[i] != '\0') {
		i++;
	}
	return i;
}