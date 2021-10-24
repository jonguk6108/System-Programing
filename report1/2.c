#include <stdio.h>
#define DELTA sizeof(int)

int main() {
	int i;
	for(i = 10; i - (signed int) DELTA >= 0; i -=  (signed int) DELTA)
		printf("%d\n", i);
}
