//=============================================================================
//
// title.cpp
// Author : shota fukuoka
//
//=============================================================================
#include "title_scene.h"
#include "game_scene.h"
#include "../object/object.h"
#include "../renderer/renderer.h"
#include "../object/camera/main_camera.h"
#include "../object/camera/light_camera.h"
#include "../shader/shader_manager.h"
#include "../renderer/render_manager.h"
#include "../object/mesh/mesh_manager.h"
#include "../object/mesh/meshfiled/mesh_field.h"
#include "../object/mesh/skybox/skybox.h"
#include "../object/canvas/canvas_manager.h"
#include "../object/canvas/shadow_map/shadow_map.h"
#include "../object/canvas/player_life/player_life.h"
#include "../object/canvas/logo/logo.h"
#include "../model/model_manager.h"
#include "../object/character/player/player.h"
#include "../device/input.h"
#include "../gui/imgui.h"
#include "../gui/imgui_impl_dx11.h"
#include "../object/mesh/grass/grass.h"
#include "../object/character/enemy/enemy_manager.h"
#include "../collision/collision_manager.h"
#include "../scene/next_scene.h"
#include "../scene/scene.h"
#include "../scene/title_scene.h"
#include "../scene/tutorial_scene.h"
#include "../scene/game_scene.h"
#include "../scene/result_scene.h"
#include "../scene/fade_scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

///////////////////////////////////////////////////////////////////////////////
//�R���X�g���N�^
///////////////////////////////////////////////////////////////////////////////
Title::Title()
	: m_pModelManager(NULL)
	, m_pPlayer(NULL)
	, m_pCamera(NULL)
	, m_pLightCamera(NULL)
	, m_pShaderManager(NULL)
	, m_pTextureManager(NULL)
	, m_pRenderManager(NULL)
	, m_pMeshManager(NULL)
	, m_pCanvasManager(NULL)
{
	;
}

///////////////////////////////////////////////////////////////////////////////
// ����������
///////////////////////////////////////////////////////////////////////////////
HRESULT Title::Init(NextScene* pNextScene, Fade* pFade)
{
	m_pFade = pFade;

	m_pLightCamera = new LightCamera(VECTOR3(-3000, 8000, -12000), VECTOR3(0, 0, 0), VECTOR3(0, 1, 0));
	m_pLightCamera->Init();

	m_pTextureManager = new TextureManager();

	new Texture("resource/sprite/toon.png", m_pTextureManager);

	m_pShaderManager = new ShaderManager();
	m_pShaderManager->GenerateShader();

	m_pModelManager = new ModelManager();

	m_pRenderManager = new RenderManager();

	m_pCanvasManager = new CanvasManager();
	m_pCanvasManager->AddCanvas(new ShadowMap(m_pRenderManager, m_pShaderManager, m_pTextureManager));

	m_pMeshManager = new MeshManager();

	m_pCamera = new MainCamera(VECTOR3(0.0f, 100.0f, -500.0f), VECTOR3(0.0f, 0.0f, 0.0f), VECTOR3(0.0f, 1.0f, 0.0f));

	//for (int i = 0; i < 100; i++)
	//{
	//	m_pMeshManager->AddMesh(new Grass(m_pRenderManager, m_pShaderManager, m_pTextureManager, m_pCamera->GetConstant(), m_pLightCamera->GetConstant(), m_pCamera, i));
	//}

	m_pMeshManager->AddMesh(new MeshField(m_pRenderManager, m_pShaderManager, m_pTextureManager, m_pCamera->GetConstant(), m_pLightCamera->GetConstant()));
	m_pMeshManager->AddMesh(new SkyBox(m_pRenderManager, m_pShaderManager, m_pTextureManager, m_pCamera->GetConstant()));

	//m_pPlayer = new Player(m_pRenderManager, m_pShaderManager, m_pTextureManager, m_pModelManager, m_pCamera->GetConstant(), m_pLightCamera->GetConstant(), m_pCamera, NULL);

	m_pCanvasManager->AddCanvas(new Logo(m_pRenderManager, m_pShaderManager, m_pTextureManager));

	m_pCamera->Init(m_pPlayer);

	m_pFade->Init(pNextScene, m_pRenderManager, m_pShaderManager, m_pTextureManager);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// �I������
///////////////////////////////////////////////////////////////////////////////
void Title::Release(void)
{
	if (m_pCamera == NULL) { return; }
	m_pCamera->Release();
	delete[] m_pCamera;
	m_pCamera = NULL;

	if (m_pLightCamera == NULL) { return; }
	m_pLightCamera->Release();
	delete[] m_pCamera;
	m_pLightCamera = NULL;

	if (m_pShaderManager == NULL) { return; }
	m_pShaderManager->ReleaseAll();
	delete m_pShaderManager;
	m_pShaderManager = NULL;

	if (m_pModelManager == NULL) { return; }
	m_pModelManager->ReleaseAll();
	delete m_pModelManager;
	m_pModelManager = NULL;

	if (m_pMeshManager == NULL) { return; }
	m_pMeshManager->ReleaseAll();
	delete m_pMeshManager;
	m_pMeshManager = NULL;

	if (m_pCanvasManager == NULL) { return; }
	m_pCanvasManager->ReleaseAll();
	delete m_pCanvasManager;
	m_pCanvasManager = NULL;

	if (m_pRenderManager == NULL) { return; }
	m_pRenderManager->ReleaseAll();
	delete m_pRenderManager;
	m_pRenderManager = NULL;

	//if (m_pPlayer == NULL) { return; }
	//delete m_pPlayer;
	//m_pPlayer = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// �X�V����
///////////////////////////////////////////////////////////////////////////////
void Title::Update()
{
	InputKeyboard* pInputKeyboard = InputKeyboard::GetInstance();

	if (pInputKeyboard->GetKeyTrigger(DIK_RETURN))
	{
		m_pFade->SetFade(Fade::FADE_OUT, new Game);
		//m_pNextScene->NextSceneUpdate(new Game);
	}

	m_pLightCamera->Update();

	m_pMeshManager->UpdateAll();

	//m_pPlayer->Update();

	m_pCanvasManager->UpdateAll();

}

///////////////////////////////////////////////////////////////////////////////
// �`�揈��
///////////////////////////////////////////////////////////////////////////////
void Title::Draw(void)
{
	m_pLightCamera->SetCamera();

	m_pCamera->SetCamera();

	AppRenderer* pAppRenderer = AppRenderer::GetInstance();
	pAppRenderer->Draw(m_pRenderManager);
}