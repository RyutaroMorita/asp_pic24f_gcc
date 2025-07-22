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
 *  $Id: messagebuf.c 2728 2015-12-30 01:46:11Z ertl-honda $
 */

/*
 *		���b�Z�[�W�o�b�t�@�@�\
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "messagebuf.h"
#include <string.h>

/*
 *  �g���[�X���O�}�N���̃f�t�H���g��`
 */
#ifndef LOG_SND_MBF_ENTER
#define LOG_SND_MBF_ENTER(mbfid, msg, msgsz)
#endif /* LOG_SND_MBF_ENTER */

#ifndef LOG_SND_MBF_LEAVE
#define LOG_SND_MBF_LEAVE(ercd)
#endif /* LOG_SND_MBF_LEAVE */

#ifndef LOG_PSND_MBF_ENTER
#define LOG_PSND_MBF_ENTER(mbfid, msg, msgsz)
#endif /* LOG_PSND_MBF_ENTER */

#ifndef LOG_PSND_MBF_LEAVE
#define LOG_PSND_MBF_LEAVE(ercd)
#endif /* LOG_PSND_MBF_LEAVE */

#ifndef LOG_TSND_MBF_ENTER
#define LOG_TSND_MBF_ENTER(mbfid, msg, msgsz, tmout)
#endif /* LOG_TSND_MBF_ENTER */

#ifndef LOG_TSND_MBF_LEAVE
#define LOG_TSND_MBF_LEAVE(ercd)
#endif /* LOG_TSND_MBF_LEAVE */

#ifndef LOG_RCV_MBF_ENTER
#define LOG_RCV_MBF_ENTER(mbfid, msg)
#endif /* LOG_RCV_MBF_ENTER */

#ifndef LOG_RCV_MBF_LEAVE
#define LOG_RCV_MBF_LEAVE(msgsz, msg)
#endif /* LOG_RCV_MBF_LEAVE */

#ifndef LOG_PRCV_MBF_ENTER
#define LOG_PRCV_MBF_ENTER(mbfid, msg)
#endif /* LOG_PRCV_MBF_ENTER */

#ifndef LOG_PRCV_MBF_LEAVE
#define LOG_PRCV_MBF_LEAVE(msgsz, msg)
#endif /* LOG_PRCV_MBF_LEAVE */

#ifndef LOG_TRCV_MBF_ENTER
#define LOG_TRCV_MBF_ENTER(mbfid, msg, tmout)
#endif /* LOG_TRCV_MBF_ENTER */

#ifndef LOG_TRCV_MBF_LEAVE
#define LOG_TRCV_MBF_LEAVE(msgsz, msg)
#endif /* LOG_TRCV_MBF_LEAVE */

#ifndef LOG_INI_MBF_ENTER
#define LOG_INI_MBF_ENTER(mbfid)
#endif /* LOG_INI_MBF_ENTER */

#ifndef LOG_INI_MBF_LEAVE
#define LOG_INI_MBF_LEAVE(ercd)
#endif /* LOG_INI_MBF_LEAVE */

#ifndef LOG_REF_MBF_ENTER
#define LOG_REF_MBF_ENTER(mbfid, pk_rmbf)
#endif /* LOG_REF_MBF_ENTER */

#ifndef LOG_REF_MBF_LEAVE
#define LOG_REF_MBF_LEAVE(ercd, pk_rmbf)
#endif /* LOG_REF_MBF_LEAVE */

/*
 *  ���b�Z�[�W�o�b�t�@�̐�
 */
#define tnum_mbf	((uint_t)(tmax_mbfid - TMIN_MBFID + 1))

/*
 *  ���b�Z�[�W�o�b�t�@ID���烁�b�Z�[�W�o�b�t�@�Ǘ��u���b�N�����o����
 *  �߂̃}�N��
 */
#define INDEX_MBF(mbfid)	((uint_t)((mbfid) - TMIN_MBFID))
#define get_mbfcb(mbfid)	(&(mbfcb_table[INDEX_MBF(mbfid)]))

/*
 *  �t�b�N���[�`���ďo���p�̕ϐ�
 */
#ifdef TOPPERS_mbfhook

