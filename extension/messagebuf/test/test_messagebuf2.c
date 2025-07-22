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
 *  $Id: test_messagebuf2.c 2728 2015-12-30 01:46:11Z ertl-honda $
 */

/* 
 *		���b�Z�[�W�o�b�t�@�̃e�X�g(2)
 *
 * �y�e�X�g�̖ړI�z
 *
 *  FIFO�����b�Z�[�W�o�b�t�@�̑��M�҂��^�X�N���C�����I�ɑ҂��������ꂽ
 *  �ꍇ����ʂ�e�X�g����D
 *
 * �y�e�X�g���ځz
 *
 *	(A) ���M�҂��^�X�N�������I���iter_tsk�j
 *		(A-1) ���M�҂��^�X�N�̑҂������Ȃ�
 *		(A-2) ���M�҂��^�X�N�i1�܂��͕����j���҂������i�^�X�N�؊����Ȃ��j
 *		(A-3) ���M�҂��^�X�N�i1�܂��͕����j���҂������i�^�X�N�؊�������j
 *	(B) ���M�҂��^�X�N�������҂������irel_wai�j
 *		(B-1) ���M�҂��^�X�N�̑҂������Ȃ�
 *		(B-2) ���M�҂��^�X�N�i1�܂��͕����j���҂������i�^�X�N�؊����Ȃ��j
 *		(B-3) ���M�҂��^�X�N�i1�܂��͕����j���҂������i�^�X�N�؊�������j
 *	(C) ���M�҂��^�X�N�������҂������iirel_wai�j
 *		(C-1) ���M�҂��^�X�N�̑҂������Ȃ�
 *		(C-2) ���M�҂��^�X�N�i1�܂��͕����j���҂������i�^�X�N�؊����Ȃ��j
 *		(C-3) ���M�҂��^�X�N�i1�܂��͕����j���҂������i�^�X�N�؊�������j
 *	(D) ���M�҂��^�X�N���^�C���A�E�g�ő҂�����
 *		(D-1) ���M�҂��^�X�N�̑҂������Ȃ�
 *		(D-2) ���M�҂��^�X�N�i1�܂��͕����j���҂������i�^�X�N�؊����Ȃ��j
 *		(D-3) ���M�҂��^�X�N�i1�܂��͕����j���҂������i�^�X�N�؊�������j
 *
 * �y�g�p���\�[�X�z
 *
 *	TASK1: ���D��x�^�X�N�C���C���^�X�N�C�ŏ�����N��
 *	TASK2: ���D��x�^�X�N
 *	TASK3: ��D��x�^�X�N
 *	MBF1: ���b�Z�[�W�o�b�t�@�iTA_NULL�����C�ő僁�b�Z�[�W�T�C�Y�F26�C���b
 *		  �Z�[�W�o�b�t�@�Ǘ��̈�̃T�C�Y�F26�����ۂɂ�28�j
 *
 * �y�e�X�g�V�[�P���X�z
 *
 *	== TASK1�i�D��x�F���j==
 *		call(set_bit_func(bit_kernel))
 *	1:	act_tsk(TASK2)
 *		act_tsk(TASK3)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2-1�i�D��x�F���j1��� ==
 *	2:	snd_mbf(MBF1, string1, 26)
 *	== TASK3�i�D��x�F��j==
 *	3:	snd_mbf(MBF1, string2, 26)
 *	== TASK1�i�����j==
 *	4:	ter_tsk(TASK2)									... (A-1)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK1�i�����j==
 *	5:	rcv_mbf(MBF1, buf1) -> 26
 *		assert(strncmp(buf1, string2, 26) == 0)
 *		act_tsk(TASK2)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2-2�i�D��x�F���j2��� ==
 *	6:	snd_mbf(MBF1, string1, 26)
 *	== TASK3�i�����j==
 *	7:	snd_mbf(MBF1, string3, 10)
 *	== TASK1�i�����j==
 *	8:	ter_tsk(TASK2)									... (A-2)
 *		slp_tsk()
 *	== TASK3�i�����j==
 *	9:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *	10:	act_tsk(TASK2)
 *	== TASK2-3�i�D��x�F���j3��� ==
 *	11:	snd_mbf(MBF1, string1, 26)
 *	== TASK3�i�����j==
 *	12:	wup_tsk(TASK1)
 *	== TASK1�i�����j==
 *	13:	snd_mbf(MBF1, string3, 10)
 *	== TASK3�i�����j==
 *	14:	ter_tsk(TASK2)									... (A-3)
 *	== TASK1�i�����j==
 *	15:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *		act_tsk(TASK2)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2-4�i�D��x�F���j4��� ==
 *	16:	snd_mbf(MBF1, string1, 26) -> E_RLWAI
 *	== TASK3�i�����j==
 *	17:	snd_mbf(MBF1, string2, 26)
 *	== TASK1�i�����j==
 *	18:	rel_wai(TASK2)									... (B-1)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2-4�i�����j==
 *	19:	slp_tsk()
 *	== TASK1�i�����j==
 *	20:	rcv_mbf(MBF1, buf1) -> 26
 *		assert(strncmp(buf1, string2, 26) == 0)
 *		wup_tsk(TASK2)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2-4�i�����j==
 *	21:	snd_mbf(MBF1, string1, 26) -> E_RLWAI
 *	== TASK3�i�����j==
 *	22:	snd_mbf(MBF1, string3, 10)
 *	== TASK1�i�����j==
 *	23:	rel_wai(TASK2)									... (B-2)
 *		slp_tsk()
 *	== TASK2-4�i�����j==
 *	24:	slp_tsk()
 *	== TASK3�i�����j==
 *	25:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *	26:	wup_tsk(TASK2)
 *	== TASK2-4�i�����j==
 *	27:	snd_mbf(MBF1, string1, 26) -> E_RLWAI
 *	== TASK3�i�����j==
 *	28:	wup_tsk(TASK1)
 *	== TASK1�i�����j==
 *	29:	snd_mbf(MBF1, string3, 10)
 *	== TASK3�i�����j==
 *	30:	rel_wai(TASK2)									... (B-3)
 *	== TASK1�i�����j==
 *	31:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2-4�i�����j==
 *	32:	snd_mbf(MBF1, string1, 26) -> E_RLWAI
 *	== TASK3�i�����j==
 *	33:	snd_mbf(MBF1, string2, 26)
 *	== TASK1�i�����j==
 *	34:	sta_alm(ALM1, 1U)
 *		slp_tsk()
 *	== ALM1-1 ==
 *	35:	irel_wai(TASK2)									... (C-1)
 *		iwup_tsk(TASK1)
 *		RETURN
 *	== TASK1�i�����j==
 *	36:	tslp_tsk(1) -> E_TMOUT
 *	== TASK2-4�i�����j==
 *	37:	slp_tsk()
 *	== TASK1�i�����j==
 *	38:	rcv_mbf(MBF1, buf1) -> 26
 *		assert(strncmp(buf1, string2, 26) == 0)
 *		wup_tsk(TASK2)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2-4�i�����j==
 *	39:	snd_mbf(MBF1, string1, 26) -> E_RLWAI
 *	== TASK3�i�����j==
 *	40:	snd_mbf(MBF1, string3, 10)
 *	== TASK1�i�����j==
 *	41:	sta_alm(ALM1, 1U)
 *		slp_tsk()
 *	== ALM1-2 ==
 *	42:	irel_wai(TASK2)									... (C-2)
 *		RETURN
 *	== TASK2-4�i�����j==
 *	43:	slp_tsk()
 *	== TASK3�i�����j==
 *	44:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *	45:	wup_tsk(TASK2)
 *	== TASK2-4�i�����j==
 *	46:	snd_mbf(MBF1, string1, 26) -> E_RLWAI
 *	== TASK3�i�����j==
 *	47:	wup_tsk(TASK1)
 *	== TASK1�i�����j==
 *	48:	snd_mbf(MBF1, string3, 10)
 *	== TASK3�i�����j==
 *	49:	sta_alm(ALM1, 1U)
 *		slp_tsk()
 *	== ALM1-3 ==
 *	50:	irel_wai(TASK2)									... (C-3)
 *		RETURN
 *	== TASK1�i�����j==
 *	51:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *		wup_tsk(TASK3)
 *		slp_tsk()
 *	== TASK2-4�i�����j==
  *	52:	tsnd_mbf(MBF1, string1, 26, 1) -> E_TMOUT		... (D-1)
 *	== TASK3�i�����j==
 *	53:	snd_mbf(MBF1, string2, 26)
 *	== TASK2-4�i�����j==
 *	54:	tslp_tsk(1) -> E_TMOUT
 *	== TASK2-4�i�����j==
 *	55:	rcv_mbf(MBF1, buf1) -> 26
 *		assert(strncmp(buf1, string2, 26) == 0)
 *	56:	tsnd_mbf(MBF1, string1, 26, 1) -> E_TMOUT		... (D-2)
 *	== TASK3�i�����j==
 *	57:	snd_mbf(MBF1, string3, 10)
 *	== TASK2-4�i�����j==
 *	58:	slp_tsk()
 *	== TASK3�i�����j==
 *	59:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *	60:	wup_tsk(TASK2)
 *	== TASK2-4�i�����j==
 *	61:	tsnd_mbf(MBF1, string1, 26, 1) -> E_TMOUT		... (D-3)
 *	== TASK3�i�����j==
 *	62:	wup_tsk(TASK1)
 *	== TASK1�i�����j==
 *	63:	snd_mbf(MBF1, string3, 10)
 *	== TASK3�i�����j==
 *	64:	slp_tsk()
 *	== TASK1�i�����j==
 *	65:	rcv_mbf(MBF1, buf1) -> 10
 *		assert(strncmp(buf1, string3, 10) == 0)
 *		slp_tsk()
 *	== TASK2-4�i�����j==
 *	66:	END
 */

