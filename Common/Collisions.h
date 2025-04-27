/**
 * @file   Collisions.h
 *
 * @brief  コリジョンたちのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/01/03
 */

#pragma once
#include "Geometry2D.h"

namespace Collisions
{
	struct Box
	{
		float left;
		float right;
		float top;
		float bottom;
	};

	class BoxCollision
	{
	private:
		Position2D m_Position;
		float m_Width;
		float m_Height;

		Box m_Box;
	public:
		enum class TOUCH_AREA
		{
			NONE,
			UP,
			DOWN,
			LEFT,
			RIGHT
		};

		BoxCollision(const Position2D& position, float width, float height);
		~BoxCollision() = default;
		bool Handling(const BoxCollision& _collider);

		// Setter
		void SetPosition(const Position2D& position);
		void SetPosition(float x, float y);

		// Getter
		Position2D GetPosition() const { return m_Position; }
		Box        GetBox()      const { return m_Box; }
		float      GetWidth()    const { return m_Width; }
		float      GetHeight()   const { return m_Height; }

		// Addtion
		void AddPosition(const Position2D& _position);
	};

	class CircleCollision
	{
	private:
		Position2D m_Position;
		float      m_Range;

	public:
		CircleCollision(const Position2D& position, float range);
		~CircleCollision() = default;

		// Setter
		void SetPosition(const Position2D& position) { m_Position = position; }
		void SetPosition(float x, float y)           { m_Position = Position2D(x, y); }
		void SetRange   (float range)                { m_Range = range; }

		// Getter
		Position2D GetPosition() const { return m_Position; }
		float      GetRange()    const { return m_Range; }
	};

	/// <summary>
	/// BoxCollision同士のあたり判定
	/// </summary>
	/// <param name="box1">基準となるBoxCollision</param>
	/// <param name="box2">判定対象のBoxCollision</param>
	/// <param name="isLine">せ線を含めるか</param>
	/// <returns>true = 当たっている false = 当たっていない</returns>
	bool Detection(const BoxCollision& box1, const BoxCollision& box2, bool isLine = true);

	/// <summary>
	/// 円と点のあたり判定
	/// </summary>
	/// <param name="point1">円の座標</param>
	/// <param name="range">円の半径</param>
	/// <param name="point2">点の座標</param>
	/// <returns>true = 当たっている false = 当たっていない</returns>
	bool Detection(const Position2D& point1, float range, const Position2D& point2);

	/// <summary>
	/// BoxCollisionと点のあたり判定
	/// </summary>
	/// <param name="box">基準となるコライダー</param>
	/// <param name="point">判定する点</param>
	/// <returns>true = 当たっている false = 当たっていない</returns>
	bool Detection(const BoxCollision& box, const Position2D& point);

	/// <summary>
	/// 四角と点のあたり判定
	/// </summary>
	/// <param name="x1">四角の最左頂点の座標X</param>
	/// <param name="y1">四角の最左頂点の座標Y</param>
	/// <param name="x2">四角の最右低点の座標X</param>
	/// <param name="y2">四角の最右低点の座標Y</param>
	/// <param name="point">点の座標</param>
	/// <returns>true = 当たっている false = 当たっていない</returns>
	bool Detection(float x1, float y1, float x2, float y2, const Position2D& point);

	/// <summary>
	/// CircleCollisionとBoxCollisionのあたり判定
	/// </summary>
	/// <param name="circle">基準となるCircleCollision</param>
	/// <param name="box">判定対象のBoxCollision</param>
	/// <returns></returns>
	bool Detection(const CircleCollision& circle, const BoxCollision& box);

	bool Detection(const CircleCollision& circle, const CircleCollision& box);
	
	/// <summary>
	/// BoxCollision同士の接触辺
	/// </summary>
	/// <param name="box1">基準となるBoxCollision</param>
	/// <param name="box2">判定対象のBoxCollision</param>
	/// <returns>接触辺もしくは接触していない</returns>
	BoxCollision::TOUCH_AREA DetectionTouchArea(const BoxCollision& box1, const BoxCollision& box2);
};

