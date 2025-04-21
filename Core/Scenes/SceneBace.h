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
class ControllerManager;

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

	// �R���g���[���}�l�[�W���ւ̃|�C���^
	ControllerManager* mp_ControllerManager;

	// �I�u�W�F�N�g�}�l�[�W���ւ̃|�C���^
	ObjectManager m_ObjectManager;

public:
	/*���C���V�X�e��*/
	SceneBace(WSI* pWSI, SceneManager* pSceneManager, ControllerManager* pControllerManager, Position2D cameraPosition = Position2D(0.f, 0.f));
	virtual ~SceneBace() = default;
	virtual void Initialize() = 0;
	virtual void Update()     = 0;
	virtual void Render()     = 0;
	virtual void Finalize()   = 0;

protected:
	/*��������*/
	// �V�[���̕ύX
	void ChangeScene(const std::string& nextSceneName);

	// ���L�f�[�^�̓ǂݍ���
	void ReadSharedData(const std::string& key, int*         pValue) const;
	void ReadSharedData(const std::string& key, float*       pValue) const;
	void ReadSharedData(const std::string& key, std::string* pValue) const;

	// ���L�f�[�^�ւ̏�������
	void WriteSharedData(const std::string& key, int         value);
	void WriteSharedData(const std::string& key, float       value);
	void WriteSharedData(const std::string& key, std::string value);
};

