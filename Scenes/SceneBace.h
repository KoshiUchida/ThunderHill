/**
 * @file   SceneBace.h
 *
 * @brief  シーンの基底クラスのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#pragma once

#include <string>
#include "../Common/Camera.h"
#include "../WindowSettingItems.h"

class SceneManager;

/// <summary>
/// シーンの基底クラス
/// </summary>
class SceneBace
{
protected:
	// カメラ
	Camera m_camera;

	// ウインドウの設定へのポインタ
	WSI* p_wsi;

	// シーンマネージャへのポインタ
	SceneManager* p_SceneManager;

public:
	/*メインシステム*/
	SceneBace(Position2D cameraPosition = Position2D(0.f, 0.f));
	virtual ~SceneBace() = default;
	virtual void Initialize() = 0;
	virtual void Update()     = 0;
	virtual void Render()     = 0;
	virtual void Finalize()   = 0;

	Camera& GetCamera();

protected:
	/*内部実装*/
	// シーンの変更
	void ChangeScene(const std::string& nextSceneName);
};

