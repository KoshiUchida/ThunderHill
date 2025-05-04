/**
 * @file   SceneManaager.cpp
 *
 * @brief  �V�[���̊Ǘ��N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2024/05/04
 */

#include "SceneManager.h"

#include "../Scenes/SceneBace.h"
#include "../Common/Error.h"

#include "../Scenes/Title.h"
#include "../Scenes/Gameplay.h"
#include "../Scenes/Logo.h"
#include "../Scenes/Result.h"

std::unique_ptr<SceneManager> SceneManager::s_SceneManager = nullptr;

SceneManager& SceneManager::GetInstance()
{
	if (!s_SceneManager)
	{
		s_SceneManager.reset(new SceneManager());
		s_SceneManager->Clear();
		s_SceneManager->SetScene();
	}

	return *s_SceneManager.get();
}

void SceneManager::Clear()
{
	m_pCurrentScene = nullptr;
	m_pRequestedScene = nullptr;
	m_IsEnd = false;
}

SceneManager::SceneManager() = default;

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager()
{
	if (m_pCurrentScene)
		m_pCurrentScene->Finalize();
}

/// <summary>
/// �X�V����
/// </summary>
void SceneManager::Update()
{
	// �V�[���̕ύX�v�����������ꍇ�̓V�[���̕ύX���s��
	if (m_pRequestedScene)
	{
		ChangeScene();
	}

	// ���݂̃V�[�����X�V
	if (m_pCurrentScene)
	{
		p_ObjectManager->Update();
		m_pCurrentScene->Update();
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneManager::Render()
{
	// ���݂̃V�[����`��
	if (m_pCurrentScene)
	{
		m_pCurrentScene->Render();
		p_ObjectManager->Render(m_pCurrentScene->GetCamera());
	}
}

/// <summary>
/// �V�[���̓o�^
/// </summary>
void SceneManager::SetScene()
{
	p_ObjectManager = &ObjectManager::GetInstance();

	m_scenes.emplace("Logo"    , std::make_unique<Logo>());
	m_scenes.emplace("Title"   , std::make_unique<Title>());
	m_scenes.emplace("Gameplay", std::make_unique<Gameplay>());
	m_scenes.emplace("Result"  , std::make_unique<Result>());

	// �J�n�V�[���̐ݒ�
#if defined(_DEBUG)
	SetStartScene("Result");
#else
	SetStartScene("Logo");
#endif
}

/// <summary>
/// �J�n�V�[���̐ݒ�
/// </summary>
/// <param name="startSceneName">�J�n�V�[����</param>
void SceneManager::SetStartScene(const std::string& startSceneName)
{
	RequestSceneChange(startSceneName);
}

/// <summary>
/// �V�[���ύX�̗v��
/// </summary>
/// <param name="changeSceneName">�ύX�\��̃V�[����</param>
void SceneManager::RequestSceneChange(const std::string& changeSceneName)
{
	if (changeSceneName == "End")
	{
		m_IsEnd = true;
		return;
	}

	if (m_scenes.count(changeSceneName) == 0)
	{
		printError(changeSceneName + "�V�[���͓o�^����Ă��܂���B");
		return;
	}

	m_pRequestedScene = m_scenes[changeSceneName].get();
}

/// <summary>
/// �V�[���̕ύX
/// </summary>
void SceneManager::ChangeScene()
{
	if (!m_pRequestedScene)
		return;

	if (m_pCurrentScene)
	{
		p_ObjectManager->Finalize();
		m_pCurrentScene->Finalize();
	}

	if (m_IsEnd)
		return;

	m_pCurrentScene = m_pRequestedScene;
	m_pCurrentScene->Initialize();
	p_ObjectManager->Initialize();

	m_pRequestedScene = nullptr;
}
