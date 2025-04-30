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

#include "../Manager/Joypad.h"

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene :
	public SceneBace
{
private:
	Position2D m_StartStringPos;
	Position2D m_TitleStringPos;

	int m_FontSize;
	int m_TitleFontSize;

	Joypad& p_Joypad;

	bool m_Bottom;

public:
	// メインシステム
	TitleScene();
	~TitleScene();
	void Initialize() override;
	void Update()     override;
	void Render()     override;
	void Finalize()   override;
};

