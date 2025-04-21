/**
 * @file   WindowSettingItems.cpp
 *
 * @brief  �E�B���h�E�̃f�t�H���g�ݒ肪����ݒ�t�@�C��
 *
 * @author CatCode
 *
 * @date   2024/12/28
 */

#include "WindowSettingItems.h"

#include "Core/Common/FileIO.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
WSI::WSI(const std::string& filename)
	: WindowTitle{}
	, WindowSizeExtendRate{}
	, FragChangeWindowMode{}
	, ScreenWidth{}
	, ScreenHeight{}
	, ScreenLeft{}
	, ScreenCenterX{}
	, ScreenRight{}
	, ScreenTop{}
	, ScreenCenterY{}
	, ScreenBotton{}
	, ColorBitDepth{}
	, RunTimeMin{}
	, Volume{}
	, Font{}
	, FontSize{}
	, FragOutApplicationLogValid{}
{
	WindowSettings WSS         = ReadWindowSettings(filename);
	WindowTitle                = WSS.WindowTitle;
	WindowSizeExtendRate       = WSS.WindowSizeExtendRate;
	FragChangeWindowMode       = WSS.FragChangeWindowMode;
	ScreenWidth                = WSS.Screen.width;
	ScreenLeft                 = 0;
	ScreenCenterX              = ScreenWidth / 2;
	ScreenRight                = ScreenWidth;
	ScreenHeight               = WSS.Screen.height;
	ScreenTop                  = 0;
	ScreenCenterY              = ScreenHeight / 2;
	ScreenBotton               = ScreenHeight;
	ColorBitDepth              = WSS.ColorBitDepth;
	RunTimeMin                 = WSS.RunTimeMin;
	Volume                     = WSS.Volume;
	Font                       = WSS.Font;
	FontSize                   = WSS.FontSize;
	FragOutApplicationLogValid = WSS.FragOutApplicationLogValid;
}
