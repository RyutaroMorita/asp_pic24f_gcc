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
 *  $Id: mempfix.c 2728 2015-12-30 01:46:11Z ertl-honda $
 */

/*
 *		�Œ蒷�������v�[���@�\
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "mempfix.h"

/*
 *  �g���[�X���O�}�N���̃f�t�H���g��`
 */
#ifndef LOG_ACRE_MPF_ENTER
#define LOG_ACRE_MPF_ENTER(pk_cmpf)
#endif /* LOG_ACRE_MPF_ENTER */

#ifndef LOG_ACRE_MPF_LEAVE
#define LOG_ACRE_MPF_LEAVE(ercd)
#endif /* LOG_ACRE_MPF_LEAVE */

#ifndef LOG_DEL_MPF_ENTER
#define LOG_DEL_MPF_ENTER(mpfid)
#endif /* LOG_DEL_MPF_ENTER */

#ifndef LOG_DEL_MPF_LEAVE
#define LOG_DEL_MPF_LEAVE(ercd)
#endif /* LOG_DEL_MPF_LEAVE */

#ifndef LOG_GET_MPF_ENTER
#define LOG_GET_MPF_ENTER(mpfid, p_blk)
#endif /* LOG_GET_MPF_ENTER */

#ifndef LOG_GET_MPF_LEAVE
#define LOG_GET_MPF_LEAVE(ercd, blk)
#endif /* LOG_GET_MPF_LEAVE */

#ifndef LOG_PGET_MPF_ENTER
#define LOG_PGET_MPF_ENTER(mpfid, p_blk)
#endif /* LOG_PGET_MPF_ENTER */

#ifndef LOG_PGET_MPF_LEAVE
#define LOG_PGET_MPF_LEAVE(ercd, blk)
#endif /* LOG_PGET_MPF_LEAVE */

#ifndef LOG_TGET_MPF_ENTER
#define LOG_TGET_MPF_ENTER(mpfid, p_blk, tmout)
#endif /* LOG_TGET_MPF_ENTER */

#ifndef LOG_TGET_MPF_LEAVE
#define LOG_TGET_MPF_LEAVE(ercd, blk)
#endif /* LOG_TGET_MPF_LEAVE */

#ifndef LOG_REL_MPF_ENTER
#define LOG_REL_MPF_ENTER(mpfid, blk)
#endif /* LOG_REL_MPF_ENTER */

#ifndef LOG_REL_MPF_LEAVE
#define LOG_REL_MPF_LEAVE(ercd)
#endif /* LOG_REL_MPF_LEAVE */

#ifndef LOG_INI_MPF_ENTER
#define LOG_INI_MPF_ENTER(mpfid)
#endif /* LOG_INI_MPF_ENTER */

#ifndef LOG_INI_MPF_LEAVE
#define LOG_INI_MPF_LEAVE(ercd)
#endif /* LOG_INI_MPF_LEAVE */

#ifndef LOG_REF_MPF_ENTER
#define LOG_REF_MPF_ENTER(mpfid, pk_rmpf)
#endif /* LOG_REF_MPF_ENTER */

#ifndef LOG_REF_MPF_LEAVE
#define LOG_REF_MPF_LEAVE(ercd, pk_rmpf)
#endif /* LOG_REF_MPF_LEAVE */

/*
 *  �Œ蒷�������v�[���̐�
 */
#define tnum_mpf	((uint_t)(tmax_mpfid - TMIN_MPFID + 1))
#define tnum_smpf	((uint_t)(tmax_smpfid - TMIN_MPFID + 1))

/*
 *  �Œ蒷�������v�[��ID����Œ蒷�������v�[���Ǘ��u���b�N�����o����
 *  �߂̃}�N��
 */
#define INDEX_MPF(mpfid)	((uint_t)((mpfid) - TMIN_MPFID))
#define get_mpfcb(mpfid)	(&(mpfcb_table[INDEX_MPF(mpfid)]))

/*
 *  ����ȃC���f�b�N�X�l�̒�`
 */
#define INDEX_NULL		(~0U)		/* �󂫃u���b�N���X�g�̍Ō� */
#define INDEX_ALLOC		(~1U)		/* �����čς݂̃u���b�N */

#ifdef TOPPERS_mpfini

/*
 *  �g�p���Ă��Ȃ��Œ蒷�������v�[���Ǘ��u���b�N�̃��X�g
 */
QUEUE	free_mpfcb;

/*
 *  �Œ蒷�������v�[���@�\�̏�����
 */
