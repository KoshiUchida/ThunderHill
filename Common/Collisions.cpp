/**
 * @file   Collisions.cpp
 *
 * @brief  コリジョンたちのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/05/05
 */

#include "Collisions.h"
#include "iostream"
#include <DxLib.h>

/*BoxCollision*/

/// <summary>
/// コンストラクタ
/// </summary>
Collisions::BoxCollider::BoxCollider(float width, float height) noexcept :
	m_Position{},
	m_Width{ width },
	m_Height{ height },
	m_Box{}
{
	m_Box.left = m_Position.x() - (m_Width / 2.f);
	m_Box.right = m_Position.x() + (m_Width / 2.f);
	m_Box.top = m_Position.y() - (m_Height / 2.f);
	m_Box.bottom = m_Position.y() + (m_Height / 2.f);
}

/// <summary>
/// コンストラクタ
/// </summary>
Collisions::BoxCollider::BoxCollider(const Position2D& position, float width, float height) noexcept
	: m_Position { position }
	, m_Width { width }
	, m_Height{ height }
	, m_Box{}
{
	m_Box.left   = m_Position.x() - (m_Width  / 2.f);
	m_Box.right  = m_Position.x() + (m_Width  / 2.f);
	m_Box.top    = m_Position.y() - (m_Height / 2.f);
	m_Box.bottom = m_Position.y() + (m_Height / 2.f);
}

Collisions::BoxCollider::~BoxCollider() noexcept = default;

bool Collisions::BoxCollider::Handling(const BoxCollider& _collider)
{

	if (!Collisions::Detection(*this, _collider)) {
		return false;
	}

	switch (DetectionTouchArea(*this, _collider))
	{
	case TOUCH_AREA::UP:
		m_Position.SetY(_collider.GetBox().bottom + this->GetHeight() / 2.f);
		break;
	case TOUCH_AREA::DOWN:
		m_Position.SetY(_collider.GetBox().top - this->GetHeight() / 2.f);
		break;
	case TOUCH_AREA::LEFT:
		m_Position.SetX(_collider.GetBox().right + this->GetWidth() / 2.f);
		break;
	case TOUCH_AREA::RIGHT:
		m_Position.SetX(_collider.GetBox().left - this->GetWidth() / 2.f);
		break;
	}

	return true;
}

/// <summary>
/// 座標の設定
/// </summary>
void Collisions::BoxCollider::SetPosition(const Position2D& position)
{
	m_Position = position;

	m_Box.left = m_Position.x() - (m_Width / 2.f);
	m_Box.right = m_Position.x() + (m_Width / 2.f);
	m_Box.top = m_Position.y() - (m_Height / 2.f);
	m_Box.bottom = m_Position.y() + (m_Height / 2.f);
}

/// <summary>
/// 座標の設定
/// </summary>
void Collisions::BoxCollider::SetPosition(float x, float y)
{
	SetPosition(Position2D(x, y));
}

void Collisions::BoxCollider::AddPosition(const Position2D& _position)
{
	m_Position += _position;

	m_Box.left = m_Position.x() - (m_Width / 2.f);
	m_Box.right = m_Position.x() + (m_Width / 2.f);
	m_Box.top = m_Position.y() - (m_Height / 2.f);
	m_Box.bottom = m_Position.y() + (m_Height / 2.f);
}

/*CircleCollision*/

/// <summary>
/// コンストラクタ
/// </summary>
Collisions::CircleCollider::CircleCollider(const Position2D& position, float range)
	: m_Position{ position }
	, m_Range{ range }
{
}

/*Detections*/

bool Collisions::Detection(const BoxCollider& box1, const BoxCollider& box2, bool isLine)
{
	// 衝突範囲の計算
	Box box = box1.GetBox();
	float b2_width  = (box2.GetBox().right  - box2.GetBox().left) / 2.f;
	float b2_height = (box2.GetBox().bottom - box2.GetBox().top ) / 2.f;
	box.left   -= b2_width;
	box.right  += b2_width;
	box.top    -= b2_height;
	box.bottom += b2_height;

	// 対象の座標を取得
	Position2D b2_point = box2.GetPosition();

	// 調べる
	if (isLine)
	{
		if (
			b2_point.x() >= box.left &&
			b2_point.x() <= box.right &&
			b2_point.y() >= box.top &&
			b2_point.y() <= box.bottom
			)
		{
			return true;
		}
	}
	else
	{
		if (
			b2_point.x() > box.left &&
			b2_point.x() < box.right &&
			b2_point.y() > box.top &&
			b2_point.y() < box.bottom
			)
		{
			return true;
		}
	}

	return false;
}

bool Collisions::Detection(const Position2D& point1, float range, const Position2D& point2)
{
	float diff = point1.MeasureUpTo(point2);

	if (diff <= range)
	{
		return true;
	}
	return false;
}

bool Collisions::Detection(const BoxCollider& box, const Position2D& point)
{
	if (
		point.x() >= box.GetBox().left && point.x() <= box.GetBox().right &&
		point.y() >= box.GetBox().top && point.y() <= box.GetBox().bottom
		)
	{
		return true;
	}
	return false;
}

