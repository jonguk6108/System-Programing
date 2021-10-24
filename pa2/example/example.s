.globl main

.data
msg_0: .string "hello_world\n"
msg_1: .string "bye_world\n"
len_0 = 12
len_1 = 10
#len_0 = . -msg_0
#len_1 = . -msg_1

.text
main:

movl $2, %ebx		# i = 2
movl $3, %ecx		# j = 3

cmpl %ebx, %ecx		# === if (i < j)
jle .L1 		#  goto L1

movl $1, %eax		# write (	    | syscall #: 1
movl $1, %edi		# 1,		    | file descriptor (stdout:1)
movl $msg_1, %esi 	# "bye_world\n",  | buffer address
movl $len_1, %edx	# <length of text>  | buffer length
syscall			# )
jmp .L2

			# === else
.L1:
movl $1, %eax		# write (	   | syscall #: 1
movl $1, %edi		# 1,		   | file descriptor (stdout:1)
movl $msg_0, %esi	# "hello_world\n",   | buffer address
movl $len_0, %edx	# <length of text> | buffer length
syscall			# )

.L2:
movl $60, %eax		# exit (	  | syscall #: 60
movl $0, %ebx		# 0		  | error_code
syscall			# )
