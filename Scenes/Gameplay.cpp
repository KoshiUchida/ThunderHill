/**
 * @file   Gameplay.cpp
 *
 * @brief  ゲームプレイシーンのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/05/04
 */

#include "Gameplay.h"

#include <DxLib.h>
#include "../WindowSettingItems.h"
#include "../Common/Colors.h"

#include "../Common/Collisions.h"

#include "../Manager/ObjectManager.h"
#include "../Objects/Player.h"
#include "../Objects/ThunderGenerater.h"
#include "../Objects/TimeLimitUI.h"
#include "../Objects/FlyingDebrisGenerater.h"

using namespace std;

/// <summary>
/// Constructor
/// </summary>
Gameplay::Gameplay():
	SceneBace(),
	m_FontSize{},
	m_OpeFontSize{},
	s_Joypad{ Joypad::GetInstance() }
{
}

/// <summary>
/// Destructor
/// </summary>
Gameplay::~Gameplay() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void Gameplay::Initialize()
{
	// Font Size
	m_FontSize = p_wsi->GetWindowSetting().FontSize;
	SetFontSize(m_FontSize);
	m_OpeFontSize = m_FontSize - 1;
	m_OpeStringPos = Position2D(static_cast<float>(p_wsi->ScreenLeft()) + 5.f, static_cast<float>(p_wsi->ScreenBottom() - m_FontSize));

	// Object Set
	ObjectManager& om{ ObjectManager::GetInstance() };
	om.AddObject("Player"      , make_unique<Player>());
	om.AddObject("Generater"   , make_unique<ThunderGenerater>());
	om.AddObject("TimeLimitUI" , make_unique<TimeLimitUI>());
	om.AddObject("FlyingDebris", make_unique<FlyingDebrisGenerater>());
}

/// <summary>
/// 更新処理
/// </summary>
void Gameplay::Update()
{
}

static constexpr unsigned int StringColor{ Colors::White };
static constexpr char OpePadString[] = { "Move:L-Stick" };
static constexpr char OpeKeyString[] = { "Move:←→ Jump:↑" };

/// <summary>
/// 描画処理
/// </summary>
void Gameplay::Render()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	SetFontSize(m_OpeFontSize);

	if (s_Joypad.IsConnected())
		DrawString(m_OpeStringPos.x(), m_OpeStringPos.y(), OpePadString, StringColor);
	else
		DrawString(m_OpeStringPos.x(), m_OpeStringPos.y(), OpeKeyString, StringColor);

	SetFontSize(m_FontSize);

#if defined(_DEBUG)
	DrawString(p_wsi->ScreenRight() - m_FontSize * 13, p_wsi->ScreenBottom() - m_FontSize * 2, "GameplayScene", Colors::Cyan);
#endif
}

/// <summary>
/// 終了処理
/// </summary>
void Gameplay::Finalize()
{
}