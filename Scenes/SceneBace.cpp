/**
 * @file   SceneBace.cpp
 *
 * @brief  �V�[���̊��N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#include "SceneBace.h"

#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pSceneManager">�V�[���}�l�[�W���ւ̃|�C���^</param>
/// <param name="pResourceManager">���\�[�X�}�l�[�W���ւ̃|�C���^</param>
/// <param name="pControllerManager">�R���g���[���}�l�[�W���ւ̃|�C���^</param>
SceneBace::SceneBace(Position2D cameraPosition)
	: p_wsi              { &WSI::GetInstance()}
	, p_SceneManager     { &SceneManager::GetInstance()}
{
	m_camera = Camera(cameraPosition, p_wsi->ScreenRight(), p_wsi->ScreenBottom());
}

Camera& SceneBace::GetCamera()
{
	return m_camera;
}

/// <summary>
/// �V�[���̕ύX
/// </summary>
/// <param name="nextSceneName">�ύX��̃V�[����</param>
void SceneBace::ChangeScene(const std::string& nextSceneName)
{
	p_SceneManager->RequestSceneChange(nextSceneName);
}