void
initialize_mempfix(void)
{
	uint_t	i, j;
	MPFCB	*p_mpfcb;
	MPFINIB	*p_mpfinib;

	for (i = 0; i < tnum_smpf; i++) {
		p_mpfcb = &(mpfcb_table[i]);
		queue_initialize(&(p_mpfcb->wait_queue));
		p_mpfcb->p_mpfinib = &(mpfinib_table[i]);
		p_mpfcb->fblkcnt = p_mpfcb->p_mpfinib->blkcnt;
		p_mpfcb->unused = 0U;
		p_mpfcb->freelist = INDEX_NULL;
	}
	queue_initialize(&free_mpfcb);
	for (j = 0; i < tnum_mpf; i++, j++) {
		p_mpfcb = &(mpfcb_table[i]);
		p_mpfinib = &(ampfinib_table[j]);
		p_mpfinib->mpfatr = TA_NOEXS;
		p_mpfcb->p_mpfinib = ((const MPFINIB *) p_mpfinib);
		queue_insert_prev(&free_mpfcb, &(p_mpfcb->wait_queue));
	}
}

#endif /* TOPPERS_mpfini */

/*
 *  �Œ蒷�������v�[������u���b�N���l��
 */
#ifdef TOPPERS_mpfget

void
get_mpf_block(MPFCB *p_mpfcb, void **p_blk)
{
	uint_t	blkidx;

	if (p_mpfcb->freelist != INDEX_NULL) {
		blkidx = p_mpfcb->freelist;
		p_mpfcb->freelist = (p_mpfcb->p_mpfinib->p_mpfmb + blkidx)->next;
	}
	else {
		blkidx = p_mpfcb->unused;
		p_mpfcb->unused++;
	}
	*p_blk = (void *)((char *)(p_mpfcb->p_mpfinib->mpf)
								+ p_mpfcb->p_mpfinib->blksz * blkidx);
	p_mpfcb->fblkcnt--;
	(p_mpfcb->p_mpfinib->p_mpfmb + blkidx)->next = INDEX_ALLOC;
}

#endif /* TOPPERS_mpfget */

/*
 *  �Œ蒷�������v�[���̐���
 */
#ifdef TOPPERS_acre_mpf

