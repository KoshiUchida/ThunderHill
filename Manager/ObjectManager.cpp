/**
 * @file   ObjectManaager.cpp
 *
 * @brief  �I�u�W�F�N�g�̊Ǘ��N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#include "ObjectManager.h"

#include "../Objects/ObjectBace.h"

#include "../Common/Camera.h"
#include "../Common/Error.h"

#include <vector>

std::unique_ptr<ObjectManager> ObjectManager::s_ObjectManager = nullptr;

ObjectManager& ObjectManager::GetInstance()
{
	if (!s_ObjectManager)
		s_ObjectManager.reset(new ObjectManager);

	return *s_ObjectManager.get();
}

/// <summary>
/// Constructor
/// </summary>
ObjectManager::ObjectManager()
	: m_MaxLayer{}
{
}

/// <summary>
/// Destructor
/// </summary>
ObjectManager::~ObjectManager()
{
	Finalize();
}

/// <summary>
/// ����������
/// </summary>
void ObjectManager::Initialize()
{
	m_MaxLayer = 0;

	for (auto& element : m_Objects)
	{
		if (element.second->layer() > m_MaxLayer)
			m_MaxLayer = element.second->layer();
	}
}

/// <summary>
/// �X�V����
/// </summary>
void ObjectManager::Update()
{
	std::vector<std::string> destroyName;

	for (auto& element : m_Objects)
	{
		element.second->Update();
		if (element.second->isDestroy())
		{
			destroyName.push_back(element.first);
		}
	}

	for (std::string& name : destroyName)
	{
		m_Objects.erase(name);
	}
 	destroyName.clear();
}

/// <summary>
/// �`�揈��
/// </summary>
void ObjectManager::Render(const Camera& camera)
{
	for (int layer = 0; layer <= m_MaxLayer; ++layer)
	{
		for (auto& element : m_Objects)
		{
			if (element.second->layer() == layer)
				element.second->Render(camera);
		}
	}
}

/// <summary>
/// �I������
/// </summary>
void ObjectManager::Finalize()
{
	for (auto& element : m_Objects)
		element.second->Finalize();
	
	m_Objects.clear();
}

/// <summary>
/// �I�u�W�F�N�g�̒ǉ�
/// </summary>
void ObjectManager::AddObject(const std::string& objectName, std::unique_ptr<ObjectBace> object)
{
	object->Initialize();
	m_Objects.emplace(objectName, std::move(object));
}

/// <summary>
/// �I�u�W�F�N�g�ւ̃|�C���^�̎擾
/// </summary>
ObjectBace* ObjectManager::GetObjectPtr(const std::string& objectName)
{
	if (m_Objects.count(objectName) == 0)
	{
		//printError(objectName + "�@�͓o�^����Ă��܂���B");
		return nullptr;
	}

	return m_Objects.at(objectName).get();
}