bool_t	(*mbfhook_dequeue_wobj)(TCB *p_tcb) = NULL;
bool_t	(*mbfhook_change_priority)(WOBJCB *p_wobjcb) = NULL;

#endif /* TOPPERS_mbfhook */

/*
 *  ���b�Z�[�W�o�b�t�@�@�\�̏�����
 */
#ifdef TOPPERS_mbfini

void
initialize_messagebuf(void)
{
	uint_t	i;
	MBFCB	*p_mbfcb;

	mbfhook_dequeue_wobj = messagebuf_dequeue_wobj;
	mbfhook_change_priority = messagebuf_change_priority;

	for (i = 0; i < tnum_mbf; i++) {
		p_mbfcb = &(mbfcb_table[i]);
		queue_initialize(&(p_mbfcb->swait_queue));
		p_mbfcb->p_mbfinib = &(mbfinib_table[i]);
		queue_initialize(&(p_mbfcb->rwait_queue));
		p_mbfcb->fmbfsz = p_mbfcb->p_mbfinib->mbfsz;
		p_mbfcb->head = 0U;
		p_mbfcb->tail = 0U;
		p_mbfcb->smbfcnt = 0U;
	}
}

#endif /* TOPPERS_mbfini */

/*
 *  ���b�Z�[�W�o�b�t�@�Ǘ��̈�ւ̃��b�Z�[�W�̊i�[
 */
#ifdef TOPPERS_mbfenq

bool_t
enqueue_message(MBFCB *p_mbfcb, const void *msg, uint_t msgsz)
{
	const MBFINIB	*p_mbfinib = p_mbfcb->p_mbfinib;
	char	*mbuffer = (char *)(p_mbfinib->mbfmb);
	uint_t	allocsz;
	SIZE	remsz;

	allocsz = sizeof(uint_t) + TOPPERS_ROUND_SZ(msgsz, sizeof(uint_t));
	if (allocsz <= p_mbfcb->fmbfsz) {
		*((uint_t *) &(mbuffer[p_mbfcb->tail])) = msgsz;
		p_mbfcb->tail += sizeof(uint_t);
		if (p_mbfcb->tail >= p_mbfinib->mbfsz) {
			p_mbfcb->tail = 0U;
		}

		remsz = p_mbfinib->mbfsz - p_mbfcb->tail;
		if (remsz < msgsz) {
			memcpy(&(mbuffer[p_mbfcb->tail]), msg, remsz);
			msg = ((char *) msg) + remsz;
			msgsz -= remsz;
			p_mbfcb->tail = 0U;
		}
		memcpy(&(mbuffer[p_mbfcb->tail]), msg, msgsz);
		p_mbfcb->tail += TOPPERS_ROUND_SZ(msgsz, sizeof(uint_t));
		if (p_mbfcb->tail >= p_mbfinib->mbfsz) {
			p_mbfcb->tail = 0U;
		}

		p_mbfcb->fmbfsz -= allocsz;
		p_mbfcb->smbfcnt++;
		return(true);
	}
	return(false);
}

#endif /* TOPPERS_mbfenq */

/*
 *  ���b�Z�[�W�o�b�t�@�Ǘ��̈悩��̃��b�Z�[�W�̎�o��
 */
#ifdef TOPPERS_mbfdeq

uint_t
dequeue_message(MBFCB *p_mbfcb, void *msg)
{
	const MBFINIB	*p_mbfinib = p_mbfcb->p_mbfinib;
	char	*mbuffer = (char *)(p_mbfinib->mbfmb);
	uint_t	msgsz, copysz;
	SIZE	remsz;

	assert(p_mbfcb->smbfcnt > 0);
	msgsz = *((uint_t *) &(mbuffer[p_mbfcb->head]));
	p_mbfcb->head += sizeof(uint_t);
	if (p_mbfcb->head >= p_mbfcb->p_mbfinib->mbfsz) {
		p_mbfcb->head = 0U;
	}

	remsz = p_mbfcb->p_mbfinib->mbfsz - p_mbfcb->head;
	copysz = msgsz;
	if (remsz < copysz) {
		memcpy(msg, &(mbuffer[p_mbfcb->head]), remsz);
		msg = ((char *) msg) + remsz;
		copysz -= remsz;
		p_mbfcb->head = 0U;
	}
	memcpy(msg, &(mbuffer[p_mbfcb->head]), copysz);
	p_mbfcb->head += TOPPERS_ROUND_SZ(copysz, sizeof(uint_t));
	if (p_mbfcb->head >= p_mbfcb->p_mbfinib->mbfsz) {
		p_mbfcb->head = 0U;
	}

	p_mbfcb->fmbfsz += sizeof(uint_t) + TOPPERS_ROUND_SZ(msgsz, sizeof(uint_t));
	p_mbfcb->smbfcnt--;
	return(msgsz);
}

