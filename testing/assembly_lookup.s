	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	_routine                ## -- Begin function routine
	.p2align	4, 0x90
_routine:                               ## @routine
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	$0, -16(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movabsq	$1000000000000000, %rax ## imm = 0x38D7EA4C68000
	cmpq	%rax, -16(%rbp)
	jge	LBB0_4
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movq	_test(%rip), %rax
	addq	$1, %rax
	movq	%rax, _test(%rip)
## %bb.3:                               ##   in Loop: Header=BB0_1 Depth=1
	movq	-16(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -16(%rbp)
	jmp	LBB0_1
LBB0_4:
	movq	$0, -24(%rbp)
LBB0_5:                                 ## =>This Inner Loop Header: Depth=1
	movabsq	$1000000000000000, %rax ## imm = 0x38D7EA4C68000
	cmpq	%rax, -24(%rbp)
	jge	LBB0_8



# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    assembly_lookup.s                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 03:02:44 by absalhi           #+#    #+#              #
#    Updated: 2023/01/25 03:02:45 by absalhi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## %bb.6:                               ##   in Loop: Header=BB0_5 Depth=1
	movq	_test(%rip), %rax			##		read variable
	addq	$-1, %rax					##		increment value
	movq	%rax, _test(%rip)			##		write variable
## %bb.7:                               ##   in Loop: Header=BB0_5 Depth=1
	movq	-24(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -24(%rbp)
	jmp	LBB0_5
LBB0_8:
	movq	$0, -32(%rbp)
LBB0_9:                                 ## =>This Inner Loop Header: Depth=1
	movabsq	$1000000000000000, %rax ## imm = 0x38D7EA4C68000
	cmpq	%rax, -32(%rbp)
	jge	LBB0_12
## %bb.10:                              ##   in Loop: Header=BB0_9 Depth=1
	movq	_test(%rip), %rax
	addq	$1, %rax
	movq	%rax, _test(%rip)
## %bb.11:                              ##   in Loop: Header=BB0_9 Depth=1
	movq	-32(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -32(%rbp)
	jmp	LBB0_9
LBB0_12:
	xorl	%eax, %eax
                                        ## kill: def $rax killed $eax
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	xorl	%eax, %eax
	movl	%eax, %ecx
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	-24(%rbp), %rdi
	movq	%rcx, %rsi
	leaq	_routine(%rip), %rdx
	callq	_pthread_create
	cmpl	$0, %eax
	je	LBB1_2
## %bb.1:
	movl	$1, -4(%rbp)
	jmp	LBB1_9
LBB1_2:
	xorl	%eax, %eax
	movl	%eax, %ecx
	leaq	-32(%rbp), %rdi
	movq	%rcx, %rsi
	leaq	_routine(%rip), %rdx
	callq	_pthread_create
	cmpl	$0, %eax
	je	LBB1_4
## %bb.3:
	movl	$1, -4(%rbp)
	jmp	LBB1_9
LBB1_4:
	xorl	%eax, %eax
	movl	%eax, %esi
	movq	-24(%rbp), %rdi
	callq	_pthread_join
	cmpl	$0, %eax
	je	LBB1_6
## %bb.5:
	movl	$1, -4(%rbp)
	jmp	LBB1_9
LBB1_6:
	xorl	%eax, %eax
	movl	%eax, %esi
	movq	-32(%rbp), %rdi
	callq	_pthread_join
	cmpl	$0, %eax
	je	LBB1_8
## %bb.7:
	movl	$1, -4(%rbp)
	jmp	LBB1_9
LBB1_8:
	movq	_test(%rip), %rsi
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$0, -4(%rbp)
	movl	%eax, -36(%rbp)         ## 4-byte Spill
LBB1_9:
	movl	-4(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_test                   ## @test
.zerofill __DATA,__common,_test,8,3
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%lld\n"


.subsections_via_symbols
