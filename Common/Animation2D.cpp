/**
 * @file   Animation2D.cpp
 *
 * @brief  アニメーションのソースファイル
 *
 * @author CatCode
 *
 * @date   2024/12/04
 */

#include "Animation2D.h"

#include "FileIO.h"
#include "Camera.h"
//#include "../Screen.h"

/// <summary>
/// コンストラクタ
/// </summary>
Animation2D::Animation2D(const std::string filename, const int texture, const int chipWidth, const int chipHeight, const float exRate)
	: Sprite2D(texture, chipWidth, chipHeight, exRate)
	, m_Time{}
{
	// アニメーションデータの読み込み
	m_AnimationData = ReadAnimation(filename);

	// このプロジェクトのランタイムに合わせる
	for (int i = 0; i < m_AnimationData.size(); i++)
	{
		//m_AnimationData[i].time /= scr::RunTime;
	}
}

/// <summary>
/// デストラクタ
/// </summary>
Animation2D::~Animation2D()
{
	m_AnimationData.clear();
}

/// <summary>
/// 描画処理
/// </summary>
void Animation2D::Render()
{
	// 切り替えタイムであるかを確認
	for (int i = 0; i < this->m_AnimationData.size(); i++)
	{
		if (this->m_Time == this->m_AnimationData[i].time)
			this->m_Page = this->m_AnimationData[i].number;
	}

	// スプライトの描画
	this->Draw();

	// タイムの更新
	this->m_Time++;

	// タイムがアニメーションの最大の切り替えタイムの設定を超えたときに０にもどす
	if (this->m_Time > this->m_AnimationData[this->m_AnimationData.size() - 1].time)
	{
		this->m_Time = 0;
	}
}

/// <summary>
/// 描画処理
/// </summary>
void Animation2D::Render(const Camera& camera)
{
	// 切り替えタイムであるかを確認
	for (int i = 0; i < this->m_AnimationData.size(); i++)
	{
		if (this->m_Time == this->m_AnimationData[i].time)
			this->m_Page = this->m_AnimationData[i].number;
	}

	// スプライトの描画
	this->Draw(camera);

	// タイムの更新
	this->m_Time++;

	// タイムがアニメーションの最大の切り替えタイムの設定を超えたときに０にもどす
	if (this->m_Time > this->m_AnimationData[this->m_AnimationData.size() - 1].time)
	{
		this->m_Time = 0;
	}
}
