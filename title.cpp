//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTitle(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTitle = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleStart = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleOut = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pD3DTextureTitleSelect = NULL;	// �e�N�X�`���ւ̃|�C���^

VERTEX_2D				g_vertexWkTitle[NUM_VERTEX];			// ���_���i�[���[�N
VERTEX_2D				g_vertexWkTitleStart[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_vertexWkTitleOut[NUM_VERTEX];		// ���_���i�[���[�N
VERTEX_2D				g_vertexWkTitleSelect[NUM_VERTEX];		// ���_���i�[���[�N


static float move;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE,				// �t�@�C���̖��O
		&g_pD3DTextureTitle);		// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE_START,			// �t�@�C���̖��O
		&g_pD3DTextureTitleStart);	// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE_OUT,			// �t�@�C���̖��O
		&g_pD3DTextureTitleOut);	// �ǂݍ��ރ������[

	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TITLE_SELECT,			// �t�@�C���̖��O
		&g_pD3DTextureTitleSelect);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	MakeVertexTitle();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	if (g_pD3DTextureTitle != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTitle->Release();
		g_pD3DTextureTitle = NULL;
	}

	if (g_pD3DTextureTitleStart != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTitleStart->Release();
		g_pD3DTextureTitleStart = NULL;
	}

	if (g_pD3DTextureTitleOut != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTitleOut->Release();
		g_pD3DTextureTitleOut = NULL;
	}

	if (g_pD3DTextureTitleSelect != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTitleSelect->Release();
		g_pD3DTextureTitleSelect = NULL;
	}

}

//=============================================================================
// �X�V����
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
		{// Enter��������A�X�e�[�W��؂�ւ���
			SetStage(STAGE_GAME);
		}
		// �Q�[���p�b�h�łňړ�����
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
		{// Enter��������A�X�e�[�W��؂�ւ���
			exit(0);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTitle);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitle, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTitleStart);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleStart, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTitleOut);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleOut, sizeof(VERTEX_2D));


	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTitleSelect);

	// �|���S���̕`��
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, g_vertexWkTitleSelect, sizeof(VERTEX_2D));


}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTitle(void)
{

	// ���_���W�̐ݒ�
	g_vertexWkTitle[0].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	g_vertexWkTitle[1].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y, 0.0f);
	g_vertexWkTitle[2].vtx = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);
	g_vertexWkTitle[3].vtx = D3DXVECTOR3(TITLE_POS_X + TITLE_SIZE_X, TITLE_POS_Y + TITLE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTitle[0].rhw =
		g_vertexWkTitle[1].rhw =
		g_vertexWkTitle[2].rhw =
		g_vertexWkTitle[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTitle[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitle[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTitle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitle[3].tex = D3DXVECTOR2(1.0f, 1.0f);



	// ���_���W�̐ݒ�
	g_vertexWkTitleStart[0].vtx = D3DXVECTOR3(TITLESTART_POS_X, TITLESTART_POS_Y, 0.0f);
	g_vertexWkTitleStart[1].vtx = D3DXVECTOR3(TITLESTART_POS_X + TITLESTART_SIZE_X, TITLESTART_POS_Y, 0.0f);
	g_vertexWkTitleStart[2].vtx = D3DXVECTOR3(TITLESTART_POS_X, TITLESTART_POS_Y + TITLESTART_SIZE_Y, 0.0f);
	g_vertexWkTitleStart[3].vtx = D3DXVECTOR3(TITLESTART_POS_X + TITLESTART_SIZE_X, TITLESTART_POS_Y + TITLESTART_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTitleStart[0].rhw =
		g_vertexWkTitleStart[1].rhw =
		g_vertexWkTitleStart[2].rhw =
		g_vertexWkTitleStart[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTitleStart[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleStart[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleStart[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleStart[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTitleStart[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleStart[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleStart[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleStart[3].tex = D3DXVECTOR2(1.0f, 1.0f);



	// ���_���W�̐ݒ�
	g_vertexWkTitleOut[0].vtx = D3DXVECTOR3(TITLEOUT_POS_X, TITLEOUT_POS_Y, 0.0f);
	g_vertexWkTitleOut[1].vtx = D3DXVECTOR3(TITLEOUT_POS_X + TITLEOUT_SIZE_X, TITLEOUT_POS_Y, 0.0f);
	g_vertexWkTitleOut[2].vtx = D3DXVECTOR3(TITLEOUT_POS_X, TITLEOUT_POS_Y + TITLEOUT_SIZE_Y, 0.0f);
	g_vertexWkTitleOut[3].vtx = D3DXVECTOR3(TITLEOUT_POS_X + TITLEOUT_SIZE_X, TITLEOUT_POS_Y + TITLEOUT_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTitleOut[0].rhw =
		g_vertexWkTitleOut[1].rhw =
		g_vertexWkTitleOut[2].rhw =
		g_vertexWkTitleOut[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTitleOut[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleOut[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleOut[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleOut[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTitleOut[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleOut[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleOut[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleOut[3].tex = D3DXVECTOR2(1.0f, 1.0f);



	// ���_���W�̐ݒ�
	g_vertexWkTitleSelect[0].vtx = D3DXVECTOR3(TITLESELECT_POS_X , TITLESELECT_POS_Y , 0.0f);
	g_vertexWkTitleSelect[1].vtx = D3DXVECTOR3(TITLESELECT_POS_X + TITLESELECT_SIZE_X , TITLESELECT_POS_Y, 0.0f);
	g_vertexWkTitleSelect[2].vtx = D3DXVECTOR3(TITLESELECT_POS_X , TITLESELECT_POS_Y+ TITLESELECT_SIZE_Y, 0.0f);
	g_vertexWkTitleSelect[3].vtx = D3DXVECTOR3(TITLESELECT_POS_X + TITLESELECT_SIZE_X, TITLESELECT_POS_Y + TITLESELECT_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	g_vertexWkTitleSelect[0].rhw =
		g_vertexWkTitleSelect[1].rhw =
		g_vertexWkTitleSelect[2].rhw =
		g_vertexWkTitleSelect[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	g_vertexWkTitleSelect[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleSelect[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleSelect[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	g_vertexWkTitleSelect[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	g_vertexWkTitleSelect[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	g_vertexWkTitleSelect[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	g_vertexWkTitleSelect[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	g_vertexWkTitleSelect[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	return S_OK;
}

