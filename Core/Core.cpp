/**
 * @file   Core.cpp
 *
 * @brief  �V�X�e����������̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/01/23
 */

#include "Core.h"

#include "../WindowSettingItems.h"
#include "Manager/SceneManager.h"

#include "Scenes/TitleScene.h"
#include "Scenes/GameplayScene.h"
#include "Scenes/LogoScene.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Core::Core(WSI* pWSI)
	: mp_wsi{ pWSI }
	, m_sceneManager{ nullptr }
	, m_IsEnd{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Core::~Core() = default;

/// <summary>
/// ����������
/// </summary>
void Core::Initialize()
{
	// �}�l�[�W���̐���
	m_sceneManager      = std::make_unique<SceneManager>();

	// �V�[���̓o�^
	m_sceneManager->addScene("Logo"    , std::make_unique<LogoScene>    (mp_wsi, m_sceneManager.get()));
	m_sceneManager->addScene("Title"   , std::make_unique<TitleScene>   (mp_wsi, m_sceneManager.get()));
	m_sceneManager->addScene("Gameplay", std::make_unique<GameplayScene>(mp_wsi, m_sceneManager.get()));

	// �J�n�V�[���̐ݒ�

#if defined(_DEBUG)
	m_sceneManager->SetStartScene("Gameplay");
#else
	m_sceneManager->SetStartScene("Logo");
#endif
}

/// <summary>
/// �X�V����
/// </summary>
void Core::Update()
{
	if (m_sceneManager->isEnd())
		m_IsEnd = true;

	m_sceneManager->Update();
}

/// <summary>
/// �`�揈��
/// </summary>
void Core::Render()
{
	// �V�[���̕`��
	m_sceneManager->Render();
}

/// <summary>
/// �I������
/// </summary>
void Core::Finalize()
{
}
