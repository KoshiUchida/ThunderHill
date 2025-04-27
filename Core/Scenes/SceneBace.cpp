/**
 * @file   SceneBace.cpp
 *
 * @brief  �V�[���̊��N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/01/12
 */

#include "SceneBace.h"

#include "../../WindowSettingItems.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pSceneManager">�V�[���}�l�[�W���ւ̃|�C���^</param>
/// <param name="pResourceManager">���\�[�X�}�l�[�W���ւ̃|�C���^</param>
/// <param name="pControllerManager">�R���g���[���}�l�[�W���ւ̃|�C���^</param>
SceneBace::SceneBace(WSI* pWSI, SceneManager* pSceneManager,  Position2D cameraPosition)
	: mp_wsi              { pWSI }
	, mp_SceneManager     { pSceneManager }
	, m_camera            { cameraPosition, pWSI->ScreenWidth, pWSI->ScreenHeight }
{
}

/// <summary>
/// �V�[���̕ύX
/// </summary>
/// <param name="nextSceneName">�ύX��̃V�[����</param>
void SceneBace::ChangeScene(const std::string& nextSceneName)
{
	mp_SceneManager->RequestSceneChange(nextSceneName);
}
