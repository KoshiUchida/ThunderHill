/**
 * @file   SceneManaager.h
 *
 * @brief  シーンの管理クラスのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "ObjectManager.h"

class SceneBace;

/// <summary>
/// シーン管理クラス
/// </summary>
class SceneManager final
{
private:
	static std::unique_ptr<SceneManager> s_SceneManager;

public:
	static SceneManager& GetInstance();

	void Clear();

private:
	// エイリアス宣言
	using SceneCollection = std::unordered_map<std::string, std::unique_ptr<SceneBace>>;

	// シーンの集合体
	SceneCollection m_scenes;

	// 現在のシーン
	SceneBace* m_pCurrentScene;
	// 変更要求のあったシーン
	SceneBace* m_pRequestedScene;

	// 終了命令
	bool m_IsEnd;

	// ゲームマネージャへのポインタ
	ObjectManager* p_ObjectManager;

	/*メインシステム*/
	SceneManager();

public:
	~SceneManager();
	void Update();
	void Render();

	// シーン変更の要求
	void RequestSceneChange(const std::string& changeSceneName);

	/*取得/設定*/
	// 終了命令の取得
	bool isEnd() const { return m_IsEnd; }

private:
	// シーンの登録
	void SetScene();

	// 起動時のシーンの設定
	void SetStartScene(const std::string& startSceneName);

	// シーンの変更
	void ChangeScene();

};

