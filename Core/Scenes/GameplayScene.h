/**
 * @file   GameplayScene.h
 *
 * @brief  ゲームプレイシーンのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/04/21
 */

#pragma once
#include "SceneBace.h"
#include <memory>

/// <summary>
/// ゲームプレイシーン
/// </summary>
class GameplayScene
	: public SceneBace
{
public:
	// Main System
	GameplayScene(WSI* wsi, SceneManager* sceneManager);
	~GameplayScene() noexcept;
	void Initialize() override final;
	void Update()     override final;
	void Render()     override final;
	void Finalize()   override final;
};

