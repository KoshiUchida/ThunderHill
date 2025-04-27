/**
 * @file   Core.cpp
 *
 * @brief  システム中央制御のソースファイル
 *
 * @author CatCode
 *
 * @date   2025/01/23
 */

#include "Core.h"

#include "../WindowSettingItems.h"
#include "Manager/SceneManager.h"

#include "Scenes/TitleScene.h"
#include "Scenes/GameplayScene.h"
#include "Scenes/LogoScene.h"

/// <summary>
/// コンストラクタ
/// </summary>
Core::Core(WSI* pWSI)
	: mp_wsi{ pWSI }
	, m_sceneManager{ nullptr }
	, m_IsEnd{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
Core::~Core() = default;

/// <summary>
/// 初期化処理
/// </summary>
void Core::Initialize()
{
	// マネージャの生成
	m_sceneManager      = std::make_unique<SceneManager>();

	// シーンの登録
	m_sceneManager->addScene("Logo"    , std::make_unique<LogoScene>    (mp_wsi, m_sceneManager.get()));
	m_sceneManager->addScene("Title"   , std::make_unique<TitleScene>   (mp_wsi, m_sceneManager.get()));
	m_sceneManager->addScene("Gameplay", std::make_unique<GameplayScene>(mp_wsi, m_sceneManager.get()));

	// 開始シーンの設定

#if defined(_DEBUG)
	m_sceneManager->SetStartScene("Gameplay");
#else
	m_sceneManager->SetStartScene("Logo");
#endif
}

/// <summary>
/// 更新処理
/// </summary>
void Core::Update()
{
	if (m_sceneManager->isEnd())
		m_IsEnd = true;

	m_sceneManager->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void Core::Render()
{
	// シーンの描画
	m_sceneManager->Render();
}

/// <summary>
/// 終了処理
/// </summary>
void Core::Finalize()
{
}
