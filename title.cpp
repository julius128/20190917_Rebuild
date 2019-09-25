//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexTitle(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTitle = NULL;		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleStart = NULL;	// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleOut = NULL;	// テクスチャへのポインタ
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleSelect = NULL;	// テクスチャへのポインタ

VERTEX_2D				g_vertexWkTitle[NUM_VERTEX];			// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTitleStart[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTitleOut[NUM_VERTEX];		// 頂点情報格納ワーク
VERTEX_2D				g_vertexWkTitleSelect[NUM_VERTEX];		// 頂点情報格納ワーク


static float move;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_TITLE,				// ファイルの名前
		&g_pD3DTextureTitle);		// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_TITLE_START,			// ファイルの名前
		&g_pD3DTextureTitleStart);	// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_TITLE_OUT,			// ファイルの名前
		&g_pD3DTextureTitleOut);	// 読み込むメモリー

	D3DXCreateTextureFromFile(pDevice,						// デバイスへのポインタ
		TEXTURE_TITLE_SELECT,			// ファイルの名前
		&g_pD3DTextureTitleSelect);	// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexTitle();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	if (g_pD3DTextureTitle != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitle->Release();
		g_pD3DTextureTitle = NULL;
	}

	if (g_pD3DTextureTitleStart != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitleStart->Release();
		g_pD3DTextureTitleStart = NULL;
	}

	if (g_pD3DTextureTitleOut != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitleOut->Release();
		g_pD3DTextureTitleOut = NULL;
	}

	if (g_pD3DTextureTitleSelect != NULL)
	{// テクスチャの開放
		g_pD3DTextureTitleSelect->Release();
		g_pD3DTextureTitleSelect = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	int choice = 0;

	if (GetKeyboardTrigger(DIK_DOWN))
	{
		move = 80.0f;
		g_vertexWkTitleSelect[0].vtx = D3DXVECTOR3(TITLESELECT_POS_X, TITLESELECT_POS_Y + move, 0.0f);
		g_vertexWkTitleSelect[1].vtx = D3DXVECTOR3(TITLESELECT_POS_X + TITLESELECT_SIZE_X, TITLESELECT_POS_Y + move, 0.0f);
		g_vertexWkTitleSelect[2].vtx = D3DXVECTOR3(TITLESELECT_POS_X, TITLESELECT_POS_Y + TITLESELECT_SIZE_Y + move, 0.0f);
		g_vertexWkTitleSelect[3].vtx = D3DXVECTOR3(TITLESELECT_POS_X + TITLESELECT_SIZE_X, TITLESELECT_POS_Y + TITLESELECT_SIZE_Y + move, 0.0f);
		choice = 1;
	}
	else if (GetKeyboardTrigger(DIK_UP))
	{
		move = 0.0f;
		g_vertexWkTitleSelect[0].vtx = D3DXVECTOR3(TITLESELECT_POS_X, TITLESELECT_POS_Y + move, 0.0f);
		g_vertexWkTitleSelect[1].vtx = D3DXVECTOR3(TITLESELECT_POS_X + TITLESELECT_SIZE_X, TITLESELECT_POS_Y + move, 0.0f);
		g_vertexWkTitleSelect[2].vtx = D3DXVECTOR3(TITLESELECT_POS_X, TITLESELECT_POS_Y + TITLESELECT_SIZE_Y + move, 0.0f);
		g_vertexWkTitleSelect[3].vtx = D3DXVECTOR3(TITLESELECT_POS_X + TITLESELECT_SIZE_X, TITLESELECT_POS_Y + TITLESELECT_SIZE_Y + move, 0.0f);
		choice = 0;
	}

	
	if (choice == 0)
	{
		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter押したら、ステージを切り替える
			SetStage(STAGE_GAME);
		}
		// ゲームパッドでで移動処理
		else if (IsButtonTriggered(0, BUTTON_START))
		{
			SetStage(STAGE_GAME);
		}
		else if (IsButtonTriggered(0, BUTTON_B))
		{
			SetStage(STAGE_GAME);
		}
	}
	else if (choice == 1)
	{
		if (GetKeyboardTrigger(DIK_RETURN))
		{// Enter押したら、ステージを切り替える
			exit(0);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitle);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitle, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitleStart);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleStart, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitleOut);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleOut, sizeof(VERTEX_2D));


	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pD3DTextureTitleSelect);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleSelect, sizeof(VERTEX_2D));


}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexTitle(void)
{

	// 頂点座標の設定
	g_vertexWkTitle[0].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	g_vertexWkTitle[1].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y, 0.0f);
	g_vertexWkTitle[2].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);
	g_vertexWkTitle[3].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTitle[0].rhw =
		g_vertexWkTitle[1].rhw =
		g_vertexWkTitle[2].rhw =
		g_vertexWkTitle[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTitle[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTitle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitle[3].tex = D3DXVECTOR2(1.0f, 1.0f);



	// 頂点座標の設定
	g_vertexWkTitleStart[0].vtx = D3DXVECTOR3(TITLESTART_POS_X, TITLESTART_POS_Y, 0.0f);
	g_vertexWkTitleStart[1].vtx = D3DXVECTOR3(TITLESTART_POS_X + TITLESTART_SIZE_X, TITLESTART_POS_Y, 0.0f);
	g_vertexWkTitleStart[2].vtx = D3DXVECTOR3(TITLESTART_POS_X, TITLESTART_POS_Y + TITLESTART_SIZE_Y, 0.0f);
	g_vertexWkTitleStart[3].vtx = D3DXVECTOR3(TITLESTART_POS_X + TITLESTART_SIZE_X, TITLESTART_POS_Y + TITLESTART_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTitleStart[0].rhw =
		g_vertexWkTitleStart[1].rhw =
		g_vertexWkTitleStart[2].rhw =
		g_vertexWkTitleStart[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTitleStart[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleStart[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleStart[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleStart[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTitleStart[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleStart[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleStart[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleStart[3].tex = D3DXVECTOR2(1.0f, 1.0f);



	// 頂点座標の設定
	g_vertexWkTitleOut[0].vtx = D3DXVECTOR3(TITLEOUT_POS_X, TITLEOUT_POS_Y, 0.0f);
	g_vertexWkTitleOut[1].vtx = D3DXVECTOR3(TITLEOUT_POS_X + TITLEOUT_SIZE_X, TITLEOUT_POS_Y, 0.0f);
	g_vertexWkTitleOut[2].vtx = D3DXVECTOR3(TITLEOUT_POS_X, TITLEOUT_POS_Y + TITLEOUT_SIZE_Y, 0.0f);
	g_vertexWkTitleOut[3].vtx = D3DXVECTOR3(TITLEOUT_POS_X + TITLEOUT_SIZE_X, TITLEOUT_POS_Y + TITLEOUT_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTitleOut[0].rhw =
		g_vertexWkTitleOut[1].rhw =
		g_vertexWkTitleOut[2].rhw =
		g_vertexWkTitleOut[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTitleOut[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleOut[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleOut[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleOut[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTitleOut[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleOut[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleOut[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleOut[3].tex = D3DXVECTOR2(1.0f, 1.0f);



	// 頂点座標の設定
	g_vertexWkTitleSelect[0].vtx = D3DXVECTOR3(TITLESELECT_POS_X , TITLESELECT_POS_Y , 0.0f);
	g_vertexWkTitleSelect[1].vtx = D3DXVECTOR3(TITLESELECT_POS_X + TITLESELECT_SIZE_X , TITLESELECT_POS_Y, 0.0f);
	g_vertexWkTitleSelect[2].vtx = D3DXVECTOR3(TITLESELECT_POS_X , TITLESELECT_POS_Y+ TITLESELECT_SIZE_Y, 0.0f);
	g_vertexWkTitleSelect[3].vtx = D3DXVECTOR3(TITLESELECT_POS_X + TITLESELECT_SIZE_X, TITLESELECT_POS_Y + TITLESELECT_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	g_vertexWkTitleSelect[0].rhw =
		g_vertexWkTitleSelect[1].rhw =
		g_vertexWkTitleSelect[2].rhw =
		g_vertexWkTitleSelect[3].rhw = 1.0f;

	// 反射光の設定
	g_vertexWkTitleSelect[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleSelect[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleSelect[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleSelect[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	g_vertexWkTitleSelect[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleSelect[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleSelect[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleSelect[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

