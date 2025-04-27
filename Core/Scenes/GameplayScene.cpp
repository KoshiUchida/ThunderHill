/**
 * @file   GameplayScene.cpp
 *
 * @brief  �Q�[���v���C�V�[���̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/21
 */

#include "GameplayScene.h"

#include <DxLib.h>
#include "../../WindowSettingItems.h"
#include "../Common/Colors.h"

#include "../Common/Collisions.h"

using namespace std;

/// <summary>
/// Constructor
/// </summary>
GameplayScene::GameplayScene(WSI* wsi, SceneManager* sceneManager)
	: SceneBace(wsi, sceneManager)
{
}

/// <summary>
/// Destructor
/// </summary>
GameplayScene::~GameplayScene() noexcept = default;

/// <summary>
/// ����������
/// </summary>
void GameplayScene::Initialize()
{
	// Font Size
	SetFontSize(mp_wsi->FontSize);

	// Object Initialize
	m_ObjectManager.Initialize();
}

/// <summary>
/// �X�V����
/// </summary>
void GameplayScene::Update()
{
	m_ObjectManager.Update();
}

/// <summary>
/// �`�揈��
/// </summary>
void GameplayScene::Render()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	m_ObjectManager.Render(m_camera);

#if defined(_DEBUG)
	DrawString(mp_wsi->ScreenRight - mp_wsi->FontSize * 13, mp_wsi->ScreenBotton - mp_wsi->FontSize * 2, "GameplayScene", Colors::Cyan);
#endif
}

/// <summary>
/// �I������
/// </summary>
void GameplayScene::Finalize()
{
	m_ObjectManager.Finalize();
}