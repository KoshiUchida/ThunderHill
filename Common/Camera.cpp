/**
 * @file   Camera.h
 *
 * @brief  カメラのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/01/15
 */

#include "Camera.h"

Camera::Camera() = default;

/// <summary>
/// Constractor
/// </summary>
Camera::Camera(Position2D position, int screenWidth, int screenHeight)
	: m_Position{ position }
	, m_Screen  { screenWidth, screenHeight }
{
}

/// <summary>
/// Destructor
/// </summary>
Camera::~Camera() = default;

/// <summary>
/// ワールド座標をスクリーン座標に変換
/// </summary>
void Camera::ConvertWorldToScreenPosition(int* x, int* y)
{
	(*x) = static_cast<int>(m_Screen.width / 2.f - m_Position.x() + static_cast<float>(*x));
	(*y) = static_cast<int>(m_Screen.height / 2.f - m_Position.y() + static_cast<float>(*y));
}

Position2D Camera::ConvertWorldToScreenPosition(const Position2D& _position) const
{
	float x = m_Screen.width  / 2.f - m_Position.x() + _position.x();
	float y = m_Screen.height / 2.f - m_Position.y() + _position.y();
	return Position2D(x, y);
}

/// <summary>
/// スクリーン座標をワールド座標に変換
/// </summary>
Position2D Camera::ConvertScreenToWorldPosition(const Position2D& _position) const
{
	float x = static_cast<float>(m_Screen.width ) / (-2.f) + m_Position.x() + _position.x();
	float y = static_cast<float>(m_Screen.height) / (-2.f) + m_Position.y() + _position.y();
	return Position2D(x, y);
}
