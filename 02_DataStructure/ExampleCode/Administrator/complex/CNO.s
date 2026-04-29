	.file	"CNO.c"
	.text
.globl _complex_number_init
	.def	_complex_number_init;	.scl	2;	.type	32;	.endef
_complex_number_init:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movl	%eax, (%edx)
	movl	8(%ebp), %edx
	movl	16(%ebp), %eax
	movl	%eax, 4(%edx)
	popl	%ebp
	ret
.globl _complex_number_add
	.def	_complex_number_add;	.scl	2;	.type	32;	.endef
_complex_number_add:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	flds	(%eax)
	movl	12(%ebp), %eax
	flds	(%eax)
	faddp	%st, %st(1)
	movl	16(%ebp), %eax
	fstps	(%eax)
	movl	8(%ebp), %eax
	flds	4(%eax)
	movl	12(%ebp), %eax
	flds	4(%eax)
	faddp	%st, %st(1)
	movl	16(%ebp), %eax
	fstps	4(%eax)
	popl	%ebp
	ret
.globl _complex_number_sub
	.def	_complex_number_sub;	.scl	2;	.type	32;	.endef
_complex_number_sub:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	flds	(%eax)
	movl	12(%ebp), %eax
	flds	(%eax)
	fsubrp	%st, %st(1)
	movl	16(%ebp), %eax
	fstps	(%eax)
	movl	8(%ebp), %eax
	flds	4(%eax)
	movl	12(%ebp), %eax
	flds	4(%eax)
	fsubrp	%st, %st(1)
	movl	16(%ebp), %eax
	fstps	4(%eax)
	popl	%ebp
	ret
	.section .rdata,"dr"
LC1:
	.ascii "A = %5.2f + %5.2fi\12\0"
	.text
.globl _complex_number_print
	.def	_complex_number_print;	.scl	2;	.type	32;	.endef
_complex_number_print:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	flds	4(%eax)
	movl	8(%ebp), %eax
	flds	(%eax)
	fxch	%st(1)
	fstpl	12(%esp)
	fstpl	4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	leave
	ret
.globl _complex_my_private_fun1
	.def	_complex_my_private_fun1;	.scl	2;	.type	32;	.endef
_complex_my_private_fun1:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	leave
	ret
	.def	_complex_my_private_fun2;	.scl	3;	.type	32;	.endef
_complex_my_private_fun2:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	leave
	ret
.lcomm _Complex_VAR2,16
	.comm	_Complex_VAR1, 4, 2
	.def	_printf;	.scl	2;	.type	32;	.endef
