//=============================================================================
//
// app.h
// Author : SHOTA FUKUOKA
//
//=============================================================================
#ifndef _APP_H_
#define _APP_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <Windows.h>
#include <assert.h>
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)		// �E�C���h�E�̍���

//���S�ɉ������
#define SAFE_RELEASE(x) if(x){x->Release(); x=NULL;}

//*****************************************************************************
// �O���錾
//*****************************************************************************
class AppRenderer;
class MainCamera;
class LightCamera;
class TextureManager;
class RenderManager;
class ShaderManager;
class MeshManager;
class CanvasManager;
class InputKeyboard;
class ModelManager;
class Player;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class App
{
public:
	//�R���X�g���N�^
	App();

	//�f�X�g���N�^
	virtual ~App();

	//������
	HRESULT Init(const HWND hWnd, HINSTANCE hInstance);

	//�I��
	void Release(void);

	//�X�V
	void Update(void);

	//�`��
	void Draw(void);

private:
	AppRenderer*					m_pAppRenderer;

	MainCamera*						m_pCamera;

	LightCamera*					m_pLightCamera;

	TextureManager*					m_pTextureManager;

	ShaderManager*					m_pShaderManager;

	RenderManager*					m_pRenderManager;

	MeshManager*					m_pMeshManager;

	CanvasManager*					m_pCanvasManager;

	InputKeyboard*					m_pInputKeybord;

	ModelManager*					m_pModelManager;

	Player*							m_pPlayer;
};

#endif