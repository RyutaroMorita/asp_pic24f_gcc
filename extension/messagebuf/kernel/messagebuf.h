/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2014 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: messagebuf.h 2728 2015-12-30 01:46:11Z ertl-honda $
 */

/*
 *		���b�Z�[�W�o�b�t�@�@�\
 */

#ifndef TOPPERS_MESSAGEBUF_H
#define TOPPERS_MESSAGEBUF_H

#include "wait.h"

/*
 *  ���b�Z�[�W�o�b�t�@�������u���b�N
 *
 *  ���̍\���̂́C�����E�ʐM�I�u�W�F�N�g�̏������u���b�N�̋��ʕ���
 *  �iWOBJINIB�j���g���i�I�u�W�F�N�g�w������̌p���ɑ����j�������̂ŁC
 *  �ŏ��̃t�B�[���h�����ʂɂȂ��Ă���D
 */
typedef struct messagebuf_initialization_block {
	ATR			mbfatr;			/* ���b�Z�[�W�o�b�t�@���� */
	uint_t		maxmsz;			/* ���b�Z�[�W�̍ő咷 */
	SIZE		mbfsz;			/* ���b�Z�[�W�o�b�t�@�Ǘ��̈�̃T�C�Y */
	void		*mbfmb;			/* ���b�Z�[�W�o�b�t�@�Ǘ��̈�̐擪�Ԓn */
} MBFINIB;

/*
 *  ���b�Z�[�W�o�b�t�@�Ǘ��u���b�N
 *
 *  ���̍\���̂́C�����E�ʐM�I�u�W�F�N�g�̊Ǘ��u���b�N�̋��ʕ����iWOBJCB�j
 *  ���g���i�I�u�W�F�N�g�w������̌p���ɑ����j�������̂ŁC�ŏ���2��
 *  �t�B�[���h�����ʂɂȂ��Ă���D
 */
typedef struct messagebuf_control_block {
	QUEUE		swait_queue;	/* ���b�Z�[�W�o�b�t�@���M�҂��L���[ */
	const MBFINIB *p_mbfinib;	/* �������u���b�N�ւ̃|�C���^ */
	QUEUE		rwait_queue;	/* ���b�Z�[�W�o�b�t�@��M�҂��L���[ */
	SIZE		fmbfsz;			/* �󂫗̈�̃T�C�Y */
	SIZE		head;			/* �ŏ��̃��b�Z�[�W�̊i�[�ꏊ */
	SIZE		tail;			/* �Ō�̃��b�Z�[�W�̊i�[�ꏊ�̎� */
	uint_t		smbfcnt;		/* �Ǘ��̈�Ɋi�[����Ă��郁�b�Z�[�W�̐� */
} MBFCB;

/*
 *  ���b�Z�[�W�o�b�t�@�҂����u���b�N�̒�`
 *
 *  ���̍\���̂́C�����E�ʐM�I�u�W�F�N�g�̑҂����u���b�N�̋��ʕ���
 *  �iWINFO_WOBJ�j���g���i�I�u�W�F�N�g�w������̌p���ɑ����j�������̂ŁC
 *  �ŏ���2�̃t�B�[���h�����ʂɂȂ��Ă���D
 *  ���b�Z�[�W�o�b�t�@�ւ̑��M�҂��ƃ��b�Z�[�W�o�b�t�@����̎�M�҂��ŁC
 *  �����҂����u���b�N���g���D
 */
typedef struct messagebuf_waiting_information {
	WINFO		winfo;			/* �W���̑҂����u���b�N */
	MBFCB		*p_mbfcb;		/* �҂��Ă��郁�b�Z�[�W�o�b�t�@�̊Ǘ��u���b�N */
	void		*msg;			/* ����M���b�Z�[�W */
	uint_t		msgsz;			/* ����M���b�Z�[�W�T�C�Y */
} WINFO_MBF;

/*
 *  ���b�Z�[�W�o�b�t�@ID�̍ő�l�ikernel_cfg.c�j
 */
extern const ID	tmax_mbfid;

/*
 *  ���b�Z�[�W�o�b�t�@�������u���b�N�̃G���A�ikernel_cfg.c�j
 */
extern const MBFINIB	mbfinib_table[];

/*
 *  ���b�Z�[�W�o�b�t�@�Ǘ��u���b�N�̃G���A�ikernel_cfg.c�j
 */
extern MBFCB	mbfcb_table[];

/*
 *  ���b�Z�[�W�o�b�t�@�Ǘ��u���b�N���烁�b�Z�[�W�o�b�t�@ID�����o����
 *  �߂̃}�N��
 */
#define	MBFID(p_mbfcb)	((ID)(((p_mbfcb) - mbfcb_table) + TMIN_MBFID))

/*
 *  ���b�Z�[�W�o�b�t�@�@�\�̏�����
 */
extern void	initialize_messagebuf(void);

/*
 *  ���b�Z�[�W�o�b�t�@�Ǘ��̈�ւ̃��b�Z�[�W�̊i�[
 */
extern bool_t	enqueue_message(MBFCB *p_mbfcb, const void *msg, uint_t msgsz);

/*
 *  ���b�Z�[�W�o�b�t�@�Ǘ��̈悩��̃��b�Z�[�W�̎�o��
 */
extern uint_t	dequeue_message(MBFCB *p_mbfcb, void *msg);

/*
 *  ���b�Z�[�W�o�b�t�@�ւ̃��b�Z�[�W���M
 */
extern bool_t	send_message(MBFCB *p_mbfcb, const void *msg,
											uint_t msgsz, bool_t *p_dspreq);

/*
 *  ���b�Z�[�W�o�b�t�@���M�҂��^�X�N�̃`�F�b�N
 */
extern bool_t	messagebuf_signal(MBFCB *p_mbfcb);

/*
 *  ���b�Z�[�W�o�b�t�@����̃��b�Z�[�W��M
 */
extern uint_t	receive_message(MBFCB *p_mbfcb, void *msg, bool_t *p_dspreq);

/*
 *  ���b�Z�[�W�o�b�t�@���M�҂��^�X�N�̑҂�����������
 */
extern bool_t	(*mbfhook_dequeue_wobj)(TCB *p_tcb);
extern bool_t	messagebuf_dequeue_wobj(TCB *p_tcb);

/*
 *  ���b�Z�[�W�o�b�t�@���M�҂��^�X�N�̗D��x�ύX������
 */
extern bool_t	(*mbfhook_change_priority)(WOBJCB *p_wobjcb);
extern bool_t	messagebuf_change_priority(WOBJCB *p_wobjcb);

#endif /* TOPPERS_MESSAGEBUF_H */
