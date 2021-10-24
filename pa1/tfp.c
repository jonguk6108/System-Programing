#include "tfp.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TFP_BIAS	127
#define TFP_BIT		19
#define TFP_FRAC	10
#define TFP_EXP		8
#define PINF		0x3fc00
#define NINF		0x7fc00
#define PZERO		0x0
#define NZERO		0x40000
#define PNAN		0x3fc01	
#define NNAN		0x7fc01

tfp int2tfp(int input) {
	tfp exp = 0;
	tfp frac = 0;
	unsigned int mask = 0x1;
	tfp ret = 0;
	tfp i = 0;

	if(input < 0) {
		ret = ret | 0x40000;
		input = -input;
	}
	
	else if(input == 0) return ret;
	
	for(exp = 30; exp > 0; exp--)
		if((mask << exp) & input) break;
	
	for(i = 0; i < TFP_FRAC; i++) {
		if((exp-i-1 >= 0) && (input & (mask << (exp-i-1))))
			frac = frac | 0x1;
		if(i != TFP_FRAC - 1) frac = frac << 1;
	}
	ret = ret | frac;

	exp = exp + TFP_BIAS;
	exp = exp << TFP_FRAC;
	ret = ret | exp;
	
	return ret;
}

int tfp2int(tfp input) {
	int exp = 0;
	unsigned int mask = 0x1;
	int ret = 0;

	memcpy((void*)(&ret), (void*)(&input), sizeof(int));
	exp = ret>>TFP_FRAC;
	exp = exp & 0xFF;
	exp = exp - TFP_BIAS;

	ret = ret & 0x3FF;
	ret = ret | 0x400;
	exp = exp-10;

	if(exp >= 0) ret = ret << exp;
	if(exp < 0) ret = ret >> (-exp);


	if(input & (mask << (TFP_BIT-1)))
		ret = -ret;

	return ret;
}

tfp float2tfp(float input) {
	tfp ret;
	memcpy((void*)(&ret), (void*)(&input), sizeof(float));
	ret = ret >> (32-TFP_BIT);

	return ret;
}

float tfp2float(tfp input) {
	float ret;
	input = input << (32-TFP_BIT);
	memcpy((void*)(&ret), (void*)(&input), sizeof(float));
	return ret;
}

tfp tfp_add(tfp a, tfp b) {
	tfp ret;
	tfp temp;
	tfp exp, expb, exps;
	unsigned int mask = 0x1;
	int i;
	int ts, sa, sb;
	sa = -((mask << (TFP_BIT-1))&a && 1);
	sb = -((mask << (TFP_BIT-1))&b && 1);


	tfp checka = a, checkb = b;
    for(i=0; i<2; i++) {
        if(checka == PINF && checkb == PINF) return PINF;
        if(checka == PINF && checkb == NINF) return PNAN;
        if(checka == PINF) return PINF;
        if(checka == NINF && checkb == NINF) return NINF;
        if(checka == NINF && checkb == PINF) return PNAN;
        if(checka == NINF) return NINF;
        checka = b;
        checkb = a;
    }
	if(checka == PZERO || checka == NZERO) return checkb;
	if(checkb == PZERO || checkb == NZERO) return checka;
	expb = a >> TFP_FRAC;
	expb = expb & 0xFF;
	exps = b >> TFP_FRAC;
	exps = exps & 0xFF;

	if(expb >= exps) exp = expb;
	else {
		temp = a;
		a = b;
		b = temp;
		exp = exps;
		temp = exps;
		exps = expb;
		expb = temp;
		ts = sa;
		sa = sb;
		sb =sa;
	}
	
	exp = exp-exps;
	a = (a & 0x3ff) | 0x400;
	b = (b & 0x3ff) | 0x400;
	
	int g = b&0x1,r = 0,s = 0;
	for(i = 0; i < exp; i++) {
		b = b>>1;
		s = 2*s+r;
		r = g;
		g = b&0x1;

		s = 1 && s;
		r = 1 && r;
		g = 1 && g;
	}

	if( (r==1 && s==1) || ( g==1 && r==1 && s==0))
		b++;
	
	int f;
	if(sa == 0) sa = 1;
	if(sb == 0) sb = 1;

	f = sa*a + sb*b;
	if(f == 0) return PZERO;

	ret = 0;
	if(f < 0) {
		ret = 0x1;
		f = -f;
	}
	ret = ret << TFP_EXP;
	
	exp = expb;
	if( f >= (mask<<(TFP_FRAC+1)) ) {
		exp++;
		f = f>>1;
	}
	while( f < (mask<<(TFP_FRAC)) ) {
		exp--;
		f = f<<1;
	}
	f = f&0x3ff;
	
	if(exp > 11111) {
        if(sa^sb == 1) ret = NZERO;
        else ret = PZERO;
        return ret;
    }
	if(exp >= 255) {
        if(sa^sb == 1) ret = NINF;
        else ret = PINF;
        return ret;
    }

	ret = ret | exp;
	ret = ret << TFP_FRAC;
	ret = ret | f;
	return ret;
}

