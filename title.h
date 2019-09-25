//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : 
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TITLE		_T("data/TEXTURE/title.png")			// 読み込むテクスチャファイル名
#define	TEXTURE_TITLE_START	_T("data/TEXTURE/start.png")		// 読み込むテクスチャファイル名
#define	TEXTURE_TITLE_OUT	_T("data/TEXTURE/out.png")		// 読み込むテクスチャファイル名
#define	TEXTURE_TITLE_SELECT	_T("data/TEXTURE/select.png")		// 読み込むテクスチャファイル名

#define	TITLE_POS_X				(0)								// タイトルの表示位置
#define	TITLE_POS_Y				(0)								// タイトルの表示位置
#define	TITLE_SIZE_X			(1280)							// タイトルの幅
#define	TITLE_SIZE_Y			(800)							// タイトルの高さ

#define	TITLESTART_POS_X		(800)							// タイトルロゴの表示位置
#define	TITLESTART_POS_Y		(630)							// タイトルロゴの表示位置
#define	TITLESTART_SIZE_X		(420)							// タイトルロゴの幅
#define	TITLESTART_SIZE_Y		(70)							// タイトルロゴの高さ

#define	TITLEOUT_POS_X			(800)							// タイトルロゴの表示位置
#define	TITLEOUT_POS_Y			(710)							// タイトルロゴの表示位置
#define	TITLEOUT_SIZE_X			(420)							// タイトルロゴの幅
#define	TITLEOUT_SIZE_Y			(70)							// タイトルロゴの高さ

#define	TITLESELECT_POS_X		(700)							// タイトルロゴの表示位置
#define	TITLESELECT_POS_Y		(620)							// タイトルロゴの表示位置
#define	TITLESELECT_SIZE_X		(80)							// タイトルロゴの幅
#define	TITLESELECT_SIZE_Y		(80)							// タイトルロゴの高さ


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif
