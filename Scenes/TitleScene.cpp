/**
 * @file   TitleScene.cpp
 *
 * @brief  タイトルシーンのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#include "TitleScene.h"

#include <DxLib.h>
#include "../WindowSettingItems.h"

#include "../Manager/ResourceManager.h"
#include "../Common/Colors.h"

using namespace std;

/// <summary>
/// Constructor
/// </summary>
TitleScene::TitleScene()
	: SceneBace()
{
}

/// <summary>
/// Destructor
/// </summary>
TitleScene::~TitleScene() = default;

/// <summary>
/// 初期化処理
/// </summary>
void TitleScene::Initialize()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

/// <summary>
/// 更新処理
/// </summary>
void TitleScene::Update()
{
}

/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Render()
{
}

/// <summary>
/// 終了処理
/// </summary>
void TitleScene::Finalize()
{
}
