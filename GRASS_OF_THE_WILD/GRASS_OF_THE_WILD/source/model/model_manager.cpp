//=============================================================================
//
// [manager.h]
// Author : shota fukuoka
//
//=============================================================================
#include "model_manager.h"
#include "model.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//追加
void ModelManager::AddSkinMeshModel(SkinMeshModel* model)
{
	m_SkinMeshList.push_back(model);
}

//モデルデータ探索
Model *ModelManager::SeekSkinMeshModel(SkinMeshModel* model)
{
	for (auto ite = m_SkinMeshList.begin(); ite != m_SkinMeshList.end(); ++ite)
	{
		if ((*ite)->GetFileName() == model->GetFileName())
		{
			return dynamic_cast<SkinMeshModel*>(*ite);
		}
	}
	AddSkinMeshModel(model);
	return  model;
}