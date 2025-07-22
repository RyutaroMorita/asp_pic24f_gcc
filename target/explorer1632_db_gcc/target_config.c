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
 *		ターゲット依存モジュール（Explorer16/32 Development Board用）
 */

#include "kernel_impl.h"
#include <sil.h>
#include "mcc_generated_files/system.h"

/*
 *  プロセッサ識別のための変数（マルチプロセッサ対応）
 */
uint_t	board_id;			/* ボードID */
void	*board_addr;		/* ローカルメモリの先頭アドレス */

/*
 *  ターゲット依存の初期化
 */
void
target_initialize(void)
{
	/*
	 *  プロセッサ依存の初期化
	 */
	prc_initialize();

	// initialize the device
	SYSTEM_Initialize();

	/*
	 *  リセットで割り込み許可状態になるが、ここではまだ早いので、すぐに禁止
	 *  本当の割り込み許可は、start_r で行う
	 */
	disint();
}

/*
 *  ターゲット依存の終了処理
 */
void
target_exit(void)
{
	/*
	 *  プロセッサ依存の終了処理
	 */
	prc_terminate();

	while(1);
}

/*
 *  システムログの低レベル出力のための文字出力
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
 *  割込み要求ラインの属性の設定
 *
 *  ASPカーネルでの利用を想定して，パラメータエラーはアサーションでチェッ
 *  クしている．cfg_intサービスコールを設ける場合には，エラーを返すよう
 *  にすべきであろう．
 */
void
x_config_int(INTNO intno, ATR intatr, PRI intpri)
{
	uint16_t	*ipc;

	assert(VALID_INTNO_CFGINT(intno));
	assert(TMIN_INTPRI <= intpri && intpri <= TMAX_INTPRI);

	/*
	 *  割込みのマスク
	 *
	 *  割込みを受け付けたまま，レベルトリガ／エッジトリガの設定や，割
	 *  込み優先度の設定を行うのは危険なため，割込み属性にかかわらず，
	 *  一旦マスクする．
	 */
	(void) x_disable_int(intno);

	/*
	 *  割込み優先度の設定
	 */
	ipc = (uint16_t *)&IPC0bits;
	ipc += (intno / 4);
	*ipc &= ~(0xF << (4 * (intno % 4)));
	*ipc |= -(intpri) << (4 * (intno % 4));

	/*
	 *  割込みのマスク解除（必要な場合）
 	 */
	if ((intatr & TA_ENAINT) != 0U) {
		(void) x_enable_int(intno);
	}
}

/*
 *  割込み要求禁止フラグのセット
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをセットしようとした場合には，falseを返す．
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
 *  割込み要求禁止フラグのクリア
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをクリアしようとした場合には，falseを返す．
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
 *  割込み要求のクリア
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
 *  割込み要求のチェック
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
