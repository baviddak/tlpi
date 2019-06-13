	.file	"mem_segments.c"
	.comm	globBuf,65536,32
	.globl	primes
	.data
	.align 16
	.type	primes, @object
	.size	primes, 16
primes:
	.long	2
	.long	3
	.long	5
	.long	7
	.text
	.type	square, @function
square:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	-20(%rbp), %eax
	imull	-20(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	square, .-square
	.section	.rodata
.LC0:
	.string	"The square of %d is %d\n"
.LC1:
	.string	"The cube of %d is %d\n"
	.text
	.type	doCalc, @function
doCalc:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, %edi
	call	square
	movl	%eax, %edx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	cmpl	$999, -20(%rbp)
	jg	.L5
	movl	-20(%rbp), %eax
	imull	-20(%rbp), %eax
	imull	-20(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L5:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	doCalc, .-doCalc
	.globl	main
	.type	main, @function
main:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$1024, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	movl	key.2719(%rip), %eax
	movl	%eax, %edi
	call	doCalc
	movl	$0, %edi
	call	exit@PLT
	.cfi_endproc
.LFE4:
	.size	main, .-main
	.data
	.align 4
	.type	key.2719, @object
	.size	key.2719, 4
key.2719:
	.long	9973
	.local	mbuf.2720
	.comm	mbuf.2720,10240000,32
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
