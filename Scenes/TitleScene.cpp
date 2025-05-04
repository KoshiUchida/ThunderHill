/**
 * @file   TitleScene.cpp
 *
 * @brief  タイトルシーンのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#include "TitleScene.h"

#include <DxLib.h>
#include "../WindowSettingItems.h"

#include "../Manager/ResourceManager.h"
#include "../Common/Colors.h"

using namespace std;

/// <summary>
/// Constructor
/// </summary>
TitleScene::TitleScene() :
	SceneBace(),
	p_Joypad{ Joypad::GetInstance() },
	m_FontSize{},
	m_TitleFontSize{},
	m_Bottom{},
	m_OpeFontSize{}
{
}

/// <summary>
/// Destructor
/// </summary>
TitleScene::~TitleScene() = default;

/// <summary>
/// 初期化処理
/// </summary>
void TitleScene::Initialize()
{
	WSI& wsi{ WSI::GetInstance() };

	m_FontSize = wsi.GetWindowSetting().FontSize + 1;
	m_TitleFontSize = m_FontSize + 10;
	m_OpeFontSize = m_FontSize - 3;

	m_TitleStringPos = Position2D(wsi.ScreenCenterX() - 70.f, wsi.ScreenCenterY() - 20.f);
	m_StartStringPos = Position2D(wsi.ScreenCenterX() - 15.f, wsi.ScreenBottom() - 60.f);
	m_OpeStringPos = Position2D(wsi.ScreenLeft() + 5.f, wsi.ScreenBottom() - m_FontSize);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	m_Bottom = false;

	PlaySoundMem(ResourceManager::GetInstance().RequestSound("ThunderRainBGM.ogg"), DX_PLAYTYPE_LOOP);
}

/// <summary>
/// 更新処理
/// </summary>
void TitleScene::Update()
{
	if (!m_Bottom && !p_Joypad.IsPressed(XINPUT_GAMEPAD_A))
		m_Bottom = true;

	if (m_Bottom && p_Joypad.IsPressed(XINPUT_GAMEPAD_A))
	{
		PlaySoundMem(ResourceManager::GetInstance().RequestSound("ClickSE.ogg"), DX_PLAYTYPE_BACK);
		ChangeScene("Gameplay");
	}
}

static constexpr char StartString[] = { "Start" };
static constexpr unsigned int StartStringColor{ Colors::White };
static constexpr char TitleString[] = { "THUNDER HILL" };
static constexpr unsigned int TitleStringColor{ Colors::LightBlue };
static constexpr char OpeString[] = { "Select:pad(A),key(Z) End:key(Escape)" };

/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Render()
{
	SetFontSize(m_TitleFontSize);

	DrawString(m_TitleStringPos.x(), m_TitleStringPos.y(), TitleString, TitleStringColor);

	SetFontSize(m_OpeFontSize);

	DrawString(m_OpeStringPos.x(), m_OpeStringPos.y(), OpeString, StartStringColor);

	SetFontSize(m_FontSize);

	DrawString(m_StartStringPos.x(), m_StartStringPos.y(), StartString, StartStringColor);
}

/// <summary>
/// 終了処理
/// </summary>
void TitleScene::Finalize()
{
	StopSoundMem(ResourceManager::GetInstance().RequestSound("ThunderRainBGM.ogg"));
}
