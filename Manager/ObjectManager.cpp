/**
 * @file   ObjectManaager.cpp
 *
 * @brief  オブジェクトの管理クラスのソースファイル
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
/// 初期化処理
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
/// 更新処理
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
/// 描画処理
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
/// 終了処理
/// </summary>
void ObjectManager::Finalize()
{
	for (auto& element : m_Objects)
		element.second->Finalize();
	
	m_Objects.clear();
}

/// <summary>
/// オブジェクトの追加
/// </summary>
void ObjectManager::AddObject(const std::string& objectName, std::unique_ptr<ObjectBace> object)
{
	object->Initialize();
	m_Objects.emplace(objectName, std::move(object));
}

/// <summary>
/// オブジェクトへのポインタの取得
/// </summary>
ObjectBace* ObjectManager::GetObjectPtr(const std::string& objectName)
{
	if (m_Objects.count(objectName) == 0)
	{
		//printError(objectName + "　は登録されていません。");
		return nullptr;
	}

	return m_Objects.at(objectName).get();
}
