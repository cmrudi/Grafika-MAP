#include "algorithm.h"

int min(int x, int y) {
	if(x < y) {
		return x;
	} else {
		return y;
	}
}

int max(int x, int y) {
	if(x > y) {
		return x;
	} else {
		return y;
	}
}

int absolute(int n) {
	if(n < 0) {
		return n * (-1);
	} else {
		return n;
	}	
}
