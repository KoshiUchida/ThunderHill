/**
 * @file   GameplayScene.cpp
 *
 * @brief  ゲームプレイシーンのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/21
 */

#include "GameplayScene.h"

#include <DxLib.h>
#include "../WindowSettingItems.h"
#include "../Common/Colors.h"

#include "../Common/Collisions.h"

#include "../Manager/ObjectManager.h"
#include "../Objects/Player.h"
#include "../Objects/ThunderGenerater.h"

using namespace std;

/// <summary>
/// Constructor
/// </summary>
GameplayScene::GameplayScene()
	: SceneBace()
	, m_FontSize{}
{
}

/// <summary>
/// Destructor
/// </summary>
GameplayScene::~GameplayScene() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void GameplayScene::Initialize()
{
	// Font Size
	m_FontSize = p_wsi->GetWindowSetting().FontSize;
	SetFontSize(m_FontSize);

	// Object Set
	ObjectManager& om{ ObjectManager::GetInstance() };
	om.AddObject("Player", make_unique<Player>());
	om.AddObject("Generater", make_unique<ThunderGenerater>());
}

/// <summary>
/// 更新処理
/// </summary>
void GameplayScene::Update()
{
}

/// <summary>
/// 描画処理
/// </summary>
void GameplayScene::Render()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

#if defined(_DEBUG)
	DrawString(p_wsi->ScreenRight() - m_FontSize * 13, p_wsi->ScreenBottom() - m_FontSize * 2, "GameplayScene", Colors::Cyan);
#endif
}

/// <summary>
/// 終了処理
/// </summary>
void GameplayScene::Finalize()
{
}