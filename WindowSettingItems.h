/**
 * @file   WindowSettingItems.h
 *
 * @brief  ウィンドウのデフォルト設定があるヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2024/12/28
 */

#pragma once
#include <string>
#include <memory>

/// <summary>
/// ウインドウ設定型
/// </summary>
struct WindowSettings {

	/*ウインドウのタイトル*/
	std::string WindowTitle;
	
	/*ウインドウの拡大比率*/
	double WindowSizeExtendRate;

	/*非全画面にセットするか*/
	bool FragChangeWindowMode;

	/*画面の設定*/
	// 画面サイズ
	struct {
		int width;
		int height;
	} Screen;

	// 色深度
	int ColorBitDepth;

	// １ループでの処理速度の下限[ms]
	int RunTimeMin;

	/*サウンドの設定*/
	int Volume;

	/*文字関係の設定*/
	// デフォルトフォント
	std::string Font;
	// フォントサイズ
	int FontSize;

	/*Log.txtの生成設定*/
	bool FragOutApplicationLogValid;
};

/// <summary>
/// ウインドウの設定クラス
/// </summary>
class WSI final
{
private:
	static std::unique_ptr<WSI> s_WSI;

public:
	static WSI& GetInstance();

private:
	WindowSettings m_WSS;

	/*スクリーンの設定*/
	static constexpr int MaxVolume{ 255 };
	static constexpr int MinVolume{ 0 };

private:
	/*メインシステム*/
	WSI(const std::string& filename);
public:
	~WSI() = default;

	WindowSettings GetWindowSetting() noexcept;

	int ScreenLeft();

	int ScreenCenterX();

	int ScreenRight();

	int ScreenTop();

	int ScreenCenterY();

	int ScreenBottom();
};