/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2010 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 *
 *	2025/07/20 Ryutaro Morita
 */

/*
 *		プロセッサ依存モジュール アセンブリ言語部（PIC24F用）
 */

#define	TOPPERS_MACRO_ONLY
#define UINT_C(val)			(val)			/* uint_t型の定数を作るマクロ */
#define ULONG_C(val)		(val)			/* ulong_t型の定数を作るマクロ */
#define CAST(type, val)		(val)			/* 型キャストを行うマクロ */
#include "kernel_impl.h"
#include "offset.h"

/*
 *  タスクディスパッチャ
 */
	.section .support.text, code
	.globl __kernel_dispatch
__kernel_dispatch:
	/*
	 *  このルーチンは，タスクコンテキスト・CPUロック状態・ディスパッチ
	 *  許可状態・（モデル上の）割込み優先度マスク全解除状態で呼び出さ
	 *  れる．
	 */
	mov.d		w8,  [w15++]				/* レジスタを保存 */
	mov.d		w10, [w15++]
	mov.d		w12, [w15++]
	mov			w14, [w15++]

	mov			__kernel_p_runtsk, w1		/* p_runtskをw1に */
	mov			w15, [w1 + TCB_msp]			/* タスクスタックを保存 */
	mov			#tbloffset(dispatch_r), w2
;	mov			#psvoffset(dispatch_r), w2
	mov			w2, [w1 + TCB_pc]			/* 実行再開番地を保存 */
	bra			dispatcher

dispatch_r:
	mov			[--w15], w14				/* レジスタを復帰 */
	mov.d		[--w15], w12
	mov.d		[--w15], w10
	mov.d		[--w15], w8

	mov			[w1 + TCB_enatex], w2
	btsts.z		w2, #TCB_enatex_bit
	bra			z, dispatch_r_1				/* enatexがfalseならリターン */
	mov			[w1 + TCB_texptn], w2
	cp			w2, #0
	bra			z, dispatch_r_1				/* texptnが0ならリターン */
	mov			#0, w0
	cp			__kernel_ipmflg				/* ipmflgがtrueであれば           */
	bra			nz, __kernel_call_texrtn	/* タスク例外処理ルーチンの呼出し */

dispatch_r_1:
	return

/*
 *  ディスパッチャの動作開始（prc_support.S）
 */
	.globl __kernel_start_dispatch
__kernel_start_dispatch:
	/*
	 *  このルーチンは，カーネル起動時に，すべての割込みを禁止した状態
	 * （割込みロック状態と同等）で呼び出される．また，割込みモード（非
	 *  タスクコンテキストと同等）で呼び出されることを想定している．
	 *
	 *  prc_initializeで，lock_flagをtrueに，saved_iipmをIIPM_ENAALLに
	 *  初期化しているため，カーネル管理外の割込みを許可することで，
	 *  CPUロック状態・（モデル上の）割込み優先度マスク全解除状態になる．
	 *  また，initialize_taskでdisdspをfalseに初期化しているため，ディ
	 *  スパッチ許可状態になっている．
	 */
	clr			__kernel_int_cnt			/* マスタモードに */
	mov			_SR, w0						/* マスタモード・                */
	mov			#~0x00E0, w2
	and			w2, w0, w0
	mov			#IIPM_LOCK, w2
	ior			w2, w0, w0
	mov			w0, _SR						/*  カーネル管理外の割込みを許可 */
	bra			dispatcher_0

/*
 *  現在のコンテキストを捨ててディスパッチ
 */
	.globl __kernel_exit_and_dispatch
__kernel_exit_and_dispatch:
	/* ディスパッチャ本体（dispatcher）へ */

/*
 *  ディスパッチャ本体
 */
dispatcher:
	/*
	 *  このルーチンは，タスクコンテキスト・CPUロック状態・ディスパッチ
	 *  許可状態・（モデル上の）割込み優先度マスク全解除状態で呼び出さ
	 *  れる．
	 *
	 *  すなわち，マスタモード・lock_flagがtrue・disdspがfalse・dspflg
	 *  がtrue・saved_iipmがIIPM_ENAALLとなっている．実行再開番地へもこ
	 *  の状態のまま分岐する．
	 */
#ifdef LOG_DSP_ENTER
	mov			__kernel_p_runtsk, w0		/* p_runtskをパラメータに */
	rcall		log_dsp_enter
#endif /* LOG_DSP_ENTER */

