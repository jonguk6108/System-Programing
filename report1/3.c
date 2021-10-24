#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int strlonger (char *s, char *t) {
	return strlen(s) > strlen(t);
}

int main() {
	char *s1 = malloc(sizeof(char)*10000);
	char *s2 = malloc(sizeof(char)*10000);

	scanf("%s", s1);
	scanf("%s", s2);


	printf("%d\n", strlonger(s1,s2));
}
