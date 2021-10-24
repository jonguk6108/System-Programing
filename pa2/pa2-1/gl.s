/*
2017312848 Park Jong Uk code.
SWE2001 System Program (Spring 2021)
Prof:	Jinkyu Jeong (jinkyu@skku.edu)

TA: Jongwon Park(jongwon.park@csi.skku.edu)
	Jaeguk Lee(jaekuk.lee@csi.skku.edu)
Semiconductor Building #400509
Author: Jaeguk Lee
Description: Find GCD (Greate Common Divisor) and LCM (Least Common Multiple)
***Copyright (c) 2021 SungKyunKwan Univ. CSI***
*/

.data
buffer: 	.space 	12
BUFSIZE: 	.int 	12
file_in:	.string "pa2-1.in"
msg_GCD:	.string "Greate Common Divisor\t[%d, %d, %d] = %d\n"
msg_LCM:	.string "Least Common Multiple\t[%d, %d, %d] = %d\n"

/* code section start */
.text
.globl	main
main: 
/* === file open === */
movq $2, %rax		/* open(	; syscall #: 2 */
movq $file_in, %rdi	/* "hw2-3.in"	; filename */
movq $0x000, %rsi	/* O_RDONLY	; flags */
movq $0644, %rdx	/* 0644		; mode */
syscall			/* );		; */

movq %rax, %rbx		/* save fd */
/* === file read === */
movq $0, %rax		/* read (	; syscall #: 0 */
movq %rbx, %rdi		/* fd 		; file descriptor */
movq $buffer, %rsi	/* buf 		; buffer address */
movq $BUFSIZE, %rdx	/* BUFSIZE	; read size (byte unit) */
syscall			/* ); */

/* === file close === */
movq $3, %rax
movq %rbx, %rdi
syscall

/* === call gcd() === */
push %rax
movq $buffer, %r12
movl (%r12), %edi
movl 4(%r12), %esi
movl 8(%r12), %edx

call _gcd
movl %eax, %ebx
pop %rax

/* === call lcm() === */
push %rax
movq $buffer, %r12
movl (%r12), %edi
movl 4(%r12), %esi
movl 8(%r12), %edx
call _lcm
movl %eax, %ecx
pop %rax

/* === print result === */
push %rax
push %rcx
movq $msg_GCD, %rdi
movq $buffer, %r12
movl (%r12), %esi
movl 4(%r12), %edx
movl 8(%r12), %ecx
movq %rbx, %r8
call printf
pop %rcx
pop %rax

movq $msg_LCM, %rdi
movq $buffer, %r12
movl (%r12), %esi
movl 4(%r12), %edx
movq %rcx, %r8
movl 8(%r12), %ecx
call printf

/* === exit === */
movq $60, %rax
movq $0, %rdi
syscall

_gcd:
/* ============= Start of your code ================== */
push %rbx
push %rcx

movq $0, %rbx
movq $0, %rcx

cmpl %esi, %edi
movl %esi, %ecx
cmovg %edi, %ecx

cmpl %edx, %ecx
cmovg %edx, %ecx
movl %ecx, %ebx


cmpl $0, %ebx 
jle .L1


.L2 :
push %rdx
movq $0, %rdx
movq %rdi, %rax
idivl %ebx
cmpl $0, %edx
pop %rdx
jne .L3

push %rdx
movq $0, %rdx
movq %rsi, %rax
idivl %ebx
cmpl $0, %edx
pop %rdx
jne .L3

push %rdx
movq $0, %rdx
movq %rdx, %rax
idivl %ebx
cmpl $0, %edx
pop %rdx
je .L1

.L3 :
decl %ebx
cmpl $0, %ebx
jg .L2

.L1:
movq %rbx, %rax
pop %rcx
pop %rbx
/* ============== End of your code =================== */
ret

_lcm:
/* ============= Start of your code ================== */
push %r10
push %rbx
push %rcx

movq $0, %r10
movq $0, %rbx
movq $0, %rcx

cmpl %esi, %edi
movl %esi, %ecx
cmovg %edi, %ecx

cmpl %edx, %ecx
cmovg %edx, %ecx


movq %rdi, %r10
imulq %rsi, %r10
imulq %rdx, %r10

movl %ecx, %ebx
cmpq %r10, %rbx 
jg .L4

.L5 :
push %rdx
movq $0, %rdx
movq %rbx, %rax
idivl %edi
cmpl $0, %edx
pop %rdx
jne .L6

push %rdx
movq $0, %rdx
movq %rbx, %rax
idivl %esi
cmpl $0, %edx
pop %rdx
jne .L6

push %rsi
movq %rdx, %rsi
push %rdx
movq $0, %rdx
movq %rbx, %rax
idivl %esi
cmpl $0, %edx
pop %rdx
pop %rsi
je .L4

.L6 :
addq %rcx, %rbx
cmpq %r10, %rbx 
jle .L5

.L4 :
movq %rbx, %rax
pop %rcx
pop %rbx
pop %r10
/* ============== End of your code =================== */
ret
