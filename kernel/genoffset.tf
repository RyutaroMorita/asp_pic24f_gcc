$ ======================================================================
$ 
$   TOPPERS/ASP Kernel
$       Toyohashi Open Platform for Embedded Real-Time Systems/
$       Advanced Standard Profile Kernel
$ 
$   Copyright (C) 2011 by Embedded and Real-Time Systems Laboratory
$               Graduate School of Information Science, Nagoya Univ., JAPAN
$  
$   ��L���쌠�҂́C�ȉ���(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
$   �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E��
$   �ρE�Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
$   (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
$       ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
$       �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
$   (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
$       �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
$       �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
$       �̖��ۏ؋K����f�ڂ��邱�ƁD
$   (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
$       �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
$       �ƁD
$     (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
$         �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
$     (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
$         �񍐂��邱�ƁD
$   (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
$       �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
$       �܂��C�{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝
$       �R�Ɋ�Â�����������C��L���쌠�҂����TOPPERS�v���W�F�N�g��
$       �Ɛӂ��邱�ƁD
$  
$   �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
$   ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI
$   �ɑ΂���K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F
$   �A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C��
$   �̐ӔC�𕉂�Ȃ��D
$ 
$   $Id: genoffset.tf 2728 2015-12-30 01:46:11Z ertl-honda $
$ 
$ =====================================================================

$ 
$  #define�f�B���N�e�B�u�̐���
$ 
$FUNCTION DEFINE$
	#define $ARGV[1]$$TAB$$FORMAT("%d", +ARGV[2])$$NL$
$END$

$ 
$  �r�b�g�̃T�[�`
$ 
$FUNCTION SEARCH_BIT$
	$_val = ARGV[1]$
	$FOREACH _val_bit RANGE(0,7)$
		$IF (_val & 1) != 0$
			$RESULT = _val_bit$
		$END$
		$_val = _val >> 1$
	$END$
$END$

$ 
$  �r�b�g�t�B�[���h�̃I�t�Z�b�g�ƃr�b�g�ʒu�̒�`�̐���
$ 
$FUNCTION DEFINE_BIT$
	$label = ARGV[1]$
	$struct_size = ARGV[2]$
	$output_size = ARGV[3]$

	$top = SYMBOL(label)$
	$IF !LENGTH(top)$
		$ERROR$$FORMAT("label %1% not found", label)$$END$
	$ELSE$
		$val = 0$
		$FOREACH i RANGE(0,struct_size-1)$
			$tmp_val = PEEK(top + i, 1)$
			$IF val == 0 && tmp_val != 0$
				$val = tmp_val$
				$offset = i$
			$END$
		$END$

		$IF val == 0$
			$ERROR$$FORMAT("bit not found in %1%", ARGV[1])$$END$
		$ELSE$
			$val_bit = SEARCH_BIT(val)$
			$RESULT = {}$
			$IF EQ(output_size, "W")$
				$IF SIL_ENDIAN_BIG$
					$val_bit = val_bit + 24 - ((offset & 0x03) << 3)$
				$ELSE$
					$val_bit = val_bit + ((offset & 0x03) << 3)$
				$END$
				$offset = offset & ~0x03$
			$ELSE$$IF EQ(output_size, "H")$
				$IF SIL_ENDIAN_BIG$
					$val_bit = val_bit + 8 - ((offset & 0x01) << 3)$
				$ELSE$
					$val_bit = val_bit + ((offset & 0x01) << 3)$
				$END$
				$offset = offset & ~0x01$
			$END$$END$
		$END$

		#define $label$$TAB$$FORMAT("%d", +offset)$$NL$
		#define $label$_bit$TAB$$FORMAT("%d", +val_bit)$$NL$
		#define $label$_mask$TAB$$FORMAT("0x%x", 1 << val_bit)$$NL$
	$END$
$END$

$ 
$  �o�C�g�z�u�̃`�F�b�N
$ 
$FUNCTION MAGIC_CHECK$
	$size = ARGV[1]$
	$check = ARGV[2]$

	$label = FORMAT("MAGIC_%d", +size)$
	$top = SYMBOL(label)$
	$IF !LENGTH(top)$
		$ERROR$$FORMAT("label %1% not found", label)$$END$
	$ELSE$
		$FOREACH offset RANGE(1,size)$
			$IF SIL_ENDIAN_BIG$
				$val = PEEK(top + offset - 1, 1)$
			$ELSE$
				$val = PEEK(top + size - offset, 1)$
			$END$
			$IF val != AT(check, offset - 1)$
				$ERROR$$FORMAT("value check of %1% failed", label)$$END$
			$END$
		$END$
	$END$
$END$

$MAGIC_CHECK(1, { 0x12 })$
$MAGIC_CHECK(2, { 0x12, 0x34 })$
$MAGIC_CHECK(4, { 0x12, 0x34, 0x56, 0x78 })$

$ 
$  �t�@�C���w�b�_�̐���
$ 
$FILE "offset.h"$
/* offset.h */$NL$
$NL$