dispatcher_0:
	mov			__kernel_p_schedtsk, w1
	mov			w1, __kernel_p_runtsk
	cp			w1, #0						/* p_runtskがNULLならdispatcher_1へ */
	bra			z, dispatcher_1
	mov			[w1 + TCB_msp], w2
	mov			w2, w15						/* タスクスタックを復帰 */

#ifdef LOG_DSP_LEAVE
	mov			__kernel_p_runtsk, w0		/* p_runtskをパラメータに */
	rcall		log_dsp_leave
	mov			__kernel_p_runtsk, w1
#endif /* LOG_DSP_LEAVE */

	mov			[w1 + TCB_pc], w2			/* 実行再開番地へ分岐 */
	goto		w2

dispatcher_1:
	/*
	 *  CPUロック状態を解除する準備をする．
	 */
	inc			__kernel_int_cnt			/* 割込みモードに */
	mov			#__SP_init, w15				/* 割込み用のスタックへ切替え */
	mov			_SR, w3						/* SRをw3に保存 */
	clr			__kernel_lock_flag			/* CPUロック解除状態に */

dispatcher_2:
	/*
	 *  割込みを許可し，割込みモードに切り換えて，割込みを待つ．
	 *
	 *  ここで割込みモードに切り換えるのは，ここで発生する割込み処理に
	 *  どのスタックを使うかという問題の解決と，割込みハンドラ内でのタ
	 *  スクディスパッチの防止という2つの意味がある．
	 *
	 *  プロセッサを割込み待ちに移行させる処理と，割込み許可とは，不可
	 *  分に行なう必要がある（M68040ではstop命令で両方行なうので問題な
	 *  い）．これを不可分に行なわない場合，割込みを許可した直後に割込
	 *  みが入り，その中でタスクが実行可能状態になると，実行すべきタス
	 *  クがあるにもかかわらずプロセッサが割込み待ちになってしまう．
	 *
	 *  割込み待ちの間は，p_runtskをNULL（＝0）に設定しなければならな
	 *  い．このように設定しないと，割込みハンドラからiget_tidを呼び出
	 *  した際の動作が仕様に合致しなくなる．
	 */
	mov			_SR, w0						/* 割込み待ち */
	mov			#~0x00E0, w2
	and			w2, w0, w0
	mov			w0, _SR
	mov			#0x00E0, w2
	ior			w2, w0, w0
	mov			w0, _SR
	mov			#0, w0
	cp			__kernel_reqflg				/* reqflgがfalseならdispatcher_2へ */
	bra			z, dispatcher_2
	mov			w3, _SR						/* 元の状態に戻す */
	clr			__kernel_reqflg

	/*
	 *  CPUロック状態に戻す．割込み待ちの間に実行した割込みハンドラによ
	 *  り，saved_iipmが書き換えられる可能性があるため，元の値に戻す必
	 *  要がある．dispatcherが実行される時は，saved_iipmがIIPM_ENAALL
	 *  となっているため，ここではsaved_iipmをIIPM_ENAALL（＝0）に戻せ
	 *  ばよい．
	 */
	clr			__kernel_int_cnt			/* マスタモードに */
	clr			__kernel_saved_iipm			/* saved_iipmを0にする */
	inc			__kernel_lock_flag			/* CPUロック状態に */
	bra			dispatcher_0

/*
 *  カーネルの終了処理の呼出し
 */
	.globl __kernel_call_exit_kernel
__kernel_call_exit_kernel:
	inc			__kernel_int_cnt			/* 割込みモードに */
	mov			#__SP_init, w15
	goto		__kernel_exit_kernel		/* カーネルの終了処理を呼ぶ */

/*
 *  タスク開始時処理
 */
	.section .support.text, code
	.globl __kernel_start_r
__kernel_start_r:
	clr			__kernel_lock_flag			/* CPUロック解除状態に */
	mov			_SR, w0
	mov			#~0x00E0, w2
	and			w2, w0, w0
	mov			w0, _SR
	mov			[w1 + TCB_p_tinib], w2		/* p_runtsk->p_tinibをw2に */
	mov			[w2 + TINIB_exinf], w0		/* exinfをタスクへの引数に */
	mov			#tbloffset(exit_r), w1
;	mov			#psvoffset(exit_r), w1		/* ext_tskをスタックに積む */
	mov			w1, [w15++]
	mov			#0, w1
	mov			w1, [w15++]
	mov			[w2 + TINIB_task], w1		/* タスクの起動番地をw1に */
	goto		w1