#endif /* TOPPERS_mbfdeq */

/*
 *  ���M�҂��s��Ɏ��^�X�N���D�悵�ă��b�Z�[�W�𑗐M�ł���^�X�N����
 *  �݂��Ȃ��ꍇ��true��Ԃ��֐�
 */
Inline bool_t
have_precedence(MBFCB *p_mbfcb)
{
	if (queue_empty(&(p_mbfcb->swait_queue))) {
		/* ���M�҂��s�񂪋�̎� */
		return(true);
	}
	else if ((p_mbfcb->p_mbfinib->mbfatr & TA_TPRI) != 0) {
		if (((TCB *)(p_mbfcb->swait_queue.p_next))->priority
												> p_runtsk->priority) {
			/* ���M�҂��s�񂪃^�X�N�̗D��x���ŁC
					�擪�̃^�X�N�̗D��x�����^�X�N�̗D��x�����Ⴂ�� */
			return(true);
		}
	}
	return(false);
}

/*
 *  ���b�Z�[�W�o�b�t�@�ւ̃��b�Z�[�W���M
 */
#ifdef TOPPERS_mbfsnd

bool_t
send_message(MBFCB *p_mbfcb, const void *msg, uint_t msgsz, bool_t *p_dspreq)
{
	TCB		*p_tcb;

	if (!queue_empty(&(p_mbfcb->rwait_queue))) {
		p_tcb = (TCB *) queue_delete_next(&(p_mbfcb->rwait_queue));
		memcpy(((WINFO_MBF *)(p_tcb->p_winfo))->msg, msg, msgsz);
		((WINFO_MBF *)(p_tcb->p_winfo))->msgsz = msgsz;
		*p_dspreq = wait_complete(p_tcb);
		return(true);
	}
	else if (have_precedence(p_mbfcb)
							&& enqueue_message(p_mbfcb, msg, msgsz)) {
		*p_dspreq = false;
		return(true);
	}
	else {
		return(false);
	}
}

#endif /* TOPPERS_mbfsnd */

/*
 *  ���b�Z�[�W�o�b�t�@���M�҂��^�X�N�̃`�F�b�N
 *
 *  ���b�Z�[�W�o�b�t�@���M�҂��L���[�̐擪�̃^�X�N�̑��M���b�Z�[�W���C
 *  ���b�Z�[�W�o�b�t�@�Ǘ��̈�Ɋi�[���邱�Ƃł���Ίi�[���C�҂�������
 *  ��D���̏������C�擪�̃^�X�N�̑��M���b�Z�[�W���i�[�ł��Ȃ��Ȃ�܂�
 *  �J��Ԃ��D
 */
#ifdef TOPPERS_mbfsig

bool_t
messagebuf_signal(MBFCB *p_mbfcb)
{
	TCB		*p_tcb;
	bool_t	dspreq = false;

	while (!queue_empty(&(p_mbfcb->swait_queue))) {
		p_tcb = (TCB *)(p_mbfcb->swait_queue.p_next);
		if (enqueue_message(p_mbfcb, ((WINFO_MBF *)(p_tcb->p_winfo))->msg,
									((WINFO_MBF *)(p_tcb->p_winfo))->msgsz)) {
			queue_delete(&(p_tcb->task_queue));
			if (wait_complete(p_tcb)) {
				dspreq = true;
			}
		}
		else {
			break;
		}
	}
	return(dspreq);
}

