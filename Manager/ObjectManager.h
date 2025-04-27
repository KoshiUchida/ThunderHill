/**
 * @file   ObjectManaager.h
 *
 * @brief  オブジェクトの管理クラスのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#pragma once
#include <unordered_map>
#include <string>
#include <memory>

class ObjectBace;
class Camera;

/// <summary>
/// オブジェクトの管理クラス
/// </summary>
class ObjectManager
{
	/*使用する上での注意点
	* 
	* 必ず、初期化処理を含む４つの関数を対応する部分に記述すること
	* 
	* できる限り、オブジェクトの追加は初期化処理の前に行うこと
	*/
private:
	static std::unique_ptr<ObjectManager> s_ObjectManager;

public:
	static ObjectManager& GetInstance();

	// エイリアス宣言
	using ObjectCollection = std::unordered_map<std::string, std::unique_ptr<ObjectBace>>;

	// オブジェクトの集合
	ObjectCollection m_Objects;

	// レイヤーの最大優先度
	int m_MaxLayer;

	/*メインシステム*/
	ObjectManager();
public:
	~ObjectManager();
	void Initialize();
	void Update();
	void Render(const Camera& camera);
	void Finalize();

	void AddObject(const std::string& objectName, std::unique_ptr<ObjectBace> object);

	ObjectBace* GetObjectPtr(const std::string& objectName);
};
