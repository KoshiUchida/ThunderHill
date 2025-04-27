/**
 * @file   SceneBace.h
 *
 * @brief  �V�[���̊��N���X�̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/01/12
 */

#pragma once

#include <string>
#include "../Common/Camera.h"
#include "../Manager/ObjectManager.h"

class WSI;
class SceneManager;

/// <summary>
/// �V�[���̊��N���X
/// </summary>
class SceneBace
{
protected:
	// �J����
	Camera m_camera;

	// �E�C���h�E�̐ݒ�ւ̃|�C���^
	WSI* mp_wsi;

	// �V�[���}�l�[�W���ւ̃|�C���^
	SceneManager* mp_SceneManager;

	// �I�u�W�F�N�g�}�l�[�W���ւ̃|�C���^
	ObjectManager m_ObjectManager;

public:
	/*���C���V�X�e��*/
	SceneBace(WSI* pWSI, SceneManager* pSceneManager, Position2D cameraPosition = Position2D(0.f, 0.f));
	virtual ~SceneBace() = default;
	virtual void Initialize() = 0;
	virtual void Update()     = 0;
	virtual void Render()     = 0;
	virtual void Finalize()   = 0;

protected:
	/*��������*/
	// �V�[���̕ύX
	void ChangeScene(const std::string& nextSceneName);
};

