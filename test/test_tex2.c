/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2007-2013 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: test_tex2.c 2728 2015-12-30 01:46:11Z ertl-honda $
 */

/* 
 *		�^�X�N��O�����Ɋւ���e�X�g(2)
 *
 * �y�e�X�g�̖ړI�z
 *
 *  �����݃n���h���i�A���[���n���h���j�����CPU��O�n���h������^�X�N��
 *  �O�������[�`�����N�����鏈����ԗ��I�Ƀe�X�g����D
 *
 * �y�e�X�g���ځz
 *
 *	(A) iras_tex�̃G���[���o
 *		(A-1) �Ώۃ^�X�N���x�~���
 *		(A-2) �Ώۃ^�X�N�̃^�X�N��O�������[�`������`����Ă��Ȃ�
 *	(B) �����݃n���h������Ă΂ꂽiras_tex�̐��폈��
 *		(B-1) �Ώۃ^�X�N�����s��Ԃ̃^�X�N���^�X�N��O��������
 *		(B-2) �Ώۃ^�X�N�����s��Ԃ̃^�X�N�łȂ�
 *		(B-3) �Ώۃ^�X�N�����s��Ԃ̃^�X�N�����^�X�N��O�����֎~
 *	(C) CPU��O�n���h������Ă΂ꂽiras_tex�̐��폈��
 *		(C-1) �Ώۃ^�X�N�����s��Ԃ̃^�X�N���^�X�N��O��������
 *		(C-2) �Ώۃ^�X�N�����s��Ԃ̃^�X�N�łȂ�
 *		(C-3) �Ώۃ^�X�N�����s��Ԃ̃^�X�N�����^�X�N��O�����֎~
 *				�� ���{���Ȃ��i�^�[�Q�b�g��ˑ��Ɏ����ł��Ȃ��j
 *	(D) �����݃n���h���̏o�������ɂ��N��
 *		(D-1) �f�B�X�p�b�`��̃^�X�N���^�X�N��O���Ń^�X�N��O�����v
 *			  ������
 *	(E) CPU��O�n���h���̏o�������ɂ��N��
 *		(E-1) �f�B�X�p�b�`��̃^�X�N���^�X�N��O���Ń^�X�N��O�����v
 *			  ������
 *	(F) sns_tex�Ŏ��s��Ԃ̃^�X�N���Ȃ�
 *
 * �y�g�p���\�[�X�z
 *
 *	TASK1: ���C���̃^�X�N�D���s��Ԃ̃^�X�N�ɑ΂��ă^�X�N��O������v����
 *		   ��Ώۃ^�X�N
 *	TASK2: ���s��ԂłȂ��^�X�N�ɑ΂��ă^�X�N��O������v������Ώۃ^�X�N
 *	TASK3: �^�X�N��O�������[�`������`����Ă��Ȃ��^�X�N
 *	TASK4: �x�~��Ԃ̃^�X�N
 *	ALM1:  �A���[���n���h��1
 *	ALM2:  �A���[���n���h��2
 *	ALM3:  �A���[���n���h��3
 *	CPUEXC: CPU��O�n���h��
 *
 * �y�e�X�g�V�[�P���X�z
 *
 *	== TASK1�i�D��x�F10�j==
 *	1:	state(false, false, TIPM_ENAALL, false, false, true)
 *		ref_tex(TSK_SELF, &rtex)
 *		assert((rtex.texstat & TTEX_DIS) != 0U)
 *		assert(rtex.pndptn == 0U)
 *	2:	sta_alm(ALM1, 1U)
 *		DO(while (!(alm1_flag)))	... �A���[���n���h��1�̎��s��҂�
 *	== ALM1 ==
 *	3:	state_i(true, false, false, true, true)
 *		iras_tex(TASK3, 0x0001) -> E_OBJ		... (A-2)
 *		iras_tex(TASK4, 0x0001) -> E_OBJ		... (A-1)
 *		iras_tex(TASK2, 0x0001)					... (B-2)
 *		iras_tex(TASK1, 0x0001)					... (B-3)
 *		DO(alm1_flag = true)
 *		RETURN
 *	== TASK1�i�����j==
 *	4:	ena_tex()
 *	== TASK1-TEX-1�i1��ځj==
 *	5:	assert(texptn == 0x0001)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *	6:	dis_dsp() ... 4�̏�Ԃ����ꂼ��ω�������
 *		chg_ipm(TMAX_INTPRI)
 *		ena_tex()
 *		loc_cpu()
 *		state(false, true, TMAX_INTPRI, true, true, false)
 *		RETURN
 *	== TASK1�i�����j==
 *	7:	state(false, false, TIPM_ENAALL, false, false, false)
 *		ref_tex(TSK_SELF, &rtex)
 *		assert((rtex.texstat & TTEX_ENA) != 0U)
 *		assert(rtex.pndptn == 0U)
 *	8:	sta_alm(ALM2, 1U)
 *		DO(while (!(alm2_flag)))
 *	== ALM2 ==
 *	9:	state_i(true, false, false, true, false)
 *		iras_tex(TASK1, 0x0002)					... (B-1)
 *		DO(alm2_flag = true)
 *		RETURN									... (D-1)
 *	== TASK1-TEX-2�i2��ځj==
 *	10:	assert(texptn == 0x0002)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *		RETURN
 *	== TASK1�i�����j==
 *	11:	sus_tsk(TASK2)
 *		sus_tsk(TASK3)
 *	12:	sta_alm(ALM3, 10U)
 *	13:	dly_tsk(50U)
 *	== ALM3 ==
 *	14:	state_i(true, false, false, true, true)	... (F)�msns_tex()���܂ށn
 *		iget_tid(&tskid)
 *		assert(tskid == TSK_NONE)
 *		iras_tex(TASK1, 0x0004)
 *		DO(alm3_flag = true)
 *		RETURN
 *	== TASK1-TEX-3�i3��ځj==
 *	15:	assert(texptn == 0x0004)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *		RETURN
 *	== TASK1�i�����j==
 *	16:	rsm_tsk(TASK2)
 *		rsm_tsk(TASK3)
 *		dis_dsp()
 *	17:	DO(RAISE_CPU_EXCEPTION)
 *	== CPUEXC ==
 *	18:	state_i(true, false, true, true, false)
 *		assert(xsns_xpn(p_excinf) == false)
 *		iras_tex(TASK3, 0x0010) -> E_OBJ		... (A-2)
 *		iras_tex(TASK4, 0x0010) -> E_OBJ		... (A-1)
 *		iras_tex(TASK2, 0x0010)					... (C-2)
 *		iras_tex(TASK1, 0x0010)					... (C-1)
 *		RETURN									... (E-1)
 *	== TASK1-TEX-4�i4��ځj==
 *	19:	assert(texptn == 0x0010)
 *		state(false, false, TIPM_ENAALL, true, true, true)
 *	20:	ext_tsk()
 *	== TASK2�i�D��x�F10�j==
 *	21:	state(false, false, TIPM_ENAALL, false, false, true)
 *	22:	ena_tex()
 *	== TASK2-TEX ==
 *	23:	assert(texptn == 0x0011)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *		RETURN
 *	== TASK2�i�����j==
 *	24:	sus_tsk(TASK3)
 *	25:	END
 */