#endif /* TOPPERS_mbfsig */

/*
 *  ���b�Z�[�W�o�b�t�@����̃��b�Z�[�W��M
 */
#ifdef TOPPERS_mbfrcv

uint_t
receive_message(MBFCB *p_mbfcb, void *msg, bool_t *p_dspreq)
{
	TCB		*p_tcb;
	uint_t	msgsz;

	if (p_mbfcb->smbfcnt > 0) {
		msgsz = dequeue_message(p_mbfcb, msg);
		*p_dspreq = messagebuf_signal(p_mbfcb);
		return(msgsz);
	}
	else if (!queue_empty(&(p_mbfcb->swait_queue))) {
		p_tcb = (TCB *) queue_delete_next(&(p_mbfcb->swait_queue));
		msgsz = ((WINFO_MBF *)(p_tcb->p_winfo))->msgsz;
		memcpy(msg, ((WINFO_MBF *)(p_tcb->p_winfo))->msg, msgsz);
		*p_dspreq = wait_complete(p_tcb);
		return(msgsz);
	}
	else {
		return(0U);
	}
}

#endif /* TOPPERS_mbfrcv */

/*
 *  ���b�Z�[�W�o�b�t�@���M�҂��^�X�N�̑҂�����������
 */
#ifdef TOPPERS_mbfwobj

bool_t
messagebuf_dequeue_wobj(TCB *p_tcb)
{
	return(messagebuf_signal(((WINFO_MBF *)(p_tcb->p_winfo))->p_mbfcb));
}

#endif /* TOPPERS_mbfwobj */

/*
 *  ���b�Z�[�W�o�b�t�@���M�҂��^�X�N�̗D��x�ύX������
 */
#ifdef TOPPERS_mbfpri

bool_t
messagebuf_change_priority(WOBJCB *p_wobjcb)
{
	return(messagebuf_signal((MBFCB *) p_wobjcb));
}

#endif /* TOPPERS_mbfpri */

/*
 *  ���b�Z�[�W�o�b�t�@�ւ̑��M
 */
#ifdef TOPPERS_snd_mbf

ER
snd_mbf(ID mbfid, const void *msg, uint_t msgsz)
{
	MBFCB	*p_mbfcb;
	WINFO_MBF winfo_mbf;
	bool_t	dspreq;
	ER		ercd;

	LOG_SND_MBF_ENTER(mbfid, msg, msgsz);
	CHECK_DISPATCH();
	CHECK_MBFID(mbfid);
	p_mbfcb = get_mbfcb(mbfid);
	CHECK_PAR(0 < msgsz && msgsz <= p_mbfcb->p_mbfinib->maxmsz);

	t_lock_cpu();
	if (send_message(p_mbfcb, msg, msgsz, &dspreq)) {
		if (dspreq) {
			dispatch();
		}
		ercd = E_OK;
	}
	else {
		winfo_mbf.msg = (void *) msg;
		winfo_mbf.msgsz = msgsz;
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_SMBF);
		wobj_make_wait((WOBJCB *) p_mbfcb, (WINFO_WOBJ *) &winfo_mbf);
		dispatch();
		ercd = winfo_mbf.winfo.wercd;
	}
	t_unlock_cpu();

  error_exit:
	LOG_SND_MBF_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_snd_mbf */

/*
 *  ���b�Z�[�W�o�b�t�@�ւ̑��M�i�|�[�����O�j
 */
#ifdef TOPPERS_psnd_mbf

