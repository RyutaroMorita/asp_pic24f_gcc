/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: interrupt.h 2728 2015-12-30 01:46:11Z ertl-honda $
 */

/*
 *		�����݊Ǘ��@�\
 */

#ifndef TOPPERS_INTERRUPT_H
#define TOPPERS_INTERRUPT_H

/*
 *  �����݃T�[�r�X���[�`���������u���b�N
 */
typedef struct isr_initialization_block {
	ATR			isratr;			/* �����݃T�[�r�X���[�`������ */
	intptr_t	exinf;			/* �����݃T�[�r�X���[�`���̊g����� */
	INTNO		intno;			/* �����݃T�[�r�X���[�`����o�^���銄���ݔԍ� */
	QUEUE		*p_isr_queue;	/* �o�^�抄���݃T�[�r�X���[�`���L���[�̔Ԓn */
	ISR			isr;			/* �����݃T�[�r�X���[�`���̐擪�Ԓn */
	PRI			isrpri;			/* �����݃T�[�r�X���[�`���D��x */
} ISRINIB;

/*
 *  �����݃T�[�r�X���[�`���Ǘ��u���b�N
 */
typedef struct isr_control_block {
	QUEUE		isr_queue;		/* �����݃T�[�r�X���[�`���ďo���L���[ */
	const ISRINIB *p_isrinib;	/* �������u���b�N�ւ̃|�C���^ */
} ISRCB;

/*
 *  �����݃T�[�r�X���[�`���ďo���L���[���������邽�߂̃f�[�^�\��
 */
typedef struct {
	INTNO		intno;			/* �����ݔԍ� */
	QUEUE		*p_isr_queue;	/* �����݃T�[�r�X���[�`���ďo���L���[ */
} ISR_ENTRY;

/*
 *  �����݃T�[�r�X���[�`���L���[�̃G���g�����ikernel_cfg.c�j
 */
extern const uint_t tnum_isr_queue;

/*
 *  �����݃T�[�r�X���[�`���L���[���X�g�ikernel_cfg.c�j
 */
extern const ISR_ENTRY isr_queue_list[];

/*
 *  �����݃T�[�r�X���[�`���L���[�̃G���A�ikernel_cfg.c�j
 */
extern QUEUE isr_queue_table[];

/*
 *  �g�p���Ă��Ȃ������݃T�[�r�X���[�`���Ǘ��u���b�N�̃��X�g
 */
extern QUEUE	free_isrcb;

/*
 *  �����݃T�[�r�X���[�`��ID�̍ő�l�ikernel_cfg.c�j
 *
 *  �ÓI�ɐ�������銄���݃T�[�r�X���[�`����ID�ԍ��������Ȃ����߁C
 *  tmax_isrid�͓��I�ɐ�������銄���݃T�[�r�X���[�`����ID�ԍ��̍ő�l
 *  �ł���D�ÓI�ɐ�������銄���݃T�[�r�X���[�`���̐��́Ctnum_sisr�ɕ�
 *  ������D
 */
extern const ID		tmax_isrid;
extern const uint_t	tnum_sisr;

/*
 *  �����݃T�[�r�X���[�`���������u���b�N�̃G���A�ikernel_cfg.c�j
 */
extern const ISRINIB	sisrinib_table[];
extern ISRINIB			aisrinib_table[];

/*
 *  �����݃T�[�r�X���[�`���Ǘ��u���b�N�̃G���A�ikernel_cfg.c�j
 */
extern ISRCB	isrcb_table[];

/*
 *  �����݃T�[�r�X���[�`���Ǘ��u���b�N���犄���݃T�[�r�X���[�`��ID����
 *  ��o�����߂̃}�N��
 */
#define	ISRID(p_isrcb)	((ID)(((p_isrcb) - isrcb_table) \
										- tnum_sisr + TMIN_ISRID))

/*
 *  �����݃T�[�r�X���[�`���@�\�̏�����
 */
extern void initialize_isr(void);

/*
 *  �����݃T�[�r�X���[�`���̌ďo��
 */
extern void call_isr(QUEUE *p_isr_queue);

#ifndef OMIT_INITIALIZE_INTERRUPT

/*
 *  �����݃n���h���������u���b�N
 */
typedef struct interrupt_handler_initialization_block {
	INHNO		inhno;			/* �����݃n���h���ԍ� */
	ATR			inhatr;			/* �����݃n���h������ */
	FP			int_entry;		/* �����݃n���h���̏o���������̔Ԓn */
} INHINIB;

/*
 *  �����ݗv�����C���������u���b�N
 */
typedef struct interrupt_request_initialization_block {
	INTNO		intno;			/* �����ݔԍ� */
	ATR			intatr;			/* �����ݑ��� */
	PRI			intpri;			/* �����ݗD��x */
} INTINIB;

/*
 *  �����݃n���h���ԍ��̐��ikernel_cfg.c�j
 */
extern const uint_t	tnum_inhno;

/*
 *  �����݃n���h���������u���b�N�̃G���A�ikernel_cfg.c�j
 */
extern const INHINIB	inhinib_table[];

/*
 *  �����ݗv�����C���̐��ikernel_cfg.c�j
 */
extern const uint_t	tnum_intno;

/*
 *  �����ݗv�����C���������u���b�N�̃G���A�ikernel_cfg.c�j
 */
extern const INTINIB	intinib_table[];

#endif /* OMIT_INITIALIZE_INTERRUPT */

/*
 *  �����݊Ǘ��@�\�̏�����
 */
extern void	initialize_interrupt(void);

#endif /* TOPPERS_INTERRUPT_H */
