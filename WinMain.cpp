/**
 * @file   WinMain.cpp
 *
 * @brief  ���C���\�[�X�t�@�C��
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
/// ���C���R�[�h
/// </summary>
/// <returns>0 = ����I�� / -1 = �ُ�I��</returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	/*����������*/
    // �E�B���h�E�̃f�t�H���g�ݒ�
    WSI wsi{ "WindowSettings.wss" };
    SetMainWindowText(wsi.WindowTitle.c_str());
    ChangeWindowMode(wsi.FragChangeWindowMode);
    SetGraphMode(wsi.ScreenWidth, wsi.ScreenHeight, wsi.ColorBitDepth);
    SetOutApplicationLogValidFlag(wsi.FragOutApplicationLogValid);
    SetFontSize(wsi.FontSize);
    SetWindowSizeExtendRate(wsi.WindowSizeExtendRate);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
    SetWindowIconID(IDI_ICON1);

    // �E�B���h�E�̐������s���ɃG���[�I��
    if (DxLib::DxLib_Init()) return -1;


#if defined(_Release)
    SetMouseDispFlag(false);
#endif
    
    // �V�[�h�l��ݒ�
    srand(static_cast<unsigned int>(time(NULL)));

    // �R�A�̐����Ə�����
    Core m_core{ &wsi };
    m_core.Initialize();

    while (ProcessMessage() == 0 && !PressedEndKey() && !m_core.isEnd())
    {

        //�������Ԃ̌v���J�n
        int StartTime = GetNowCount();

        //����ʏ���
        ClearDrawScreen();
        //�`���𗠉�ʂ�
        SetDrawScreen(DX_SCREEN_BACK);

        /*�X�V����*/
        m_core.Update();

        /*�`�揈��*/
        m_core.Render();

        // �������Ԃ̌v���I��
        int RunTime = GetNowCount() - StartTime;


#if defined(_DEBUG)
        // RunTime �̕\��
        DrawFormatString(wsi.ScreenRight - 100, wsi.ScreenBotton - 50, GetColor(255, 0, 0), "%dFPS", ((wsi.RunTimeMin - RunTime > 0) ? (1000 / wsi.RunTimeMin) : (1000 / RunTime)));
#endif

        //����ʂ�\��ʂɃR�s�[
        ScreenFlip();

        // �����^�C���̐���
        if (wsi.RunTimeMin - RunTime > 0)
            WaitTimer(wsi.RunTimeMin - RunTime);
    }

    /*�I������*/
    m_core.Finalize();

    // �E�B���h�E�̔j��
    DxLib::DxLib_End();

    return 0;
}

bool PressedEndKey()
{
    // �ȉ��ӂ��̃L�[��������Ă��Ȃ����莟�ɐi�܂Ȃ�
    if (!CheckHitKey(KEY_INPUT_LCONTROL) || !CheckHitKey(KEY_INPUT_LSHIFT))
        return false;

    return CheckHitKey(KEY_INPUT_E);
}