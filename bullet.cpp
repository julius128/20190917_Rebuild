//=============================================================================
//
// プレイヤー処理 [Bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "bullet.h"
#include "player.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBullet(void);
void SetTextureBullet(int cntPattern);	// 
void SetVertexBullet(void);					// 頂点の計算処理


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// テクスチャへのポインタ



//D3DXVECTOR3				g_posBullet;						// ポリゴンの座標
//D3DXVECTOR3				g_rotBullet;						// ポリゴンの回転量
//int						g_nCountAnim;						// アニメーションカウント
//int						g_nPatternAnim;						// アニメーションパターンナンバー

float					g_fRadiusBullet;					// ポリゴンの半径
float					g_fBaseAngleBullet;					// ポリゴンの角度

static int 				i;


BULLET					bullet[BULLET_MAX];


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *bullet = GetBulletAdr(0);




	for (i = 0, bullet = &bullet[0]; i < BULLET_MAX; i++, bullet++)
	{

		bullet->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
		bullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bullet->use = false;


		bullet->CountAnim = 0;
		bullet->PatternAnim = 0;



	}

	// 頂点情報の作成
	MakeVertexBullet();



	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXTURE_GAME_SAMPLE01,				// ファイルの名前
		&g_pD3DTexture);					// 読み込むメモリのポインタ








	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
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
void UpdateBullet(void)
{
	PLAYER *player = GetPlayerAdr(0);
	BULLET *bullet = GetBulletAdr(0);

	SetVertexBullet();	// 頂点の計算処理


	// アニメーション

	for (i = 0, bullet = &bullet[0]; i < BULLET_MAX; i++, bullet++)
	{


		bullet->CountAnim++;

		// アニメーションWaitチェック



		//if (GetKeyboardPress(DIK_SPACE))
		//{
		//	if (bullet->use == false)
		//	{
		//		bullet->use = true;
		//	}
		//	if (bullet->use == true && player->posX == true)
		//	{
		//		k = 1;
		//	}
		//	else if(bullet->use == true)
		//	{
		//		k = 2;
		//	}

		//}


		//if (k == 1)
		//{
		//	bullet->pos.x -= 8.0f;
		//}
		//else if (k == 2)
		//{
		//	g_vertexWk[0].vtx = D3DXVECTOR3(bullet->pos.x + TEXTURE_BULLET_SIZE_X, bullet->pos.y, bullet->pos.z);
		//	g_vertexWk[1].vtx = D3DXVECTOR3(bullet->pos.x, bullet->pos.y, bullet->pos.z);
		//	g_vertexWk[2].vtx = D3DXVECTOR3(bullet->pos.x + TEXTURE_BULLET_SIZE_X, bullet->pos.y + TEXTURE_BULLET_SIZE_Y, bullet->pos.z);
		//	g_vertexWk[3].vtx = D3DXVECTOR3(bullet->pos.x, bullet->pos.y + TEXTURE_BULLET_SIZE_Y, bullet->pos.z);

		//	bullet->pos.x += 8.0f;
		//}

		/*
		// 弾発射
		if (GetKeyboardTrigger(DIK_SPACE))
		{
			D3DXVECTOR3 pos = player->pos;
			pos.y -= TEXTURE_PLAYER_SIZE_Y;
			SetBullet(pos);
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			D3DXVECTOR3 pos = player->pos;
			pos.y -= TEXTURE_PLAYER_SIZE_Y;
			SetBullet(pos);
		}
		*/

		/*弾丸使用*/
		if (bullet->use == false && GetKeyboardTrigger(DIK_C))		//使用しない時判断する
		{
			if (player->posX == true)
			{
				bullet->direction = true;
				bullet->use = true;
				bullet->pos.x = player->pos.x + (TEXTURE_PLAYER_SIZE_X / 2);
				bullet->pos.y = (TEXTURE_PLAYER_SIZE_Y / 2) + player->pos.y;
			}
			else
			{
				bullet->direction = false;
				bullet->use = true;
				bullet->pos.x = player->pos.x + (TEXTURE_PLAYER_SIZE_X / 2);
				bullet->pos.y = (TEXTURE_PLAYER_SIZE_Y / 2) + player->pos.y;
			}

			return ;
		}



		if (bullet->direction == true && bullet->use == true)
		{
			bullet->pos.x -= 8.0f;
		}
		else if (bullet->direction == false && bullet->use == true)
		{
			bullet->g_vertexWk[0].vtx = D3DXVECTOR3(bullet->pos.x + TEXTURE_BULLET_SIZE_X, bullet->pos.y, bullet->pos.z);
			bullet->g_vertexWk[1].vtx = D3DXVECTOR3(bullet->pos.x, bullet->pos.y, bullet->pos.z);
			bullet->g_vertexWk[2].vtx = D3DXVECTOR3(bullet->pos.x + TEXTURE_BULLET_SIZE_X, bullet->pos.y + TEXTURE_BULLET_SIZE_Y, bullet->pos.z);
			bullet->g_vertexWk[3].vtx = D3DXVECTOR3(bullet->pos.x, bullet->pos.y + TEXTURE_BULLET_SIZE_Y, bullet->pos.z);

			bullet->pos.x += 8.0f;
		}




		/*	壁を越えた処理	*/
		if (bullet->pos.x + TEXTURE_BULLET_SIZE_X > SCREEN_WIDTH)
		{
			bullet->use = false;
		}
		else if (bullet->pos.x < 0)
		{
			bullet->use = false;
		}
		if (bullet->use == false)
		{
			bullet->pos = D3DXVECTOR3(-100.0f, -100.0f, 0.0f);
		}

	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	BULLET *bullet = GetBulletAdr(0);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	for (i = 0, bullet = &bullet[0]; i < BULLET_MAX; i++, bullet++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTexture);


		if (bullet->use == true)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BULLET, bullet->g_vertexWk, sizeof(VERTEX_2D));
		}

	}
}

