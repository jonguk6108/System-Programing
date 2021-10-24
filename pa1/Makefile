# [ SWE2001 System Program sping 2021 ]
# [ HW1 - Tensor Floating Point ]

CC = gcc
TAR = tar
TARGET = hw1
OBJECTS = tfp.o hw1.o
STUDENT_ID = 2017312848

$(TARGET) : hw1.o tfp.o
	$(CC) -o $(TARGET) $(OBJECTS)

hw1.o : hw1.c
	$(CC) -c -o hw1.o hw1.c

tfp.o : tfp.c
	$(CC) -c -o tfp.o tfp.c

tar : 
	$(TAR) -cvzf $(STUDENT_ID).tar.gz tfp.c tfp.h

clean :
	rm *.o $(TARGET)