#include <kernel.h>
#include <test_lib.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_tex2.h"

volatile bool_t	alm1_flag = false;
volatile bool_t	alm2_flag = false;
volatile bool_t	alm3_flag = false;

/*
 *  task3�Ctask4��tex_task4�͐�������Ȃ�
 */

void
task3(intptr_t exinf)
{
	check_point(0);
}

void
task4(intptr_t exinf)
{
	check_point(0);
}

void
tex_task4(TEXPTN texptn, intptr_t exinf)
{
	check_point(0);
}

/* DO NOT DELETE THIS LINE -- gentest depends on it. */

void
alarm1_handler(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point(3);
	check_state_i(true, false, false, true, true);

	ercd = iras_tex(TASK3, 0x0001);
	check_ercd(ercd, E_OBJ);

	ercd = iras_tex(TASK4, 0x0001);
	check_ercd(ercd, E_OBJ);

	ercd = iras_tex(TASK2, 0x0001);
	check_ercd(ercd, E_OK);

	ercd = iras_tex(TASK1, 0x0001);
	check_ercd(ercd, E_OK);

	alm1_flag = true;

	return;

	check_point(0);
}

void
alarm2_handler(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point(9);
	check_state_i(true, false, false, true, false);

	ercd = iras_tex(TASK1, 0x0002);
	check_ercd(ercd, E_OK);

	alm2_flag = true;

	return;

	check_point(0);
}

void
alarm3_handler(intptr_t exinf)
{
	ID		tskid;
	ER_UINT	ercd;

	check_point(14);
	check_state_i(true, false, false, true, true);

	ercd = iget_tid(&tskid);
	check_ercd(ercd, E_OK);

	check_assert(tskid == TSK_NONE);

	ercd = iras_tex(TASK1, 0x0004);
	check_ercd(ercd, E_OK);

	alm3_flag = true;

	return;

	check_point(0);
}

