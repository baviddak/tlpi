	.file	"my_readv.c"
	.text
	.globl	my_readv
	.type	my_readv, @function
my_readv:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -24(%rbp)
	movq	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L2
.L7:
	movl	-12(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	8(%rax), %rdx
	movl	-12(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rcx
	movq	-32(%rbp), %rax
	addq	%rcx, %rax
	movq	(%rax), %rcx
	movl	-20(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read@PLT
	movl	%eax, -16(%rbp)
	cmpl	$-1, -16(%rbp)
	jne	.L3
	movq	$-1, %rax
	jmp	.L4
.L3:
	cmpl	$0, -16(%rbp)
	jne	.L5
	movl	$0, %eax
	jmp	.L4
.L5:
	cmpl	$0, -16(%rbp)
	jle	.L6
	movl	-16(%rbp), %eax
	cltq
	addq	%rax, -8(%rbp)
	nop
.L6:
	addl	$1, -12(%rbp)
.L2:
	movl	-12(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jl	.L7
	movq	-8(%rbp), %rax
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	my_readv, .-my_readv
	.section	.rodata
.LC0:
	.string	"--help"
.LC1:
	.string	"%s input_file output_file\n"
.LC2:
	.string	"open"
.LC3:
	.string	"buffer %d has the string: %s\n"
	.align 8
.LC4:
	.string	"The number of bytes that is available in the buffer is %d\n"
	.align 8
.LC5:
	.string	"The number of bytes read into memory (the buffer) is %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$144, %rsp
	movl	%edi, -132(%rbp)
	movq	%rsi, -144(%rbp)
	cmpl	$2, -132(%rbp)
	jne	.L9
	movq	-144(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	leaq	.LC0(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L10
.L9:
	movq	-144(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	usageErr@PLT
.L10:
	movl	$0, -20(%rbp)
	movl	$384, -24(%rbp)
	movq	-144(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	-24(%rbp), %edx
	movl	-20(%rbp), %ecx
	movl	%ecx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	open@PLT
	movl	%eax, -28(%rbp)
	cmpl	$-1, -28(%rbp)
	jne	.L11
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	errExit@PLT
.L11:
	movl	$0, -4(%rbp)
	movq	$2, -120(%rbp)
	movq	$4, -104(%rbp)
	movq	$6, -88(%rbp)
	movq	$8, -72(%rbp)
	movq	$100, -56(%rbp)
	movq	$270, -40(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L12
.L13:
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$120, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, %rdx
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	addq	$-128, %rax
	movq	%rdx, (%rax)
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$120, %rax
	movq	(%rax), %rax
	movl	%eax, %edx
	movl	-4(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	addl	$1, -8(%rbp)
.L12:
	cmpl	$5, -8(%rbp)
	jle	.L13
	leaq	-128(%rbp), %rcx
	movl	-28(%rbp), %eax
	movl	$6, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	my_readv
	movl	%eax, -32(%rbp)
	cmpl	$-1, -32(%rbp)
	jne	.L14
	movl	$-1, %eax
	jmp	.L20
.L14:
	movl	$0, -12(%rbp)
	jmp	.L16
.L17:
	movl	-12(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	addq	$-128, %rax
	movq	(%rax), %rdx
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -12(%rbp)
.L16:
	cmpl	$5, -12(%rbp)
	jle	.L17
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-32(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC5(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-28(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	$0, -16(%rbp)
	jmp	.L18
.L19:
	movl	-16(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	addq	$-128, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	addl	$1, -16(%rbp)
.L18:
	cmpl	$5, -16(%rbp)
	jle	.L19
	movl	$0, %eax
.L20:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
