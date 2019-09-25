//=============================================================================
//
// プレイヤー処理 [Player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "bg.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPlayer(void);
void SetTexturePlayer(int cntPattern);	// 
void SetVertexPlayer(void);					// 頂点の計算処理


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// テクスチャへのポインタ

float					g_fRadiusPlayer;					// ポリゴンの半径
float					g_fBaseAnglePlayer;					// ポリゴンの角度
PLAYER					player[PLAYER_MAX];
static int				i = 0;

XYZ						abc[1];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayerAdr(0);
	BG *bg = GetBGAdr(0);



	D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X / 2, TEXTURE_PLAYER_SIZE_Y / 2);

	g_fRadiusPlayer = D3DXVec2Length(&temp);
	g_fBaseAnglePlayer = atan2f(TEXTURE_PLAYER_SIZE_Y, TEXTURE_PLAYER_SIZE_Y);

	player->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	player->HP = 100;
	player->use = true;
	player->floor = false;
	player->jump = false;

	//画像の初期化
	player->g_vertexWkPlayer[0].vtx = D3DXVECTOR3(player->pos.x, player->pos.y, player->pos.z);
	player->g_vertexWkPlayer[1].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y, player->pos.z);
	player->g_vertexWkPlayer[2].vtx = D3DXVECTOR3(player->pos.x, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);
	player->g_vertexWkPlayer[3].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);
	player->posX = true;
	player->Npos = player->pos;

	player->CountAnim = 0;
	player->PatternAnim = 0;

	// 頂点情報の作成
	MakeVertexPlayer();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXTURE_GAME_SAMPLE00,				// ファイルの名前
		&g_pD3DTexture);					// 読み込むメモリのポインタ

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
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
void UpdatePlayer(void)
{
	ENEMY *enemy = GetEnemyAdr(0);
	BULLET *bullet = GetBulletAdr(0);
	BG *bg = GetBGAdr(0);

	abc->x = (int)player->pos.x;
	abc->y = (int)player->pos.y;
	abc->z = (int)player->pos.z;

	// アニメーション
	player->CountAnim++;

	// アニメーションWaitチェック
	SetVertexPlayer();	// 頂点の計算処理

	//重力
	player->pos.y += 1.5 * XY_SPEED;

	//ジャンプのコード
	if (GetKeyboardPress(DIK_SPACE) && player->jump == false && player->floor == true)
	{
		player->jump = true;
		player->Npos = player->pos;
		return;
	}
	if (player->jump == true)
	{
		player->pos.y -= 2.5 * XY_SPEED;
		player->floor = false;
	}
	if (player->pos.y < player->Npos.y - 300.0f)
	{
		player->jump = false;
	}

	//if (player->jump = false)
	//{
	//	player->pos.y += 1.5 * XY_SPEED;
	//}
	//if (player->pos.y == player->Npos.y)
	//{
	//	i = 0;
	//	player->jump = false;
	//}





	if (GetKeyboardPress(DIK_RIGHT))
	{
		player->pos.x += 4.0f;
		player->posX = false;

		if ((player->CountAnim % TIME_ANIMATION) == 0)
		{
			// パターンの切り替え
			player->PatternAnim = (player->PatternAnim + 1) % ANIM_PATTERN_NUM;

			// テクスチャ座標を設定
			SetTexturePlayer(player->PatternAnim);
		}

		if (player->pos.x >= SCREEN_WIDTH * 0.5f)
		{
			bg->g_posBG.x -= 4.0f;
			player->pos.x = 640.0f;
		}


	}
	else if (GetKeyboardPress(DIK_LEFT))
	{
		player->pos.x -= 4.0f;
		player->posX = true;


		if ((player->CountAnim % TIME_ANIMATION) == 0)
		{
			// パターンの切り替え
			player->PatternAnim = (player->PatternAnim + 1) % ANIM_PATTERN_NUM;

			// テクスチャ座標を設定
			SetTexturePlayer(player->PatternAnim);
		}
		if (bg->g_posBG.x < 0.0f)
		{
			bg->g_posBG.x += 4.0f;
			player->pos.x = 640.0f;
		}

	}




	/*	壁を超えない	*/
	//if (player->pos.x > SCREEN_WIDTH - 100.0f) //右
	//{
	//	player->pos.x -= 4.0f;
	//}
	if (player->pos.x < 0.0f)  //左
	{
		player->pos.x += 4.0f;
	}


	//if (player->pos.y > SCREEN_HEIGHT)
	//{
	//	player->use = false;
	//}

	//if (player->pos.y > SCREEN_HEIGHT - 200.0f)
	//{
	//	player->pos.y -= XY_SPEED;
	//}
	//else if (player->pos.y < 0.0f)
	//{
	//	player->pos.y += XY_SPEED;
	//}


	/*NPCをあたらない*/
	// 人とNPC(BC)
	enemy = &enemy[0];					// エネミーのポインターを初期化


	//if (CheckHitBB(player->pos, (enemy + 2)->pos, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_ENEMY_SIZE_X, TEXTURE_ENEMY_SIZE_Y)))
	//{
	//	if (GetKeyboardPress(DIK_RIGHT))
	//	{
	//		player->pos.x -= 4.0f;
	//	}
	//	else if (GetKeyboardPress(DIK_LEFT))
	//	{
	//		player->pos.x += 4.0f;
	//	}
	//}


	//障害物の当たり判定
	//if (((player->pos.y + TEXTURE_PLAYER_SIZE_Y) > (enemy + 2)->pos.y) && (((player->pos.x + TEXTURE_PLAYER_SIZE_X) > (enemy + 2)->pos.x) && 
	//	((player->pos.x) < ((enemy + 2)->pos.x)+ TEXTURE_ENEMY_SIZE_X)))
	//{
	//	player->pos.y = (enemy + 2)->pos.y - 205.0f;
	//	player->floor = true;
	//}

	//if ((((player->pos.x + TEXTURE_PLAYER_SIZE_X) == (enemy + 2)->pos.x)) &&
	//	(player->pos.y + TEXTURE_PLAYER_SIZE_Y) >= (enemy + 2)->pos.y && 
	//	(player->pos.y + TEXTURE_PLAYER_SIZE_Y) <= ((enemy + 2)->pos.y + TEXTURE_ENEMY_SIZE_Y + 5.0f))
	//{
	//	player->pos.x -= 4.0f;
	//}
	//if ((((player->pos.x) == (enemy + 2)->pos.x + TEXTURE_ENEMY_SIZE_X)) &&
	//	(player->pos.y + TEXTURE_PLAYER_SIZE_Y) >= (enemy + 2)->pos.y &&
	//	(player->pos.y + TEXTURE_PLAYER_SIZE_Y) <= ((enemy + 2)->pos.y + TEXTURE_ENEMY_SIZE_Y + 5.0f))
	//{
	//	player->pos.x += 4.0f;
	//}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTexture);

	if (player->use == true)
	{
		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, player->g_vertexWkPlayer, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定	
	SetVertexPlayer();	// 頂点の計算処理

	// rhwの設定
	player->g_vertexWkPlayer[0].rhw =
		player->g_vertexWkPlayer[1].rhw =
		player->g_vertexWkPlayer[2].rhw =
		player->g_vertexWkPlayer[3].rhw = 1.0f;

	// 反射光の設定
	player->g_vertexWkPlayer[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->g_vertexWkPlayer[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->g_vertexWkPlayer[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->g_vertexWkPlayer[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	SetTexturePlayer(player->PatternAnim);

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTexturePlayer(int cntPattern)
{
	// テクスチャ座標の設定
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	player->g_vertexWkPlayer[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	player->g_vertexWkPlayer[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	player->g_vertexWkPlayer[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	player->g_vertexWkPlayer[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexPlayer(void)
{
	// 頂点座標の設定


	if (player->jump == true)
	{
		player->direction = 1;
	}

	else if (player->jump == false)
	{
		player->direction = 2;
	}
	if (player->direction == 2)
	{
		if (player->posX == true)
		{
			player->g_vertexWkPlayer[0].vtx = D3DXVECTOR3(player->pos.x, player->pos.y, player->pos.z);
			player->g_vertexWkPlayer[1].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y, player->pos.z);
			player->g_vertexWkPlayer[2].vtx = D3DXVECTOR3(player->pos.x, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);
			player->g_vertexWkPlayer[3].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);
		}
		else
		{
			player->g_vertexWkPlayer[0].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y, player->pos.z);
			player->g_vertexWkPlayer[1].vtx = D3DXVECTOR3(player->pos.x, player->pos.y, player->pos.z);
			player->g_vertexWkPlayer[2].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);
			player->g_vertexWkPlayer[3].vtx = D3DXVECTOR3(player->pos.x, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);

		}
	}

	if (player->direction == 1)
	{
		if (player->posX == true)
		{
			player->g_vertexWkPlayer[0].vtx = D3DXVECTOR3(player->pos.x, player->pos.y, player->pos.z);
			player->g_vertexWkPlayer[1].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y, player->pos.z);
			player->g_vertexWkPlayer[2].vtx = D3DXVECTOR3(player->pos.x, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);
			player->g_vertexWkPlayer[3].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);
		}
		else
		{
			player->g_vertexWkPlayer[0].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y, player->pos.z);
			player->g_vertexWkPlayer[1].vtx = D3DXVECTOR3(player->pos.x, player->pos.y, player->pos.z);
			player->g_vertexWkPlayer[2].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);
			player->g_vertexWkPlayer[3].vtx = D3DXVECTOR3(player->pos.x, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);

		}
	}



	if (GetKeyboardPress(DIK_RIGHT))
	{

		player->g_vertexWkPlayer[0].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y, player->pos.z);
		player->g_vertexWkPlayer[1].vtx = D3DXVECTOR3(player->pos.x, player->pos.y, player->pos.z);
		player->g_vertexWkPlayer[2].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);
		player->g_vertexWkPlayer[3].vtx = D3DXVECTOR3(player->pos.x, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);

	}


	else if (GetKeyboardPress(DIK_LEFT))
	{

		player->g_vertexWkPlayer[0].vtx = D3DXVECTOR3(player->pos.x, player->pos.y, player->pos.z);
		player->g_vertexWkPlayer[1].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y, player->pos.z);
		player->g_vertexWkPlayer[2].vtx = D3DXVECTOR3(player->pos.x, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);
		player->g_vertexWkPlayer[3].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);

	}





}

XYZ *GetXyzAdr(int pno)
{
	return &abc[pno];
}

PLAYER *GetPlayerAdr(int pno)
{
	return &player[pno];
}

