/**
 * @file   Result.h
 *
 * @brief  リザルトシーンのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/05/04
 */
#pragma once
#include "SceneBace.h"

#include "../Manager/Joypad.h"

/// <summary>
/// リザルトシーン
/// </summary>
class Result :
	public SceneBace
{
private:
	Joypad& s_Joypad;

	bool m_Bottom;

	Position2D m_ResultStringPos;
	int m_FontSize;
	int m_GameOverStringFontSize;

	Position2D m_ScoreStringPos;
	std::string m_Score;
	std::string m_High;

	Position2D m_OpeStringPos;
	int m_OpeFontSize;

public:
	Result() noexcept;
	~Result() noexcept;
	void Initialize() override;
	void Update()     override;
	void Render()     override;
	void Finalize()   override;
};

