$
$ 		�p�X2�̃^�[�Q�b�g�ˑ��e���v���[�g�iExplorer16/32 Development Board�p�j
$

$
$  �L���Ȋ����ݔԍ��C�����݃n���h���ԍ�
$
$INTNO_VALID = { 0,1,...,117 }$
$INHNO_VALID = INTNO_VALID$

$
$  ATT_ISR�Ŏg�p�ł��銄���ݔԍ��Ƃ���ɑΉ����銄���݃n���h���ԍ�
$
$INTNO_ATTISR_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INHNO_VALID$

$
$  DEF_INT�^DEF_EXC�Ŏg�p�ł��銄���݃n���h���ԍ��^CPU��O�n���h���ԍ�
$
$INHNO_DEFINH_VALID = INHNO_VALID$

$
$  CFG_INT�Ŏg�p�ł��銄���ݔԍ��Ɗ����ݗD��x
$
$INTNO_CFGINT_VALID = INTNO_VALID$
$INTPRI_CFGINT_VALID = { -7,-6,...,-1 }$

$
$  �W���e���v���[�g�t�@�C���̃C���N���[�h
$
$INCLUDE "arch/pic24f_gcc/kernel/kernel.tf"$

/*$NL$
$SPC$*  Target-dependent Definitions (Explorer16/32 Development Board)$NL$
$SPC$*/$NL$
$NL$

$
$   CFG_INT�̃^�[�Q�b�g�ˑ��̃G���[�`�F�b�N��_kernel_bitpat_cfgint�̐���
$

$FOREACH inhno INTNO_VALID$
	extern void $FORMAT("__kernel_int_handler_%d(void);", +inhno)$$NL$
	asm(".section .isr.text, code \n\t"$NL$
	$FORMAT("\"__kernel_int_handler_%d: \\n\\t\"", +inhno)$$NL$
	"	mov w1, [w15++] \n\t"$NL$
	$FORMAT("\"	mov #%d, w1 \\n\\t\"", +inhno)$$NL$
	"	goto _kernel_inthdr_entry \n\t");$NL$
	$NL$
$END$

FP _kernel_exc_tbl[] = $NL$
{$NL$
$FOREACH inhno INTNO_VALID$
	$IF LENGTH(INH.INHNO[inhno])$
		$TAB$(FP)($INH.INTHDR[inhno]$),
	$ELSE$
		$TAB$(FP)(_kernel_default_int_handler),
	$END$
	$SPC$$FORMAT("/* %d */", +inhno)$$NL$
$END$
};$NL$

$NL$
asm(".section ivt, code, address(0x00004) \n\t"$NL$
"	.pword __OscillatorFail \r\n"$NL$
"	.pword __AddressError \r\n"$NL$
"	.pword __NVMError \r\n"$NL$
"	.pword __StackError \r\n"$NL$
"	.pword __MathError \r\n"$NL$
"	.pword __DefaultInterrupt \r\n"$NL$
"	.pword __DefaultInterrupt \r\n"$NL$
"	.pword __DefaultInterrupt \r\n"$NL$
$FOREACH inhno INTNO_VALID$
	$FORMAT("\"	.pword __kernel_int_handler_%d \\n\\t\"", +inhno)$$NL$
$END$
".section .text \n\t"$NL$
);$NL$
