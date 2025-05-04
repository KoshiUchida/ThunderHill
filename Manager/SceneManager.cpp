/**
 * @file   SceneManaager.cpp
 *
 * @brief  シーンの管理クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2024/05/04
 */

#include "SceneManager.h"

#include "../Scenes/SceneBace.h"
#include "../Common/Error.h"

#include "../Scenes/Title.h"
#include "../Scenes/Gameplay.h"
#include "../Scenes/Logo.h"
#include "../Scenes/Result.h"

std::unique_ptr<SceneManager> SceneManager::s_SceneManager = nullptr;

SceneManager& SceneManager::GetInstance()
{
	if (!s_SceneManager)
	{
		s_SceneManager.reset(new SceneManager());
		s_SceneManager->Clear();
		s_SceneManager->SetScene();
	}

	return *s_SceneManager.get();
}

void SceneManager::Clear()
{
	m_pCurrentScene = nullptr;
	m_pRequestedScene = nullptr;
	m_IsEnd = false;
}

SceneManager::SceneManager() = default;

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
	if (m_pCurrentScene)
		m_pCurrentScene->Finalize();
}

/// <summary>
/// 更新処理
/// </summary>
void SceneManager::Update()
{
	// シーンの変更要求があった場合はシーンの変更を行う
	if (m_pRequestedScene)
	{
		ChangeScene();
	}

	// 現在のシーンを更新
	if (m_pCurrentScene)
	{
		p_ObjectManager->Update();
		m_pCurrentScene->Update();
	}
}

/// <summary>
/// 描画処理
/// </summary>
void SceneManager::Render()
{
	// 現在のシーンを描画
	if (m_pCurrentScene)
	{
		m_pCurrentScene->Render();
		p_ObjectManager->Render(m_pCurrentScene->GetCamera());
	}
}

/// <summary>
/// シーンの登録
/// </summary>
void SceneManager::SetScene()
{
	p_ObjectManager = &ObjectManager::GetInstance();

	m_scenes.emplace("Logo"    , std::make_unique<Logo>());
	m_scenes.emplace("Title"   , std::make_unique<Title>());
	m_scenes.emplace("Gameplay", std::make_unique<Gameplay>());
	m_scenes.emplace("Result"  , std::make_unique<Result>());

	// 開始シーンの設定
#if defined(_DEBUG)
	SetStartScene("Result");
#else
	SetStartScene("Logo");
#endif
}

/// <summary>
/// 開始シーンの設定
/// </summary>
/// <param name="startSceneName">開始シーン名</param>
void SceneManager::SetStartScene(const std::string& startSceneName)
{
	RequestSceneChange(startSceneName);
}

/// <summary>
/// シーン変更の要求
/// </summary>
/// <param name="changeSceneName">変更予定のシーン名</param>
void SceneManager::RequestSceneChange(const std::string& changeSceneName)
{
	if (changeSceneName == "End")
	{
		m_IsEnd = true;
		return;
	}

	if (m_scenes.count(changeSceneName) == 0)
	{
		printError(changeSceneName + "シーンは登録されていません。");
		return;
	}

	m_pRequestedScene = m_scenes[changeSceneName].get();
}

/// <summary>
/// シーンの変更
/// </summary>
void SceneManager::ChangeScene()
{
	if (!m_pRequestedScene)
		return;

	if (m_pCurrentScene)
	{
		p_ObjectManager->Finalize();
		m_pCurrentScene->Finalize();
	}

	if (m_IsEnd)
		return;

	m_pCurrentScene = m_pRequestedScene;
	m_pCurrentScene->Initialize();
	p_ObjectManager->Initialize();

	m_pRequestedScene = nullptr;
}
