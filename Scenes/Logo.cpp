/**
 * @file   LogoScene.cpp
 *
 * @brief  ���S�V�[���̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#include "Logo.h"

#include <DxLib.h>
#include "../Manager/ResourceManager.h"
#include "../WindowSettingItems.h"
#include "../Common/Sprite2D.h"
#include "../Manager/Joypad.h"

using namespace std;

/// <summary>
/// �R���X�g���N
/// </summary>
Logo::Logo()
	: SceneBace()
	, ms_Logo{ nullptr }
	, m_Time{}
	, m_LogoAlpha{}
	, m_IsUpAlpha{}
{
}

Logo::~Logo() = default;

/// <summary>
/// ����������
/// </summary>
void Logo::Initialize()
{
	ResourceManager& rm{ ResourceManager::GetInstance() };

	ms_Logo = std::make_unique<Sprite2D>(rm.RequestTexture("Logo.png"), 1.4f);
	ms_Logo->Initialize(Transform2D(Position2D(static_cast<float>(p_wsi->ScreenCenterX()), static_cast<float>(p_wsi->ScreenCenterY())), 0.f));
	
	m_Time      = 0;
	m_LogoAlpha = 0;
	m_IsUpAlpha = true;

	PlaySoundMem(rm.RequestSound("logoBGM.ogg"), DX_PLAYTYPE_LOOP);
}

/// <summary>
/// �X�V����
/// </summary>
void Logo::Update()
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 || Joypad::GetInstance().IsPressed(XINPUT_GAMEPAD_A) || m_Time > SceneChangeTime)
		ChangeScene("Title");

	if (m_IsUpAlpha)
	{
		m_LogoAlpha++;

		if (m_LogoAlpha >= 255)
		{
			m_IsUpAlpha = false;
		}
		return;
	}
	else
	{
		if (m_LogoAlpha > 0)
		{
			m_LogoAlpha--;
			return;
		}

		m_Time++;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Logo::Render()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_LogoAlpha);
	ms_Logo->Draw();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

/// <summary>
/// �I������
/// </summary>
void Logo::Finalize()
{
	ms_Logo.reset();
	StopSoundMem(ResourceManager::GetInstance().RequestSound("logoBGM.ogg"));
}