tfp tfp_mul(tfp a, tfp b) {
	int tal = 0;

	tfp ret = 0;
	unsigned long long mask = 0x1;
	int i;
	int sa, sb;
	sa = ((mask << (TFP_BIT-1))&a && 1);
	sb = ((mask << (TFP_BIT-1))&b && 1);
	ret = (sa^sb);
	ret = ret << TFP_EXP;

	int expa, expb;
	expa = a>>TFP_FRAC;
	expa = expa & 0xFF;
	expb = b>>TFP_FRAC;
	expb = expb & 0xFF;

	tfp checka = a, checkb = b;

	for(i=0; i<2; i++) {
		if(checka == PINF && checkb == PINF) return PINF;
		if(checka == PINF && checkb == NINF) return NINF;
		if(checka == PINF && sb == 0) return PINF;
		if(checka == PINF && sb == 1) return NINF;
		if(checka == NINF && checkb == NINF) return PINF;
		if(checka == NINF && sb == 0) return NINF;
		if(checka == NINF && sb == 1) return PINF;
		if( (checka == PINF || checka == NINF) && (b == PZERO || b == NZERO)) return PNAN;
		checka = b;
		checkb = a;
	}
	if(checka == PZERO || checka == NZERO) return checka;
	if(checkb == PZERO || checkb == NZERO) return checkb;

	if(expa == 0 && (a&0x3ff)) {
		a = a&0x3ff;
		expa = 1;
		while( (a>>TFP_FRAC)%2!= 1) {
			expa--;
			a = a<<1;
		}
	}
	if(expb == 0 && (b&0x3ff)) {
		b = b&0x3ff;
		expb = 1;
		while( (b>>TFP_FRAC)%2!= 1) {
			expb--;
			b =b<<1;
		}
	}

	int expo = expa + expb - TFP_BIAS;
	unsigned long long frac;
	frac = ((a & 0x3ff)| 0x400) * ((b & 0x3ff)| 0x400);

	if( frac >= (mask<<(TFP_FRAC*2+1)) ) {
		expo++;
		frac = frac>>1;
	}

	frac = frac & 0xFFFFF;

	unsigned long long g,r,s;
	g = (mask << TFP_FRAC) & frac;
	r = 1 && (frac& (mask << (TFP_FRAC-1)));
	s = 1 && (frac& 0x1FF);


	frac = frac >> TFP_FRAC;
	if( (r==1 && s==1) || ( g==1 && r==1 && s==0)) {
		frac++;
	}
		
	if(expo >= 255) {
		if(sa^sb == 1) ret = NINF;
		else ret = PINF;
		return ret;
	}
	if(expo < -9) {
		if(sa^sb == 1) ret = NZERO;
		else ret = PZERO;
		return ret;
	}

	if(expo <= 0 && expo > -10) {
		frac = (frac|0x400)>>(1-expo);
		ret = ret << TFP_FRAC;
		ret = ret + frac;
		return ret;
	}

	ret = ret | expo;
	ret = ret << TFP_FRAC;
	ret = ret + frac;
	return ret;
}
