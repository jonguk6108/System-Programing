#include <stdio.h>

int sum_array (int a[], unsigned len) {
	int i;
	int result = 0;

	for(i = 0; i < len; i++)
		result += a[i];

	return result;
}

int main() {
	int a[6] = {1,2,3,4,5,6};
	printf("%d\n", sum_array(a, 0));
}