//=============================================================================
// 頂点の作成 注意：この関数は循環の中にいない
//=============================================================================
HRESULT MakeVertexBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *bullet = GetBulletAdr(0);

	// 頂点座標の設定	
	SetVertexBullet();	// 頂点の計算処理


	for (i = 0, bullet = &bullet[0]; i < BULLET_MAX; i++, bullet++)
	{


		// rhwの設定
		bullet->g_vertexWk[0].rhw =
			bullet->g_vertexWk[1].rhw =
			bullet->g_vertexWk[2].rhw =
			bullet->g_vertexWk[3].rhw = 1.0f;

		// 反射光の設定
		bullet->g_vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		bullet->g_vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		bullet->g_vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		bullet->g_vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);


	}

	for (i = 0, bullet = &bullet[0]; i < BULLET_MAX; i++, bullet++)
	{
		// テクスチャ座標の設定
		SetTextureBullet(bullet->PatternAnim);

	}
	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureBullet(int cntPattern)
{
	BULLET *bullet = GetBulletAdr(0);


	for (i = 0, bullet = &bullet[0]; i < BULLET_MAX; i++, bullet++)
	{
		// テクスチャ座標の設定
		int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BULLET;
		int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BULLET;
		float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLET;
		float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLET;


		bullet->g_vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		bullet->g_vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		bullet->g_vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		bullet->g_vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
	}
}


//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexBullet(void)
{
	BULLET *bullet = GetBulletAdr(0);

	for (i = 0, bullet = &bullet[0]; i < BULLET_MAX; i++, bullet++)
	{

		// 頂点座標の設定
		bullet->g_vertexWk[0].vtx = D3DXVECTOR3(bullet->pos.x, bullet->pos.y, bullet->pos.z);
		bullet->g_vertexWk[1].vtx = D3DXVECTOR3(bullet->pos.x + TEXTURE_BULLET_SIZE_X, bullet->pos.y, bullet->pos.z);
		bullet->g_vertexWk[2].vtx = D3DXVECTOR3(bullet->pos.x, bullet->pos.y + TEXTURE_BULLET_SIZE_Y, bullet->pos.z);
		bullet->g_vertexWk[3].vtx = D3DXVECTOR3(bullet->pos.x + TEXTURE_BULLET_SIZE_X, bullet->pos.y + TEXTURE_BULLET_SIZE_Y, bullet->pos.z);

	}
}

//void SetBullet(D3DXVECTOR3 pos)		//僕使用しない
//{
//
//	if (bullet->use = false)
//	{
//		bullet->pos = pos;
//		bullet->use = true;
//	}
//}



BULLET *GetBulletAdr(int pno)
{
	return &bullet[pno];
}

