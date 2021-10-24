#ifndef TFP_H
#define TFP_H

/* TO BIN */
#define BYTE_TO_BIN(byte) \
(byte & 0x0080 ? '1' : '0'), (byte & 0x0040 ? '1' : '0'), \
(byte & 0x0020 ? '1' : '0'), (byte & 0x0010 ? '1' : '0'), \
(byte & 0x0008 ? '1' : '0'), (byte & 0x0004 ? '1' : '0'), \
(byte & 0x0002 ? '1' : '0'), (byte & 0x0001 ? '1' : '0')

#define BYTE_TO_BIN3(byte) \
(byte & 0x0004 ? '1' : '0'), \
(byte & 0x0002 ? '1' : '0'), (byte & 0x0001 ? '1' : '0')

#define U16_TO_BIN(var) BYTE_TO_BIN(var>>8), BYTE_TO_BIN(var)
#define U19_TO_BIN(var) BYTE_TO_BIN3(var>>16), U16_TO_BIN(var)
#define U24_TO_BIN(var) BYTE_TO_BIN(var>>16),U16_TO_BIN(var)
#define U32_TO_BIN(var) U16_TO_BIN(var>>16), U16_TO_BIN(var)

/* PRINT P */
#define BYTE_TO_BIN_P "%c%c%c%c%c%c%c%c"
#define BYTE3_TO_BIN_P "%c%c%c"
#define U16_TO_BIN_P  BYTE_TO_BIN_P"_"BYTE_TO_BIN_P
#define U19_To_BIN_P  BYTE3_TO_BIN_P"_"U16_TO_BIN_P
#define U24_TO_BIN_P  BYTE_TO_BIN_P"_"U16_TO_BIN_P
#define U32_TO_BIN_P  U16_TO_BIN_P"_"U16_TO_BIN_P

typedef unsigned int tfp;

tfp int2tfp(int input);
int tfp2int(tfp input);
tfp float2tfp(float input);
float tfp2float(tfp input);

tfp tfp_add(tfp in1, tfp in2);
tfp tfp_mul(tfp in1, tfp in2);

#endif