#include <kernel.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_lib.h"
#include "test_messagebuf2.h"
#include <string.h>

const char string1[26] = "abcdefghijklmnopqrstuvwxyz";
const char string2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char string3[16] = "0123456789abcdef";

char buf1[26];

extern ER	bit_kernel(void);

/* DO NOT DELETE THIS LINE -- gentest depends on it. */

static uint_t	alarm1_count = 0;

void
alarm1_handler(intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++alarm1_count) {
	case 1:
		check_point(35);
		ercd = irel_wai(TASK2);
		check_ercd(ercd, E_OK);

		ercd = iwup_tsk(TASK1);
		check_ercd(ercd, E_OK);

		return;

		check_point(0);

	case 2:
		check_point(42);
		ercd = irel_wai(TASK2);
		check_ercd(ercd, E_OK);

		return;

		check_point(0);

	case 3:
		check_point(50);
		ercd = irel_wai(TASK2);
		check_ercd(ercd, E_OK);

		return;

		check_point(0);

	default:
		check_point(0);
	}
	check_point(0);
}

void
task1(intptr_t exinf)
{
	ER_UINT	ercd;

	test_start(__FILE__);

	set_bit_func(bit_kernel);

	check_point(1);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(4);
	ercd = ter_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(5);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_assert(strncmp(buf1, string2, 26) == 0);

	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(8);
	ercd = ter_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(13);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(15);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(18);
	ercd = rel_wai(TASK2);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(20);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_assert(strncmp(buf1, string2, 26) == 0);

	ercd = wup_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(23);
	ercd = rel_wai(TASK2);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(29);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(31);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(34);
	ercd = sta_alm(ALM1, 1U);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(36);
	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(38);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_assert(strncmp(buf1, string2, 26) == 0);

	ercd = wup_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(41);
	ercd = sta_alm(ALM1, 1U);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(48);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(51);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	ercd = wup_tsk(TASK3);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(63);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(65);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

static uint_t	task2_count = 0;

void
task2(intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++task2_count) {
	case 1:
		check_point(2);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_OK);

		check_point(0);

	case 2:
		check_point(6);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_OK);

		check_point(0);

	case 3:
		check_point(11);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_OK);

		check_point(0);

	case 4:
		check_point(16);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_RLWAI);

		check_point(19);
		ercd = slp_tsk();
		check_ercd(ercd, E_OK);

		check_point(21);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_RLWAI);

		check_point(24);
		ercd = slp_tsk();
		check_ercd(ercd, E_OK);

		check_point(27);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_RLWAI);

		check_point(32);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_RLWAI);

		check_point(37);
		ercd = slp_tsk();
		check_ercd(ercd, E_OK);

		check_point(39);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_RLWAI);

		check_point(43);
		ercd = slp_tsk();
		check_ercd(ercd, E_OK);

		check_point(46);
		ercd = snd_mbf(MBF1, string1, 26);
		check_ercd(ercd, E_RLWAI);

		check_point(52);
		ercd = tsnd_mbf(MBF1, string1, 26, 1);
		check_ercd(ercd, E_TMOUT);

		check_point(54);
		ercd = tslp_tsk(1);
		check_ercd(ercd, E_TMOUT);

		check_point(55);
		ercd = rcv_mbf(MBF1, buf1);
		check_ercd(ercd, 26);

		check_assert(strncmp(buf1, string2, 26) == 0);

		check_point(56);
		ercd = tsnd_mbf(MBF1, string1, 26, 1);
		check_ercd(ercd, E_TMOUT);

		check_point(58);
		ercd = slp_tsk();
		check_ercd(ercd, E_OK);

		check_point(61);
		ercd = tsnd_mbf(MBF1, string1, 26, 1);
		check_ercd(ercd, E_TMOUT);

		check_finish(66);
		check_point(0);

	default:
		check_point(0);
	}
	check_point(0);
}

