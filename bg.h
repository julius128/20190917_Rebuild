//=============================================================================
//
// �w�i���� [bg.h]
// Author : 
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

// �}�N����`
#define TEXTURE_GAME_BG00		_T("data/TEXTURE/map.png")	// �T���v���p�摜

#define BG00_SIZE_X			(12800)	// �e�N�X�`���T�C�Y
#define BG00_SIZE_Y			(800)	// ����
#define BG00_POS_X			(0)		// �|���S���̏����ʒuX(����)
#define BG00_POS_Y			(0)		// ����
#define BG_MAX				(1)

typedef struct
{
	D3DXVECTOR3				g_posBG;					// �w�i�̈ʒu
	bool					dead_end;
}BG;

typedef struct
{
	int x;
	int y;
	int z;

}QWE;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBG(int type);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);
BG *GetBGAdr(int pno);
QWE *GetQweAdr(int pno);


#endif
