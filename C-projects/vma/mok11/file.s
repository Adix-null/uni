	.file	"file.c"
	.text
	.globl	read_counter
	.bss
	.align 4
	.type	read_counter, @object
	.size	read_counter, 4
read_counter:
	.zero	4
	.globl	write_counter
	.align 4
	.type	write_counter, @object
	.size	write_counter, 4
write_counter:
	.zero	4
	.section	.rodata
.LC0:
	.string	"wb"
.LC1:
	.string	"Klaida atidarant fail\304\205"
	.text
	.globl	saveToFile
	.type	saveToFile, @function
saveToFile:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movq	-24(%rbp), %rax
	leaq	.LC0(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L2
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	jmp	.L1
.L2:
	movl	write_counter(%rip), %eax
	addl	$1, %eax
	movl	%eax, write_counter(%rip)
	movq	-8(%rbp), %rdx
	leaq	-36(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rcx
	movq	-32(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	fwrite@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
.L1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	saveToFile, .-saveToFile
	.section	.rodata
.LC2:
	.string	"rb"
.LC3:
	.string	"Klaida skaitant dyd\304\257"
.LC4:
	.string	"Klaida skaitant duomenis"
	.text
	.globl	loadFromFile
	.type	loadFromFile, @function
loadFromFile:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-24(%rbp), %rax
	leaq	.LC2(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L5
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	jmp	.L4
.L5:
	movq	-8(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	fread@PLT
	cmpq	$1, %rax
	je	.L7
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	jmp	.L4
.L7:
	movq	-40(%rbp), %rax
	movl	(%rax), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rcx
	movq	-32(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	fread@PLT
	movq	%rax, %rdx
	movq	-40(%rbp), %rax
	movl	(%rax), %eax
	cltq
	cmpq	%rax, %rdx
	je	.L8
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	jmp	.L4
.L8:
	movl	read_counter(%rip), %eax
	addl	$1, %eax
	movl	%eax, read_counter(%rip)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	nop
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	loadFromFile, .-loadFromFile
	.globl	fillArray
	.type	fillArray, @function
fillArray:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	%ecx, -36(%rbp)
	movl	$0, %edi
	movl	$0, %eax
	call	time@PLT
	movl	%eax, %edi
	call	srand@PLT
	movl	$0, -4(%rbp)
	jmp	.L10
.L11:
	call	rand@PLT
	movl	-36(%rbp), %edx
	subl	-32(%rbp), %edx
	leal	1(%rdx), %esi
	cltd
	idivl	%esi
	movl	%edx, %ecx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	-32(%rbp), %edx
	addl	%ecx, %edx
	movl	%edx, (%rax)
	addl	$1, -4(%rbp)
.L10:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L11
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	fillArray, .-fillArray
	.section	.rodata
.LC5:
	.string	"%d "
	.text
	.globl	printArray
	.type	printArray, @function
printArray:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L13
.L14:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -4(%rbp)
.L13:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L14
	movl	$10, %edi
	call	putchar@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	printArray, .-printArray
	.section	.rodata
.LC6:
	.string	"something's wrong"
.LC7:
	.string	"all good"
	.text
	.globl	compArrays
	.type	compArrays, @function
compArrays:
.LFB10:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L16
.L19:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	-32(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	je	.L17
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L15
.L17:
	addl	$1, -4(%rbp)
.L16:
	cmpl	$99, -4(%rbp)
	jle	.L19
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L15:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	compArrays, .-compArrays
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
