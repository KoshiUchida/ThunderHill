/**
 * @file   Title.cpp
 *
 * @brief  �^�C�g���V�[���̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/05/04
 */

#include "Title.h"

#include <DxLib.h>
#include "../WindowSettingItems.h"

#include "../Manager/ResourceManager.h"
#include "../Common/Colors.h"

using namespace std;

/// <summary>
/// Constructor
/// </summary>
Title::Title() :
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
Title::~Title() = default;

/// <summary>
/// ����������
/// </summary>
void Title::Initialize()
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
/// �X�V����
/// </summary>
void Title::Update()
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
static constexpr char OpePadString[] = { "Select:A" };
static constexpr char OpeKeyString[] = { "Select:Z" };

/// <summary>
/// �`�揈��
/// </summary>
void Title::Render()
{
	SetFontSize(m_TitleFontSize);

	DrawString(m_TitleStringPos.x(), m_TitleStringPos.y(), TitleString, TitleStringColor);

	SetFontSize(m_OpeFontSize);

	if (p_Joypad.IsConnected())
		DrawString(m_OpeStringPos.x(), m_OpeStringPos.y(), OpePadString, StartStringColor);
	else
		DrawString(m_OpeStringPos.x(), m_OpeStringPos.y(), OpeKeyString, StartStringColor);

	SetFontSize(m_FontSize);

	DrawString(m_StartStringPos.x(), m_StartStringPos.y(), StartString, StartStringColor);
}

/// <summary>
/// �I������
/// </summary>
void Title::Finalize()
{
	StopSoundMem(ResourceManager::GetInstance().RequestSound("ThunderRainBGM.ogg"));
}
