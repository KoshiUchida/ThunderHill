/**
 * @file   TitleScene.cpp
 *
 * @brief  �^�C�g���V�[���̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#include "TitleScene.h"

#include <DxLib.h>
#include "../WindowSettingItems.h"

#include "../Manager/ObjectManager.h"
#include "../Manager/ResourceManager.h"
#include "../Common/Colors.h"

using namespace std;

/// <summary>
/// Constructor
/// </summary>
TitleScene::TitleScene()
	: SceneBace()
{
}

/// <summary>
/// Destructor
/// </summary>
TitleScene::~TitleScene() = default;

/// <summary>
/// ����������
/// </summary>
void TitleScene::Initialize()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	m_ObjectManager.Initialize();
}

/// <summary>
/// �X�V����
/// </summary>
void TitleScene::Update()
{
	m_ObjectManager.Update();
}

/// <summary>
/// �`�揈��
/// </summary>
void TitleScene::Render()
{
	m_ObjectManager.Render(m_camera);
}

/// <summary>
/// �I������
/// </summary>
void TitleScene::Finalize()
{
	m_ObjectManager.Finalize();
}
