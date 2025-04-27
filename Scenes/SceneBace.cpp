/**
 * @file   SceneBace.cpp
 *
 * @brief  シーンの基底クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#include "SceneBace.h"

#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pSceneManager">シーンマネージャへのポインタ</param>
/// <param name="pResourceManager">リソースマネージャへのポインタ</param>
/// <param name="pControllerManager">コントローラマネージャへのポインタ</param>
SceneBace::SceneBace(Position2D cameraPosition)
	: p_wsi              { &WSI::GetInstance()}
	, p_SceneManager     { &SceneManager::GetInstance()}
{
	m_camera = Camera(cameraPosition, p_wsi->ScreenRight(), p_wsi->ScreenBottom());
}

Camera& SceneBace::GetCamera()
{
	return m_camera;
}

/// <summary>
/// シーンの変更
/// </summary>
/// <param name="nextSceneName">変更先のシーン名</param>
void SceneBace::ChangeScene(const std::string& nextSceneName)
{
	p_SceneManager->RequestSceneChange(nextSceneName);
}