void
cpuexc_handler(void *p_excinf)
{
	ER_UINT	ercd;

	check_point(18);
	check_state_i(true, false, true, true, false);

	check_assert(xsns_xpn(p_excinf) == false);

	ercd = iras_tex(TASK3, 0x0010);
	check_ercd(ercd, E_OBJ);

	ercd = iras_tex(TASK4, 0x0010);
	check_ercd(ercd, E_OBJ);

	ercd = iras_tex(TASK2, 0x0010);
	check_ercd(ercd, E_OK);

	ercd = iras_tex(TASK1, 0x0010);
	check_ercd(ercd, E_OK);

	return;

	check_point(0);
}

void
task1(intptr_t exinf)
{
	ER_UINT	ercd;
	T_RTEX	rtex;

	test_start(__FILE__);

	check_point(1);
	check_state(false, false, TIPM_ENAALL, false, false, true);

	ercd = ref_tex(TSK_SELF, &rtex);
	check_ercd(ercd, E_OK);

	check_assert((rtex.texstat & TTEX_DIS) != 0U);

	check_assert(rtex.pndptn == 0U);

	check_point(2);
	ercd = sta_alm(ALM1, 1U);
	check_ercd(ercd, E_OK);

	while (!(alm1_flag));

	check_point(4);
	ercd = ena_tex();
	check_ercd(ercd, E_OK);

	check_point(7);
	check_state(false, false, TIPM_ENAALL, false, false, false);

	ercd = ref_tex(TSK_SELF, &rtex);
	check_ercd(ercd, E_OK);

	check_assert((rtex.texstat & TTEX_ENA) != 0U);

	check_assert(rtex.pndptn == 0U);

	check_point(8);
	ercd = sta_alm(ALM2, 1U);
	check_ercd(ercd, E_OK);

	while (!(alm2_flag));

	check_point(11);
	ercd = sus_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = sus_tsk(TASK3);
	check_ercd(ercd, E_OK);

	check_point(12);
	ercd = sta_alm(ALM3, 10U);
	check_ercd(ercd, E_OK);

	check_point(13);
	ercd = dly_tsk(50U);
	check_ercd(ercd, E_OK);

	check_point(16);
	ercd = rsm_tsk(TASK2);
	check_ercd(ercd, E_OK);

	ercd = rsm_tsk(TASK3);
	check_ercd(ercd, E_OK);

	ercd = dis_dsp();
	check_ercd(ercd, E_OK);

	check_point(17);
	RAISE_CPU_EXCEPTION;

	check_point(0);
}

static uint_t	tex_task1_count = 0;

void
tex_task1(TEXPTN texptn, intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++tex_task1_count) {
	case 1:
		check_point(5);
		check_assert(texptn == 0x0001);

		check_state(false, false, TIPM_ENAALL, false, false, true);

		check_point(6);
		ercd = dis_dsp();
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		ercd = ena_tex();
		check_ercd(ercd, E_OK);

		ercd = loc_cpu();
		check_ercd(ercd, E_OK);

		check_state(false, true, TMAX_INTPRI, true, true, false);

		return;

		check_point(0);

	case 2:
		check_point(10);
		check_assert(texptn == 0x0002);

		check_state(false, false, TIPM_ENAALL, false, false, true);

		return;

		check_point(0);

	case 3:
		check_point(15);
		check_assert(texptn == 0x0004);

		check_state(false, false, TIPM_ENAALL, false, false, true);

		return;

		check_point(0);

	case 4:
		check_point(19);
		check_assert(texptn == 0x0010);

		check_state(false, false, TIPM_ENAALL, true, true, true);

		check_point(20);
		ercd = ext_tsk();
		check_ercd(ercd, E_OK);

		check_point(0);

	default:
		check_point(0);
	}
	check_point(0);
}

void
task2(intptr_t exinf)
{
	ER_UINT	ercd;

	check_point(21);
	check_state(false, false, TIPM_ENAALL, false, false, true);

	check_point(22);
	ercd = ena_tex();
	check_ercd(ercd, E_OK);

	check_point(24);
	ercd = sus_tsk(TASK3);
	check_ercd(ercd, E_OK);

	check_finish(25);
	check_point(0);
}

void
tex_task2(TEXPTN texptn, intptr_t exinf)
{

	check_point(23);
	check_assert(texptn == 0x0011);

	check_state(false, false, TIPM_ENAALL, false, false, true);

	return;

	check_point(0);
}
