/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2006-2013 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: test_tex1.c 2728 2015-12-30 01:46:11Z ertl-honda $
 */

/* 
 *		�^�X�N��O�����Ɋւ���e�X�g(1)
 *
 * �y�e�X�g�̖ړI�z
 *
 *  �^�X�N����^�X�N��O�������[�`�����N�����鏈����ԗ��I�Ƀe�X�g����D
 *
 * �y�e�X�g���ځz
 *
 *	(A) ras_tex�̃G���[���o
 *		(A-1) �Ώۃ^�X�N���x�~��ԁmNGKI1413�n
 *		(A-2) �Ώۃ^�X�N�̃^�X�N��O�������[�`������`����Ă��Ȃ��mNGKI1414�n
 *	(B) dis_tex�̃G���[���o
 *		(B-1) ���^�X�N�̃^�X�N��O�������[�`������`����Ă��Ȃ��mNGKI1421�n
 *	(C) ena_tex�̃G���[���o
 *		(C-1) ���^�X�N�̃^�X�N��O�������[�`������`����Ă��Ȃ��mNGKI1426�n
 *	(D) ref_tex�̃G���[���o
 *		(D-1) �Ώۃ^�X�N���x�~��ԁmNGKI1439�n
 *		(D-2) �Ώۃ^�X�N�̃^�X�N��O�������[�`������`����Ă��Ȃ��mNGKI1440�n
 *	(E) ras_tex�̐��폈���mNGKI1415�n
 *		(E-1) �Ώۃ^�X�N�����^�X�N�C�^�X�N��O�������C�������ݗD��
 *			  �x�}�X�N�S������ԂŁC�����Ɏ��s�J�n
 *		(E-2) �Ώۃ^�X�N�����^�X�N�łȂ�
 *		(E-3) �Ώۃ^�X�N�����^�X�N�����C�^�X�N��O�����֎~
 *		(E-4) �Ώۃ^�X�N�����^�X�N�Ń^�X�N��O�����������C�����ݗD��
 *			  �x�}�X�N���S�����łȂ�
 *	(F) ena_tex�̐��폈���mNGKI1427�n
 *		(F-1) �^�X�N��O�����v��������C�������ݗD��x�}�X�N�S������
 *			  �ԂŁC�����Ɏ��s�J�n
 *		(F-2) �^�X�N��O�����v�����Ȃ�
 *		(F-3) �^�X�N��O�����v�������邪�C�����ݗD��x�}�X�N���S������
 *			  �Ȃ�
 *	(G) chg_ipm�̐��폈��
 *		(G-1) �^�X�N��O�����v��������C���^�X�N��O�������ŁC����
 *			  �Ɏ��s�J�n
 *		(G-2) �^�X�N��O�����v�����Ȃ�
 *		(G-3) �^�X�N��O�����v�������邪�C�^�X�N��O�����֎~
 *		(G-4) �^�X�N��O�����v�������邪�C�����ݗD��x�}�X�N���S������
 *			  �Ȃ�
 *	(H) �^�X�N�f�B�X�p�b�`���ɂ��N��
 *		(H-1) �f�B�X�p�b�`��̃^�X�N���^�X�N��O���Ń^�X�N��O�����v
 *			  ������
 *	(I) �^�X�N��O�������[�`������̃��^�[���ɂ��N���i�A���N���j
 *	(J) �^�X�N��O�������[�`������̖߂莞�ɂ���ԕ��A
 *		(J-1) �^�X�N�ɖ߂��Ă��鎞
 *		(J-2) �^�X�N��O�������[�`�����A���N������鎞
 *	(K) �^�X�N��O�������[�`���̑��d�N��
 *	(L) �^�X�N��O�������[�`������̖߂莞�̃^�X�N�؊���
 *
 * �y�g�p���\�[�X�z
 *
 *	TASK1: ���C���̃^�X�N�D���^�X�N�ɑ΂��ă^�X�N��O������v������
 *	TASK2: ���^�X�N�ɑ΂��ă^�X�N��O������v������Ώۃ^�X�N
 *	TASK3: �^�X�N��O�������[�`������`����Ă��Ȃ��^�X�N
 *	TASK4: �x�~��Ԃ̃^�X�N
 *
 * �y�e�X�g�V�[�P���X�z
 *
 *	== TASK1�i�D��x�F10�j==
 *	1:	state(false, false, TIPM_ENAALL, false, false, true)
 *		ref_tex(TSK_SELF, &rtex)
 *		assert((rtex.texstat & TTEX_DIS) != 0U)
 *		assert(rtex.pndptn == 0U)
 *		ras_tex(TASK3, 0x0001) -> E_OBJ		... (A-2)
 *		ras_tex(TASK4, 0x0001) -> E_OBJ		... (A-1)
 *		ref_tex(TASK3, &rtex) -> E_OBJ		... (D-2)
 *		ref_tex(TASK4, &rtex) -> E_OBJ		... (D-1)
 *	2:	ena_tex()							... (F-2)
 *		state(false, false, TIPM_ENAALL, false, false, false)
 *		ref_tex(TSK_SELF, &rtex)
 *		assert((rtex.texstat & TTEX_ENA) != 0U)
 *		assert(rtex.pndptn == 0U)
 *	3:	ras_tex(TSK_SELF, 0x0001)			... (E-1)
 *	== TASK1-TEX-1�i1��ځj==
 *	4:	assert(texptn == 0x0001)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *	5:	dis_dsp() ... 4�̏�Ԃ����ꂼ��ω�������
 *		chg_ipm(TMAX_INTPRI)
 *		ena_tex()
 *		loc_cpu()
 *		state(false, true, TMAX_INTPRI, true, true, false)
 *		RETURN
 *	== TASK1�i�����j==
 *	6:	state(false, false, TIPM_ENAALL, false, false, false)	... (J-1)
 *	7:	dis_dsp() ... �f�B�X�p�b�`�֎~�C�^�X�N��O�����֎~
 *		dis_tex()
 *		state(false, false, TIPM_ENAALL, true, true, true)
 *	8:	ras_tex(TASK1, 0x0002)				... (E-3)
 *		ref_tex(TSK_SELF, &rtex)
 *		assert((rtex.texstat & TTEX_DIS) != 0)
 *		assert(rtex.pndptn == 0x0002)
 *	9:	ena_tex()							... (F-1)
 *	== TASK1-TEX-2�i2��ځj==
 *	10:	assert(texptn == 0x0002)
 *		state(false, false, TIPM_ENAALL, true, true, true)
 *	11:	ras_tex(TASK1, 0x0001)				... (E-3)
 *		ras_tex(TASK1, 0x0002)				... (E-3)
 *	12:	ena_dsp() ... 3�̏�Ԃ����ꂼ��ω�������
 *		chg_ipm(TMAX_INTPRI)
 *		loc_cpu()
 *		state(false, true, TMAX_INTPRI, false, true, true)
 *		RETURN								... (I)
 *	== TASK1-TEX-3�i3��ځj==
 *	13:	assert(texptn == 0x0003)
 *		state(false, false, TIPM_ENAALL, true, true, true)	... (J-2)
 *	14:	ena_dsp() ... �f�B�X�p�b�`���C�^�X�N��O����
 *		chg_ipm(TMAX_INTPRI)
 *		ena_tex()
 *		state(false, false, TMAX_INTPRI, false, true, false)
 *		chg_ipm(TIPM_ENAALL)				... (G-2)
 *		chg_ipm(TMAX_INTPRI)
 *	15: ras_tex(TSK_SELF, 0x0004)			... (E-4)
 *		chg_ipm(TMAX_INTPRI)				... (G-4)
 *		dis_tex()
 *		chg_ipm(TIPM_ENAALL)				... (G-3)
 *		chg_ipm(TMAX_INTPRI)
 *		ena_tex()							... (F-3)
 *	16:	chg_ipm(TIPM_ENAALL)				... (G-1)(K)
 *	== TASK1-TEX-4�i4��ځj==
 *	17:	assert(texptn == 0x0004)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *	18:	dis_dsp() ... 3�̏�Ԃ����ꂼ��ω�������
 *		chg_ipm(TMAX_INTPRI)
 *		loc_cpu()
 *		state(false, true, TMAX_INTPRI, true, true, true)
 *		RETURN
 *	== TASK1-TEX-3�i3��ڑ����j==
 *	19:	state(false, false, TIPM_ENAALL, false, false, false)
 *		RETURN
 *	== TASK1�i�����j==
 *	20:	state(false, false, TIPM_ENAALL, true, true, false)	... (J-1)
 *	21: ena_dsp()
 *		rot_rdq(TPRI_SELF)
 *	== TASK2�i�D��x�F10�j	==
 *	22:	state(false, false, TIPM_ENAALL, false, false, true)
 *	23:	ena_tex()
 *		state(false, false, TIPM_ENAALL, false, false, false)
 *		rot_rdq(TPRI_SELF)
 *	== TASK3�i�D��x�F10�j	==
 *	24:	state(false, false, TIPM_ENAALL, false, false, true)
 *	25:	ena_tex() -> E_OBJ					... (C-1)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *	26:	dis_tex() -> E_OBJ					... (B-1)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *		ext_tsk()
 *	== TASK1�i�����j==
 *	27: ras_tex(TASK2, 0x0001)				... (E-2)
 *		ref_tex(TASK2, &rtex)
 *	28:	rot_rdq(TPRI_SELF)					... (H-1)
 *	== TASK2-TEX-1�i1��ځj==
 *	29:	assert(texptn == 0x0001)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *		RETURN
 *	== TASK2�i�����j==
 *	30: ras_tex(TSK_SELF, 0x0002)
 *	== TASK2-TEX-2�i2��ځj==
 *	31:	assert(texptn == 0x0002)
 *		state(false, false, TIPM_ENAALL, false, false, true)
 *	32:	dis_dsp()
 *		rot_rdq(TPRI_SELF)
 *	33:	RETURN
 *	== TASK1�i�����j==
 *	34:	RETURN
 *	== TASK2�i�����j==
 *	35:	END
 */

