/**
 * @file   Title.h
 *
 * @brief  タイトルシーンのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/05/04
 */

#pragma once
#include "SceneBace.h"

#include <memory>
#include "../Common/Sprite2D.h"
#include "../Manager/Joypad.h"
#include "../Objects/Arrow.h"

/// <summary>
/// タイトルシーン
/// </summary>
class Title :
	public SceneBace
{
private:
	Position2D m_StartStringPos;
	Position2D m_TitleStringPos;
	Position2D m_OpeStringPos;

	int m_FontSize;
	int m_TitleFontSize;
	int m_OpeFontSize;

	Joypad& p_Joypad;

	bool m_Bottom;

	Arrow* p_ArrowObject;

public:
	// メインシステム
	Title();
	~Title();
	void Initialize() override;
	void Update()     override;
	void Render()     override;
	void Finalize()   override;
};

