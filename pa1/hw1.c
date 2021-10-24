#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tfp.h"

int main(){
	char type[2];
	int input_i[2];
	union _union{
		unsigned int ui;
		float f;
	} input_f[2];
	tfp input_tfp[2];
	tfp add_tfp;
	tfp mul_tfp;

	scanf("%c ", &type[0]);
	if (type[0] == 'i') {
		scanf("%d ", &input_i[0]);
	} else if (type[0] == 'f') {
		scanf("%f ", &input_f[0].f);
	} else{
		printf("Invalid type - 1\n");
		return 0;
	}

	scanf("%c ", &type[1]);
	if (type[1] == 'i')
		scanf("%d", &input_i[1]);
	else if (type[1] == 'f')
		scanf("%f", &input_f[1].f);
	else{
		printf("Invalid type - 2\n");
		return 0;
	}

	printf("[ Test 1: Type Conversion ]\n");

	if(type[0] == 'i') 
		input_tfp[0] = int2tfp(input_i[0]);
	else 
		input_tfp[0] = float2tfp(input_f[0].f);

	if(type[1] == 'i') 
		input_tfp[1] = int2tfp(input_i[1]);
	else 
		input_tfp[1] = float2tfp(input_f[1].f);

	if(type[0] == 'i') 
		printf("    INT   "U32_TO_BIN_P" is converted into TFP   %c%c%c_"U16_TO_BIN_P"\n",
			 U32_TO_BIN(input_i[0]), BYTE_TO_BIN3(input_tfp[0]>>16), U16_TO_BIN(input_tfp[0]));
	else 
		printf("    FLOAT "U32_TO_BIN_P" is converted into TFP   %c%c%c_"U16_TO_BIN_P"\n",
			 U32_TO_BIN(input_f[0].ui), BYTE_TO_BIN3(input_tfp[0]>>16), U16_TO_BIN(input_tfp[0]));

	if(type[1] == 'i') 
		printf("    INT   "U32_TO_BIN_P" is converted into TFP   %c%c%c_"U16_TO_BIN_P"\n",
		 	U32_TO_BIN(input_i[1]), BYTE_TO_BIN3(input_tfp[1]>>16), U16_TO_BIN(input_tfp[1]));
	else 
		printf("    FLOAT "U32_TO_BIN_P" is converted into TFP   %c%c%c_"U16_TO_BIN_P"\n",
			 U32_TO_BIN(input_f[1].ui), BYTE_TO_BIN3(input_tfp[1]>>16), U16_TO_BIN(input_tfp[1]));

	if(type[0] == 'i') 
		input_i[0] = tfp2int(input_tfp[0]);
	else 
		input_f[0].f = tfp2float(input_tfp[0]);

	if(type[1] == 'i') 
		input_i[1] = tfp2int(input_tfp[1]);
	else 
		input_f[1].f = tfp2float(input_tfp[1]);

	if(type[0] == 'i') 
		printf("    TFP   %c%c%c_"U16_TO_BIN_P" is converted into INT   "U32_TO_BIN_P"\n", 
			BYTE_TO_BIN3(input_tfp[0]>>16), U16_TO_BIN(input_tfp[0]), U32_TO_BIN(input_i[0]));
	else 
		printf("    TFP   %c%c%c_"U16_TO_BIN_P" is converted into FLOAT "U32_TO_BIN_P"\n", 
			BYTE_TO_BIN3(input_tfp[0]>>16), U16_TO_BIN(input_tfp[0]), U32_TO_BIN(input_f[0].ui));

	if(type[1] == 'i') 
		printf("    TFP   %c%c%c_"U16_TO_BIN_P" is converted into INT   "U32_TO_BIN_P"\n", 
			BYTE_TO_BIN3(input_tfp[1]>>16), U16_TO_BIN(input_tfp[1]), U32_TO_BIN(input_i[1]));
	else 
		printf("    TFP   %c%c%c_"U16_TO_BIN_P" is converted into FLOAT "U32_TO_BIN_P"\n",
			 BYTE_TO_BIN3(input_tfp[1]>>16), U16_TO_BIN(input_tfp[1]), U32_TO_BIN(input_f[1].ui));

	printf("\n[ Test 2: Addition ]\n");

	add_tfp = tfp_add(input_tfp[0], input_tfp[1]);
	printf("    %c%c%c_"U16_TO_BIN_P" + %c%c%c_"U16_TO_BIN_P" = %c%c%c_"U16_TO_BIN_P"\n",
		 BYTE_TO_BIN3(input_tfp[0]>>16), U16_TO_BIN(input_tfp[0]), BYTE_TO_BIN3(input_tfp[1]>>16), U16_TO_BIN(input_tfp[1]), BYTE_TO_BIN3(add_tfp>>16), U16_TO_BIN(add_tfp));

	printf("\n[ Test 3: Multiplication ]\n");

	mul_tfp = tfp_mul(input_tfp[0], input_tfp[1]);
	printf("    %c%c%c_"U16_TO_BIN_P" * %c%c%c_"U16_TO_BIN_P" = %c%c%c_"U16_TO_BIN_P"\n",
		BYTE_TO_BIN3(input_tfp[0]>>16), U16_TO_BIN(input_tfp[0]), BYTE_TO_BIN3(input_tfp[1]>>16), U16_TO_BIN(input_tfp[1]), BYTE_TO_BIN3(mul_tfp>>16), U16_TO_BIN(mul_tfp));

	return 0;
}
