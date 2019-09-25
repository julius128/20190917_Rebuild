//=============================================================================
//
// �v���C���[���� [Enemy.cpp]
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
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy(void);

void SetTextureEnemy(int cntPattern, int no);	// 
void SetVertexEnemy(void);					// ���_�̌v�Z����


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^

//static VERTEX_2D				g_vertexWk[NUM_VERTEX];		// ���_���i�[���[�N


//D3DXVECTOR3				g_posEnemy;						// �|���S���̍��W
//D3DXVECTOR3				g_rotEnemy;						// �|���S���̉�]��
//int						g_nCountAnim_Enemy;				// �A�j���[�V�����J�E���g
//int						g_nPatternAnim_Enemy;			// �A�j���[�V�����p�^�[���i���o�[

float					g_fRadiusEnemy;					// �|���S���̔��a
float					g_fBaseAngleEnemy;				// �|���S���̊p�x

static int 				i;

int						p = 0;

ENEMY					enemy[ENEMY_MAX];


//=============================================================================
// ����������
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




	// ���_���̍쐬
	MakeVertexEnemy();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_GAME_SAMPLE00,				// �t�@�C���̖��O
		&g_pD3DTexture);					// �ǂݍ��ރ������̃|�C���^

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
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
void UpdateEnemy(void)
{
	PLAYER *player = GetPlayerAdr(0);
	BULLET *bullet = GetBulletAdr(0);
	SCORE *score = GetScoreAdr(0);
	ENEMY *enemy = GetEnemyAdr(0);

	SetVertexEnemy();	// ���_�̌v�Z����

	for (i = 0, enemy = &enemy[0], bullet = &bullet[0]; i < 2; i++, enemy++, bullet++)
	{

		/*�S���G�̓v���C���[��T��*/
		if (enemy->use == true)
		{
			// �A�j���[�V����
			enemy->CountAnim++;
			// �A�j���[�V����Wait�`�F�b�N
			if ((enemy->CountAnim % TIME_ANIMATION_ENEMY) == 0)
			{
				// �p�^�[���̐؂�ւ�
				enemy->PatternAnim = (enemy->PatternAnim + 1) % ANIM_PATTERN_NUM_ENEMY;

				// �e�N�X�`�����W��ݒ�
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



		/*�G�ƃv���B���̓����蔻��*/
		if ((enemy->pos.x + TEXTURE_ENEMY_SIZE_X) >= player->pos.x && (enemy->pos.x + TEXTURE_ENEMY_SIZE_X) <= player->pos.x + TEXTURE_PLAYER_SIZE_X
			&& (enemy->pos.y + TEXTURE_ENEMY_SIZE_Y) >= player->pos.y && (enemy->pos.y + TEXTURE_ENEMY_SIZE_Y) <= player->pos.y + TEXTURE_PLAYER_SIZE_Y
			|| (enemy->pos.x >= player->pos.x && enemy->pos.x <= player->pos.x + TEXTURE_PLAYER_SIZE_X
				&& enemy->pos.y >= player->pos.y && enemy->pos.y <= player->pos.y + TEXTURE_PLAYER_SIZE_Y))
		{
			player->HP -= 1;
		}

		/*�G�ƒe�ۂ̓����蔻��*/
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

		/*�G�g�o����*/
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
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = GetEnemyAdr(0);



	for (i = 0, enemy = &enemy[0]; i < ENEMY_MAX; i++, enemy++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexture);

		// �|���S���̕`��
		if (enemy->use == true)
		{
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, enemy->g_vertexWkEnemy, sizeof(VERTEX_2D));
		}

	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ENEMY *enemy = GetEnemyAdr(0);
	// ���_���W�̐ݒ�	
	SetVertexEnemy();	// ���_�̌v�Z����

	for (i = 0, enemy = &enemy[0]; i < ENEMY_MAX; i++, enemy++)
	{
		// rhw�̐ݒ�
		enemy->g_vertexWkEnemy[0].rhw =
			enemy->g_vertexWkEnemy[1].rhw =
			enemy->g_vertexWkEnemy[2].rhw =
			enemy->g_vertexWkEnemy[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		enemy->g_vertexWkEnemy[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		enemy->g_vertexWkEnemy[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		enemy->g_vertexWkEnemy[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		enemy->g_vertexWkEnemy[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	}
	for (i = 0, enemy = &enemy[0]; i < ENEMY_MAX; i++, enemy++)
	{
		// �e�N�X�`�����W�̐ݒ�
		SetTextureEnemy(enemy->PatternAnim,i);

	}
	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy(int cntPattern, int no)
{
	ENEMY *enemy = GetEnemyAdr(0);
	enemy = &enemy[no];

	if (enemy->use == true)
	{
		// �e�N�X�`�����W�̐ݒ�
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
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEnemy(void)
{
	ENEMY *enemy = GetEnemyAdr(0);

	for (i = 0, enemy = &enemy[0]; i < ENEMY_MAX; i++, enemy++)
	{

		// ���_���W�̐ݒ�
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
