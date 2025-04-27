/**
 * @file   Sprite2D.cpp
 *
 * @brief  スプライトのソースファイル
 *
 * @author CatCode
 *
 * @date   2024/01/10
 */

#include "Sprite2D.h"

#include <DxLib.h>
#include "../Common/Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
Sprite2D::Sprite2D(const int texture, const float exRate)
	: m_Transform    {}
	, m_TextureHandle{ texture }
	, m_Page         {}
	, m_exRate       { exRate }
	, m_TileWidth    {}
	, m_TileHeight   {}
	, m_FlipFlag     {}
{
	// テクスチャの大きさを自動に取得
	GetGraphSize(m_TextureHandle, &m_TileWidth, &m_TileHeight);
}

/// <summary>
/// コンストラクタ
/// </summary>
Sprite2D::Sprite2D(const int texture, const int tileWidth, const int tileHeight, const float exRate)
	: m_Transform      {}
	, m_TextureHandle  { texture }
	, m_Page           {}
	, m_exRate         { exRate }
	, m_TileWidth      { tileWidth }
	, m_TileHeight     { tileHeight }
	, m_FlipFlag       {}
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Sprite2D::Initialize(const Transform2D _transform)
{
	m_Transform = _transform;
}

/// <summary>
/// 描画処理
/// </summary>
void Sprite2D::Draw()
{
	DrawRectRotaGraphF
	(
		m_Transform.GetPositionX(), m_Transform.GetPositionY(),
		m_Page % 10 * m_TileWidth, m_Page / 10 * m_TileHeight,
		m_TileWidth, m_TileHeight,
		m_exRate, m_Transform.GetAngleRAD(),
		m_TextureHandle, TRUE, m_FlipFlag
	);
}

/// <summary>
/// 描画処理
/// </summary>
void Sprite2D::Draw(const Camera& camera)
{
	Position2D ScreenPosition = camera.ConvertWorldToScreenPosition(m_Transform.GetPosition());
	DrawRectRotaGraph
	(
		static_cast<int>(ScreenPosition.x()), static_cast<int>(ScreenPosition.y()),
		m_Page % 10 * m_TileWidth, m_Page / 10 * m_TileHeight,
		m_TileWidth, m_TileHeight,
		m_exRate, m_Transform.GetAngleRAD(),
		m_TextureHandle, TRUE, 0, m_FlipFlag
	);
}
