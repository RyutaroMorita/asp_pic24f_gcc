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
 *  $Id: test_messagebuf1.c 2728 2015-12-30 01:46:11Z ertl-honda $
 */

/* 
 *		���b�Z�[�W�o�b�t�@�̃e�X�g(1)
 *
 * �y�e�X�g�̖ړI�z
 *
 *  FIFO�����b�Z�[�W�o�b�t�@�ɁC���b�Z�[�W�𑗐M���鏈���Ǝ�M���鏈��
 *  ����ʂ�e�X�g����D
 *
 * �y�e�X�g���ځz
 *
 *	(A) ���b�Z�[�W�o�b�t�@�ւ̑��M�����isnd_mbf�Csend_message�j
 *		(A-1) ��M�҂��L���[�̐擪�^�X�N����M�i�^�X�N�؊����Ȃ��j
 *		(A-2) ��M�҂��L���[�̐擪�^�X�N����M�i�^�X�N�؊�������j
 *		(A-3) ���b�Z�[�W�o�b�t�@�Ǘ��̈�Ɋi�[
 *		(A-4) ���M�҂��L���[�Ƀ^�X�N�����邽�߂ɑ��M�҂���Ԃ�
 *		(A-5) ���b�Z�[�W�o�b�t�@�Ǘ��̈�ɋ󂫂��Ȃ����߂ɑ��M�҂���Ԃ�
 *	(B) ���b�Z�[�W�o�b�t�@����̎�M�����ircv_mbf�Creceive_message�j
 *		(B-1) ���b�Z�[�W�o�b�t�@�Ǘ��̈悩���M
 *		(B-2) (B-1)�{���M�҂��^�X�N�i1�܂��͕����j���҂������i�^�X�N
 *			  �؊����Ȃ��j
 *		(B-3) (B-1)�{���M�҂��^�X�N�i1�܂��͕����j���҂������i�^�X�N
 *			  �؊�������j
 *		(B-4) ���M�҂��L���[�̐擪�̃^�X�N�̃��b�Z�[�W����M�i�^�X�N��
 *			  �����Ȃ��j
 *		(B-5) ���M�҂��L���[�̐擪�̃^�X�N�̃��b�Z�[�W����M�i�^�X�N��
 *			  ��������j
 *		(B-6) ��M�҂���Ԃ�
 *	(C) ���b�Z�[�W�o�b�t�@�Ǘ��̈�ւ̃��b�Z�[�W�̊i�[�ienqueue_message�j
 *		(C-1) �T�C�Y�ƃ��b�Z�[�W�{�̂���A�̗̈�Ɋi�[
 *		(C-2) �T�C�Y���i�[��ɊǗ��̈�̐擪�ɖ߂�
 *		(C-3) ���b�Z�[�W�{�̂̊i�[�r���ŊǗ��̈�̐擪�ɖ߂�
 *		(C-4) ���b�Z�[�W�{�̂̊i�[��ɊǗ��̈�̐擪�ɖ߂�
 *	(D) ���b�Z�[�W�o�b�t�@�Ǘ��̈悩��̃��b�Z�[�W�̎�o���idequeue_message�j
 *		(D-1) �T�C�Y�ƃ��b�Z�[�W�{�̂���A�̗̈悩���o��
 *		(D-2) �T�C�Y����o����ɊǗ��̈�̐擪�ɖ߂�
 *		(D-3) ���b�Z�[�W�{�̂̎�o���r���ŊǗ��̈�̐擪�ɖ߂�
 *		(D-4) ���b�Z�[�W�{�̂̎�o����ɊǗ��̈�̐擪�ɖ߂�
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
 *		ref_mbf(MBF1, &rmbf)
 *		assert(rmbf.stskid == TSK_NONE)
 *		assert(rmbf.rtskid == TSK_NONE)
 *		assert(rmbf.smbfcnt == 0)
 *		snd_mbf(MBF1, string1, 9)		... (A-3)(C-1)�C�g�p�F0�`15
 *	2:	snd_mbf(MBF1, string2, 5)		... (A-3)(C-4)�C�g�p�F0�`27
 *	3:	snd_mbf(MBF1, string3, 4)		... (A-5)
 *	== TASK2�i�D��x�F���j==
 *	4:	ref_mbf(MBF1, &rmbf)
 *		assert(rmbf.stskid == TASK1)
 *		assert(rmbf.rtskid == TSK_NONE)
 *		assert(rmbf.smbfcnt == 2)
 *	5:	snd_mbf(MBF1, string1, 4)		... (A-4)
 *	== TASK3�i�D��x�F��j==
 *	6:	rcv_mbf(MBF1, buf1) -> 9		... (B-3)(D-1)(C-1)�C�g�p�F16�`27,0�`15
 *	== TASK1�i�����j==
 *	7:	assert(strncmp(buf1, string1, 9) == 0)
 *		slp_tsk()
 *	== TASK2�i�����j==
 *	8:	rcv_mbf(MBF1, buf1) -> 5		... (B-1)(D-4)�C�g�p�F0�`15
 *		assert(strncmp(buf1, string2, 5) == 0)
 *		rcv_mbf(MBF1, buf1) -> 4		... (B-1)(D-1)�C�g�p�F8�`15
 *		assert(strncmp(buf1, string3, 4) == 0)
 *		rcv_mbf(MBF1, buf1) -> 4		... (B-1)(D-1)�C�g�p�F�Ȃ�
 *		assert(strncmp(buf1, string1, 4) == 0)
 *	9:	rcv_mbf(MBF1, buf1) -> 10		... (B-6)
 *	== TASK3�i�����j==
 *	10:	ref_mbf(MBF1, &rmbf)
 *		assert(rmbf.stskid == TSK_NONE)
 *		assert(rmbf.rtskid == TASK2)
 *		assert(rmbf.smbfcnt == 0)
 *	11:	snd_mbf(MBF1, string2, 10)		... (A-2)
 *	== TASK2�i�����j==
 *	12:	assert(strncmp(buf1, string2, 10) == 0)
 *		rcv_mbf(MBF1, buf1) -> 11		... (B-6)
 *	== TASK3�i�����j==
 *	13:	wup_tsk(TASK1)
 *	== TASK1�i�����j==
 *	14:	snd_mbf(MBF1, string3, 11)		... (A-1)
 *		assert(strncmp(buf1, string3, 11) == 0)
 *		snd_mbf(MBF1, string1, 16)		... (A-3)(C-3)�C�g�p�F16�`27,0�`7
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2�i�����j==
 *	15:	slp_tsk()
 *	== TASK3�i�����j==
 *	16:	snd_mbf(MBF1, string2, 12)		... (A-5)
 *	== TASK1�i�����j==
 *	17:	wup_tsk(TASK2)
 *		tslp_tsk(1) -> E_TMOUT
 *	== TASK2�i�����j==
 *	18:	snd_mbf(MBF1, string3, 4)		... (A-4)
 *	== TASK1�i�����j==
 *	19:	rcv_mbf(MBF1, buf1) -> 16		... (B-2)(D-3)(C-1)(C-2)�C
 *										... 				�g�p�F8�`27,0�`3
 *		assert(strncmp(buf1, string1, 16) == 0)
 *		slp_tsk()
 *	== TASK2�i�����j==
 *	20:	rcv_mbf(MBF1, buf1) -> 12		... (B-1)(D-1)�C�g�p�F24�`27�C0�`3
 *		assert(strncmp(buf1, string2, 12) == 0)
 *	21:	snd_mbf(MBF1, string1, 25)		... (A-5)
 *	== TASK3�i�����j==
 *	22:	rcv_mbf(MBF1, buf1) -> 4		... (B-1)(D-2)�C�g�p�F�Ȃ�
 *		assert(strncmp(buf1, string3, 4) == 0)
 *		rcv_mbf(MBF1, buf1) -> 25		... (B-5)
 *	== TASK2�i�����j==
 *	23:	assert(strncmp(buf1, string1, 25) == 0)
 *		snd_mbf(MBF1, string2, 26)		... (A-5)
 *	== TASK3�i�����j==
 *	24:	wup_tsk(TASK1)
 *	== TASK1�i�����j==
 *	25:	rcv_mbf(MBF1, buf1) -> 26		... (B-4)
 *		assert(strncmp(buf1, string2, 26) == 0)
 *		slp_tsk()
 *	== TASK2�i�����j==
 *	26:	slp_tsk()
 *	== TASK3�i�����j==
 *	27:	END
 */

