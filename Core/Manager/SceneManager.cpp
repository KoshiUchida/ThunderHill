/**
 * @file   SceneManaager.cpp
 *
 * @brief  �V�[���̊Ǘ��N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2024/11/03
 */

#include "SceneManager.h"

#include "../Scenes/SceneBace.h"
#include "../Common/Error.h"

// �R���X�g���N�^
SceneManager::SceneManager()
	: m_pCurrentScene  { nullptr }
	, m_pRequestedScene{ nullptr }
	, m_scenes         {}
	, m_IsEnd          {}
{
}

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
		m_pCurrentScene->Update();
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneManager::Render()
{
	// ���݂̃V�[����`��
	if (m_pCurrentScene)
		m_pCurrentScene->Render();
}

/// <summary>
/// �V�[���̓o�^
/// </summary>
/// <param name="sceneName">�V�[���̓o�^��</param>
/// <param name="scene">�o�^�V�[��</param>
void SceneManager::addScene(const std::string& sceneName, std::unique_ptr<SceneBace> scene)
{
	m_scenes.emplace(sceneName, std::move(scene));
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
/// ���L�f�[�^�̎擾
/// </summary>
/// <param name="key">�擾���������L�f�[�^�̃L�[</param>
/// <returns>�L�[�̋��L�f�[�^</returns>
std::string SceneManager::GetShareData(const std::string& key) const
{
	if (m_shareData.count(key) == 0)
	{
		printError(key + "�@�͓o�^����Ă��܂���B");
		return std::string{};
	}

	return m_shareData.at(key);
}

/// <summary>
/// ���L�f�[�^�̐ݒ�
/// </summary>
/// <param name="key">�ݒ肵�������L�f�[�^�̃L�[</param>
/// <param name="value">�ݒ肵�������L�f�[�^�̒l</param>
void SceneManager::SetSharedData(const std::string& key, const std::string& value)
{
	m_shareData[key] = value;
}

/// <summary>
/// �V�[���̕ύX
/// </summary>
void SceneManager::ChangeScene()
{
	if (!m_pRequestedScene)
		return;

	if (m_pCurrentScene)
		m_pCurrentScene->Finalize();

	if (m_IsEnd)
		return;

	m_pCurrentScene = m_pRequestedScene;
	m_pCurrentScene->Initialize();

	m_pRequestedScene = nullptr;
}
