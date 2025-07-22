/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2011 by Embedded and Real-Time Systems Laboratory
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
 *	2025/07/20 Ryutaro Morita
 */

/*
 *		�^�[�Q�b�g�ˑ����W���[���iExplorer16/32 Development Board�p�j
 */

#include "kernel_impl.h"
#include <sil.h>
#include "mcc_generated_files/system.h"

/*
 *  �v���Z�b�T���ʂ̂��߂̕ϐ��i�}���`�v���Z�b�T�Ή��j
 */
uint_t	board_id;			/* �{�[�hID */
void	*board_addr;		/* ���[�J���������̐擪�A�h���X */

/*
 *  �^�[�Q�b�g�ˑ��̏�����
 */
void
target_initialize(void)
{
	/*
	 *  �v���Z�b�T�ˑ��̏�����
	 */
	prc_initialize();

	// initialize the device
	SYSTEM_Initialize();

	/*
	 *  ���Z�b�g�Ŋ��荞�݋���ԂɂȂ邪�A�����ł͂܂������̂ŁA�����ɋ֎~
	 *  �{���̊��荞�݋��́Astart_r �ōs��
	 */
	disint();
}

/*
 *  �^�[�Q�b�g�ˑ��̏I������
 */
void
target_exit(void)
{
	/*
	 *  �v���Z�b�T�ˑ��̏I������
	 */
	prc_terminate();

	while(1);
}

/*
 *  �V�X�e�����O�̒჌�x���o�͂̂��߂̕����o��
 */
void
target_fput_log(char c)
{
	if (c == '\n') {
		while(U1STAbits.UTXBF == 1);
		U1TXREG = '\r';		// Write the data byte to the USART.
	}
	while(U1STAbits.UTXBF == 1);
	U1TXREG = c;			// Write the data byte to the USART.
}

/*
 *  �����ݗv�����C���̑����̐ݒ�
 *
 *  ASP�J�[�l���ł̗��p��z�肵�āC�p�����[�^�G���[�̓A�T�[�V�����Ń`�F�b
 *  �N���Ă���Dcfg_int�T�[�r�X�R�[����݂���ꍇ�ɂ́C�G���[��Ԃ��悤
 *  �ɂ��ׂ��ł��낤�D
 */
void
x_config_int(INTNO intno, ATR intatr, PRI intpri)
{
	uint16_t	*ipc;

	assert(VALID_INTNO_CFGINT(intno));
	assert(TMIN_INTPRI <= intpri && intpri <= TMAX_INTPRI);

	/*
	 *  �����݂̃}�X�N
	 *
	 *  �����݂��󂯕t�����܂܁C���x���g���K�^�G�b�W�g���K�̐ݒ��C��
	 *  ���ݗD��x�̐ݒ���s���̂͊댯�Ȃ��߁C�����ݑ����ɂ�����炸�C
	 *  ��U�}�X�N����D
	 */
	(void) x_disable_int(intno);

	/*
	 *  �����ݗD��x�̐ݒ�
	 */
	ipc = (uint16_t *)&IPC0bits;
	ipc += (intno / 4);
	*ipc &= ~(0xF << (4 * (intno % 4)));
	*ipc |= -(intpri) << (4 * (intno % 4));

	/*
	 *  �����݂̃}�X�N�����i�K�v�ȏꍇ�j
 	 */
	if ((intatr & TA_ENAINT) != 0U) {
		(void) x_enable_int(intno);
	}
}

/*
 *  �����ݗv���֎~�t���O�̃Z�b�g
 *
 *  �����ݑ������ݒ肳��Ă��Ȃ������ݗv�����C���ɑ΂��Ċ����ݗv���֎~
 *  �t���O���Z�b�g���悤�Ƃ����ꍇ�ɂ́Cfalse��Ԃ��D
 */
bool_t
x_disable_int(INTNO intno)
{
	uint16_t	*iec;
	uint16_t	flg;
	if (intno > TMAX_INTNO)
		return false;
	iec = (uint16_t *)&IEC0bits;
	iec += (intno / 16);
	flg = 1 << (intno % 16);
	*iec &= ~flg;
	return true;
}

/*
 *  �����ݗv���֎~�t���O�̃N���A
 *
 *  �����ݑ������ݒ肳��Ă��Ȃ������ݗv�����C���ɑ΂��Ċ����ݗv���֎~
 *  �t���O���N���A���悤�Ƃ����ꍇ�ɂ́Cfalse��Ԃ��D
 */
bool_t
x_enable_int(INTNO intno)
{
	uint16_t	*iec;
	uint16_t	flg;
	if (intno > TMAX_INTNO)
		return false;
	iec = (uint16_t *)&IEC0bits;
	iec += (intno / 16);
	flg = 1 << (intno % 16);
	*iec |= flg;
	return true;
}

/*
 *  �����ݗv���̃N���A
 */
void
x_clear_int(INTNO intno)
{
	uint16_t	*ifs;
	uint16_t	flg;
	if (intno > TMAX_INTNO)
		return;
	ifs = (uint16_t *)&IFS0bits;
	ifs += (intno / 16);
	flg = 1 << (intno % 16);
	*ifs &= ~flg;
}

/*
 *  �����ݗv���̃`�F�b�N
 */
bool_t
x_probe_int(INTNO intno)
{
	uint16_t	*ifs;
	uint16_t	flg;
	if (intno > TMAX_INTNO)
		return false;
	ifs = (uint16_t *)&IFS0bits;
	ifs += (intno / 16);
	flg = 1 << (intno % 16);
	return (*ifs & flg);
}
