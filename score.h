//=============================================================================
//
// プレイヤー処理 [Score.h]
// Author : 
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_


// マクロ定義
#define TEXTURE_GAME_SAMPLE02	_T("data/TEXTURE/score.png")	// サンプル用画像


#define TEXTURE_SCORE_SIZE_X	(17)	// テクスチャサイズ
#define TEXTURE_SCORE_SIZE_Y	(20)	// 

#define TEXTURE_PATTERN_DIVIDE_X_SCORE	(10)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_SCORE	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_SCORE			(TEXTURE_PATTERN_DIVIDE_X_SCORE*TEXTURE_PATTERN_DIVIDE_Y_SCORE)	// アニメーションパターン数
#define TIME_ANIMATION_SCORE				(4)	// アニメーションの切り替わるカウント


#define	RADIUS_MIN				(50.0f)							// ポリゴンの半径最小値
#define	RADIUS_MAX				(300.0f)						// ポリゴンの半径最大値
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// ポリゴンの回転量
#define	VALUE_SCALE				(2.0f)							// ポリゴンのスケール変化量
#define SCORE_MAX				(5)			// プレイヤーの数



typedef struct
{
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	int						CountAnim;
	int						PatternAnim;
	bool					use;			//使用判断
	bool					direction;		//方向
	int						yi;
	int						shi;
	int						bai;
	int						qian;
	int						wan;
	int						AddScore;
	int						scoreX;
	int						num;

	VERTEX_2D				g_vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク


}SCORE;







//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
SCORE *GetScoreAdr(int pno);
//void SetScore(D3DXVECTOR3 pos); //使用しない










#endif
