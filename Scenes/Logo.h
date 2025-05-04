/**
 * @file   Logo.h
 *
 * @brief  ロゴシーンのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/05/04
 */

#pragma once
#include "SceneBace.h"
#include <memory>

class Sprite2D;

/// <summary>
/// ロゴシーン
/// </summary>
class Logo :
    public SceneBace
{
private:
	std::unique_ptr<Sprite2D> ms_Logo;

	int m_Time;

	static constexpr int SceneChangeTime{ 63 };

	// ロゴの透明度
	int m_LogoAlpha;

	// 透明度が上がるかどうか
	bool m_IsUpAlpha;


public:
	// メインシステム
	Logo();
	~Logo();
	void Initialize() override;
	void Update()     override;
	void Render()     override;
	void Finalize()   override;
};

