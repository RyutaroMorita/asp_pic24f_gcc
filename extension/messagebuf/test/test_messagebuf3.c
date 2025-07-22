/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2014 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  ��L���쌠�҂́C�ȉ���(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
 *  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E��
 *  �ρE�Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 *      �܂��C�{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝
 *      �R�Ɋ�Â�����������C��L���쌠�҂����TOPPERS�v���W�F�N�g��
 *      �Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI
 *  �ɑ΂���K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F
 *  �A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C��
 *  �̐ӔC�𕉂�Ȃ��D
 * 
 *  $Id: test_messagebuf3.c 2728 2015-12-30 01:46:11Z ertl-honda $
 */

/* 
 *		���b�Z�[�W�o�b�t�@�̃e�X�g(3)
 *
 * �y�e�X�g�̖ړI�z
 *
 *  �^�X�N�D��x�����b�Z�[�W�o�b�t�@�́CFIFO�����b�Z�[�W�o�b�t�@�ƈق�
 *  ��U�������e�X�g����D
 *
 * �y�e�X�g���ځz
 *
 *	(A) ���M�҂��L���[���^�X�N�D��x�ł��邱��
 *		(A-1) �ォ�瓞���������D��x�^�X�N���O�ɂȂ���邱��
 *		(A-2) �����D��x�̃^�X�N��FIFO���ł��邱��
 *	(B) ���M�҂��L���[�Ƀ^�X�N�����邽�߂ɑ��M�҂���ԂɂȂ�����̈Ⴂ
 *		(B-1) ���M�҂��L���[����̏ꍇ
 *		(B-2) ���M�҂��L���[�ɒႢ�D��x�̃^�X�N�݂̂�����ꍇ
 *		(B-3) ���M�҂��L���[�ɓ����������D��x�̃^�X�N������ꍇ
 *	(C) ���M�҂��L���[�̐擪�^�X�N�̗D��x�������Đ擪�^�X�N���ς��ꍇ
 *		(C-1) ���M�҂��^�X�N�̑҂������Ȃ�
 *		(C-2) ���M�҂��^�X�N�i1�܂��͕����j���҂������i�^�X�N�؊����Ȃ��j
 *		(C-3) ���M�҂��^�X�N�i1�܂��͕����j���҂������i�^�X�N�؊�������j
 *	(D) ���M�҂��L���[�̓r���^�X�N�̗D��x���グ�Đ擪�^�X�N���ς��ꍇ
 *		(D-1) ���M�҂��^�X�N�̑҂������Ȃ�
 *		(D-2) ���M�҂��^�X�N�i1�܂��͕����j���҂������i�^�X�N�؊����Ȃ��j
 *		(D-3) ���M�҂��^�X�N�i1�܂��͕����j���҂������i�^�X�N�؊�������j
 *
 * �y�g�p���\�[�X�z
 *
 *	TASK1: ���D��x�^�X�N�C���C���^�X�N�C�ŏ�����N��
 *	TASK2: ���D��x�^�X�N
 *	TASK3: ���D��x�^�X�N
 *	TASK4: ��D��x�^�X�N
 *	MBF1: ���b�Z�[�W�o�b�t�@�iTA_TPRI�����C�ő僁�b�Z�[�W�T�C�Y�F26�C���b
 *		  �Z�[�W�o�b�t�@�Ǘ��̈�̃T�C�Y�F26�����ۂɂ�28�j
 *
 * �y�e�X�g�V�[�P���X�z
 *
 *	== TASK1�i�D��x�F���j==
 *		call(set_bit_func(bit_kernel))
 *	1:	act_tsk(TASK2)
 *		act_tsk(TASK4)
 *		slp_tsk()
 *	== TASK2�i�D��x�F���j==
 *	2:	snd_mbf(MBF1, string1, 26)
 *	== TASK4�i�D��x�F��j==
 *	3:	wup_tsk(TASK1)
 *	== TASK1�i�����j==
 *	4:	snd_mbf(MBF1, string2, 25)						... (A-1)
 *	== TASK4�i�����j==
 *	5:	ref_mbf(MBF1, &rmbf)
 *		assert(rmbf.stskid == TASK1)
 *		assert(rmbf.rtskid == TSK_NONE)
 *		assert(rmbf.smbfcnt == 0)
 *		rcv_mbf(MBF1, buf1) -> 25
 *	== TASK1�i�����j==
 *	6:	assert(strncmp(buf1, string2, 25) == 0)
 *		act_tsk(TASK3)
 *		slp_tsk()
 *	== TASK3�i�D��x�F���j==
 *	7:	snd_mbf(MBF1, string2, 26)						... (A-2)
 *	== TASK4�i�����j==
 *	8:	rcv_mbf(MBF1, buf1) -> 26
 *	== TASK2�i�����j==
 *	9:	assert(strncmp(buf1, string1, 26) == 0)
 *		rcv_mbf(MBF1, buf1) -> 26
 *		assert(strncmp(buf1, string2, 26) == 0)
 *	10:	snd_mbf(MBF1, string3, 10)						... (B-1)
 *		rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *	11:	snd_mbf(MBF1, string1, 26)
 *	== TASK3�i�����j==
 *	12:	wup_tsk(TASK1)
 *	== TASK1�i�����j==
 *	13:	snd_mbf(MBF1, string2, 10)						... (B-2)
 *		rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string2, 10) == 0)
 *		slp_tsk()
 *	== TASK3�i�����j==
 *	14:	snd_mbf(MBF1, string3, 10)						... (B-3)
 *	== TASK4�i�����j==
 *	15:	rcv_mbf(MBF1, buf1) -> 26
 *	== TASK2�i�����j==
 *	16:	assert(strncmp(buf1, string1, 26) == 0)
 *		rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *	17:	snd_mbf(MBF1, string1, 26)
 *	== TASK3�i�����j==
 *	18:	snd_mbf(MBF1, string2, 26)
 *	== TASK4�i�����j==
 *	19:	chg_pri(TASK2, LOW_PRIORITY)					... (C-1)
 *		rcv_mbf(MBF1, buf1) -> 26
 *	== TASK3�i�����j==
 *	20:	assert(strncmp(buf1, string2, 26) == 0)
 *		rcv_mbf(MBF1, buf1) -> 26
 *		assert(strncmp(buf1, string1, 26) == 0)
 *		chg_pri(TASK2, TPRI_INI)						... ���ɖ߂�
 *	21:	snd_mbf(MBF1, string1, 26)
 *	== TASK2�i�����j==
 *	22:	snd_mbf(MBF1, string2, 10)
 *	== TASK4�i�����j==
 *	23:	wup_tsk(TASK1)
 *	== TASK1�i�����j==
 *	24:	chg_pri(TASK3, LOW_PRIORITY)					... (C-2)
 *		slp_tsk()
 *	== TASK2�i�����j==
 *	25:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string2, 10) == 0)
 *		chg_pri(TASK3, TPRI_INI)						... ���ɖ߂�
 *	26:	snd_mbf(MBF1, string3, 10)
 *	== TASK4�i�����j==
 *	27:	chg_pri(TASK3, LOW_PRIORITY)					... (C-3)
 *	== TASK2�i�����j==
 *	28:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *		chg_pri(TASK3, TPRI_INI)						... ���ɖ߂�
 *	29:	snd_mbf(MBF1, string1, 26)
 *	== TASK4�i�����j==
 *	30:	chg_pri(TASK2, HIGH_PRIORITY)					... (D-1)
 *		rcv_mbf(MBF1, buf1) -> 26
 *	== TASK2�i�����j==
 *	31:	assert(strncmp(buf1, string1, 26) == 0)
 *		chg_pri(TSK_SELF, TPRI_INI)						... ���ɖ߂�
 *	32:	snd_mbf(MBF1, string2, 10)
 *	== TASK4�i�����j==
 *	33:	wup_tsk(TASK1)
 *	== TASK1�i�����j==
 *	34:	chg_pri(TASK2, HIGH_PRIORITY)					... (D-2)
 *		slp_tsk()
 *	== TASK2�i�����j==
 *	35:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string2, 10) == 0)
 *		chg_pri(TSK_SELF, TPRI_INI)						... ���ɖ߂�
 *	36:	snd_mbf(MBF1, string3, 10)
 *	== TASK4�i�����j==
 *	37:	chg_pri(TASK2, HIGH_PRIORITY)					... (D-3)
 *	== TASK2�i�����j==
 *	38:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *		rcv_mbf(MBF1, buf1) -> 26
 *		assert(strncmp(buf1, string1, 26) == 0)
 *	39:	END
 */

#include <kernel.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_lib.h"
#include "test_messagebuf3.h"
#include <string.h>

const char string1[26] = "abcdefghijklmnopqrstuvwxyz";
const char string2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char string3[16] = "0123456789abcdef";

char buf1[26];

extern ER	bit_kernel(void);

/* DO NOT DELETE THIS LINE -- gentest depends on it. */

void
task1(intptr_t exinf)
{
	ER_UINT	ercd;

	test_start(__FILE__);

	set_bit_func(bit_kernel);

	check_point(1);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = act_tsk(TASK4);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(4);
	ercd = snd_mbf(MBF1, string2, 25);
	check_ercd(ercd, E_OK);

	check_point(6);
	check_assert(strncmp(buf1, string2, 25) == 0);

	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(13);
	ercd = snd_mbf(MBF1, string2, 10);
	check_ercd(ercd, E_OK);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string2, 10) == 0);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(24);
	ercd = chg_pri(TASK3, LOW_PRIORITY);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(34);
	ercd = chg_pri(TASK2, HIGH_PRIORITY);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task2(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point(2);
	ercd = snd_mbf(MBF1, string1, 26);
	check_ercd(ercd, E_OK);

	check_point(9);
	check_assert(strncmp(buf1, string1, 26) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_assert(strncmp(buf1, string2, 26) == 0);

	check_point(10);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	check_point(11);
	ercd = snd_mbf(MBF1, string1, 26);
	check_ercd(ercd, E_OK);

	check_point(16);
	check_assert(strncmp(buf1, string1, 26) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	check_point(17);
	ercd = snd_mbf(MBF1, string1, 26);
	check_ercd(ercd, E_OK);

	check_point(22);
	ercd = snd_mbf(MBF1, string2, 10);
	check_ercd(ercd, E_OK);

	check_point(25);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string2, 10) == 0);

	ercd = chg_pri(TASK3, TPRI_INI);
	check_ercd(ercd, E_OK);

	check_point(26);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(28);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	ercd = chg_pri(TASK3, TPRI_INI);
	check_ercd(ercd, E_OK);

	check_point(29);
	ercd = snd_mbf(MBF1, string1, 26);
	check_ercd(ercd, E_OK);

	check_point(31);
	check_assert(strncmp(buf1, string1, 26) == 0);

	ercd = chg_pri(TSK_SELF, TPRI_INI);
	check_ercd(ercd, E_OK);

	check_point(32);
	ercd = snd_mbf(MBF1, string2, 10);
	check_ercd(ercd, E_OK);

	check_point(35);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string2, 10) == 0);

	ercd = chg_pri(TSK_SELF, TPRI_INI);
	check_ercd(ercd, E_OK);

	check_point(36);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(38);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_assert(strncmp(buf1, string1, 26) == 0);

	check_finish(39);
	check_point(0);
}

