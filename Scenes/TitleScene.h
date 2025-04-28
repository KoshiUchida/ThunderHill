/**
 * @file   TitleScene.h
 *
 * @brief  タイトルシーンのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/04/28
 */

#pragma once
#include "SceneBace.h"

#include <memory>

#include "../Common/Sprite2D.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene
	: public SceneBace
{
public:
	// メインシステム
	TitleScene();
	~TitleScene();
	void Initialize() override;
	void Update()     override;
	void Render()     override;
	void Finalize()   override;
};