#include <kernel.h>
#include <test_lib.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "test_tex1.h"

/*
 *  task4��tex_task4�͐�������Ȃ�
 */

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

	ercd = ras_tex(TASK3, 0x0001);
	check_ercd(ercd, E_OBJ);

	ercd = ras_tex(TASK4, 0x0001);
	check_ercd(ercd, E_OBJ);

	ercd = ref_tex(TASK3, &rtex);
	check_ercd(ercd, E_OBJ);

	ercd = ref_tex(TASK4, &rtex);
	check_ercd(ercd, E_OBJ);

	check_point(2);
	ercd = ena_tex();
	check_ercd(ercd, E_OK);

	check_state(false, false, TIPM_ENAALL, false, false, false);

	ercd = ref_tex(TSK_SELF, &rtex);
	check_ercd(ercd, E_OK);

	check_assert((rtex.texstat & TTEX_ENA) != 0U);

	check_assert(rtex.pndptn == 0U);

	check_point(3);
	ercd = ras_tex(TSK_SELF, 0x0001);
	check_ercd(ercd, E_OK);

	check_point(6);
	check_state(false, false, TIPM_ENAALL, false, false, false);

	check_point(7);
	ercd = dis_dsp();
	check_ercd(ercd, E_OK);

	ercd = dis_tex();
	check_ercd(ercd, E_OK);

	check_state(false, false, TIPM_ENAALL, true, true, true);

	check_point(8);
	ercd = ras_tex(TASK1, 0x0002);
	check_ercd(ercd, E_OK);

	ercd = ref_tex(TSK_SELF, &rtex);
	check_ercd(ercd, E_OK);

	check_assert((rtex.texstat & TTEX_DIS) != 0);

	check_assert(rtex.pndptn == 0x0002);

	check_point(9);
	ercd = ena_tex();
	check_ercd(ercd, E_OK);

	check_point(20);
	check_state(false, false, TIPM_ENAALL, true, true, false);

	check_point(21);
	ercd = ena_dsp();
	check_ercd(ercd, E_OK);

	ercd = rot_rdq(TPRI_SELF);
	check_ercd(ercd, E_OK);

	check_point(27);
	ercd = ras_tex(TASK2, 0x0001);
	check_ercd(ercd, E_OK);

	ercd = ref_tex(TASK2, &rtex);
	check_ercd(ercd, E_OK);

	check_point(28);
	ercd = rot_rdq(TPRI_SELF);
	check_ercd(ercd, E_OK);

	check_point(34);
	return;

	check_point(0);
}

