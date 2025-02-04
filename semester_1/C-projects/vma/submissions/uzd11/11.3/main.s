	.file	"main.c"
	.text
	.section	.rodata
.LC0:
	.string	"dat1"
.LC1:
	.string	"dat2"
.LC2:
	.string	"all good\n"
.LC3:
	.string	"something's wrong\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$1248, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, -1232(%rbp)
	leaq	.LC1(%rip), %rax
	movq	%rax, -1224(%rbp)
	movl	$0, -1236(%rbp)
	leaq	-1216(%rbp), %rax
	movl	$73, %ecx
	movl	$0, %edx
	movl	$100, %esi
	movq	%rax, %rdi
	call	fillArray@PLT
	leaq	-816(%rbp), %rax
	movl	$73, %ecx
	movl	$0, %edx
	movl	$100, %esi
	movq	%rax, %rdi
	call	fillArray@PLT
	leaq	-416(%rbp), %rax
	movl	$73, %ecx
	movl	$0, %edx
	movl	$100, %esi
	movq	%rax, %rdi
	call	fillArray@PLT
	leaq	-1216(%rbp), %rcx
	movq	-1232(%rbp), %rax
	movl	$100, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	saveToFile@PLT
	leaq	-416(%rbp), %rcx
	movq	-1232(%rbp), %rax
	movl	$100, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	saveToFile@PLT
	leaq	-1236(%rbp), %rdx
	leaq	-1216(%rbp), %rcx
	movq	-1232(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	loadFromFile@PLT
	leaq	-816(%rbp), %rcx
	movq	-1224(%rbp), %rax
	movl	$100, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	saveToFile@PLT
	leaq	-1236(%rbp), %rdx
	leaq	-416(%rbp), %rcx
	movq	-1224(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	loadFromFile@PLT
	leaq	-1236(%rbp), %rdx
	leaq	-816(%rbp), %rcx
	movq	-1232(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	loadFromFile@PLT
	movl	read_counter(%rip), %eax
	cmpl	$3, %eax
	jne	.L2
	movl	write_counter(%rip), %eax
	cmpl	$3, %eax
	jne	.L2
	leaq	.LC2(%rip), %rax
	jmp	.L3
.L2:
	leaq	.LC3(%rip), %rax
.L3:
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.2.0-23ubuntu4) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
