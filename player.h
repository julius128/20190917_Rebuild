//=============================================================================
//
// �v���C���[���� [Player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_


// �}�N����`
#define TEXTURE_GAME_SAMPLE00	_T("data/TEXTURE/runningman003.png")	// �T���v���p�摜


#define TEXTURE_PLAYER_SIZE_X	(100)	// �e�N�X�`���T�C�Y
#define TEXTURE_PLAYER_SIZE_Y	(200)	// 

#define TEXTURE_PATTERN_DIVIDE_X	(5)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			(TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define XY_SPEED					(10.0f) //�d�͂̑���

#define	RADIUS_MIN				(50.0f)							// �|���S���̔��a�ŏ��l
#define	RADIUS_MAX				(300.0f)						// �|���S���̔��a�ő�l
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// �|���S���̉�]��
#define	VALUE_SCALE				(2.0f)							// �|���S���̃X�P�[���ω���
#define PLAYER_MAX				(1)			// �v���C���[�̐�




typedef struct
{
	int x;
	int y;
	int z;

}XYZ;




typedef struct
{
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	int						CountAnim;
	int						PatternAnim;

	int						HP;
	bool					posX;	//����
	bool					jump;	//�W�����v����
	bool					use;	//�����Ă��邩
	bool					floor;  //���̏�
	int						direction;	
	D3DXVECTOR3				Npos;

	VERTEX_2D				g_vertexWkPlayer[NUM_VERTEX];		// ���_���i�[���[�N



}PLAYER;







//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
XYZ *GetXyzAdr(int pno);	// �G�̃A�h���X���擾
PLAYER *GetPlayerAdr(int pno);










#endif
