/**
 * @file   Result.cpp
 *
 * @brief  リザルトシーンのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/05/04
 */
#include "Result.h"

#include <DxLib.h>
#include "../Common/Colors.h"

#include "../WindowSettingItems.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/ShareData.h"


/// <summary>
/// コンストラクタ
/// </summary>
Result::Result() noexcept :
	SceneBace(),
	s_Joypad{ Joypad::GetInstance() },
	m_Bottom{},
	m_FontSize{},
	m_GameOverStringFontSize{},
	m_OpeFontSize{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
Result::~Result() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void Result::Initialize()
{
	WSI& wsi{ WSI::GetInstance() };

	m_ResultStringPos = Position2D(wsi.ScreenCenterX() - 40.f, wsi.ScreenCenterY() - 30.f);
	m_ScoreStringPos = Position2D(wsi.ScreenCenterX() - 35.f, wsi.ScreenCenterY() + 30.f);

	m_FontSize = wsi.GetWindowSetting().FontSize;
	m_GameOverStringFontSize = wsi.GetWindowSetting().FontSize + 10;
	m_OpeFontSize = m_FontSize - 2;

	m_OpeStringPos = Position2D(wsi.ScreenLeft() + 5.f, static_cast<float>(wsi.ScreenBottom() - m_FontSize));


	PlaySoundMem(ResourceManager::GetInstance().RequestSound("ThunderRainBGM.ogg"), DX_PLAYTYPE_LOOP);


	ShareData& p_sd{ ShareData::GetInstance() };

	if (p_sd.HasKey("Score"))
	{
		m_Score = p_sd.Get("Score");

		m_Score = "Score : " + m_Score;
	}

	if (p_sd.HasKey("High"))
	{
		m_High = p_sd.Get("High");

		m_High = "High score : " + m_High;
	}

	m_Bottom = false;
}

/// <summary>
/// 更新処理
/// </summary>
void Result::Update()
{
	if (!m_Bottom && !s_Joypad.IsPressed(XINPUT_GAMEPAD_A))
		m_Bottom = true;

	if (m_Bottom && s_Joypad.IsPressed(XINPUT_GAMEPAD_A))
	{
		PlaySoundMem(ResourceManager::GetInstance().RequestSound("ClickSE.wav"), DX_PLAYTYPE_BACK);
		ChangeScene("Title");
	}
}

static constexpr unsigned int StringColor{ Colors::White };
static constexpr char ResultString[] = { "RESULT" };
static constexpr char OpePadString[] = { "Select:A" };
static constexpr char OpeKeyString[] = { "Select:Z" };

/// <summary>
/// 描画処理
/// </summary>
void Result::Render()
{
	SetFontSize(m_GameOverStringFontSize);

	DrawString(static_cast<int>(m_ResultStringPos.x()), static_cast<int>(m_ResultStringPos.y()), ResultString, StringColor);

	SetFontSize(m_OpeFontSize);

	if (s_Joypad.IsConnected())
		DrawString(static_cast<int>(m_OpeStringPos.x()), static_cast<int>(m_OpeStringPos.y()), OpePadString, StringColor);
	else
		DrawString(static_cast<int>(m_OpeStringPos.x()), static_cast<int>(m_OpeStringPos.y()), OpeKeyString, StringColor);

	SetFontSize(m_FontSize);

	
	if (m_Score.size())
	{
		DrawString(static_cast<int>(m_ScoreStringPos.x()), static_cast<int>(m_ScoreStringPos.y()), m_Score.c_str(), StringColor);
	}

	if (m_High.size())
	{
		DrawString(static_cast<int>(m_ScoreStringPos.x() - 35.f), static_cast<int>(m_ScoreStringPos.y() - 10.f), m_High.c_str(), StringColor);
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
