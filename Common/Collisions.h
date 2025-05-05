/**
 * @file   Collisions.h
 *
 * @brief  コリジョンたちのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/05/05
 */

#pragma once
#include "Geometry2D.h"
#include <vector>

namespace Collisions
{
	/// <summary>
	/// 線構造体
	/// </summary>
	struct Line
	{
		Position2D start;
		Position2D end;
	};

	/// <summary>
	/// 箱構造体
	/// </summary>
	struct Box
	{
		float left;
		float right;
		float top;
		float bottom;

	public:
		Box() noexcept = default;

		Box(Line line) noexcept :
			left{},
			right{},
			top{},
			bottom{}
		{
			if (line.start.x() < line.end.x())
			{
				left = line.start.x();
				right = line.end.x();
			}
			else
			{
				left = line.end.x();
				right = line.start.x();
			}

			if (line.start.y() < line.end.y())
			{
				left = line.start.y();
				right = line.end.y();
			}
			else
			{
				left = line.end.y();
				right = line.start.y();
			}
		}
	};

	/// <summary>
	/// 箱コライダー
	/// </summary>
	class BoxCollider
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

		BoxCollider(const Position2D& position, float width, float height);
		~BoxCollider() = default;
		bool Handling(const BoxCollider& _collider);

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

	/// <summary>
	/// 円コライダー
	/// </summary>
	class CircleCollider
	{
	private:
		Position2D m_Position;
		float      m_Range;

	public:
		CircleCollider(const Position2D& position, float range);
		~CircleCollider() = default;

		// Setter
		void SetPosition(const Position2D& position) { m_Position = position; }
		void SetPosition(float x, float y)           { m_Position = Position2D(x, y); }
		void SetRange   (float range)                { m_Range = range; }

		// Getter
		Position2D GetPosition() const { return m_Position; }
		float      GetRange()    const { return m_Range; }
	};

	class LineCollider
	{
	private:
		Line m_Line;

	public:
		LineCollider(const Position2D& startPos, const Position2D& endPos) noexcept;
		~LineCollider() noexcept;

		// 設定
		void SetStartPosition(const Position2D& pos);
		void SetEndPosition(const Position2D& pos);

		// 取得
		Line GetLine() const
		{
			return m_Line;
		}
		Position2D GetStartPosition() const
		{
			return m_Line.start;
		}
		Position2D GetEndPosition() const
		{
			return m_Line.end;
		}
	};

	/// <summary>
	/// 連線コライダー
	/// </summary>
	class LinesCollider
	{
	private:
		std::vector<Position2D> m_Positions;

		CircleCollider m_ActiveCircle;

	public:
		LinesCollider(const std::vector<Position2D>& positions) noexcept;
		~LinesCollider() noexcept;

	private:
		void CreateActiveCircle();

	public:
		// 取得
		std::vector<Position2D>& GetPositions();
		std::vector<Position2D>* GetPositionsPointer();
		CircleCollider& GetActiveCircle();
	};

	/// <summary>
	/// BoxCollision同士のあたり判定
	/// </summary>
	/// <param name="box1">基準となるBoxCollision</param>
	/// <param name="box2">判定対象のBoxCollision</param>
	/// <param name="isLine">せ線を含めるか</param>
	/// <returns>true = 当たっている false = 当たっていない</returns>
	bool Detection(const BoxCollider& box1, const BoxCollider& box2, bool isLine = true);

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
	bool Detection(const BoxCollider& box, const Position2D& point);

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
	bool Detection(const CircleCollider& circle, const BoxCollider& box);

	/// <summary>
	/// 円コライダー同士の重なり判定
	/// </summary>
	bool Detection(const CircleCollider& circle1, const CircleCollider& circle2);

	/// <summary>
	/// 線コライダー同士の重なり判定
	/// </summary>
	bool Detection(const LineCollider& line1, const LineCollider& line2);

	/// <summary>
	/// 連線コライダーと線コライダーの重なり判定
	/// </summary>
	bool Detection(LinesCollider& lines, const LineCollider& line);

	/// <summary>
	/// 連線コライダーと箱コライダーの重なり判定
	/// </summary>
	bool Detection(LinesCollider& lines, const BoxCollider& box);
	
	/// <summary>
	/// BoxCollision同士の接触辺
	/// </summary>
	/// <param name="box1">基準となるBoxCollision</param>
	/// <param name="box2">判定対象のBoxCollision</param>
	/// <returns>接触辺もしくは接触していない</returns>
	BoxCollider::TOUCH_AREA DetectionTouchArea(const BoxCollider& box1, const BoxCollider& box2);
};

