//=============================================================================
//
// �v���C���[���� [Block.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "block.h"
#include "input.h"
#include "player.h"
#include "bullet.h"
#include "score.h"
#include "bg.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBlock(void);

void SetVertexBlock(void);					// ���_�̌v�Z����


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^


float					g_fRadiusBlock;					// �|���S���̔��a
float					g_fBaseAngleBlock;				// �|���S���̊p�x

static int 				i;


BLOCK					block[BLOCK_MAX];


//=============================================================================
// ����������
//=============================================================================
HRESULT InitBlock(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	BLOCK *block = GetBlockAdr(0);

	block->pos = D3DXVECTOR3(0.0f, 700.0f, 0.0f);

	// ���_���̍쐬
	MakeVertexBlock();


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBlock(void)
{
	if (g_pD3DTexture != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTexture->Release();
		g_pD3DTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBlock(void)
{
	PLAYER *player = GetPlayerAdr(0);
	BLOCK *block = GetBlockAdr(0);
	BG *bg = GetBGAdr(0);

	//for (i = 0, block = GetBlockAdr(0); i < BLOCK_MAX; i++, block++)
	//{
	//	CheckHitBB(player->pos, block->pos, bg->g_posBG, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_BLOCK_SIZE_X, TEXTURE_BLOCK_SIZE_Y));
	//}

	if (CheckHitBB(player->pos, block->pos, bg->g_posBG, D3DXVECTOR2(TEXTURE_PLAYER_SIZE_X, TEXTURE_PLAYER_SIZE_Y), D3DXVECTOR2(TEXTURE_BLOCK_SIZE_X, TEXTURE_BLOCK_SIZE_Y)))
	{
		player->pos.y = block->pos.y - TEXTURE_PLAYER_SIZE_Y;
		player->floor = true;
	}
	else
	{
		player->floor = false;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBlock(void)
{

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	BLOCK *block = GetBlockAdr(0);
	// ���_���W�̐ݒ�	
	SetVertexBlock();	// ���_�̌v�Z����

	for (i = 0, block = &block[0]; i < BLOCK_MAX; i++, block++)
	{
		// rhw�̐ݒ�
		block->g_vertexWkBlock[0].rhw =
			block->g_vertexWkBlock[1].rhw =
			block->g_vertexWkBlock[2].rhw =
			block->g_vertexWkBlock[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		block->g_vertexWkBlock[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		block->g_vertexWkBlock[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		block->g_vertexWkBlock[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		block->g_vertexWkBlock[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}
	return S_OK;
}



//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBlock(void)
{
	BLOCK *block = GetBlockAdr(0);

	//// ���_���W�̐ݒ�
	//block->g_vertexWkBlock[0].vtx = D3DXVECTOR3(block->pos.x, block->pos.y, block->pos.z);
	//block->g_vertexWkBlock[1].vtx = D3DXVECTOR3(block->pos.x + TEXTURE_BLOCK_SIZE_X, block->pos.y, block->pos.z);
	//block->g_vertexWkBlock[2].vtx = D3DXVECTOR3(block->pos.x, block->pos.y + TEXTURE_BLOCK_SIZE_Y, block->pos.z);
	//block->g_vertexWkBlock[3].vtx = D3DXVECTOR3(block->pos.x + TEXTURE_BLOCK_SIZE_X, block->pos.y + TEXTURE_BLOCK_SIZE_Y, block->pos.z);

	//(block + 1)->g_vertexWkBlock[0].vtx = D3DXVECTOR3(block->pos.x, block->pos.y, block->pos.z);
	//(block + 1)->g_vertexWkBlock[1].vtx = D3DXVECTOR3(block->pos.x + TEXTURE_BLOCK1_SIZE_X, block->pos.y, block->pos.z);
	//(block + 1)->g_vertexWkBlock[2].vtx = D3DXVECTOR3(block->pos.x, block->pos.y + TEXTURE_BLOCK1_SIZE_Y, block->pos.z);
	//(block + 1)->g_vertexWkBlock[3].vtx = D3DXVECTOR3(block->pos.x + TEXTURE_BLOCK1_SIZE_X, block->pos.y + TEXTURE_BLOCK1_SIZE_Y, block->pos.z);

	//(block + 2)->g_vertexWkBlock[0].vtx = D3DXVECTOR3(block->pos.x, block->pos.y, block->pos.z);
	//(block + 2)->g_vertexWkBlock[1].vtx = D3DXVECTOR3(block->pos.x + TEXTURE_BLOCK2_SIZE_X, block->pos.y, block->pos.z);
	//(block + 2)->g_vertexWkBlock[2].vtx = D3DXVECTOR3(block->pos.x, block->pos.y + TEXTURE_BLOCK2_SIZE_Y, block->pos.z);
	//(block + 2)->g_vertexWkBlock[3].vtx = D3DXVECTOR3(block->pos.x + TEXTURE_BLOCK2_SIZE_X, block->pos.y + TEXTURE_BLOCK2_SIZE_Y, block->pos.z);

	//(block + 3)->g_vertexWkBlock[0].vtx = D3DXVECTOR3(block->pos.x, block->pos.y, block->pos.z);
	//(block + 3)->g_vertexWkBlock[1].vtx = D3DXVECTOR3(block->pos.x + TEXTURE_BLOCK1_SIZE_X, block->pos.y, block->pos.z);
	//(block + 3)->g_vertexWkBlock[2].vtx = D3DXVECTOR3(block->pos.x, block->pos.y + TEXTURE_BLOCK1_SIZE_Y, block->pos.z);
	//(block + 3)->g_vertexWkBlock[3].vtx = D3DXVECTOR3(block->pos.x + TEXTURE_BLOCK1_SIZE_X, block->pos.y + TEXTURE_BLOCK1_SIZE_Y, block->pos.z);

}


BLOCK *GetBlockAdr(int pno)
{
	return &block[pno];
}
