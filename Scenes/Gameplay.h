/**
 * @file   Gameplay.h
 *
 * @brief  ゲームプレイシーンのヘッダファイル
 *
 * @author CatCode
 * 
 * @date   2025/05/04
 */

#pragma once
#include "SceneBace.h"

#include <memory>
#include "../Manager/Joypad.h"

/// <summary>
/// ゲームプレイシーン
/// </summary>
class Gameplay
	: public SceneBace
{
private:
	int m_FontSize;

	Position2D m_OpeStringPos;
	int m_OpeFontSize;

	Joypad& s_Joypad;

public:
	// Main System
	Gameplay();
	~Gameplay() noexcept;
	void Initialize() override final;
	void Update()     override final;
	void Render()     override final;
	void Finalize()   override final;
};