#include <kernel.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_lib.h"
#include "test_messagebuf1.h"
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
	T_RMBF	rmbf;

	test_start(__FILE__);

	set_bit_func(bit_kernel);

	check_point(1);
	ercd = act_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = act_tsk(TASK3);
	check_ercd(ercd, E_OK);

	ercd = ref_mbf(MBF1, &rmbf);
	check_ercd(ercd, E_OK);

	check_assert(rmbf.stskid == TSK_NONE);

	check_assert(rmbf.rtskid == TSK_NONE);

	check_assert(rmbf.smbfcnt == 0);

	ercd = snd_mbf(MBF1, string1, 9);
	check_ercd(ercd, E_OK);

	check_point(2);
	ercd = snd_mbf(MBF1, string2, 5);
	check_ercd(ercd, E_OK);

	check_point(3);
	ercd = snd_mbf(MBF1, string3, 4);
	check_ercd(ercd, E_OK);

	check_point(7);
	check_assert(strncmp(buf1, string1, 9) == 0);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(14);
	ercd = snd_mbf(MBF1, string3, 11);
	check_ercd(ercd, E_OK);

	check_assert(strncmp(buf1, string3, 11) == 0);

	ercd = snd_mbf(MBF1, string1, 16);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(17);
	ercd = wup_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = tslp_tsk(1);
	check_ercd(ercd, E_TMOUT);

	check_point(19);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 16);

	check_assert(strncmp(buf1, string1, 16) == 0);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(25);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 26);

	check_assert(strncmp(buf1, string2, 26) == 0);

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task2(intptr_t exinf)
{
	ER_UINT	ercd;
	T_RMBF	rmbf;

	check_point(4);
	ercd = ref_mbf(MBF1, &rmbf);
	check_ercd(ercd, E_OK);

	check_assert(rmbf.stskid == TASK1);

	check_assert(rmbf.rtskid == TSK_NONE);

	check_assert(rmbf.smbfcnt == 2);

	check_point(5);
	ercd = snd_mbf(MBF1, string1, 4);
	check_ercd(ercd, E_OK);

	check_point(8);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 5);

	check_assert(strncmp(buf1, string2, 5) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 4);

	check_assert(strncmp(buf1, string3, 4) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 4);

	check_assert(strncmp(buf1, string1, 4) == 0);

	check_point(9);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 10);

	check_point(12);
	check_assert(strncmp(buf1, string2, 10) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 11);

	check_point(15);
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(18);
	ercd = snd_mbf(MBF1, string3, 4);
	check_ercd(ercd, E_OK);

	check_point(20);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 12);

	check_assert(strncmp(buf1, string2, 12) == 0);

	check_point(21);
	ercd = snd_mbf(MBF1, string1, 25);
	check_ercd(ercd, E_OK);

	check_point(23);
	check_assert(strncmp(buf1, string1, 25) == 0);

	ercd = snd_mbf(MBF1, string2, 26);
	check_ercd(ercd, E_OK);

	check_point(26);
	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}

void
task3(intptr_t exinf)
{
	ER_UINT	ercd;
	T_RMBF	rmbf;

	check_point(6);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 9);

	check_point(10);
	ercd = ref_mbf(MBF1, &rmbf);
	check_ercd(ercd, E_OK);

	check_assert(rmbf.stskid == TSK_NONE);

	check_assert(rmbf.rtskid == TASK2);

	check_assert(rmbf.smbfcnt == 0);

	check_point(11);
	ercd = snd_mbf(MBF1, string2, 10);
	check_ercd(ercd, E_OK);

	check_point(13);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_point(16);
	ercd = snd_mbf(MBF1, string2, 12);
	check_ercd(ercd, E_OK);

	check_point(22);
	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 4);

	check_assert(strncmp(buf1, string3, 4) == 0);

	ercd = rcv_mbf(MBF1, buf1);
	check_ercd(ercd, 25);

	check_point(24);
	ercd = wup_tsk(TASK1);
	check_ercd(ercd, E_OK);

	check_finish(27);
	check_point(0);
}
