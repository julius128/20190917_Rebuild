//=============================================================================
//
// プレイヤー処理 [Score.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "score.h"
#include "player.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexScore(void);
void SetTextureScore(int cntPattern , int i);	// 
void SetVertexScore(void);					// 頂点の計算処理


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// テクスチャへのポインタ



//D3DXVECTOR3				g_posScore;						// ポリゴンの座標
//D3DXVECTOR3				g_rotScore;						// ポリゴンの回転量
//int						g_nCountAnim;						// アニメーションカウント
//int						g_nPatternAnim;						// アニメーションパターンナンバー

float					g_fRadiusScore;					// ポリゴンの半径
float					g_fBaseAngleScore;					// ポリゴンの角度

static int 				i;

SCORE					score[SCORE_MAX];


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SCORE *score = GetScoreAdr(0);


	(score + 0)->pos = D3DXVECTOR3(SCREEN_WIDTH - TEXTURE_SCORE_SIZE_X, SCREEN_HEIGHT - TEXTURE_SCORE_SIZE_Y, 0.0f);
	(score + 1)->pos = D3DXVECTOR3(SCREEN_WIDTH - (TEXTURE_SCORE_SIZE_X * 2), SCREEN_HEIGHT - TEXTURE_SCORE_SIZE_Y, 0.0f);
	(score + 2)->pos = D3DXVECTOR3(SCREEN_WIDTH - (TEXTURE_SCORE_SIZE_X * 3), SCREEN_HEIGHT - TEXTURE_SCORE_SIZE_Y, 0.0f);
	(score + 3)->pos = D3DXVECTOR3(SCREEN_WIDTH - (TEXTURE_SCORE_SIZE_X * 4), SCREEN_HEIGHT - TEXTURE_SCORE_SIZE_Y, 0.0f);
	(score + 4)->pos = D3DXVECTOR3(SCREEN_WIDTH - (TEXTURE_SCORE_SIZE_X * 5), SCREEN_HEIGHT - TEXTURE_SCORE_SIZE_Y, 0.0f);





	for (i = 0, score = &score[0]; i < SCORE_MAX; i++ , score++)
	{
		score->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


		score->CountAnim = 0;
		score->PatternAnim = 0;
		score->use = true;

	}


	// 頂点情報の作成
	MakeVertexScore();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXTURE_GAME_SAMPLE02,				// ファイルの名前
		&g_pD3DTexture);					// 読み込むメモリのポインタ








	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	if (g_pD3DTexture != NULL)
	{	// テクスチャの開放
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	SCORE *score = GetScoreAdr(0);


	// アニメーション



	// アニメーションWaitチェック
	SetVertexScore();	// 頂点の計算処理

	if (score->AddScore > 1)
	{
		if (score->AddScore > 10)
		{
			if (score->AddScore > 100)
			{
				if (score->AddScore > 1000)
				{
					if (score->AddScore > 10000)
					{
						score->wan = score->AddScore / 10000;
						score->scoreX = score->AddScore % 10000;
					}
					score->qian = score->scoreX / 1000;
					score->scoreX = score->scoreX % 1000;

				}

				score->bai = score->scoreX / 100;
				score->scoreX = score->scoreX % 100;

			}
			score->shi = score->scoreX / 10;
			score->yi = score->scoreX % 10;
		}

	}

	(score + 0)->PatternAnim = score->yi;
	(score + 1)->PatternAnim = score->shi;
	(score + 2)->PatternAnim = score->bai;
	(score + 3)->PatternAnim = score->qian;
	(score + 4)->PatternAnim = score->wan;

	for (i = 0, score = &score[0]; i < SCORE_MAX; i++, score++)
	{
		SetTextureScore(score->PatternAnim, i);
	}

}




//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SCORE *score = GetScoreAdr(0);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTexture);

	for (i = 0, score = &score[0]; i < SCORE_MAX; i++, score++)
	{

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_SCORE, score->g_vertexWk, sizeof(VERTEX_2D));


	}
}

//=============================================================================
// 頂点の作成 注意：この関数は循環の中にいない
//=============================================================================
HRESULT MakeVertexScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SCORE *score = GetScoreAdr(0);

	// 頂点座標の設定	
	SetVertexScore();	// 頂点の計算処理

	// rhwの設定
	for (i = 0, score = &score[0]; i < SCORE_MAX; i++ , score++)
	{
		score->g_vertexWk[0].rhw =
			score->g_vertexWk[1].rhw =
			score->g_vertexWk[2].rhw =
			score->g_vertexWk[3].rhw = 1.0f;

		// 反射光の設定
		score->g_vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		score->g_vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		score->g_vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		score->g_vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	for (i = 0, score = &score[0]; i < SCORE_MAX; i++, score++)
	{
		// テクスチャ座標の設定
		SetTextureScore(score->PatternAnim, i);
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureScore(int cntPattern , int i)
{
	SCORE *score = GetScoreAdr(0);
	score = &score[i];


	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_SCORE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_SCORE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_SCORE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_SCORE;

	score->g_vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		score->g_vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		score->g_vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		score->g_vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

}


//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexScore(void)
{
	SCORE *score = GetScoreAdr(0);

	for (i = 0, score = &score[0]; i < SCORE_MAX; i++, score++)
	{
		// 頂点座標の設定
		score->g_vertexWk[0].vtx = D3DXVECTOR3(score->pos.x, score->pos.y, score->pos.z);
		score->g_vertexWk[1].vtx = D3DXVECTOR3(score->pos.x + TEXTURE_SCORE_SIZE_X, score->pos.y, score->pos.z);
		score->g_vertexWk[2].vtx = D3DXVECTOR3(score->pos.x, score->pos.y + TEXTURE_SCORE_SIZE_Y, score->pos.z);
		score->g_vertexWk[3].vtx = D3DXVECTOR3(score->pos.x + TEXTURE_SCORE_SIZE_X, score->pos.y + TEXTURE_SCORE_SIZE_Y, score->pos.z);

	}
}


SCORE *GetScoreAdr(int pno)
{
	return &score[pno];
}



