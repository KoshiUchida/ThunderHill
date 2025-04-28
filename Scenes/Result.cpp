#include "Result.h"
#include <DxLib.h>
#include "../Common/Colors.h"
#include "../WindowSettingItems.h"

Result::Result() noexcept :
	SceneBace()
{
}

Result::~Result() noexcept = default;

void Result::Initialize()
{
}

void Result::Update()
{
}

void Result::Render()
{
#if defined(_DEBUG)
	DrawString(p_wsi->ScreenRight() - WSI::GetInstance().GetWindowSetting().FontSize * 13, p_wsi->ScreenBottom() - WSI::GetInstance().GetWindowSetting().FontSize * 2, "GameplayScene", Colors::Cyan);
#endif
}

void Result::Finalize()
{
}
