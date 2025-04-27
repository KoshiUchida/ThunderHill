/**
 * @file   WinMain.cpp
 *
 * @brief  メインソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#include "WinMain.h"

#include "Resource.h"
#include <DxLib.h>
#include <WinBase.h>
#include <time.h>
#include "WindowSettingItems.h"
#include "Manager/Joypad.h"
#include "Manager/SceneManager.h"

/// <summary>
/// メインコード
/// </summary>
/// <returns>0 = 正常終了 / -1 = 異常終了</returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*初期化処理*/
    // ウィンドウのデフォルト設定
    WindowSettings wss = WSI::GetInstance().GetWindowSetting();
    SetMainWindowText(wss.WindowTitle.c_str());
    ChangeWindowMode(wss.FragChangeWindowMode);
    SetGraphMode(wss.Screen.width, wss.Screen.height, wss.ColorBitDepth);
    SetOutApplicationLogValidFlag(wss.FragOutApplicationLogValid);
    SetFontSize(wss.FontSize);
    SetWindowSizeExtendRate(wss.WindowSizeExtendRate);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
    SetWindowIconID(IDI_ICON1);

    // ウィンドウの生成失敗時にエラー終了
    if (DxLib::DxLib_Init()) return -1;


#if defined(_Release)
    SetMouseDispFlag(false);
#endif
    
    // シード値を設定
    srand(static_cast<unsigned int>(time(NULL)));

    // ジョイパッドのインスタンスを取得
    Joypad& joypad = Joypad::GetInstance();
    SceneManager& scene = SceneManager::GetInstance();

    while (ProcessMessage() == 0 && !PressedEndKey() && !scene.isEnd())
    {

        //処理時間の計測開始
        int StartTime = GetNowCount();

        //裏画面消す
        ClearDrawScreen();
        //描画先を裏画面に
        SetDrawScreen(DX_SCREEN_BACK);

        /*更新処理*/
        joypad.Update();
        scene.Update();

        /*描画処理*/
        scene.Render();

        // 処理時間の計測終了
        int RunTime = GetNowCount() - StartTime;


#if defined(_DEBUG)
        // RunTime の表示
        DrawFormatString(wss.Screen.width - 100, wss.Screen.height - 50, GetColor(255, 0, 0), "%dFPS", ((wss.RunTimeMin - RunTime > 0) ? (1000 / wss.RunTimeMin) : (1000 / RunTime)));
#endif

        //裏画面を表画面にコピー
        ScreenFlip();

        // ランタイムの制御
        if (wss.RunTimeMin - RunTime > 0)
            WaitTimer(wss.RunTimeMin - RunTime);
    }

    /*終了処理*/

    // ウィンドウの破棄
    DxLib::DxLib_End();

    return 0;
}

bool PressedEndKey()
{
    return (GetKeyState(VK_ESCAPE) & 0x8000);
}