exit_r:
	goto		_ext_tsk

/*
 *  割込みエントリ（w1にエントリ番号が入る）
 */
	.section .support.text, code
	.globl inthdr_entry
inthdr_entry:
	push		RCOUNT						/* スクラッチレジスタを保存 */
	mov			w0, [w15++]
	mov.d		w2, [w15++]
	mov.d		w4, [w15++]
	mov.d		w6, [w15++]
	lnk			#0x0

	inc			__kernel_int_cnt			/* 割込みモードに */
	mov			__kernel_int_cnt, w2
	cp			w2, #1
	bra			nz, inthdr_entry_0_d		/* 加算前が0でなければ多重割込み */

	mov			w15, __kernel_int_sp
	mov			#__SP_init, w15				/* 割込み用のスタックへ切替え */
	bra			inthdr_entry_0

inthdr_entry_0_d:
	bra			inthdr_entry_0

inthdr_entry_0:
	mov			#__kernel_exc_tbl, w2
	mul.uu		w1, #2, w4
	add			w2, w4, w2
	mov			[w2], w0

#ifdef LOG_INH_LEAVE
	mov.d		w0, [w15++]
#endif /* LOG_INH_LEAVE */

#ifdef LOG_INH_ENTER
	mov.d		w0, [w15++]
	mov			w1, w0
	rcall		log_inh_enter				/* log_exc_enterを呼び出す */

	mov.d		[--w15], w0
#endif /* LOG_EXC_ENTER */

	call		w0							/* Cルーチン呼び出し */

#ifdef LOG_INH_LEAVE
	mov.d		[--w15], w0
	mov			w1, w0
	rcall		log_inh_leave				/* log_exc_leaveを呼び出す */

#endif /* LOG_INH_LEAVE */

/*
 *  割込みハンドラ出口処理
 *
 *  ret_intは，割込みハンドラから戻った直後に実行するルーチンで，
 *  INTHDR_ENTRYマクロで展開する割込みハンドラの入口処理で，割込みハン
 *  ドラからの戻り番地に設定される．
 */
	.section .support.text, code
	.globl ret_int
ret_int:
	dec			__kernel_int_cnt
	mov			#0, w0
	cp			__kernel_int_cnt			/* 戻り先が割込みモードなら */
	bra			nz, ret_int_1_d				/*           すぐにリターン */

	/*
	 *  カーネル管理の割込みを禁止する．この時点では，CPUロック状態に
	 *  はならない（lock_flagとsaved_iipmは更新しない）．
	 *
	 *  reqflgをチェックする前に割込みを禁止するのは，reqflgをチェック
	 *  した直後に割込みハンドラが起動され，その中でディスパッチが要求
	 *  された場合に，すぐにディスパッチされないという問題が生じるため
	 *  である．
	 */

	/*
	 *  このルーチンはカーネル管理の割込みから起動されるため，ここでは，
	 *  割込み優先度マスクがTIPM_LOCKよりも低いと想定できる．
	 */
	mov			_SR, w0						/* カーネル管理の割込みを禁止 */
	mov			#~0x00E0, w2
	and			w2, w0, w0
	mov			#IIPM_LOCK, w2
	ior			w2, w0, w0
	mov			w0, _SR
	mov			#0, w0						/* reqflgがtrueであればret_int_2へ */
	cp			__kernel_reqflg
	bra			nz, ret_int_2

	mov			__kernel_int_sp, w15		/* マスタモードに（スタック切換え） */	/* 12/14 修正 */

ret_int_1:
	/*
	 *  割込み処理からのリターンにより，CPUロック解除状態に移行するよう
	 *  準備する．割込み優先度マスクは，RTE命令により元の値に戻るため，
	 *  lock_flagをfalseにしておけばよい（lock_flagをfalseにするのは，
	 *  CPUロック状態のまま割込みハンドラから戻った時の対策）．
	 */

	clr			__kernel_lock_flag			/* CPUロック解除の準備 */

	ulnk
	mov.d		[--w15], w6					/* スクラッチレジスタを復帰 */
	mov.d		[--w15], w4
	mov.d		[--w15], w2
	mov			[--w15], w0
	pop			RCOUNT
	mov			[--w15], w1
	retfie

ret_int_1_d:
	bra			ret_int_1

ret_int_2:
	mov			__kernel_int_sp, w15		/* マスタモードに（スタック切換え） */

