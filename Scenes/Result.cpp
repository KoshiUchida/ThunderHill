#include "Result.h"
#include <DxLib.h>
#include "../WindowSettingItems.h"
#include "../Manager/ResourceManager.h"
#include "../Common/Colors.h"
#include "../Manager/ShareData.h"

Result::Result() noexcept :
	SceneBace(),
	p_pad{ Joypad::GetInstance() },
	m_Bottom{},
	m_FontSize{},
	m_GameOverStringFontSize{}
{
}

Result::~Result() noexcept = default;

void Result::Initialize()
{
	m_Bottom = false;

	WSI& wsi{ WSI::GetInstance() };

	m_GameOverStringPos = Position2D(wsi.ScreenCenterX() - 50.f, wsi.ScreenCenterY() - 30.f);
	m_ScoreStringPos = Position2D(wsi.ScreenCenterX() - 30.f, wsi.ScreenCenterY() + 30.f);

	m_FontSize = wsi.GetWindowSetting().FontSize;
	m_GameOverStringFontSize = wsi.GetWindowSetting().FontSize + 10;

	PlaySoundMem(ResourceManager::GetInstance().RequestSound("ThunderRainBGM.ogg"), DX_PLAYTYPE_LOOP);

	ShareData& p_sd{ ShareData::GetInstance() };

	m_Score = p_sd.GetShareData("Score");

	if (m_Score.size())
	{
		m_Score = "Score : " + m_Score;
	}

}

void Result::Update()
{
	if (!m_Bottom && !p_pad.IsPressed(XINPUT_GAMEPAD_A))
		m_Bottom = true;

	if (m_Bottom && p_pad.IsPressed(XINPUT_GAMEPAD_A))
	{
		PlaySoundMem(ResourceManager::GetInstance().RequestSound("ClickSE.ogg"), DX_PLAYTYPE_BACK);
		ChangeScene("Title");
	}
}

static constexpr unsigned int StringColor{ Colors::White };
static constexpr char GameOverString[10] = { "GAME OVER" };

void Result::Render()
{
	SetFontSize(m_GameOverStringFontSize);

	DrawString(m_GameOverStringPos.x(), m_GameOverStringPos.y(), GameOverString, StringColor);

	SetFontSize(m_FontSize);

	
	if (m_Score.size())
	{
		DrawString(m_ScoreStringPos.x(), m_ScoreStringPos.y(), m_Score.c_str(), StringColor);
	}

#if defined(_DEBUG)
	DrawString(p_wsi->ScreenRight() - WSI::GetInstance().GetWindowSetting().FontSize * 13,
		p_wsi->ScreenBottom() - WSI::GetInstance().GetWindowSetting().FontSize * 2,
		"ResultScene", Colors::Cyan);
#endif
}

void Result::Finalize()
{
	StopSoundMem(ResourceManager::GetInstance().RequestSound("ThunderRainBGM.ogg"));
}
