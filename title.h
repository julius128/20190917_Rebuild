//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : 
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TITLE		_T("data/TEXTURE/title.png")			// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TITLE_START	_T("data/TEXTURE/start.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TITLE_OUT	_T("data/TEXTURE/out.png")		// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_TITLE_SELECT	_T("data/TEXTURE/select.png")		// �ǂݍ��ރe�N�X�`���t�@�C����

#define	TITLE_POS_X				(0)								// �^�C�g���̕\���ʒu
#define	TITLE_POS_Y				(0)								// �^�C�g���̕\���ʒu
#define	TITLE_SIZE_X			(1280)							// �^�C�g���̕�
#define	TITLE_SIZE_Y			(800)							// �^�C�g���̍���

#define	TITLESTART_POS_X		(800)							// �^�C�g�����S�̕\���ʒu
#define	TITLESTART_POS_Y		(630)							// �^�C�g�����S�̕\���ʒu
#define	TITLESTART_SIZE_X		(420)							// �^�C�g�����S�̕�
#define	TITLESTART_SIZE_Y		(70)							// �^�C�g�����S�̍���

#define	TITLEOUT_POS_X			(800)							// �^�C�g�����S�̕\���ʒu
#define	TITLEOUT_POS_Y			(710)							// �^�C�g�����S�̕\���ʒu
#define	TITLEOUT_SIZE_X			(420)							// �^�C�g�����S�̕�
#define	TITLEOUT_SIZE_Y			(70)							// �^�C�g�����S�̍���

#define	TITLESELECT_POS_X		(700)							// �^�C�g�����S�̕\���ʒu
#define	TITLESELECT_POS_Y		(620)							// �^�C�g�����S�̕\���ʒu
#define	TITLESELECT_SIZE_X		(80)							// �^�C�g�����S�̕�
#define	TITLESELECT_SIZE_Y		(80)							// �^�C�g�����S�̍���


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif
