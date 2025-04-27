/**
 * @file   Collisions.cpp
 *
 * @brief  コリジョンたちのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/01/03
 */

#include "Collisions.h"
#include "iostream"
#include <DxLib.h>

/*BoxCollision*/

/// <summary>
/// コンストラクタ
/// </summary>
Collisions::BoxCollision::BoxCollision(const Position2D& position, float width, float height)
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

bool Collisions::BoxCollision::Handling(const BoxCollision& _collider)
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
void Collisions::BoxCollision::SetPosition(const Position2D& position)
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
void Collisions::BoxCollision::SetPosition(float x, float y)
{
	SetPosition(Position2D(x, y));
}

void Collisions::BoxCollision::AddPosition(const Position2D& _position)
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
Collisions::CircleCollision::CircleCollision(const Position2D& position, float range)
	: m_Position{ position }
	, m_Range{ range }
{
}

/*Detections*/

bool Collisions::Detection(const BoxCollision& box1, const BoxCollision& box2, bool isLine)
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

bool Collisions::Detection(const BoxCollision& box, const Position2D& point)
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

bool Collisions::Detection(const CircleCollision& circle, const BoxCollision& box)
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

bool Collisions::Detection(const CircleCollision& circle1, const CircleCollision& circle2)
{
	// ２点間の距離を測る
	float diff = circle1.GetPosition().MeasureUpTo(circle2.GetPosition());

	// その距離が２つの半径の和よりも短かったら当たっている
	if (diff <= circle1.GetRange() + circle2.GetRange())
		return true;

	return false;
}

Collisions::BoxCollision::TOUCH_AREA Collisions::DetectionTouchArea(const BoxCollision& box1, const BoxCollision& box2)
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
				return BoxCollision::TOUCH_AREA::LEFT;
			}
			else if (cornerX > cornerY)
			{
				return BoxCollision::TOUCH_AREA::UP;
			}
		}
		else if (diffX > 0.f)
		{
			cornerX = box1.GetBox().right - box2.GetBox().left;
			cornerY = box2.GetBox().bottom - box1.GetBox().top;

			if (cornerX < cornerY)
			{
				return BoxCollision::TOUCH_AREA::RIGHT;
			}
			else if (cornerX > cornerY)
			{
				return BoxCollision::TOUCH_AREA::UP;
			}
		}
		else
		{
			return BoxCollision::TOUCH_AREA::UP;
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
				return BoxCollision::TOUCH_AREA::LEFT;
			}
			else if (cornerX > cornerY)
			{
				return BoxCollision::TOUCH_AREA::DOWN;
			}
		}
		else if (diffX > 0.f)
		{
			cornerX = box1.GetBox().right - box2.GetBox().left;
			cornerY = box1.GetBox().bottom - box2.GetBox().top;

			if (cornerX < cornerY)
			{
				return BoxCollision::TOUCH_AREA::RIGHT;
			}
			else if (cornerX > cornerY)
			{
				return BoxCollision::TOUCH_AREA::DOWN;
			}
		}
		else
		{
			return BoxCollision::TOUCH_AREA::DOWN;
		}
	}
	else
	{
		if (diffX < 0.f)
		{
			return BoxCollision::TOUCH_AREA::LEFT;
		}
		else if (diffX > 0.f)
		{
			return BoxCollision::TOUCH_AREA::RIGHT;
		}
	}

	return BoxCollision::TOUCH_AREA::NONE;

}
