/*
SWE2001 System Program (Spring 2021)
Prof:	Jinkyu Jeong (jinkyu@skku.edu)

TA: Jongwon Park(jongwon.park@csi.skku.edu)
	Jaeguk Lee(jaekuk.lee@csi.skku.edu)
Semiconductor Building #400509
Author: Jiwon Woo
Description: Find shortest path of maze
***Copyright (c) 2021 SungKyunKwan Univ. CSI***
*/


#include "maze.h"

#define INF 	400
#define TRUE	1
#define FALSE	0
#define min(a,b) (((a)<(b))?(a):(b))

int findPath(int l, int x, int y, int w, int d, char *m)
{
	int index = x + y * w;
	int up = x + (y - 1) * w;
	int down = x + (y + 1) * w;
	int left = (x - 1) + y * w;
	int right = (x + 1) + y * w;
	int total_length = INF;
	int temp = INF;
	int is_blocked = TRUE;
	
	// is it end point?
	if(index == w * d - 1){
		if(m[index])
			return INF;
		else
			return l; 
	}

	m[index] = 2;

	// go to next point - Corrected
	if((x < w - 1) && !m[right]){
		temp = findPath(l + 1, x + 1, y, w, d, m);
		total_length = min(temp, total_length);
		is_blocked = FALSE;
	} 
	if((y < d - 1) && !m[down]){
		temp = findPath(l + 1, x, y + 1, w, d, m);
		total_length = min(temp, total_length);
		is_blocked = FALSE;
	}
	if((x > 0) && !m[left]){
		temp = findPath(l + 1, x - 1, y, w, d, m);
		total_length = min(temp, total_length);
		is_blocked = FALSE;
	}
	if((y > 0) && !m[up]){
		temp = findPath(l + 1, x, y - 1, w, d, m);
		total_length = min(temp, total_length);
		is_blocked = FALSE;
	}

	m[index] = 0;
	if(is_blocked)
		return INF;
	else
		return total_length;
}
