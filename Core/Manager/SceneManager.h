/**
 * @file   SceneManaager.h
 *
 * @brief  �V�[���̊Ǘ��N���X�̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2024/11/03
 */

#pragma once
#include <unordered_map>
#include <string>
#include <memory>

class SceneBace;

/// <summary>
/// �V�[���Ǘ��N���X
/// </summary>
class SceneManager
{
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

public:
	/*���C���V�X�e��*/
	SceneManager();
	~SceneManager();
	void Update();
	void Render();

	// �V�[���̓o�^
	void addScene(const std::string& sceneName, std::unique_ptr<SceneBace> scene);

	// �N�����̃V�[���̐ݒ�
	void SetStartScene(const std::string& startSceneName);

	// �V�[���ύX�̗v��
	void RequestSceneChange(const std::string& changeSceneName);

	/*�擾/�ݒ�*/
	// �I�����߂̎擾
	bool isEnd() const { return m_IsEnd; }

private:
	// �V�[���̕ύX
	void ChangeScene();

};

