/**
 * @file   SceneBace.h
 *
 * @brief  シーンの基底クラスのヘッダファイル
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
/// シーンの基底クラス
/// </summary>
class SceneBace
{
protected:
	// カメラ
	Camera m_camera;

	// ウインドウの設定へのポインタ
	WSI* mp_wsi;

	// シーンマネージャへのポインタ
	SceneManager* mp_SceneManager;

	// コントローラマネージャへのポインタ
	ControllerManager* mp_ControllerManager;

	// オブジェクトマネージャへのポインタ
	ObjectManager m_ObjectManager;

public:
	/*メインシステム*/
	SceneBace(WSI* pWSI, SceneManager* pSceneManager, ControllerManager* pControllerManager, Position2D cameraPosition = Position2D(0.f, 0.f));
	virtual ~SceneBace() = default;
	virtual void Initialize() = 0;
	virtual void Update()     = 0;
	virtual void Render()     = 0;
	virtual void Finalize()   = 0;

protected:
	/*内部実装*/
	// シーンの変更
	void ChangeScene(const std::string& nextSceneName);

	// 共有データの読み込み
	void ReadSharedData(const std::string& key, int*         pValue) const;
	void ReadSharedData(const std::string& key, float*       pValue) const;
	void ReadSharedData(const std::string& key, std::string* pValue) const;

	// 共有データへの書き込み
	void WriteSharedData(const std::string& key, int         value);
	void WriteSharedData(const std::string& key, float       value);
	void WriteSharedData(const std::string& key, std::string value);
};