void
task3(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point(7);
	ercd = snd_mbf(MBF1, string2, 26);
	check_ercd(ercd, E_OK);

	check_point(12);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(14);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(18);
	ercd = snd_mbf(MBF1, string2, 26);
	check_ercd(ercd, E_OK);

	check_point(20);
	check_assert(strncmp(buf1, string2, 26) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_assert(strncmp(buf1, string1, 26) == 0);

	ercd = chg_pri(TASK2, TPRI_INI);
	check_ercd(ercd, E_OK);

	check_point(21);
	ercd = snd_mbf(MBF1, string1, 26);
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task4(intptr_t exinf)
{
	ER_UINT	ercd;
	T_RMBF	rmbf;

	check_point(3);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(5);
	ercd = ref_mbf(MBF1, &rmbf);
	check_ercd(ercd, E_OK);

	check_assert(rmbf.stskid == TASK1);

	check_assert(rmbf.rtskid == TSK_NONE);

	check_assert(rmbf.smbfcnt == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 25);

	check_point(8);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_point(15);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_point(19);
	ercd = chg_pri(TASK2, LOW_PRIORITY);
	check_ercd(ercd, E_OK);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_point(23);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(27);
	ercd = chg_pri(TASK3, LOW_PRIORITY);
	check_ercd(ercd, E_OK);

	check_point(30);
	ercd = chg_pri(TASK2, HIGH_PRIORITY);
	check_ercd(ercd, E_OK);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_point(33);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(37);
	ercd = chg_pri(TASK2, HIGH_PRIORITY);
	check_ercd(ercd, E_OK);

	check_point(0);
}
