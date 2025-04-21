/**
 * @file   ObjectManaager.h
 *
 * @brief  �I�u�W�F�N�g�̊Ǘ��N���X�̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/01/12
 */

#pragma once
#include <unordered_map>
#include <string>
#include <memory>

class ObjectBace;
class Camera;

/// <summary>
/// �I�u�W�F�N�g�̊Ǘ��N���X
/// </summary>
class ObjectManager
{
	/*�g�p�����ł̒��ӓ_
	* 
	* �K���A�������������܂ނS�̊֐���Ή����镔���ɋL�q���邱��
	* 
	* �ł������A�I�u�W�F�N�g�̒ǉ��͏����������̑O�ɍs������
	*/
private:
	// �G�C���A�X�錾
	using ObjectCollection = std::unordered_map<std::string, std::unique_ptr<ObjectBace>>;

	// �I�u�W�F�N�g�̏W��
	ObjectCollection m_Objects;

	// ���C���[�̍ő�D��x
	int m_MaxLayer;

public:
	/*���C���V�X�e��*/
	ObjectManager();
	~ObjectManager();
	void Initialize();
	void Update();
	void Render(const Camera& camera);
	void Finalize();

	void AddObject(const std::string& objectName, std::unique_ptr<ObjectBace> object);

	ObjectBace* GetObjectPtr(const std::string& objectName);
};
