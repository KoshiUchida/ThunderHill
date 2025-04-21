/**
 * @file   LogoScene.cpp
 *
 * @brief  ロゴシーンのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/02/10
 */

#include "LogoScene.h"

#include <DxLib.h>
#include "../Manager/ResourceManager.h"
#include "../../WindowSettingItems.h"
#include "../Common/Sprite2D.h"

using namespace std;

/// <summary>
/// コンストラク
/// </summary>
LogoScene::LogoScene(WSI* wsi, SceneManager* sceneManager, ControllerManager* contorollerManager)
	: SceneBace(wsi, sceneManager, contorollerManager)
	, ms_Logo{ nullptr }
	, ms_BGM{}
	, m_Time{}
	, m_LogoAlpha{}
	, m_IsUpAlpha{}
{
}

LogoScene::~LogoScene() = default;

/// <summary>
/// 初期化処理
/// </summary>
void LogoScene::Initialize()
{
	ResourceManager& rm{ ResourceManager::GetInstance() };

	ms_Logo = std::make_unique<Sprite2D>(rm.RequestTexture("Logo.png"), 0.2f);
	ms_Logo->Initialize(Transform2D(Position2D(static_cast<float>(mp_wsi->ScreenCenterX), static_cast<float>(mp_wsi->ScreenCenterY)), 0.f));

	ms_BGM   = rm.RequestSound("logoBGM.ogg");
	
	m_Time      = 0;
	m_LogoAlpha = 0;
	m_IsUpAlpha = true;

	PlaySoundMem(ms_BGM, DX_PLAYTYPE_LOOP);
}

/// <summary>
/// 更新処理
/// </summary>
void LogoScene::Update()
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		ChangeScene("Title");
	}

	if (m_Time > SceneChangeTime)
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
/// 描画処理
/// </summary>
void LogoScene::Render()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_LogoAlpha);
	ms_Logo->Draw();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

/// <summary>
/// 終了処理
/// </summary>
void LogoScene::Finalize()
{
	ms_Logo.reset();

	StopSoundMem(ms_BGM);

	ms_BGM = 0;
}
