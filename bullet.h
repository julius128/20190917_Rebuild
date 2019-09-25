//=============================================================================
//
// �v���C���[���� [Bullet.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_


// �}�N����`
#define TEXTURE_GAME_SAMPLE01	_T("data/TEXTURE/image 806.png")	// �T���v���p�摜


#define TEXTURE_BULLET_SIZE_X	(50)	// �e�N�X�`���T�C�Y
#define TEXTURE_BULLET_SIZE_Y	(20)	// 

#define TEXTURE_PATTERN_DIVIDE_X_BULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BULLET	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BULLET			(TEXTURE_PATTERN_DIVIDE_X_BULLET*TEXTURE_PATTERN_DIVIDE_Y_BULLET)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BULLET				(1)	// �A�j���[�V�����̐؂�ւ��J�E���g


#define	RADIUS_MIN				(50.0f)							// �|���S���̔��a�ŏ��l
#define	RADIUS_MAX				(300.0f)						// �|���S���̔��a�ő�l
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// �|���S���̉�]��
#define	VALUE_SCALE				(2.0f)							// �|���S���̃X�P�[���ω���
#define BULLET_MAX				(20)			// �v���C���[�̐�



typedef struct
{
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	int						CountAnim;
	int						PatternAnim;
	bool					use;			//�g�p���f
	bool					direction;		//�e�ە���
	VERTEX_2D				g_vertexWk[NUM_VERTEX];		// ���_���i�[���[�N
	int						Texture;

}BULLET;







//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
BULLET *GetBulletAdr(int pno);
//void SetBullet(D3DXVECTOR3 pos); //�g�p���Ȃ�










#endif
