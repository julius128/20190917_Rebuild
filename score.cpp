//=============================================================================
//
// �v���C���[���� [Score.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "score.h"
#include "player.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexScore(void);
void SetTextureScore(int cntPattern , int i);	// 
void SetVertexScore(void);					// ���_�̌v�Z����


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTexture = NULL;		// �e�N�X�`���ւ̃|�C���^



//D3DXVECTOR3				g_posScore;						// �|���S���̍��W
//D3DXVECTOR3				g_rotScore;						// �|���S���̉�]��
//int						g_nCountAnim;						// �A�j���[�V�����J�E���g
//int						g_nPatternAnim;						// �A�j���[�V�����p�^�[���i���o�[

float					g_fRadiusScore;					// �|���S���̔��a
float					g_fBaseAngleScore;					// �|���S���̊p�x

static int 				i;

SCORE					score[SCORE_MAX];


//=============================================================================
// ����������
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


	// ���_���̍쐬
	MakeVertexScore();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_GAME_SAMPLE02,				// �t�@�C���̖��O
		&g_pD3DTexture);					// �ǂݍ��ރ������̃|�C���^








	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
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
void UpdateScore(void)
{
	SCORE *score = GetScoreAdr(0);


	// �A�j���[�V����



	// �A�j���[�V����Wait�`�F�b�N
	SetVertexScore();	// ���_�̌v�Z����

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
// �`�揈��
//=============================================================================
void DrawScore(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SCORE *score = GetScoreAdr(0);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTexture);

	for (i = 0, score = &score[0]; i < SCORE_MAX; i++, score++)
	{

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_SCORE, score->g_vertexWk, sizeof(VERTEX_2D));


	}
}

//=============================================================================
// ���_�̍쐬 ���ӁF���̊֐��͏z�̒��ɂ��Ȃ�
//=============================================================================
HRESULT MakeVertexScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SCORE *score = GetScoreAdr(0);

	// ���_���W�̐ݒ�	
	SetVertexScore();	// ���_�̌v�Z����

	// rhw�̐ݒ�
	for (i = 0, score = &score[0]; i < SCORE_MAX; i++ , score++)
	{
		score->g_vertexWk[0].rhw =
			score->g_vertexWk[1].rhw =
			score->g_vertexWk[2].rhw =
			score->g_vertexWk[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		score->g_vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		score->g_vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		score->g_vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		score->g_vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	for (i = 0, score = &score[0]; i < SCORE_MAX; i++, score++)
	{
		// �e�N�X�`�����W�̐ݒ�
		SetTextureScore(score->PatternAnim, i);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureScore(int cntPattern , int i)
{
	SCORE *score = GetScoreAdr(0);
	score = &score[i];


	// �e�N�X�`�����W�̐ݒ�
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
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexScore(void)
{
	SCORE *score = GetScoreAdr(0);

	for (i = 0, score = &score[0]; i < SCORE_MAX; i++, score++)
	{
		// ���_���W�̐ݒ�
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



