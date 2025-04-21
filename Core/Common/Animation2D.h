/**
 * @file   Animation.h
 *
 * @brief  アニメーションのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2024/12/04
 */

#pragma once
#include "Sprite2D.h"
#include <vector>
#include <string>

class Camera;

/// <summary>
/// アニメーションデータの最小構造体
/// </summary>
struct AnimationStep
{
	int time;
	int number;
};

/// <summary>
/// アニメーションクラス
/// </summary>
class Animation2D
	: public Sprite2D
{
private:
	// アニメーションデータ
	std::vector<AnimationStep> m_AnimationData;

	// 現在の時間
	int m_Time;

public:
	/*メインシステム*/
	Animation2D(const std::string filename, const int texture, const int chipWidth, const int chipHeight, const float exRate = 1.f);
	~Animation2D();
	void Render();
	void Render(const Camera& camera);
	void ResetTime() { m_Time = 0; }
};

