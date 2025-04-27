/**
 * @file   SceneBace.cpp
 *
 * @brief  シーンの基底クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/01/12
 */

#include "SceneBace.h"

#include "../../WindowSettingItems.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pSceneManager">シーンマネージャへのポインタ</param>
/// <param name="pResourceManager">リソースマネージャへのポインタ</param>
/// <param name="pControllerManager">コントローラマネージャへのポインタ</param>
SceneBace::SceneBace(WSI* pWSI, SceneManager* pSceneManager,  Position2D cameraPosition)
	: mp_wsi              { pWSI }
	, mp_SceneManager     { pSceneManager }
	, m_camera            { cameraPosition, pWSI->ScreenWidth, pWSI->ScreenHeight }
{
}

/// <summary>
/// シーンの変更
/// </summary>
/// <param name="nextSceneName">変更先のシーン名</param>
void SceneBace::ChangeScene(const std::string& nextSceneName)
{
	mp_SceneManager->RequestSceneChange(nextSceneName);
}
