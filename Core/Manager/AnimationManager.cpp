/**
 * @file   AnimationManaager.h
 *
 * @brief  アニメーションの管理クラスのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/01/10
 */

#include "AnimationManager.h"

#include "../Common/Animation2D.h"
#include "../Common/Error.h"
#include "../Common/Camera.h"

/// <summary>
/// コンストラクト
/// </summary>
AnimationManager::AnimationManager()
	: m_animations         {}
	, m_pCurrentAnimation  { nullptr }
	, m_pRequestedAnimation{ nullptr }
	, m_CurrentName        {}
{
}

/// <summary>
/// デストラクタ
/// </summary>
AnimationManager::~AnimationManager()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="position">座標</param>
/// <param name="rotate">向き</param>
void AnimationManager::Update(const Transform2D& _transform)
{
	if (m_pCurrentAnimation)
	{
		// アニメーションの座標を更新
		m_pCurrentAnimation->SetTransform(_transform);

		// テクスチャの向きを調べる
		m_pCurrentAnimation->FlipTexture(_transform.GetAngle() < 270.f && _transform.GetAngle() > 90.f || _transform.GetAngle() < -90.f && _transform.GetAngle() > -270.f);
	}
}

/// <summary>
/// 描画処理
/// </summary>
void AnimationManager::Render()
{
	// シーンの変更要求があった場合はシーンの変更を行う
	if (m_pRequestedAnimation)
	{
		ChangeAnimation();
	}

	// 現在のシーンを描画
	if (m_pCurrentAnimation)
		m_pCurrentAnimation->Draw();
}

/// <summary>
/// 描画処理
/// </summary>
void AnimationManager::Render(const Camera& camera)
{
	// シーンの変更要求があった場合はシーンの変更を行う
	if (m_pRequestedAnimation)
	{
		ChangeAnimation();
	}

	// 現在のシーンを描画
	if (m_pCurrentAnimation)
		m_pCurrentAnimation->Render(camera);
}

/// <summary>
/// アニメーションの追加
/// </summary>
/// <param name="sceneName">登録アニメーションの名前</param>
/// <param name="animation">登録アニメーション</param>
void AnimationManager::addAnimation(const std::string& animationName, std::unique_ptr<Animation2D> animation)
{
	m_animations.emplace(animationName, std::move(animation));
}

/// <summary>
/// 開始アニメーションの設定
/// </summary>
/// <param name="startAnimationName">開始アニメーションの名前</param>
void AnimationManager::SetStartAnimation(const std::string& startAnimationName)
{
	RequestAnimationChange(startAnimationName);
	m_CurrentName = startAnimationName;
}

/// <summary>
/// アニメーション変更の要求
/// </summary>
/// <param name="changeAnimation">変更予定のアニメーション名</param>
void AnimationManager::RequestAnimationChange(const std::string& changeAnimation)
{
	if (m_animations.count(changeAnimation) == 0)
	{
		printError(changeAnimation + "アニメーションは登録されていません。");
		return;
	}

	if (m_pCurrentAnimation)
		nowTransform = m_pCurrentAnimation->GetTransform();

	m_CurrentName = changeAnimation;
	m_pRequestedAnimation = m_animations[changeAnimation].get();
}

/// <summary>
/// アニメーションの変更
/// </summary>
void AnimationManager::ChangeAnimation()
{
	if (!m_pRequestedAnimation)
		return;

	m_pCurrentAnimation = m_pRequestedAnimation;

	m_pCurrentAnimation->Initialize();
	m_pCurrentAnimation->ResetTime();
	m_pCurrentAnimation->SetTransform(nowTransform);

	m_pRequestedAnimation = nullptr;
}