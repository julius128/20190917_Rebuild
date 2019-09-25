//=============================================================================
//
// プレイヤー処理 [Block.h]
// Author : 
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_


// マクロ定義
#define TEXTURE_BLOCK_SIZE_X	(1150)	// テクスチャサイズ
#define TEXTURE_BLOCK_SIZE_Y	(200)	// 

#define TEXTURE_BLOCK1_SIZE_X	(128)	// forest_pack_15
#define TEXTURE_BLOCK1_SIZE_Y	(64)	// 

#define TEXTURE_BLOCK2_SIZE_X	(360)	// 
#define TEXTURE_BLOCK2_SIZE_Y	(3000)	// 

#define TEXTURE_BLOCK3_SIZE_X	(256)	// 
#define TEXTURE_BLOCK3_SIZE_Y	(100)	// 

#define TEXTURE_BLOCK4_SIZE_X	(384)	// 
#define TEXTURE_BLOCK4_SIZE_Y	(64)	// 

#define TEXTURE_BLOCK5_SIZE_X	(620)	// 
#define TEXTURE_BLOCK5_SIZE_Y	(3000)	// 

#define TEXTURE_BLOCK6_SIZE_X	(128)	// 
#define TEXTURE_BLOCK6_SIZE_Y	(3000)	// 

#define TEXTURE_BLOCK7_SIZE_X	(128)	// 
#define TEXTURE_BLOCK7_SIZE_Y	(200)	// 

#define TEXTURE_BLOCK8_SIZE_X	(500)	// 
#define TEXTURE_BLOCK8_SIZE_Y	(3000)	// 


#define	RADIUS_MIN				(50.0f)							// ポリゴンの半径最小値
#define	RADIUS_MAX				(300.0f)						// ポリゴンの半径最大値
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// ポリゴンの回転量
#define	VALUE_SCALE				(2.0f)							// ポリゴンのスケール変化量
#define BLOCK_MAX				(1)			// プレイヤーの数

typedef struct
{
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	int						CountAnim;
	int						PatternAnim;

	VERTEX_2D				g_vertexWkBlock[NUM_VERTEX];		// 頂点情報格納ワーク


	int						HP;
	bool					use ;


}BLOCK;




//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
BLOCK *GetBlockAdr(int pno);





#endif
