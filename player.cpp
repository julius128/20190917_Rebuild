//=============================================================================
//
// �v���C���[���� [Player.cpp]
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
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexPlayer(void);
void SetTexturePlayer(int cntPattern);	// 
void SetVertexPlayer(void);					// ���_�̌v�Z����


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^

float					g_fRadiusPlayer;					// �|���S���̔��a
float					g_fBaseAnglePlayer;					// �|���S���̊p�x
PLAYER					player[PLAYER_MAX];
static int				i = 0;

XYZ						abc[1];

//=============================================================================
// ����������
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

	//�摜�̏�����
	player->g_vertexWkPlayer[0].vtx = D3DXVECTOR3(player->pos.x, player->pos.y, player->pos.z);
	player->g_vertexWkPlayer[1].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y, player->pos.z);
	player->g_vertexWkPlayer[2].vtx = D3DXVECTOR3(player->pos.x, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);
	player->g_vertexWkPlayer[3].vtx = D3DXVECTOR3(player->pos.x + TEXTURE_PLAYER_SIZE_X, player->pos.y + TEXTURE_PLAYER_SIZE_Y, player->pos.z);
	player->posX = true;
	player->Npos = player->pos;

	player->CountAnim = 0;
	player->PatternAnim = 0;

	// ���_���̍쐬
	MakeVertexPlayer();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_GAME_SAMPLE00,				// �t�@�C���̖��O
		&g_pD3DTexture);					// �ǂݍ��ރ������̃|�C���^

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
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
void UpdatePlayer(void)
{
	ENEMY *enemy = GetEnemyAdr(0);
	BULLET *bullet = GetBulletAdr(0);
	BG *bg = GetBGAdr(0);

	abc->x = (int)player->pos.x;
	abc->y = (int)player->pos.y;
	abc->z = (int)player->pos.z;

	// �A�j���[�V����
	player->CountAnim++;

	// �A�j���[�V����Wait�`�F�b�N
	SetVertexPlayer();	// ���_�̌v�Z����

	//�d��
	player->pos.y += 1.5 * XY_SPEED;

	//�W�����v�̃R�[�h
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
			// �p�^�[���̐؂�ւ�
			player->PatternAnim = (player->PatternAnim + 1) % ANIM_PATTERN_NUM;

			// �e�N�X�`�����W��ݒ�
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
			// �p�^�[���̐؂�ւ�
			player->PatternAnim = (player->PatternAnim + 1) % ANIM_PATTERN_NUM;

			// �e�N�X�`�����W��ݒ�
			SetTexturePlayer(player->PatternAnim);
		}
		if (bg->g_posBG.x < 0.0f)
		{
			bg->g_posBG.x += 4.0f;
			player->pos.x = 640.0f;
		}

	}




	/*	�ǂ𒴂��Ȃ�	*/
	//if (player->pos.x > SCREEN_WIDTH - 100.0f) //�E
	//{
	//	player->pos.x -= 4.0f;
	//}
	if (player->pos.x < 0.0f)  //��
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


	/*NPC��������Ȃ�*/
	// �l��NPC(BC)
	enemy = &enemy[0];					// �G�l�~�[�̃|�C���^�[��������


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


	//��Q���̓����蔻��
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
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTexture);

	if (player->use == true)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, player->g_vertexWkPlayer, sizeof(VERTEX_2D));
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���W�̐ݒ�	
	SetVertexPlayer();	// ���_�̌v�Z����

	// rhw�̐ݒ�
	player->g_vertexWkPlayer[0].rhw =
		player->g_vertexWkPlayer[1].rhw =
		player->g_vertexWkPlayer[2].rhw =
		player->g_vertexWkPlayer[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	player->g_vertexWkPlayer[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->g_vertexWkPlayer[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->g_vertexWkPlayer[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	player->g_vertexWkPlayer[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	SetTexturePlayer(player->PatternAnim);

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTexturePlayer(int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
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
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexPlayer(void)
{
	// ���_���W�̐ݒ�


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

