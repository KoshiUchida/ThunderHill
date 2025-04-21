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
	GameplayScene(WSI* wsi, SceneManager* sceneManager, ControllerManager* contorollerManager);
	~GameplayScene();
	void Initialize() override;
	void Update()     override;
	void Render()     override;
	void Finalize()   override;
};

