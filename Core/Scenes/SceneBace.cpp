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
#include "../Manager/ControllerManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pSceneManager">シーンマネージャへのポインタ</param>
/// <param name="pResourceManager">リソースマネージャへのポインタ</param>
/// <param name="pControllerManager">コントローラマネージャへのポインタ</param>
SceneBace::SceneBace(WSI* pWSI, SceneManager* pSceneManager, ControllerManager* pControllerManager, Position2D cameraPosition)
	: mp_wsi              { pWSI }
	, mp_SceneManager     { pSceneManager }
	, mp_ControllerManager{ pControllerManager }
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

/// <summary>
/// 共有データの読み込み
/// </summary>
/// <param name="key">共有データキー</param>
/// <param name="pValue">読み込み先</param>
void SceneBace::ReadSharedData(const std::string& key, int* pValue) const
{
	*pValue = std::stoi(mp_SceneManager->GetShareData(key));
}

void SceneBace::ReadSharedData(const std::string& key, float* pValue) const
{
	*pValue = std::stof(mp_SceneManager->GetShareData(key));
}

void SceneBace::ReadSharedData(const std::string& key, std::string* pValue) const
{
	*pValue = mp_SceneManager->GetShareData(key);
}

/// <summary>
/// 共有データへの書き込み
/// </summary>
void SceneBace::WriteSharedData(const std::string& key, int value)
{
	mp_SceneManager->SetSharedData(key, std::to_string(value));
}

void SceneBace::WriteSharedData(const std::string& key, float value)
{
	mp_SceneManager->SetSharedData(key, std::to_string(value));
}

void SceneBace::WriteSharedData(const std::string& key, std::string value)
{
	mp_SceneManager->SetSharedData(key, value);
}
