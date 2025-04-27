/**
 * @file   WindowSettingItems.cpp
 *
 * @brief  ウィンドウのデフォルト設定がある設定ファイル
 *
 * @author CatCode
 *
 * @date   2024/12/28
 */

#include "WindowSettingItems.h"

#include "Common/FileIO.h"

std::unique_ptr<WSI> WSI::s_WSI = nullptr;

WSI& WSI::GetInstance()
{
	if (!s_WSI)
		s_WSI.reset(new WSI("WindowSettings.wss"));

	return *s_WSI.get();
}

/// <summary>
/// コンストラクタ
/// </summary>
WSI::WSI(const std::string& filename)
	: m_WSS{}
{
	m_WSS = ReadWindowSettings(filename);
}

WindowSettings WSI::GetWindowSetting() noexcept
{
	return m_WSS;
}

int WSI::ScreenLeft()
{
	return 0;
}

int WSI::ScreenCenterX()
{
	return m_WSS.Screen.width / 2;
}

int WSI::ScreenRight()
{
	return m_WSS.Screen.width;
}

int WSI::ScreenTop()
{
	return 0;
}

int WSI::ScreenCenterY()
{
	return m_WSS.Screen.height / 2;
}

int WSI::ScreenBottom()
{
	return m_WSS.Screen.height;
}
