//=============================================================================
//
// 背景処理 [bg.h]
// Author : 
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

// マクロ定義
#define TEXTURE_GAME_BG00		_T("data/TEXTURE/map.png")	// サンプル用画像

#define BG00_SIZE_X			(12800)	// テクスチャサイズ
#define BG00_SIZE_Y			(800)	// 同上
#define BG00_POS_X			(0)		// ポリゴンの初期位置X(左上)
#define BG00_POS_Y			(0)		// 同上
#define BG_MAX				(1)

typedef struct
{
	D3DXVECTOR3				g_posBG;					// 背景の位置
	bool					dead_end;
}BG;

typedef struct
{
	int x;
	int y;
	int z;

}QWE;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBG(int type);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
BG *GetBGAdr(int pno);
QWE *GetQweAdr(int pno);


#endif
