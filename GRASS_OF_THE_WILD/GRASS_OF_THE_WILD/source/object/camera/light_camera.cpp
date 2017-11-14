//=============================================================================
//
// camera.cpp
// Author : shota fukuoka
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "light_camera.h"
#include "../../../source/app/app.h"
#include "../../device/input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

///////////////////////////////////////////////////////////////////////////////
// コンストラクタ
///////////////////////////////////////////////////////////////////////////////
LightCamera::LightCamera(VECTOR3 position, VECTOR3 positionAt, VECTOR3 vectorUp)
{
	m_pTransform->position = position;

	m_positionAt = positionAt;

	m_vectorUp = vectorUp;

	m_ner = 14000;

	m_for = 10000;
}

///////////////////////////////////////////////////////////////////////////////
// デストラクタ
///////////////////////////////////////////////////////////////////////////////
LightCamera::~LightCamera()
{
	;
}

///////////////////////////////////////////////////////////////////////////////
// 初期化
///////////////////////////////////////////////////////////////////////////////
HRESULT LightCamera::Init(void )
{
	Camera::Init();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// 終了
///////////////////////////////////////////////////////////////////////////////
void LightCamera::Release(void)
{
	Camera::Release();
}

///////////////////////////////////////////////////////////////////////////////
// 更新
///////////////////////////////////////////////////////////////////////////////
void LightCamera::Update(void)
{
	InputKeyboard* pInputKeyboard = InputKeyboard::GetInstance();

	if (pInputKeyboard->GetKeyPress(DIK_1))
	{
		m_ner++;
	}

	if (pInputKeyboard->GetKeyPress(DIK_2))
	{
		m_ner--;
	}

	if (pInputKeyboard->GetKeyPress(DIK_3))
	{
		m_for+= 100;
	}

	if (pInputKeyboard->GetKeyPress(DIK_4))
	{
		m_for-= 100;
	}

	if (pInputKeyboard->GetKeyPress(DIK_UP))
	{
		m_pTransform->position.y++;
		//m_positionAt.y++;
	}

	if (pInputKeyboard->GetKeyPress(DIK_DOWN))
	{
		m_pTransform->position.y--;
		//m_positionAt.y--;
	}

	Camera::Update();
}

///////////////////////////////////////////////////////////////////////////////
// カメラセット
///////////////////////////////////////////////////////////////////////////////
void LightCamera::SetCamera(void)
{
	XMMATRIX hView = XMMatrixIdentity();
	XMVECTOR hEye = XMVectorSet(m_pTransform->position.x, m_pTransform->position.y, m_pTransform->position.z, 0.0f);	//カメラの位置
	XMVECTOR hAt = XMVectorSet(m_positionAt.x, m_positionAt.y, m_positionAt.z, 0.0f);		//焦点の位置
	XMVECTOR hUp = XMVectorSet(m_vectorUp.x, m_vectorUp.y, m_vectorUp.z, 0.0f);
	hView = XMMatrixLookAtLH(hEye, hAt, hUp);

	XMMATRIX hProjection;	//透視射影変換行列
	hProjection = XMMatrixOrthographicLH(4086, 4086, m_ner, m_for);

	XMVECTOR LightPos = XMVectorSet(m_pTransform->position.x, m_pTransform->position.y, m_pTransform->position.z, 1);
	m_pConstant->light = LightPos;

	m_pConstant->view = hView;
	m_pConstant->projection = hProjection;
}

///////////////////////////////////////////////////////////////////////////////
//定数取得
///////////////////////////////////////////////////////////////////////////////
AppRenderer::Constant* LightCamera::GetConstant(void)
{
	return m_pConstant;
}