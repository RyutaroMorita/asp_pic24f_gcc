$
$ 		パス2のターゲット依存テンプレート（Explorer16/32 Development Board用）
$

$
$  有効な割込み番号，割込みハンドラ番号
$
$INTNO_VALID = { 0,1,...,117 }$
$INHNO_VALID = INTNO_VALID$

$
$  ATT_ISRで使用できる割込み番号とそれに対応する割込みハンドラ番号
$
$INTNO_ATTISR_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INHNO_VALID$

$
$  DEF_INT／DEF_EXCで使用できる割込みハンドラ番号／CPU例外ハンドラ番号
$
$INHNO_DEFINH_VALID = INHNO_VALID$

$
$  CFG_INTで使用できる割込み番号と割込み優先度
$
$INTNO_CFGINT_VALID = INTNO_VALID$
$INTPRI_CFGINT_VALID = { -7,-6,...,-1 }$

$
$  標準テンプレートファイルのインクルード
$
$INCLUDE "arch/pic24f_gcc/kernel/kernel.tf"$

/*$NL$
$SPC$*  Target-dependent Definitions (Explorer16/32 Development Board)$NL$
$SPC$*/$NL$
$NL$

$
$   CFG_INTのターゲット依存のエラーチェックと_kernel_bitpat_cfgintの生成
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
