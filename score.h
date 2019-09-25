//=============================================================================
//
// �v���C���[���� [Score.h]
// Author : 
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_


// �}�N����`
#define TEXTURE_GAME_SAMPLE02	_T("data/TEXTURE/score.png")	// �T���v���p�摜


#define TEXTURE_SCORE_SIZE_X	(17)	// �e�N�X�`���T�C�Y
#define TEXTURE_SCORE_SIZE_Y	(20)	// 

#define TEXTURE_PATTERN_DIVIDE_X_SCORE	(10)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_SCORE	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_SCORE			(TEXTURE_PATTERN_DIVIDE_X_SCORE*TEXTURE_PATTERN_DIVIDE_Y_SCORE)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_SCORE				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g


#define	RADIUS_MIN				(50.0f)							// �|���S���̔��a�ŏ��l
#define	RADIUS_MAX				(300.0f)						// �|���S���̔��a�ő�l
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// �|���S���̉�]��
#define	VALUE_SCALE				(2.0f)							// �|���S���̃X�P�[���ω���
#define SCORE_MAX				(5)			// �v���C���[�̐�



typedef struct
{
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	int						CountAnim;
	int						PatternAnim;
	bool					use;			//�g�p���f
	bool					direction;		//����
	int						yi;
	int						shi;
	int						bai;
	int						qian;
	int						wan;
	int						AddScore;
	int						scoreX;
	int						num;

	VERTEX_2D				g_vertexWk[NUM_VERTEX];		// ���_���i�[���[�N


}SCORE;







//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
SCORE *GetScoreAdr(int pno);
//void SetScore(D3DXVECTOR3 pos); //�g�p���Ȃ�










#endif