bool Collisions::Detection(float x1, float y1, float x2, float y2, const Position2D& point)
{
	if (
		point.x() >= x1 && point.x() <= x2 &&
		point.y() >= y1 && point.y() <= y2
		)
	{
		return true;
	}
	return false;
}

bool Collisions::Detection(const CircleCollider& circle, const BoxCollider& box)
{
	/*Initialize*/
	//基準円を点に変換
	Position2D pointK{ circle.GetPosition() };

	//判定対象に追加する増加分を産出
	float addRange{ circle.GetRange() };

	// 判定対象の四角形データを取得
	Box boxD{box.GetBox()};

	/*Main*/
	// 角が当たってないかを判定
	if (pointK.MeasureUpTo(Position2D( boxD.left, boxD.top )) <= addRange)
	{
		return true;
	}
	if (pointK.MeasureUpTo(Position2D( boxD.left, boxD.bottom )) <= addRange)
	{
		return true;
	}
	if (pointK.MeasureUpTo(Position2D( boxD.right, boxD.top )) <= addRange)
	{
		return true;
	}
	if (pointK.MeasureUpTo(Position2D( boxD.right, boxD.bottom )) <= addRange)
	{
		return true;
	}
	// 中心の四角形が当たっていないか
	if (boxD.left - addRange <= pointK.x() && boxD.right + addRange >= pointK.x() &&
		boxD.top <= pointK.y() && boxD.bottom >= pointK.y())
	{
		return true;
	}
	if (boxD.left <= pointK.x() && boxD.right >= pointK.x() &&
		boxD.top - addRange <= pointK.y() && boxD.bottom + addRange >= pointK.y())
	{
		return true;
	}

	return false;
}

bool Collisions::Detection(const CircleCollider& circle1, const CircleCollider& circle2)
{
	// ２点間の距離を測る
	float diff = circle1.GetPosition().MeasureUpTo(circle2.GetPosition());

	// その距離が２つの半径の和よりも短かったら当たっている
	if (diff <= circle1.GetRange() + circle2.GetRange())
		return true;

	return false;
}

bool Collisions::Detection(const LineCollider& line1, const LineCollider& line2)
{
	return IsCrossing(line1.GetStartPosition(), line1.GetEndPosition(),
		line2.GetStartPosition(), line2.GetEndPosition());
}

bool Collisions::Detection(LinesCollider& lines, const LineCollider& line)
{
	const CircleCollider& circle = lines.GetActiveCircle();
	const Position2D& circlePos = circle.GetPosition();
	float radius = circle.GetRange();

	// ActiveCircleの外接で早期リターン
	if (!Detection(circlePos, radius, line.GetStartPosition()) &&
		!Detection(circlePos, radius, line.GetEndPosition())) {
		return false;
	}

	const std::vector<Position2D>& poses = lines.GetPositions();
	for (size_t i = 1; i < poses.size(); ++i) {
		LineCollider lc(poses[i - 1], poses[i]);
		if (Detection(line, lc)) return true;
	}

	return false;
}

bool Collisions::Detection(LinesCollider& lines, const BoxCollider& box)
{
	if (!Detection(lines.GetActiveCircle(), box)) return false;

	const Box& b = box.GetBox();

	const Position2D topLeft(b.left, b.top);
	const Position2D topRight(b.right, b.top);
	const Position2D bottomLeft(b.left, b.bottom);
	const Position2D bottomRight(b.right, b.bottom);

	LineCollider edges[] = {
		{ topLeft, topRight },
		{ topRight, bottomRight },
		{ bottomRight, bottomLeft },
		{ bottomLeft, topLeft }
	};

	for (const auto& edge : edges) {
		if (Detection(lines, edge)) return true;
	}

	return false;
}

bool Collisions::IsCrossing(const Position2D& a1, const Position2D& a2, const Position2D& b1, const Position2D& b2)
{
	Vector2D A = a2 - a1;
	Vector2D B1 = b1 - a1;
	Vector2D B2 = b2 - a1;

	float cross1 = A.Cross(B1);
	float cross2 = A.Cross(B2);

	Vector2D C = b2 - b1;
	Vector2D C1 = a1 - b1;
	Vector2D C2 = a2 - b1;

	float cross3 = C.Cross(C1);
	float cross4 = C.Cross(C2);

	return (cross1 * cross2 < 0) && (cross3 * cross4 < 0);
}