ret_int_3:
	/*
	 *  ここへは，CPU例外ハンドラの出口処理からも分岐してくる．
	 *
	 *  ここでは，戻り先がタスクであり，スタックは，例外スタックフレー
	 *  ムの上にスクラッチレジスタのみが保存された状態になっている．ま
	 *  た，プロセッサは，マスタモード・カーネル管理の割込みを禁止した
	 *  状態となっている．
	 */
	clr			__kernel_reqflg				/* reqflgをfalseに */

	/*
	 *  CPUロック状態に移行し，割込み優先度マスクを割込み処理前の値に設
	 *	定する．カーネル管理の割込みはすでに禁止しているので，lock_flag
	 *  とsaved_iipmを更新する．saved_iipmは，戻り先の割込み優先度マス
	 *  ク（の内部表現）に設定する．
	 *
	 *  この時点でCPUロック状態とするのは，dispatcherへ分岐する時と，
	 *  call_texrtnを呼び出す時に，CPUロック状態になっている必要がある
	 *  ためである．
	 */
	mov			[w15 - 0x16], w0			/* 戻り先のSRをw0に */
	lsr			w0, #8, w0
	mov			#0x00E0, w2					/* IPMを取り出してsaved_iipmに */
	and			w2, w0, w2
	mov			w2, __kernel_saved_iipm
	inc			__kernel_lock_flag			/* lock_flagをtrueに */

	/*
	 *  dspflgがfalseである場合と，p_runtskとp_schedtskが同じ場合には，
	 *  ディスパッチを行わない．このチェックが必要なのは，タスク例外処
	 *  理ルーチンの呼出しが必要な場合に，ディスパッチが必要なくても，
	 *  reqflgをtrueにするためである．
	 */
	mov			__kernel_p_runtsk, w1		/* p_runtskをw1に */
	mov			#0, w0
	cp			__kernel_dspflg				/* dspflgがfalseならret_int_4へ */
	bra			z, ret_int_4
	mov			__kernel_p_schedtsk, w2
	cp			w1, w2						/* p_runtskとp_schedtskが同じなら */
	bra			z, ret_int_4				/*                    ret_int_4へ */

	mov.d		w8,  [w15++]				/* 残りのレジスタを保存 */
	mov.d		w10, [w15++]
	mov.d		w12, [w15++]
	mov			w14, [w15++]

	mov			w15, [w1 + TCB_msp]			/* タスクスタックを保存 */
	mov			#tbloffset(ret_int_r), w2
;	mov			#psvoffset(ret_int_r), w2
	mov			w2, [w1 + TCB_pc]			/* 実行再開番地を保存 */
	bra			dispatcher

ret_int_r:
	mov			[--w15], w14				/* レジスタを復帰 */
	mov.d		[--w15], w12
	mov.d		[--w15], w10
	mov.d		[--w15], w8

ret_int_4:
	/*
	 *  enatexがtrueで，texptnが0でなく，ipmflgがtrueであれば，タスク
	 *  例外処理ルーチンを呼び出す．
	 */
	mov			[w1 + TCB_enatex], w2
	btsts.z		w2, #TCB_enatex_bit
	bra			z, ret_int_5				/* enatexがfalseならret_int_5へ */
	mov			[w1 + TCB_texptn], w2
	cp			w2, #0
	bra			z, ret_int_5				/* texptnが0ならret_int_5へ */
	mov			#0, w0
	cp			__kernel_ipmflg				/* ipmflgがfalseならret_int_5へ */
	bra			z, ret_int_5
	rcall		__kernel_call_texrtn		/* タスク例外処理ルーチンの呼出し */

ret_int_5:
	/*
	 *  割込み処理からのリターンにより，CPUロック解除状態に移行するよ
	 *  う準備する．割込み優先度マスクは，RTE命令により元の値に戻るた
	 *  め，lock_flagをfalseにしておけばよい．
	 */
	clr			__kernel_lock_flag			/* CPUロック解除の準備 */

	ulnk
	mov.d		[--w15], w6					/* スクラッチレジスタを復帰 */
	mov.d		[--w15], w4
	mov.d		[--w15], w2
	mov			[--w15], w0
	pop			RCOUNT
	mov			[--w15], w1
	retfie

;.include "null_signature.s"
;
;       This file provides a null signature that is suitable for assembly
;       code that does not use any special features
;
	.section __c30_signature, info, data
	.word 0x0000
	.word 0x0000
	.word 0x0000
