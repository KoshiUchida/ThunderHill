/**
 * @file   Core.h
 *
 * @brief  システム中央制御のヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2024/11/11
 */

#pragma once
#include <memory>

class WSI;
class SceneManager;

/// <summary>
/// コアクラス
/// </summary>
class Core
{
private:
	// 終了
	bool m_IsEnd;

	// ウィンドウの設定
	WSI* mp_wsi;

	/*マネージャ関連*/
	// シーンマネージャ
	std::unique_ptr<SceneManager>      m_sceneManager;

public:
	/*メインシステム*/
	Core(WSI* pWSI);
	~Core();
	void Initialize();
	void Update();
	void Render();
	void Finalize();

	/*取得*/
	bool isEnd() const { return m_IsEnd; }
};

