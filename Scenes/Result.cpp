#include "Result.h"
#include <DxLib.h>
#include "../Common/Colors.h"
#include "../WindowSettingItems.h"
#include "../Manager/ResourceManager.h"

Result::Result() noexcept :
	SceneBace(),
	p_pad{ Joypad::GetInstance() },
	m_Bottom{}
{
}

Result::~Result() noexcept = default;

void Result::Initialize()
{
	m_Bottom = false;
}

void Result::Update()
{
	if (!m_Bottom && !p_pad.IsPressed(XINPUT_GAMEPAD_A))
		m_Bottom = true;

	if (m_Bottom && p_pad.IsPressed(XINPUT_GAMEPAD_A))
		ChangeScene("Title");
}

void Result::Render()
{
#if defined(_DEBUG)
	DrawString(p_wsi->ScreenRight() - WSI::GetInstance().GetWindowSetting().FontSize * 13,
		p_wsi->ScreenBottom() - WSI::GetInstance().GetWindowSetting().FontSize * 2,
		"ResultScene", Colors::Cyan);
#endif
}

void Result::Finalize()
{
	PlaySoundMem(ResourceManager::GetInstance().RequestSound("ClickSE.ogg"), DX_PLAYTYPE_BACK);
}
