	.file	"list_procID.c"
	.section	.rodata
.LC0:
	.string	"/proc"
.LC1:
	.string	"."
.LC2:
	.string	".."
.LC3:
	.string	"%s is a directory!\n"
.LC4:
	.string	"The line is: %s\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$208, %rsp
	movl	%edi, -196(%rbp)
	movq	%rsi, -208(%rbp)
	movl	$144, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, -16(%rbp)
	movq	-208(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	userIdFromName@PLT
	movl	%eax, -20(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	opendir@PLT
	movq	%rax, -32(%rbp)
	call	__errno_location@PLT
	movl	$0, (%rax)
	jmp	.L2
.L6:
	movq	-40(%rbp), %rax
	addq	$19, %rax
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	je	.L2
	movq	-40(%rbp), %rax
	addq	$19, %rax
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L4
	jmp	.L2
.L4:
	leaq	-144(%rbp), %rax
	movl	$1869770799, (%rax)
	movw	$12131, 4(%rax)
	movb	$0, 6(%rax)
	movq	-40(%rbp), %rax
	leaq	19(%rax), %rdx
	leaq	-144(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcat@PLT
	movq	-8(%rbp), %rdx
	leaq	-144(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	lstat@PLT
	movq	-8(%rbp), %rax
	movl	24(%rax), %eax
	andl	$61440, %eax
	cmpl	$16384, %eax
	jne	.L2
	leaq	-144(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-144(%rbp), %rax
	movq	$-1, %rcx
	movq	%rax, %rdx
	movl	$0, %eax
	movq	%rdx, %rdi
	repnz scasb
	movq	%rcx, %rax
	notq	%rax
	leaq	-1(%rax), %rdx
	leaq	-144(%rbp), %rax
	addq	%rdx, %rax
	movabsq	$32498765033403183, %rcx
	movq	%rcx, (%rax)
	leaq	-144(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	open@PLT
	movl	%eax, -44(%rbp)
	cmpl	$-1, -44(%rbp)
	jne	.L5
	jmp	.L2
.L5:
	leaq	-192(%rbp), %rcx
	movl	-44(%rbp), %eax
	movl	$40, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read@PLT
	leaq	-192(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-44(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
.L2:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	readdir@PLT
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L6
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
