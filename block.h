//=============================================================================
//
// �v���C���[���� [Block.h]
// Author : 
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_


// �}�N����`
#define TEXTURE_BLOCK_SIZE_X	(1150)	// �e�N�X�`���T�C�Y
#define TEXTURE_BLOCK_SIZE_Y	(200)	// 

#define TEXTURE_BLOCK1_SIZE_X	(128)	// forest_pack_15
#define TEXTURE_BLOCK1_SIZE_Y	(64)	// 

#define TEXTURE_BLOCK2_SIZE_X	(360)	// 
#define TEXTURE_BLOCK2_SIZE_Y	(3000)	// 

#define TEXTURE_BLOCK3_SIZE_X	(256)	// 
#define TEXTURE_BLOCK3_SIZE_Y	(100)	// 

#define TEXTURE_BLOCK4_SIZE_X	(384)	// 
#define TEXTURE_BLOCK4_SIZE_Y	(64)	// 

#define TEXTURE_BLOCK5_SIZE_X	(620)	// 
#define TEXTURE_BLOCK5_SIZE_Y	(3000)	// 

#define TEXTURE_BLOCK6_SIZE_X	(128)	// 
#define TEXTURE_BLOCK6_SIZE_Y	(3000)	// 

#define TEXTURE_BLOCK7_SIZE_X	(128)	// 
#define TEXTURE_BLOCK7_SIZE_Y	(200)	// 

#define TEXTURE_BLOCK8_SIZE_X	(500)	// 
#define TEXTURE_BLOCK8_SIZE_Y	(3000)	// 


#define	RADIUS_MIN				(50.0f)							// �|���S���̔��a�ŏ��l
#define	RADIUS_MAX				(300.0f)						// �|���S���̔��a�ő�l
#define	VALUE_ROTATION			(D3DX_PI * 0.01f)				// �|���S���̉�]��
#define	VALUE_SCALE				(2.0f)							// �|���S���̃X�P�[���ω���
#define BLOCK_MAX				(1)			// �v���C���[�̐�

typedef struct
{
	D3DXVECTOR3				pos;
	D3DXVECTOR3				rot;
	int						CountAnim;
	int						PatternAnim;

	VERTEX_2D				g_vertexWkBlock[NUM_VERTEX];		// ���_���i�[���[�N


	int						HP;
	bool					use ;


}BLOCK;




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
BLOCK *GetBlockAdr(int pno);





#endif
