//=============================================================================
//
// �v���C���[���� [Bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "bullet.h"
#include "player.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBullet(void);
void SetTextureBullet(int cntPattern);	// 
void SetVertexBullet(void);					// ���_�̌v�Z����


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^



//D3DXVECTOR3				g_posBullet;						// �|���S���̍��W
//D3DXVECTOR3				g_rotBullet;						// �|���S���̉�]��
//int						g_nCountAnim;						// �A�j���[�V�����J�E���g
//int						g_nPatternAnim;						// �A�j���[�V�����p�^�[���i���o�[

float					g_fRadiusBullet;					// �|���S���̔��a
float					g_fBaseAngleBullet;					// �|���S���̊p�x

static int 				i;


BULLET					bullet[BULLET_MAX];


//=============================================================================
// ����������
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

	// ���_���̍쐬
	MakeVertexBullet();



	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_GAME_SAMPLE01,				// �t�@�C���̖��O
		&g_pD3DTexture);					// �ǂݍ��ރ������̃|�C���^








	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
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
void UpdateBullet(void)
{
	PLAYER *player = GetPlayerAdr(0);
	BULLET *bullet = GetBulletAdr(0);

	SetVertexBullet();	// ���_�̌v�Z����


	// �A�j���[�V����

	for (i = 0, bullet = &bullet[0]; i < BULLET_MAX; i++, bullet++)
	{


		bullet->CountAnim++;

		// �A�j���[�V����Wait�`�F�b�N



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
		// �e����
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

		/*�e�ێg�p*/
		if (bullet->use == false && GetKeyboardTrigger(DIK_C))		//�g�p���Ȃ������f����
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




		/*	�ǂ��z��������	*/
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
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	BULLET *bullet = GetBulletAdr(0);

	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	for (i = 0, bullet = &bullet[0]; i < BULLET_MAX; i++, bullet++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexture);


		if (bullet->use == true)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BULLET, bullet->g_vertexWk, sizeof(VERTEX_2D));
		}

	}
}

//=============================================================================
// ���_�̍쐬 ���ӁF���̊֐��͏z�̒��ɂ��Ȃ�
//=============================================================================
HRESULT MakeVertexBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *bullet = GetBulletAdr(0);

	// ���_���W�̐ݒ�	
	SetVertexBullet();	// ���_�̌v�Z����


	for (i = 0, bullet = &bullet[0]; i < BULLET_MAX; i++, bullet++)
	{


		// rhw�̐ݒ�
		bullet->g_vertexWk[0].rhw =
			bullet->g_vertexWk[1].rhw =
			bullet->g_vertexWk[2].rhw =
			bullet->g_vertexWk[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		bullet->g_vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		bullet->g_vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		bullet->g_vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		bullet->g_vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);


	}

	for (i = 0, bullet = &bullet[0]; i < BULLET_MAX; i++, bullet++)
	{
		// �e�N�X�`�����W�̐ݒ�
		SetTextureBullet(bullet->PatternAnim);

	}
	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBullet(int cntPattern)
{
	BULLET *bullet = GetBulletAdr(0);


	for (i = 0, bullet = &bullet[0]; i < BULLET_MAX; i++, bullet++)
	{
		// �e�N�X�`�����W�̐ݒ�
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
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexBullet(void)
{
	BULLET *bullet = GetBulletAdr(0);

	for (i = 0, bullet = &bullet[0]; i < BULLET_MAX; i++, bullet++)
	{

		// ���_���W�̐ݒ�
		bullet->g_vertexWk[0].vtx = D3DXVECTOR3(bullet->pos.x, bullet->pos.y, bullet->pos.z);
		bullet->g_vertexWk[1].vtx = D3DXVECTOR3(bullet->pos.x + TEXTURE_BULLET_SIZE_X, bullet->pos.y, bullet->pos.z);
		bullet->g_vertexWk[2].vtx = D3DXVECTOR3(bullet->pos.x, bullet->pos.y + TEXTURE_BULLET_SIZE_Y, bullet->pos.z);
		bullet->g_vertexWk[3].vtx = D3DXVECTOR3(bullet->pos.x + TEXTURE_BULLET_SIZE_X, bullet->pos.y + TEXTURE_BULLET_SIZE_Y, bullet->pos.z);

	}
}

//void SetBullet(D3DXVECTOR3 pos)		//�l�g�p���Ȃ�
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

