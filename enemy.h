//=============================================================================
//
// プレイヤー処理 [Enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_


// マクロ定義
#define TEXTURE_GAME_SAMPLE00	_T("data/TEXTURE/runningman003.png")	// サンプル用画像
#define TEXTURE_ENEMY_SIZE_X	(100)	// テクスチャサイズ
#define TEXTURE_ENEMY_SIZE_Y	(200)	// 

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY	(5)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_ENEMY		(TEXTURE_PATTERN_DIVIDE_X_ENEMY*TEXTURE_PATTERN_DIVIDE_Y_ENEMY)	// アニメーションパターン数
#define TIME_ANIMATION_ENEMY			(4)	// アニメーションの切り替わるカウント


#define	RADIUS_MIN				(50.0f)							// ポリゴンの半径最小値
#define	RADIUS_MAX				(300.0f)						// ポリゴンの半径最大値
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// ポリゴンの回転量
#define	VALUE_SCALE				(2.0f)							// ポリゴンのスケール変化量
#define ENEMY_MAX				(2)			// プレイヤーの数

typedef struct
{
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	int						CountAnim;
	int						PatternAnim;

	VERTEX_2D				g_vertexWkEnemy[NUM_VERTEX];		// 頂点情報格納ワーク


	int						HP;
	bool					use ;


}ENEMY;




//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemyAdr(int pno);





#endif
