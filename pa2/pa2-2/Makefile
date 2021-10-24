# [ SWE2001 System Program spring 2021 ]
# [ HW2 - x86 assembly ]

CC = gcc
TARGET = all

all : factorial_c factorial_s

factorial_c :
	$(CC) factorial.c -o factorial_c

factorial_s :
	$(CC) -no-pie factorial.s -o factorial_s

clean :
	rm -f factorial_c factorial_s
