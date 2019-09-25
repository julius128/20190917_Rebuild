//=============================================================================
//
// プレイヤー処理 [Enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "enemy.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "score.h"



//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEnemy(void);

void SetTextureEnemy(int cntPattern, int no);	// 
void SetVertexEnemy(void);					// 頂点の計算処理


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// テクスチャへのポインタ

//static VERTEX_2D				g_vertexWk[NUM_VERTEX];		// 頂点情報格納ワーク


//D3DXVECTOR3				g_posEnemy;						// ポリゴンの座標
//D3DXVECTOR3				g_rotEnemy;						// ポリゴンの回転量
//int						g_nCountAnim_Enemy;				// アニメーションカウント
//int						g_nPatternAnim_Enemy;			// アニメーションパターンナンバー

float					g_fRadiusEnemy;					// ポリゴンの半径
float					g_fBaseAngleEnemy;				// ポリゴンの角度

static int 				i;

int						p = 0;

ENEMY					enemy[ENEMY_MAX];


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	ENEMY *enemy = GetEnemyAdr(0);


	enemy->pos = D3DXVECTOR3(SCREEN_WIDTH- TEXTURE_ENEMY_SIZE_X, SCREEN_HEIGHT- TEXTURE_ENEMY_SIZE_Y, 0.0f);
	(enemy + 1)->pos = D3DXVECTOR3(0.0f, 200.0f, 0.0f);
	(enemy + 2)->pos = D3DXVECTOR3(300.0f, 600.0f, 0.0f);



	for (i = 0, enemy = &enemy[0]; i < ENEMY_MAX; i++, enemy++)
	{
		enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		enemy->CountAnim = 0;
		enemy->PatternAnim = 0;
		enemy->HP = 0;
		enemy->use = true;
	}




	// 頂点情報の作成
	MakeVertexEnemy();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXTURE_GAME_SAMPLE00,				// ファイルの名前
		&g_pD3DTexture);					// 読み込むメモリのポインタ

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
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
void UpdateEnemy(void)
{
	PLAYER *player = GetPlayerAdr(0);
	BULLET *bullet = GetBulletAdr(0);
	SCORE *score = GetScoreAdr(0);
	ENEMY *enemy = GetEnemyAdr(0);

	SetVertexEnemy();	// 頂点の計算処理

	for (i = 0, enemy = &enemy[0], bullet = &bullet[0]; i < 2; i++, enemy++, bullet++)
	{

		/*全部敵はプレイヤーを探す*/
		if (enemy->use == true)
		{
			// アニメーション
			enemy->CountAnim++;
			// アニメーションWaitチェック
			if ((enemy->CountAnim % TIME_ANIMATION_ENEMY) == 0)
			{
				// パターンの切り替え
				enemy->PatternAnim = (enemy->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY;

				// テクスチャ座標を設定
				SetTextureEnemy(enemy->PatternAnim, i);
			}

			if (enemy->pos.x != player->pos.x || enemy->pos.y != player->pos.y || enemy->pos.z != player->pos.z)
			{
				if (enemy->pos.x < player->pos.x)
				{
					enemy->pos.x += 2.0f;


				}
				else
				{
					enemy->pos.x -= 2.0f;

				}

				if (enemy->pos.y < player->pos.y)
				{
					enemy->pos.y += 2.0f;

				}
				else
				{
					enemy->pos.y -= 2.0f;

				}
			}

		}



		/*敵とプレィヤの当たり判定*/
		if ((enemy->pos.x + TEXTURE_ENEMY_SIZE_X) >= player->pos.x && (enemy->pos.x + TEXTURE_ENEMY_SIZE_X) <= player->pos.x + TEXTURE_PLAYER_SIZE_X
			&& (enemy->pos.y + TEXTURE_ENEMY_SIZE_Y) >= player->pos.y && (enemy->pos.y + TEXTURE_ENEMY_SIZE_Y) <= player->pos.y + TEXTURE_PLAYER_SIZE_Y
			|| (enemy->pos.x >= player->pos.x && enemy->pos.x <= player->pos.x + TEXTURE_PLAYER_SIZE_X
				&& enemy->pos.y >= player->pos.y && enemy->pos.y <= player->pos.y + TEXTURE_PLAYER_SIZE_Y))
		{
			player->HP -= 1;
		}

		/*敵と弾丸の当たり判定*/
		if ((enemy->pos.x + TEXTURE_ENEMY_SIZE_X) >= bullet->pos.x && (enemy->pos.x + TEXTURE_ENEMY_SIZE_X) <= bullet->pos.x + TEXTURE_PLAYER_SIZE_X
			&& (enemy->pos.y + TEXTURE_ENEMY_SIZE_Y) >= bullet->pos.y && (enemy->pos.y + TEXTURE_ENEMY_SIZE_Y) <= bullet->pos.y + TEXTURE_PLAYER_SIZE_Y
			|| (enemy->pos.x >= bullet->pos.x && enemy->pos.x <= bullet->pos.x + TEXTURE_PLAYER_SIZE_X
				&& enemy->pos.y >= bullet->pos.y && enemy->pos.y <= bullet->pos.y + TEXTURE_PLAYER_SIZE_Y))
		{
			enemy->HP -= 1;
			bullet->use = false;
			bullet->pos.x = player->pos.x + (TEXTURE_PLAYER_SIZE_X / 2);
			bullet->pos.y = (TEXTURE_PLAYER_SIZE_Y / 2) + player->pos.y;
			p = 1;
		}

		/*敵ＨＰ判定*/
		if (enemy->HP > 0)
		{
			enemy->use = true;
		}
		else
		{
			enemy->use = false;
			enemy->pos = D3DXVECTOR3(-300.0f, -300.0f, 0.0f);

		}

		if (enemy->use == false && p == 1)
		{
			score->AddScore += 12345;
			p++;
		}


	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = GetEnemyAdr(0);



	for (i = 0, enemy = &enemy[0]; i < ENEMY_MAX; i++, enemy++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTexture);

		// ポリゴンの描画
		if (enemy->use == true)
		{
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, enemy->g_vertexWkEnemy, sizeof(VERTEX_2D));
		}

	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ENEMY *enemy = GetEnemyAdr(0);
	// 頂点座標の設定	
	SetVertexEnemy();	// 頂点の計算処理

	for (i = 0, enemy = &enemy[0]; i < ENEMY_MAX; i++, enemy++)
	{
		// rhwの設定
		enemy->g_vertexWkEnemy[0].rhw =
			enemy->g_vertexWkEnemy[1].rhw =
			enemy->g_vertexWkEnemy[2].rhw =
			enemy->g_vertexWkEnemy[3].rhw = 1.0f;

		// 反射光の設定
		enemy->g_vertexWkEnemy[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		enemy->g_vertexWkEnemy[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		enemy->g_vertexWkEnemy[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		enemy->g_vertexWkEnemy[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}
	for (i = 0, enemy = &enemy[0]; i < ENEMY_MAX; i++, enemy++)
	{
		// テクスチャ座標の設定
		SetTextureEnemy(enemy->PatternAnim,i);

	}
	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureEnemy(int cntPattern, int no)
{
	ENEMY *enemy = GetEnemyAdr(0);
	enemy = &enemy[no];

	if (enemy->use == true)
	{
		// テクスチャ座標の設定
		int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY;
		int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
		float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
		float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY;

		enemy->g_vertexWkEnemy[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		enemy->g_vertexWkEnemy[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		enemy->g_vertexWkEnemy[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		enemy->g_vertexWkEnemy[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

	}
}


//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEnemy(void)
{
	ENEMY *enemy = GetEnemyAdr(0);

	for (i = 0, enemy = &enemy[0]; i < ENEMY_MAX; i++, enemy++)
	{

		// 頂点座標の設定
		enemy->g_vertexWkEnemy[0].vtx = D3DXVECTOR3(enemy->pos.x, enemy->pos.y, enemy->pos.z);
		enemy->g_vertexWkEnemy[1].vtx = D3DXVECTOR3(enemy->pos.x + TEXTURE_ENEMY_SIZE_X, enemy->pos.y, enemy->pos.z);
		enemy->g_vertexWkEnemy[2].vtx = D3DXVECTOR3(enemy->pos.x, enemy->pos.y + TEXTURE_ENEMY_SIZE_Y, enemy->pos.z);
		enemy->g_vertexWkEnemy[3].vtx = D3DXVECTOR3(enemy->pos.x + TEXTURE_ENEMY_SIZE_X, enemy->pos.y + TEXTURE_ENEMY_SIZE_Y, enemy->pos.z);


	}

}


ENEMY *GetEnemyAdr(int pno)
{
	return &enemy[pno];
}
