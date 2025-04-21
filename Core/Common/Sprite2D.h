/**
 * @file   Sprite2D.h
 *
 * @brief  スプライトのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2024/12/04
 */

#pragma once
#include "Geometry2D.h"

class Camera;

/// <summary>
/// 二次元スプライトクラス
/// </summary>
class Sprite2D
{
protected:
	// 座標
	Transform2D m_Transform;

	// テクスチャのハンドル
	int m_TextureHandle;

	// 表示するページ
	int m_Page;

	// 拡大率
	float m_exRate;

	// 切り取りサイズ
	int m_TileWidth;
	int m_TileHeight;

	// 反転フラッグ
	bool m_FlipFlag;

public:
	/*メインシステム*/
	Sprite2D(const int texture, const float exRate = 1.f);
	Sprite2D(const int texture, const int tileWidth, const int tileHeight, const float exRate = 1.f);
	virtual ~Sprite2D() = default;
	virtual void Initialize(const Transform2D _transform = Transform2D(Position2D(0.f, 0.f), 0.f));
	void Draw();
	void Draw(const Camera& camera);

	// テクスチャの反転
	void FlipTexture()                { m_FlipFlag = !m_FlipFlag; }
	void FlipTexture(const bool flip) { m_FlipFlag = flip; }

	/*設定/取得*/
	void SetTransform(const Transform2D _transform) { m_Transform = _transform; }
	void SetPosition (const Position2D _position)   { m_Transform = _position; }
	void SetAngle    (const float& _angle)          { m_Transform = _angle; }
	void SetPage     (const int number)             { m_Page = number; }

	Transform2D GetTransform() const { return m_Transform; }
};

