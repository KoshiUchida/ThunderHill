/**
 * @file   Camera.h
 *
 * @brief  カメラのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/01/15
 */

#pragma once
#include "Geometry2D.h"

/// <summary>
/// カメラクラス
/// </summary>
class Camera
{
private:
	/*Common*/
	// Camera Position
	Position2D m_Position;

	// Camera Size
	struct Screen
	{
		int width;
		int height;
	} m_Screen;

public:
	/*Main System*/
	Camera();
	Camera(Position2D position, int screenWidth, int screenHeight);
	~Camera();

	/*Sub System*/
	void       ConvertWorldToScreenPosition(int* _x, int* _y);
	Position2D ConvertWorldToScreenPosition(const Position2D& _position) const;

	Position2D ConvertScreenToWorldPosition(const Position2D& _position) const;

	/*Setter*/
	void SetPosition(const Position2D& _position) { m_Position = _position; }

	/*Getter*/
	Position2D GetPosition()   const { return m_Position; }
	Position2D GetScreenSize() const { return Position2D(static_cast<float>(m_Screen.width), static_cast<float>(m_Screen.height)); }
	float x()      const { return m_Position.x(); }
	float y()      const { return m_Position.y(); }
	float width()  const { return static_cast<float>(m_Screen.width); }
	float height() const { return static_cast<float>(m_Screen.height); }
};
