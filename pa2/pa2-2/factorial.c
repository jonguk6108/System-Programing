/*
SWE2001 System Program (Spring 2021)
Prof:	Jinkyu Jeong (jinkyu@skku.edu)

TA: Jongwon Park(jongwon.park@csi.skku.edu)
	Jaeguk Lee(jaekuk.lee@csi.skku.edu)
Semiconductor Building #400509
Author: Jongwon Park
Description: Find shortest path of maze
***Copyright (c) 2021 SungKyunKwan Univ. CSI***
*/


#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define INPUT  "pa2-2.in"

int factorial (int n)
{
	if (n==0 || n==1) return 1;

	return n * factorial(n-1);
}

int main (void)
{
	int fd_in;
	int ret, val_i;
	
	/* open */
	if((fd_in = open(INPUT, O_RDONLY)) == -1)
		perror(INPUT);
	/* read */
	ret = read(fd_in, (void*)&val_i, sizeof(int));
	/* close */
	close(fd_in);

	ret = factorial(val_i);

	printf("factorial[%d] = %d\n", val_i, ret);	

	return 0;	
}