Collisions::BoxCollider::TOUCH_AREA Collisions::DetectionTouchArea(const BoxCollider& box1, const BoxCollider& box2)
{
	float diffX = box2.GetPosition().x() - box1.GetPosition().x();
	float diffY = box2.GetPosition().y() - box1.GetPosition().y();

	float cornerX;
	float cornerY;

	/*上下の方向を判定*/
	// box2は上にある
	if (diffY < 0.f)
	{
		if (diffX < 0.f)
		{
			cornerX = box2.GetBox().right - box1.GetBox().left;
			cornerY = box2.GetBox().bottom - box1.GetBox().top;

			if (cornerX < cornerY)
			{
				return BoxCollider::TOUCH_AREA::LEFT;
			}
			else if (cornerX > cornerY)
			{
				return BoxCollider::TOUCH_AREA::UP;
			}
		}
		else if (diffX > 0.f)
		{
			cornerX = box1.GetBox().right - box2.GetBox().left;
			cornerY = box2.GetBox().bottom - box1.GetBox().top;

			if (cornerX < cornerY)
			{
				return BoxCollider::TOUCH_AREA::RIGHT;
			}
			else if (cornerX > cornerY)
			{
				return BoxCollider::TOUCH_AREA::UP;
			}
		}
		else
		{
			return BoxCollider::TOUCH_AREA::UP;
		}
	}
	// box2は下にある
	else if (diffY > 0.f)
	{
		if (diffX < 0.f)
		{
			cornerX = box2.GetBox().right - box1.GetBox().left;
			cornerY = box1.GetBox().bottom - box2.GetBox().top;

			if (cornerX < cornerY)
			{
				return BoxCollider::TOUCH_AREA::LEFT;
			}
			else if (cornerX > cornerY)
			{
				return BoxCollider::TOUCH_AREA::DOWN;
			}
		}
		else if (diffX > 0.f)
		{
			cornerX = box1.GetBox().right - box2.GetBox().left;
			cornerY = box1.GetBox().bottom - box2.GetBox().top;

			if (cornerX < cornerY)
			{
				return BoxCollider::TOUCH_AREA::RIGHT;
			}
			else if (cornerX > cornerY)
			{
				return BoxCollider::TOUCH_AREA::DOWN;
			}
		}
		else
		{
			return BoxCollider::TOUCH_AREA::DOWN;
		}
	}
	else
	{
		if (diffX < 0.f)
		{
			return BoxCollider::TOUCH_AREA::LEFT;
		}
		else if (diffX > 0.f)
		{
			return BoxCollider::TOUCH_AREA::RIGHT;
		}
	}

	return BoxCollider::TOUCH_AREA::NONE;

}

/*LinesCollider*/

/// <summary>
/// コンストラクタ
/// </summary>
Collisions::LinesCollider::LinesCollider(const std::vector<Position2D>& positions) noexcept :
	m_ActiveCircle{Position2D(), 0.f}
{
	m_Positions = positions;

	CreateActiveCircle();
}

/// <summary>
/// デストラクタ
/// </summary>
Collisions::LinesCollider::~LinesCollider() noexcept
{
	m_Positions.clear();
}

/// <summary>
/// 計算範囲の作成
/// </summary>
void Collisions::LinesCollider::CreateActiveCircle()
{
	float sumX{};
	float sumY{};

	int posesSize{ static_cast<int>(m_Positions.size()) };

	float maxX{ m_Positions[0].x() };
	float maxY{ m_Positions[0].y() };
	float minX{ m_Positions[0].x() };
	float minY{ m_Positions[0].y() };

	for (int i{ 0 }; i < posesSize; i++)
	{
		sumX += m_Positions[i].x();
		sumY += m_Positions[i].y();

		if (m_Positions[i].x() > maxX)
			maxX = m_Positions[i].x();
		else if(m_Positions[i].x() < minX)
			minX = m_Positions[i].x();

		if (m_Positions[i].y() > maxY)
			maxY = m_Positions[i].y();
		else if (m_Positions[i].y() < minY)
			minY = m_Positions[i].y();
	}

	m_ActiveCircle.SetPosition(Position2D(sumX / posesSize, sumY / posesSize));

	Vector2D range{ Position2D(minX - maxX, minY - maxY) };

	m_ActiveCircle.SetRange(range.range * 2.f);
}

/// <summary>
/// 座標群の取得関数
/// </summary>
std::vector<Position2D>& Collisions::LinesCollider::GetPositions()
{
	return m_Positions;
}

/// <summary>
/// 座標群へのポインタの取得関数
/// </summary>
std::vector<Position2D>* Collisions::LinesCollider::GetPositionsPointer()
{
	return &m_Positions;
}

/// <summary>
/// 計算範囲の取得関数
/// </summary>
Collisions::CircleCollider& Collisions::LinesCollider::GetActiveCircle()
{
	return m_ActiveCircle;
}

/*LineCollider*/

/// <summary>
/// コンストラクタ
/// </summary>
Collisions::LineCollider::LineCollider(const Position2D& startPos, const Position2D& endPos) noexcept
{
	m_Line = { startPos, endPos };
}

/// <summary>
/// デストラクタ
/// </summary>
Collisions::LineCollider::~LineCollider() noexcept = default;

/// <summary>
/// 始点座標設定関数
/// </summary>
void Collisions::LineCollider::SetStartPosition(const Position2D& pos)
{
	m_Line.start = pos;
}

/// <summary>
/// 終点座標設定関数
/// </summary>
void Collisions::LineCollider::SetEndPosition(const Position2D& pos)
{
	m_Line.end = pos;
}
