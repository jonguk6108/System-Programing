/*
2017312848 Park Jong Uk code.
SWE2001 System Program (Spring 2021)
Prof:	Jinkyu Jeong (jinkyu@skku.edu)

TA: Jongwon Park(jongwon.park@csi.skku.edu)
	Jaeguk Lee(jaekuk.lee@csi.skku.edu)
Semiconductor Building #400509
Author: Jiwon Woo
Description: Find shortest path of maze
***Copyright (c) 2021 SungKyunKwan Univ. CSI***
*/


/* data section start */
.data
/* ============= Your code can be here =============== */
INF:	.int 0x190
MAX_INDEX:	.int	80
/* =================================================== */


/* code section start */
.text
.globl	findPath
findPath:
/* ============= Start of your code ================== */
push %rbp
push %r10
push %r12
push %r13
push %r11
push %r15
push %rbx

movq $0, %r10
movq $400, %r10
movq $1, %r12

movq $0, %r15	 #index
movl %edx, %r15d 
imull %ecx, %r15d
leal (%r15d, %esi, 1), %r15d

push %r14 #is it end point?
movq $0, %r14
movl %ecx, %r14d
imull %r8d, %r14d
subl $0x1, %r14d
cmpl %r14d, %r15d
jne .L1 	#skip
movl (%r9, %r15, 1), %r14d
cmpl $0, %r14d
movl $INF, %eax
cmove %edi, %eax
jmp .L2		#finsh
.L1 :

movb $0x2, (%r9, %r15, 1)	#m[index] = 2;


movq $0, %r11		#state 0
movl %esi, %ebx
movq $0, %r14
movl %ecx, %r14d
subl $0x1, %r14d
movq $0, %r13
movl %edx, %r13d
imull %ecx, %r13d
leal 1(%r13d, %esi, 1), %r13d
jmp .L3
.L6 :
push %rdi
push %rsi
addq $0x1, %rdi
addq $0x1, %rsi
callq findPath
pop %rsi
pop %rdi
jmp .L8

.L5 :		#state 1
movq $1, %r11
movl %edx, %ebx
movq $0, %r14
movl %r8d, %r14d
subl $0x1, %r14d
movq $0, %r13
movl %edx, %r13d
addl $1, %r13d
imull %ecx, %r13d
leal (%r13d, %esi, 1), %r13d
jmp .L3
.L7 :
push %rdi
push %rdx
addq $0x1, %rdi
addq $0x1, %rdx
callq findPath
pop %rdx
pop %rdi
jmp .L8

.L9 :		#state 2
movq $2, %r11
movl %esi, %r14d
movq $0, %rbx
movq $0, %r13
movl %edx, %r13d
imull %ecx, %r13d
leal -1(%r13d, %esi, 1), %r13d
jmp .L3
.L11 :
push %rdi
push %rsi
addq $0x1, %rdi
subq $0x1, %rsi
callq findPath
pop %rsi
pop %rdi
jmp .L8


.L12 :		#state 3
movq $3, %r11
movl %edx, %r14d
movq $0, %rbx
movq $0, %r13
movl %edx, %r13d
subl $1, %r13d
imull %ecx, %r13d
leal (%r13d, %esi, 1), %r13d
jmp .L3
.L13 :
push %rdi
push %rdx
subq $0x1, %rdx
addq $0x1, %rdi
callq findPath
pop %rdx
pop %rdi
jmp .L8




.L8 :
cmpl %eax, %r10d
cmovg %eax, %r10d
movl $0, %r12d
jmp .L10

.L10 :	#checking start point
cmpl $1, %r11d
jl .L5 #state 1's start
je .L9 #state 2's start
cmpl $2, %r11d
je .L12 #state 3's start
jg .L4


.L3 :		#if
cmpl %ebx, %r14d
jle .L10
cmpl $0, %r13d
jl .L10
cmpl $MAX_INDEX, %r13d
jg .L10
movzbq (%r9, %r13, 1), %r13
cmpl $0, %r13d
jne .L10

cmpl $1, %r11d
jl .L6 #state 0's normal
je .L7 #state 1's normal
cmpl $2, %r11d
je .L11 #state 2's normal
jg .L13 #state 3's normal


.L4 : #m[index] = 0;
movb $0x0, (%r9, %r15, 1)	#m[index] = 0;
cmpl $0, %r12d

movq $0, %rax
movq $400, %rax
cmove %r10d, %eax


.L2 :
pop %rbx
pop %r14
pop %r15
pop %r11
pop %r13
pop %r12
pop %r10
pop %rbp
/* ============== End of your code =================== */
ret