static uint_t	tex_task1_count = 0;

void
tex_task1(TEXPTN texptn, intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++tex_task1_count) {
	case 1:
		check_point(4);
		check_assert(texptn == 0x0001);

		check_state(false, false, TIPM_ENAALL, false, false, true);

		check_point(5);
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

		check_state(false, false, TIPM_ENAALL, true, true, true);

		check_point(11);
		ercd = ras_tex(TASK1, 0x0001);
		check_ercd(ercd, E_OK);

		ercd = ras_tex(TASK1, 0x0002);
		check_ercd(ercd, E_OK);

		check_point(12);
		ercd = ena_dsp();
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		ercd = loc_cpu();
		check_ercd(ercd, E_OK);

		check_state(false, true, TMAX_INTPRI, false, true, true);

		return;

		check_point(0);

	case 3:
		check_point(13);
		check_assert(texptn == 0x0003);

		check_state(false, false, TIPM_ENAALL, true, true, true);

		check_point(14);
		ercd = ena_dsp();
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		ercd = ena_tex();
		check_ercd(ercd, E_OK);

		check_state(false, false, TMAX_INTPRI, false, true, false);

		ercd = chg_ipm(TIPM_ENAALL);
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		check_point(15);
		ercd = ras_tex(TSK_SELF, 0x0004);
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		ercd = dis_tex();
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TIPM_ENAALL);
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		ercd = ena_tex();
		check_ercd(ercd, E_OK);

		check_point(16);
		ercd = chg_ipm(TIPM_ENAALL);
		check_ercd(ercd, E_OK);

		check_point(19);
		check_state(false, false, TIPM_ENAALL, false, false, false);

		return;

		check_point(0);

	case 4:
		check_point(17);
		check_assert(texptn == 0x0004);

		check_state(false, false, TIPM_ENAALL, false, false, true);

		check_point(18);
		ercd = dis_dsp();
		check_ercd(ercd, E_OK);

		ercd = chg_ipm(TMAX_INTPRI);
		check_ercd(ercd, E_OK);

		ercd = loc_cpu();
		check_ercd(ercd, E_OK);

		check_state(false, true, TMAX_INTPRI, true, true, true);

		return;

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

	check_point(22);
	check_state(false, false, TIPM_ENAALL, false, false, true);

	check_point(23);
	ercd = ena_tex();
	check_ercd(ercd, E_OK);

	check_state(false, false, TIPM_ENAALL, false, false, false);

	ercd = rot_rdq(TPRI_SELF);
	check_ercd(ercd, E_OK);

	check_point(30);
	ercd = ras_tex(TSK_SELF, 0x0002);
	check_ercd(ercd, E_OK);

	check_finish(35);
	check_point(0);
}

static uint_t	tex_task2_count = 0;

void
tex_task2(TEXPTN texptn, intptr_t exinf)
{
	ER_UINT	ercd;

	switch (++tex_task2_count) {
	case 1:
		check_point(29);
		check_assert(texptn == 0x0001);

		check_state(false, false, TIPM_ENAALL, false, false, true);

		return;

		check_point(0);

	case 2:
		check_point(31);
		check_assert(texptn == 0x0002);

		check_state(false, false, TIPM_ENAALL, false, false, true);

		check_point(32);
		ercd = dis_dsp();
		check_ercd(ercd, E_OK);

		ercd = rot_rdq(TPRI_SELF);
		check_ercd(ercd, E_OK);

		check_point(33);
		return;

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

	check_point(24);
	check_state(false, false, TIPM_ENAALL, false, false, true);

	check_point(25);
	ercd = ena_tex();
	check_ercd(ercd, E_OBJ);

	check_state(false, false, TIPM_ENAALL, false, false, true);

	check_point(26);
	ercd = dis_tex();
	check_ercd(ercd, E_OBJ);

	check_state(false, false, TIPM_ENAALL, false, false, true);

	ercd = ext_tsk();
	check_ercd(ercd, E_OK);

	check_point(0);
}