void
task3(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point(3);
	ercd = snd_mbf(MBF1, string2, 26);
	check_ercd(ercd, E_OK);

	check_point(7);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(9);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	check_point(10);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(12);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(14);
	ercd = ter_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(17);
	ercd = snd_mbf(MBF1, string2, 26);
	check_ercd(ercd, E_OK);

	check_point(22);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(25);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	check_point(26);
	ercd = wup_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(28);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(30);
	ercd = rel_wai(TASK2);
	check_ercd(ercd, E_OK);

	check_point(33);
	ercd = snd_mbf(MBF1, string2, 26);
	check_ercd(ercd, E_OK);

	check_point(40);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(44);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	check_point(45);
	ercd = wup_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(47);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(49);
	ercd = sta_alm(ALM1, 1U);
	check_ercd(ercd, E_OK);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(53);
	ercd = snd_mbf(MBF1, string2, 26);
	check_ercd(ercd, E_OK);

	check_point(57);
	ercd = snd_mbf(MBF1, string3, 10);
	check_ercd(ercd, E_OK);

	check_point(59);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_assert(strncmp(buf1, string3, 10) == 0);

	check_point(60);
	ercd = wup_tsk(TASK2);
	check_ercd(ercd, E_OK);

	check_point(62);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(64);
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}