ER
psnd_mbf(ID mbfid, const void *msg, uint_t msgsz)
{
	MBFCB	*p_mbfcb;
	bool_t	dspreq;
	ER		ercd;

	LOG_PSND_MBF_ENTER(mbfid, msg, msgsz);
	CHECK_TSKCTX_UNL();
	CHECK_MBFID(mbfid);
	p_mbfcb = get_mbfcb(mbfid);
	CHECK_PAR(0 < msgsz && msgsz <= p_mbfcb->p_mbfinib->maxmsz);

	t_lock_cpu();
	if (send_message(p_mbfcb, msg, msgsz, &dspreq)) {
		if (dspreq) {
			dispatch();
		}
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();

  error_exit:
	LOG_PSND_MBF_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_psnd_mbf */

/*
 *  ���b�Z�[�W�o�b�t�@�ւ̑��M�i�^�C���A�E�g����j
 */
#ifdef TOPPERS_tsnd_mbf

ER
tsnd_mbf(ID mbfid, const void *msg, uint_t msgsz, TMO tmout)
{
	MBFCB	*p_mbfcb;
	WINFO_MBF winfo_mbf;
	TMEVTB	tmevtb;
	bool_t	dspreq;
	ER		ercd;

	LOG_TSND_MBF_ENTER(mbfid, msg, msgsz, tmout);
	CHECK_DISPATCH();
	CHECK_MBFID(mbfid);
	CHECK_TMOUT(tmout);
	p_mbfcb = get_mbfcb(mbfid);
	CHECK_PAR(0 < msgsz && msgsz <= p_mbfcb->p_mbfinib->maxmsz);

	t_lock_cpu();
	if (send_message(p_mbfcb, msg, msgsz, &dspreq)) {
		if (dspreq) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		ercd = E_TMOUT;
	}
	else {
		winfo_mbf.msg = (void *) msg;
		winfo_mbf.msgsz = msgsz;
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_SMBF);
		wobj_make_wait_tmout((WOBJCB *) p_mbfcb, (WINFO_WOBJ *) &winfo_mbf,
														&tmevtb, tmout);
		dispatch();
		ercd = winfo_mbf.winfo.wercd;
	}
	t_unlock_cpu();

  error_exit:
	LOG_TSND_MBF_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_tsnd_mbf */

/*
 *  ���b�Z�[�W�o�b�t�@����̎�M
 */
#ifdef TOPPERS_rcv_mbf

ER_UINT
rcv_mbf(ID mbfid, void *msg)
{
	MBFCB	*p_mbfcb;
	WINFO_MBF winfo_mbf;
	uint_t	msgsz;
	bool_t	dspreq;
	ER_UINT	ercd;

	LOG_RCV_MBF_ENTER(mbfid, msg);
	CHECK_DISPATCH();
	CHECK_MBFID(mbfid);
	p_mbfcb = get_mbfcb(mbfid);

	t_lock_cpu();
	if ((msgsz = receive_message(p_mbfcb, msg, &dspreq)) > 0U) {
		if (dspreq) {
			dispatch();
		}
		ercd = (ER_UINT) msgsz;
	}
	else {
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_RMBF);
		make_wait(&(winfo_mbf.winfo));
		queue_insert_prev(&(p_mbfcb->rwait_queue), &(p_runtsk->task_queue));
		winfo_mbf.p_mbfcb = p_mbfcb;
		winfo_mbf.msg = msg;
		LOG_TSKSTAT(p_runtsk);
		dispatch();
		ercd = winfo_mbf.winfo.wercd;
		if (ercd == E_OK) {
			ercd = (ER_UINT)(winfo_mbf.msgsz);
		}
	}
	t_unlock_cpu();

  error_exit:
	LOG_RCV_MBF_LEAVE(ercd, msg);
	return(ercd);
}

#endif /* TOPPERS_rcv_mbf */

/*
 *  ���b�Z�[�W�o�b�t�@����̎�M�i�|�[�����O�j
 */
#ifdef TOPPERS_prcv_mbf

ER
prcv_mbf(ID mbfid, void *msg)
{
	MBFCB	*p_mbfcb;
	uint_t	msgsz;
	bool_t	dspreq;
	ER_UINT	ercd;

	LOG_PRCV_MBF_ENTER(mbfid, msg);
	CHECK_TSKCTX_UNL();
	CHECK_MBFID(mbfid);
	p_mbfcb = get_mbfcb(mbfid);

	t_lock_cpu();
	if ((msgsz = receive_message(p_mbfcb, msg, &dspreq)) > 0U) {
		if (dspreq) {
			dispatch();
		}
		ercd = (ER_UINT) msgsz;
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();

  error_exit:
	LOG_PRCV_MBF_LEAVE(ercd, msg);
	return(ercd);
}

#endif /* TOPPERS_prcv_mbf */

/*
 *  ���b�Z�[�W�o�b�t�@����̎�M�i�^�C���A�E�g����j
 */
#ifdef TOPPERS_trcv_mbf

ER
trcv_mbf(ID mbfid, void *msg, TMO tmout)
{
	MBFCB	*p_mbfcb;
	WINFO_MBF winfo_mbf;
	TMEVTB	tmevtb;
	uint_t	msgsz;
	bool_t	dspreq;
	ER_UINT	ercd;

	LOG_TRCV_MBF_ENTER(mbfid, msg, tmout);
	CHECK_DISPATCH();
	CHECK_MBFID(mbfid);
	CHECK_TMOUT(tmout);
	p_mbfcb = get_mbfcb(mbfid);

	t_lock_cpu();
	if ((msgsz = receive_message(p_mbfcb, msg, &dspreq)) > 0U) {
		if (dspreq) {
			dispatch();
		}
		ercd = (ER_UINT) msgsz;
	}
	else if (tmout == TMO_POL) {
		ercd = E_TMOUT;
	}
	else {
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_RMBF);
		make_wait_tmout(&(winfo_mbf.winfo), &tmevtb, tmout);
		queue_insert_prev(&(p_mbfcb->rwait_queue), &(p_runtsk->task_queue));
		winfo_mbf.p_mbfcb = p_mbfcb;
		winfo_mbf.msg = msg;
		LOG_TSKSTAT(p_runtsk);
		dispatch();
		ercd = winfo_mbf.winfo.wercd;
		if (ercd == E_OK) {
			ercd = (ER_UINT)(winfo_mbf.msgsz);
		}
	}
	t_unlock_cpu();

  error_exit:
	LOG_TRCV_MBF_LEAVE(ercd, msg);
	return(ercd);
}

#endif /* TOPPERS_trcv_mbf */

/*
 *  ���b�Z�[�W�o�b�t�@�̍ď�����
 */
#ifdef TOPPERS_ini_mbf

ER
ini_mbf(ID mbfid)
{
	MBFCB	*p_mbfcb;
	bool_t	dspreq;
	ER		ercd;
    
	LOG_INI_MBF_ENTER(mbfid);
	CHECK_TSKCTX_UNL();
	CHECK_MBFID(mbfid);
	p_mbfcb = get_mbfcb(mbfid);

	t_lock_cpu();
	dspreq = init_wait_queue(&(p_mbfcb->swait_queue));
	if (init_wait_queue(&(p_mbfcb->rwait_queue))) {
		dspreq = true;
	}
	p_mbfcb->fmbfsz = p_mbfcb->p_mbfinib->mbfsz;
	p_mbfcb->head = 0U;
	p_mbfcb->tail = 0U;
	p_mbfcb->smbfcnt = 0U;
	if (dspreq) {
		dispatch();
	}
	ercd = E_OK;
	t_unlock_cpu();

  error_exit:
	LOG_INI_MBF_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ini_mbf */

/*
 *  ���b�Z�[�W�o�b�t�@�̏�ԎQ��
 */
#ifdef TOPPERS_ref_mbf

ER
ref_mbf(ID mbfid, T_RMBF *pk_rmbf)
{
	MBFCB	*p_mbfcb;
	ER		ercd;
    
	LOG_REF_MBF_ENTER(mbfid, pk_rmbf);
	CHECK_TSKCTX_UNL();
	CHECK_MBFID(mbfid);
	p_mbfcb = get_mbfcb(mbfid);

	t_lock_cpu();
	pk_rmbf->stskid = wait_tskid(&(p_mbfcb->swait_queue));
	pk_rmbf->rtskid = wait_tskid(&(p_mbfcb->rwait_queue));
	pk_rmbf->smbfcnt = p_mbfcb->smbfcnt;
	pk_rmbf->fmbfsz = p_mbfcb->fmbfsz;
	ercd = E_OK;
	t_unlock_cpu();

  error_exit:
	LOG_REF_MBF_LEAVE(ercd, pk_rmbf);
	return(ercd);
}

#endif /* TOPPERS_ref_mbf */
