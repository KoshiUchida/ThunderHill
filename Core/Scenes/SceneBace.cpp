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
#include "../Manager/ControllerManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pSceneManager">�V�[���}�l�[�W���ւ̃|�C���^</param>
/// <param name="pResourceManager">���\�[�X�}�l�[�W���ւ̃|�C���^</param>
/// <param name="pControllerManager">�R���g���[���}�l�[�W���ւ̃|�C���^</param>
SceneBace::SceneBace(WSI* pWSI, SceneManager* pSceneManager, ControllerManager* pControllerManager, Position2D cameraPosition)
	: mp_wsi              { pWSI }
	, mp_SceneManager     { pSceneManager }
	, mp_ControllerManager{ pControllerManager }
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

/// <summary>
/// ���L�f�[�^�̓ǂݍ���
/// </summary>
/// <param name="key">���L�f�[�^�L�[</param>
/// <param name="pValue">�ǂݍ��ݐ�</param>
void SceneBace::ReadSharedData(const std::string& key, int* pValue) const
{
	*pValue = std::stoi(mp_SceneManager->GetShareData(key));
}

void SceneBace::ReadSharedData(const std::string& key, float* pValue) const
{
	*pValue = std::stof(mp_SceneManager->GetShareData(key));
}

void SceneBace::ReadSharedData(const std::string& key, std::string* pValue) const
{
	*pValue = mp_SceneManager->GetShareData(key);
}

/// <summary>
/// ���L�f�[�^�ւ̏�������
/// </summary>
void SceneBace::WriteSharedData(const std::string& key, int value)
{
	mp_SceneManager->SetSharedData(key, std::to_string(value));
}

void SceneBace::WriteSharedData(const std::string& key, float value)
{
	mp_SceneManager->SetSharedData(key, std::to_string(value));
}

void SceneBace::WriteSharedData(const std::string& key, std::string value)
{
	mp_SceneManager->SetSharedData(key, value);
}
