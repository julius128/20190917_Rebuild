//=============================================================================
//
// �v���C���[���� [Enemy.h]
// Author : 
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_


// �}�N����`
#define TEXTURE_GAME_SAMPLE00	_T("data/TEXTURE/runningman003.png")	// �T���v���p�摜
#define TEXTURE_ENEMY_SIZE_X	(100)	// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMY_SIZE_Y	(200)	// 

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMY		(TEXTURE_PATTERN_DIVIDE_X_ENEMY*TEXTURE_PATTERN_DIVIDE_Y_ENEMY)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMY			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g


#define	RADIUS_MIN				(50.0f)							// �|���S���̔��a�ŏ��l
#define	RADIUS_MAX				(300.0f)						// �|���S���̔��a�ő�l
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// �|���S���̉�]��
#define	VALUE_SCALE				(2.0f)							// �|���S���̃X�P�[���ω���
#define ENEMY_MAX				(2)			// �v���C���[�̐�

typedef struct
{
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	int						CountAnim;
	int						PatternAnim;

	VERTEX_2D				g_vertexWkEnemy[NUM_VERTEX];		// ���_���i�[���[�N


	int						HP;
	bool					use ;


}ENEMY;




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
ENEMY *GetEnemyAdr(int pno);





#endif
