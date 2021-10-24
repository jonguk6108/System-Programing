/*
SWE2001 System Program (Spring 2021)
Prof:	Jinkyu Jeong (jinkyu@skku.edu)

TA: Jongwon Park(jongwon.park@csi.skku.edu)
	Jaeguk Lee(jaekuk.lee@csi.skku.edu)
Semiconductor Building #400509
Author: Jaeguk Lee
Description: Find GCD (Greate Common Divisor) and LCM (Least Common Multiple)
***Copyright (c) 2021 SungKyunKwan Univ. CSI***
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define INPUT "pa2-1.in"

int gcd (int n, int m, int l)
{
	int i, j;

	if (n > m)	j = n;
	else		j = m;

	if (j > l)	j = l;

	for (i=j; i>0; i--)
		if (n%i == 0 && m%i == 0 && l%i == 0)
			break;
	return i;
}

int lcm (int n, int m, int l)
{
	int i, j;

	if (n > m)	j = n;
	else		j = m;

	if (j > l)	j = l;

	for (i=j; i <= m*n*l; i+=j)
		if (i%n==0 && i%m==0 && i%l == 0)
			break;
	return i;
}

int main (void)
{
	int fd_in;
	int ret, n, m, l;	

	if((fd_in = open(INPUT, O_RDONLY)) == -1)
		perror(INPUT);

	ret = read(fd_in, (void*)&n, sizeof(int));
	ret = read(fd_in, (void*)&m, sizeof(int));
	ret = read(fd_in, (void*)&l, sizeof(int));
	
	printf("Greate Common Divisor\t[%d, %d, %d] = %d\n", n, m, l, gcd(n,m,l));
	printf("Least Common Multiple\t[%d, %d, %d] = %d\n", n, m, l, lcm(n,m,l));

	return 0;	
}
