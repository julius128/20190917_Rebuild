//=============================================================================
//
// プレイヤー処理 [Bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_


// マクロ定義
#define TEXTURE_GAME_SAMPLE01	_T("data/TEXTURE/image 806.png")	// サンプル用画像


#define TEXTURE_BULLET_SIZE_X	(50)	// テクスチャサイズ
#define TEXTURE_BULLET_SIZE_Y	(20)	// 

#define TEXTURE_PATTERN_DIVIDE_X_BULLET	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_BULLET	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_BULLET			(TEXTURE_PATTERN_DIVIDE_X_BULLET*TEXTURE_PATTERN_DIVIDE_Y_BULLET)	// アニメーションパターン数
#define TIME_ANIMATION_BULLET				(1)	// アニメーションの切り替わるカウント


#define	RADIUS_MIN				(50.0f)							// ポリゴンの半径最小値
#define	RADIUS_MAX				(300.0f)						// ポリゴンの半径最大値
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// ポリゴンの回転量
#define	VALUE_SCALE				(2.0f)							// ポリゴンのスケール変化量
#define BULLET_MAX				(20)			// プレイヤーの数



typedef struct
{
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	int						CountAnim;
	int						PatternAnim;
	bool					use;			//使用判断
	bool					direction;		//弾丸方向
	VERTEX_2D				g_vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク
	int						Texture;

}BULLET;







//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
BULLET *GetBulletAdr(int pno);
//void SetBullet(D3DXVECTOR3 pos); //使用しない










#endif
