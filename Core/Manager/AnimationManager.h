/**
 * @file   AnimationManaager.h
 *
 * @brief  アニメーションの管理クラスのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2024/11/04
 */

#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <DxLib.h>
#include "../Common/Geometry2D.h"

class Animation2D;
class Camera;

/// <summary>
/// アニメーションの管理クラス
/// </summary>
class AnimationManager
{
private:
	// エイリアス宣言
	using AnimationCollection = std::unordered_map<std::string, std::unique_ptr<Animation2D>>;

	// アニメーションの集合
	AnimationCollection m_animations;

	// 現在のアニメーション
	Animation2D* m_pCurrentAnimation;
	// 変更要求のあったアニメーション
	Animation2D* m_pRequestedAnimation;

	// 現在のアニメーションの名前
	std::string m_CurrentName;

	// 現在のトランスフォーム
	Transform2D nowTransform;

public:
	/*メインシステム*/
	AnimationManager();
	~AnimationManager();
	void Update(const Transform2D& _transform);
	void Render();
	void Render(const Camera& camera);

	// アニメーションの登録
	void addAnimation(const std::string& animationName, std::unique_ptr<Animation2D> animation);

	// スタートのアニメーションの設定
	void SetStartAnimation(const std::string& startAnimationName);

	// アニメーション変更の要求
	void RequestAnimationChange(const std::string& changeAnimation);

private:
	// アニメーションの変更
	void ChangeAnimation();

public:
	/*取得*/
	std::string GetCurrentName() { return m_CurrentName; }
};