ER_UINT
acre_mpf(const T_CMPF *pk_cmpf)
{
	MPFCB	*p_mpfcb;
	MPFINIB	*p_mpfinib;
	ATR		mpfatr;
	void	*mpf;
	MPFMB	*p_mpfmb;
	ER		ercd;

	LOG_ACRE_MPF_ENTER(pk_cmpf);
	CHECK_TSKCTX_UNL();
	CHECK_RSATR(pk_cmpf->mpfatr, TA_TPRI);
	CHECK_PAR(pk_cmpf->blkcnt != 0);
	CHECK_PAR(pk_cmpf->blksz != 0);
	if (pk_cmpf->mpf != NULL) {
		CHECK_ALIGN_MPF(pk_cmpf->mpf);
	}
	if (pk_cmpf->mpfmb != NULL) {
		CHECK_ALIGN_MB(pk_cmpf->mpfmb);
	}
	mpfatr = pk_cmpf->mpfatr;
	mpf = pk_cmpf->mpf;
	p_mpfmb = pk_cmpf->mpfmb;

	t_lock_cpu();
	if (tnum_mpf == 0 || queue_empty(&free_mpfcb)) {
		ercd = E_NOID;
	}
	else {
		if (mpf == NULL) {
			mpf = kernel_malloc(ROUND_MPF_T(pk_cmpf->blksz) * pk_cmpf->blkcnt);
			mpfatr |= TA_MEMALLOC;
		}
		if (mpf == NULL) {
			ercd = E_NOMEM;
		}
		else {
			if (p_mpfmb == NULL) {
				p_mpfmb = kernel_malloc(sizeof(MPFMB) * pk_cmpf->blkcnt);
				mpfatr |= TA_MBALLOC;
			}
			if (p_mpfmb == NULL) {
				if (pk_cmpf->mpf == NULL) {
					kernel_free(mpf);
				}
				ercd = E_NOMEM;
			}
			else {
				p_mpfcb = ((MPFCB *) queue_delete_next(&free_mpfcb));
				p_mpfinib = (MPFINIB *)(p_mpfcb->p_mpfinib);
				p_mpfinib->mpfatr = mpfatr;
				p_mpfinib->blkcnt = pk_cmpf->blkcnt;
				p_mpfinib->blksz = ROUND_MPF_T(pk_cmpf->blksz);
				p_mpfinib->mpf = mpf;
				p_mpfinib->p_mpfmb = p_mpfmb;

				queue_initialize(&(p_mpfcb->wait_queue));
				p_mpfcb->fblkcnt = p_mpfcb->p_mpfinib->blkcnt;
				p_mpfcb->unused = 0U;
				p_mpfcb->freelist = INDEX_NULL;
				ercd = MPFID(p_mpfcb);
			}
		}
	}
	t_unlock_cpu();

  error_exit:
	LOG_ACRE_MPF_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_acre_mpf */

/*
 *  �Œ蒷�������v�[���̍폜
 */
#ifdef TOPPERS_del_mpf

ER
del_mpf(ID mpfid)
{
	MPFCB	*p_mpfcb;
	MPFINIB	*p_mpfinib;
	bool_t	dspreq;
	ER		ercd;

	LOG_DEL_MPF_ENTER(mpfid);
	CHECK_TSKCTX_UNL();
	CHECK_MPFID(mpfid);
	p_mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (p_mpfcb->p_mpfinib->mpfatr == TA_NOEXS) {
		ercd = E_NOEXS;
	}
	else if (MPFID(p_mpfcb) > tmax_smpfid) {
		dspreq = init_wait_queue(&(p_mpfcb->wait_queue));
		p_mpfinib = (MPFINIB *)(p_mpfcb->p_mpfinib);
		if ((p_mpfinib->mpfatr & TA_MEMALLOC) != 0U) {
			kernel_free(p_mpfinib->mpf);
		}
		if ((p_mpfinib->mpfatr & TA_MBALLOC) != 0U) {
			kernel_free(p_mpfinib->p_mpfmb);
		}
		p_mpfinib->mpfatr = TA_NOEXS;
		queue_insert_prev(&free_mpfcb, &(p_mpfcb->wait_queue));
		if (dspreq) {
			dispatch();
		}
		ercd = E_OK;
	}
	else {
		ercd = E_OBJ;
	}
	t_unlock_cpu();

  error_exit:
	LOG_DEL_MPF_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_del_mpf */

/*
 *  �Œ蒷�������u���b�N�̊l��
 */
#ifdef TOPPERS_get_mpf

ER
get_mpf(ID mpfid, void **p_blk)
{
	MPFCB	*p_mpfcb;
	WINFO_MPF winfo_mpf;
	ER		ercd;

	LOG_GET_MPF_ENTER(mpfid, p_blk);
	CHECK_DISPATCH();
	CHECK_MPFID(mpfid);
	p_mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (p_mpfcb->p_mpfinib->mpfatr == TA_NOEXS) {
		ercd = E_NOEXS;
	}
	else if (p_mpfcb->fblkcnt > 0) {
		get_mpf_block(p_mpfcb, p_blk);
		ercd = E_OK;
	}
	else {
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_MPF);
		wobj_make_wait((WOBJCB *) p_mpfcb, (WINFO_WOBJ *) &winfo_mpf);
		dispatch();
		ercd = winfo_mpf.winfo.wercd;
		if (ercd == E_OK) {
			*p_blk = winfo_mpf.blk;
		}
	}
	t_unlock_cpu();

  error_exit:
	LOG_GET_MPF_LEAVE(ercd, *p_blk);
	return(ercd);
}

#endif /* TOPPERS_get_mpf */

/*
 *  �Œ蒷�������u���b�N�̊l���i�|�[�����O�j
 */
#ifdef TOPPERS_pget_mpf

ER
pget_mpf(ID mpfid, void **p_blk)
{
	MPFCB	*p_mpfcb;
	ER		ercd;

	LOG_PGET_MPF_ENTER(mpfid, p_blk);
	CHECK_TSKCTX_UNL();
	CHECK_MPFID(mpfid);
	p_mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (p_mpfcb->p_mpfinib->mpfatr == TA_NOEXS) {
		ercd = E_NOEXS;
	}
	else if (p_mpfcb->fblkcnt > 0) {
		get_mpf_block(p_mpfcb, p_blk);
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();

  error_exit:
	LOG_PGET_MPF_LEAVE(ercd, *p_blk);
	return(ercd);
}

#endif /* TOPPERS_pget_mpf */

/*
 *  �Œ蒷�������u���b�N�̊l���i�^�C���A�E�g����j
 */
#ifdef TOPPERS_tget_mpf

ER
tget_mpf(ID mpfid, void **p_blk, TMO tmout)
{
	MPFCB	*p_mpfcb;
	WINFO_MPF winfo_mpf;
	TMEVTB	tmevtb;
	ER		ercd;

	LOG_TGET_MPF_ENTER(mpfid, p_blk, tmout);
	CHECK_DISPATCH();
	CHECK_MPFID(mpfid);
	CHECK_TMOUT(tmout);
	p_mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (p_mpfcb->p_mpfinib->mpfatr == TA_NOEXS) {
		ercd = E_NOEXS;
	}
	else if (p_mpfcb->fblkcnt > 0) {
		get_mpf_block(p_mpfcb, p_blk);
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		ercd = E_TMOUT;
	}
	else {
		p_runtsk->tstat = (TS_WAITING | TS_WAIT_MPF);
		wobj_make_wait_tmout((WOBJCB *) p_mpfcb, (WINFO_WOBJ *) &winfo_mpf,
														&tmevtb, tmout);
		dispatch();
		ercd = winfo_mpf.winfo.wercd;
		if (ercd == E_OK) {
			*p_blk = winfo_mpf.blk;
		}
	}
	t_unlock_cpu();

  error_exit:
	LOG_TGET_MPF_LEAVE(ercd, *p_blk);
	return(ercd);
}

#endif /* TOPPERS_tget_mpf */

/*
 *  �Œ蒷�������u���b�N�̕ԋp
 */
#ifdef TOPPERS_rel_mpf

ER
rel_mpf(ID mpfid, void *blk)
{
	MPFCB	*p_mpfcb;
	SIZE	blkoffset;
	uint_t	blkidx;
	TCB		*p_tcb;
	ER		ercd;
    
	LOG_REL_MPF_ENTER(mpfid, blk);
	CHECK_TSKCTX_UNL();
	CHECK_MPFID(mpfid);
	p_mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (p_mpfcb->p_mpfinib->mpfatr == TA_NOEXS) {
		ercd = E_NOEXS;
	}
	else {
		blkoffset = ((char *) blk) - (char *)(p_mpfcb->p_mpfinib->mpf);
		blkidx = (uint_t)(blkoffset / p_mpfcb->p_mpfinib->blksz);
		if (!(p_mpfcb->p_mpfinib->mpf <= blk)
				|| !(blkoffset % p_mpfcb->p_mpfinib->blksz == 0U)
				|| !(blkoffset / p_mpfcb->p_mpfinib->blksz < p_mpfcb->unused)
				|| !((p_mpfcb->p_mpfinib->p_mpfmb + blkidx)->next
															== INDEX_ALLOC)) {
			ercd = E_PAR;
		}
		else if (!queue_empty(&(p_mpfcb->wait_queue))) {
			p_tcb = (TCB *) queue_delete_next(&(p_mpfcb->wait_queue));
			((WINFO_MPF *)(p_tcb->p_winfo))->blk = blk;
			if (wait_complete(p_tcb)) {
				dispatch();
			}
			ercd = E_OK;
		}
		else {
			p_mpfcb->fblkcnt++;
			(p_mpfcb->p_mpfinib->p_mpfmb + blkidx)->next = p_mpfcb->freelist;
			p_mpfcb->freelist = blkidx;
			ercd = E_OK;
		}
	}
	t_unlock_cpu();

  error_exit:
	LOG_REL_MPF_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_rel_mpf */

/*
 *  �Œ蒷�������v�[���̍ď�����
 */
#ifdef TOPPERS_ini_mpf

ER
ini_mpf(ID mpfid)
{
	MPFCB	*p_mpfcb;
	bool_t	dspreq;
	ER		ercd;
    
	LOG_INI_MPF_ENTER(mpfid);
	CHECK_TSKCTX_UNL();
	CHECK_MPFID(mpfid);
	p_mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (p_mpfcb->p_mpfinib->mpfatr == TA_NOEXS) {
		ercd = E_NOEXS;
	}
	else {
		dspreq = init_wait_queue(&(p_mpfcb->wait_queue));
		p_mpfcb->fblkcnt = p_mpfcb->p_mpfinib->blkcnt;
		p_mpfcb->unused = 0U;
		p_mpfcb->freelist = INDEX_NULL;
		if (dspreq) {
			dispatch();
		}
		ercd = E_OK;
	}
	t_unlock_cpu();

  error_exit:
	LOG_INI_MPF_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ini_mpf */

/*
 *  �Œ蒷�������v�[���̏�ԎQ��
 */
#ifdef TOPPERS_ref_mpf

ER
ref_mpf(ID mpfid, T_RMPF *pk_rmpf)
{
	MPFCB	*p_mpfcb;
	ER		ercd;
    
	LOG_REF_MPF_ENTER(mpfid, pk_rmpf);
	CHECK_TSKCTX_UNL();
	CHECK_MPFID(mpfid);
	p_mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (p_mpfcb->p_mpfinib->mpfatr == TA_NOEXS) {
		ercd = E_NOEXS;
	}
	else {
		pk_rmpf->wtskid = wait_tskid(&(p_mpfcb->wait_queue));
		pk_rmpf->fblkcnt = p_mpfcb->fblkcnt;
		ercd = E_OK;
	}
	t_unlock_cpu();

  error_exit:
	LOG_REF_MPF_LEAVE(ercd, pk_rmpf);
	return(ercd);
}

#endif /* TOPPERS_ref_mpf */
