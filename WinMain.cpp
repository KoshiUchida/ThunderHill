/**
 * @file   WinMain.cpp
 *
 * @brief  ���C���\�[�X�t�@�C��
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
/// ���C���R�[�h
/// </summary>
/// <returns>0 = ����I�� / -1 = �ُ�I��</returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*����������*/
    // �E�B���h�E�̃f�t�H���g�ݒ�
    WindowSettings wss = WSI::GetInstance().GetWindowSetting();
    SetMainWindowText(wss.WindowTitle.c_str());
    ChangeWindowMode(wss.FragChangeWindowMode);
    SetGraphMode(wss.Screen.width, wss.Screen.height, wss.ColorBitDepth);
    SetOutApplicationLogValidFlag(wss.FragOutApplicationLogValid);
    SetFontSize(wss.FontSize);
    SetWindowSizeExtendRate(wss.WindowSizeExtendRate);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
    SetWindowIconID(IDI_ICON1);

    // �E�B���h�E�̐������s���ɃG���[�I��
    if (DxLib::DxLib_Init()) return -1;


#if defined(_Release)
    SetMouseDispFlag(false);
#endif
    
    // �V�[�h�l��ݒ�
    srand(static_cast<unsigned int>(time(NULL)));

    // �W���C�p�b�h�̃C���X�^���X���擾
    Joypad& joypad = Joypad::GetInstance();
    SceneManager& scene = SceneManager::GetInstance();

    while (ProcessMessage() == 0 && !PressedEndKey() && !scene.isEnd())
    {

        //�������Ԃ̌v���J�n
        int StartTime = GetNowCount();

        //����ʏ���
        ClearDrawScreen();
        //�`���𗠉�ʂ�
        SetDrawScreen(DX_SCREEN_BACK);

        /*�X�V����*/
        joypad.Update();
        scene.Update();

        /*�`�揈��*/
        scene.Render();

        // �������Ԃ̌v���I��
        int RunTime = GetNowCount() - StartTime;


#if defined(_DEBUG)
        // RunTime �̕\��
        DrawFormatString(wss.Screen.width - 100, wss.Screen.height - 50, GetColor(255, 0, 0), "%dFPS", ((wss.RunTimeMin - RunTime > 0) ? (1000 / wss.RunTimeMin) : (1000 / RunTime)));
#endif

        //����ʂ�\��ʂɃR�s�[
        ScreenFlip();

        // �����^�C���̐���
        if (wss.RunTimeMin - RunTime > 0)
            WaitTimer(wss.RunTimeMin - RunTime);
    }

    /*�I������*/

    // �E�B���h�E�̔j��
    DxLib::DxLib_End();

    return 0;
}

bool PressedEndKey()
{
    return (GetKeyState(VK_ESCAPE) & 0x8000);
}