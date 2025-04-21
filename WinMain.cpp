/**
 * @file   WinMain.cpp
 *
 * @brief  メインソースファイル
 *
 * @author CatCode
 *
 * @date   2025/01/23
 */

#include "WinMain.h"

#include "Resource.h"
#include <DxLib.h>
#include <WinBase.h>
#include <time.h>
#include "WindowSettingItems.h"
#include "Core/Core.h"

/// <summary>
/// メインコード
/// </summary>
/// <returns>0 = 正常終了 / -1 = 異常終了</returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*初期化処理*/
    // ウィンドウのデフォルト設定
    WSI wsi{ "WindowSettings.wss" };
    SetMainWindowText(wsi.WindowTitle.c_str());
    ChangeWindowMode(wsi.FragChangeWindowMode);
    SetGraphMode(wsi.ScreenWidth, wsi.ScreenHeight, wsi.ColorBitDepth);
    SetOutApplicationLogValidFlag(wsi.FragOutApplicationLogValid);
    SetFontSize(wsi.FontSize);
    SetWindowSizeExtendRate(wsi.WindowSizeExtendRate);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
    SetWindowIconID(IDI_ICON1);

    // ウィンドウの生成失敗時にエラー終了
    if (DxLib::DxLib_Init()) return -1;


#if defined(_Release)
    SetMouseDispFlag(false);
#endif
    
    // シード値を設定
    srand(static_cast<unsigned int>(time(NULL)));

    // コアの生成と初期化
    Core m_core{ &wsi };
    m_core.Initialize();

    while (ProcessMessage() == 0 && !PressedEndKey() && !m_core.isEnd())
    {

        //処理時間の計測開始
        int StartTime = GetNowCount();

        //裏画面消す
        ClearDrawScreen();
        //描画先を裏画面に
        SetDrawScreen(DX_SCREEN_BACK);

        /*更新処理*/
        m_core.Update();

        /*描画処理*/
        m_core.Render();

        // 処理時間の計測終了
        int RunTime = GetNowCount() - StartTime;


#if defined(_DEBUG)
        // RunTime の表示
        DrawFormatString(wsi.ScreenRight - 100, wsi.ScreenBotton - 50, GetColor(255, 0, 0), "%dFPS", ((wsi.RunTimeMin - RunTime > 0) ? (1000 / wsi.RunTimeMin) : (1000 / RunTime)));
#endif

        //裏画面を表画面にコピー
        ScreenFlip();

        // ランタイムの制御
        if (wsi.RunTimeMin - RunTime > 0)
            WaitTimer(wsi.RunTimeMin - RunTime);
    }

    /*終了処理*/
    m_core.Finalize();

    // ウィンドウの破棄
    DxLib::DxLib_End();

    return 0;
}

bool PressedEndKey()
{
    // 以下ふたつのキーが押されていない限り次に進まない
    if (!CheckHitKey(KEY_INPUT_LCONTROL) || !CheckHitKey(KEY_INPUT_LSHIFT))
        return false;

    return CheckHitKey(KEY_INPUT_E);
}