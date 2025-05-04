#pragma once
#include "SceneBace.h"
#include "../Manager/Joypad.h"

class Result :
	public SceneBace
{
private:
	Joypad& p_pad;

	bool m_Bottom;

	Position2D m_GameOverStringPos;
	int m_FontSize;
	int m_GameOverStringFontSize;

	Position2D m_ScoreStringPos;
	std::string m_Score;

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

