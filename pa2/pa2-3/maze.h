#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 400

char maze[BUFSIZE];

int  findPath(int l, int x, int y, int w, int d, char *m);
void printResult(int l, int w, int d);
