/**
 * @file   SceneManaager.h
 *
 * @brief  �V�[���̊Ǘ��N���X�̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#pragma once
#include <unordered_map>
#include <string>
#include <memory>

class SceneBace;

/// <summary>
/// �V�[���Ǘ��N���X
/// </summary>
class SceneManager final
{
private:
	static std::unique_ptr<SceneManager> s_SceneManager;

public:
	static SceneManager& GetInstance();

	void Clear();

private:
	// �G�C���A�X�錾
	using SceneCollection = std::unordered_map<std::string, std::unique_ptr<SceneBace>>;

	// �V�[���̏W����
	SceneCollection m_scenes;

	// ���݂̃V�[��
	SceneBace* m_pCurrentScene;
	// �ύX�v���̂������V�[��
	SceneBace* m_pRequestedScene;

	// �I������
	bool m_IsEnd;

	/*���C���V�X�e��*/
	SceneManager();

public:
	~SceneManager();
	void Update();
	void Render();

	// �V�[���ύX�̗v��
	void RequestSceneChange(const std::string& changeSceneName);

	/*�擾/�ݒ�*/
	// �I�����߂̎擾
	bool isEnd() const { return m_IsEnd; }

private:
	// �V�[���̓o�^
	void SetScene();

	// �N�����̃V�[���̐ݒ�
	void SetStartScene(const std::string& startSceneName);

	// �V�[���̕ύX
	void ChangeScene();

};

