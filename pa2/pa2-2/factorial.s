/*
2017312848 Park Jong Uk code.
SWE2001 System Program (Spring 2021)
Prof:	Jinkyu Jeong (jinkyu@skku.edu)

TA: Jongwon Park(jongwon.park@csi.skku.edu)
	Jaeguk Lee(jaekuk.lee@csi.skku.edu)
Semiconductor Building #400509
Author: Jongwon Park
Description: Find shortest path of maze
***Copyright (c) 2021 SungKyunKwan Univ. CSI***
*/

.data
buffer: 	.space 	4
BUFSIZE: 	.int 	4
file_in:	.string "pa2-2.in"
msg_print:	.string "factorial[%d] = %d\n"
msg_nl:		.string "\n"

/* code section start */
.text
.globl	main
main: 
/* === file open === */
movq $2, %rax		/* open(	; syscall #: 2 */
movq $file_in, %rdi	/* "pa2-2.in"	; filename */
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

/* === call fibo() === */
push %rax
movq $buffer, %r12
movl (%r12), %edi	/* Corrected */
call _factorial
movq %rax, %rbx
pop %rax

/* === print result === */
movq $msg_print, %rdi
movq $buffer, %r12
movl (%r12), %esi	/* Corrected */
movq %rbx, %rdx
call printf

/* === exit === */
movq $60, %rax
movq $0, %rdi
syscall

_factorial:
/* ============= Start of your code ================== */
cmpl $0, %edi
je .L1
cmpl $1, %edi
je .L1

push %rdi
decq %rdi
call _factorial
pop %rdi

.L2 :
imull %edi, %eax
ret

.L1 :
movl $1, %eax
ret
/* ============== End of your code =================== */
ret
