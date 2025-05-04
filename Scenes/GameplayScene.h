/**
 * @file   GameplayScene.h
 *
 * @brief  ゲームプレイシーンのヘッダファイル
 *
 * @author CatCode
 * @date   2025/04/27
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
private:
	int m_FontSize;

	Position2D m_OpeStringPos;
	int m_OpeFontSize;

public:
	// Main System
	GameplayScene();
	~GameplayScene() noexcept;
	void Initialize() override final;
	void Update()     override final;
	void Render()     override final;
	void Finalize()   override final;
};

