/**
 * @file   Geometry2D.cpp
 *
 * @brief  �􉽕ϊ��֘A�N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/01/12
 */

#include "Geometry2D.h"
#include <corecrt_math.h>
#include <cmath>

 /// <summary>
 /// Float�^�̉����̐؂�̂�
 /// </summary>
//float RoundToDecimalPlaces(float val)
//{
//	return std::ceilf(val * FLOAT_PRECISION_LIMIT) / FLOAT_PRECISION_LIMIT;
//}

/*Position2D class*/

/// <summary>
/// Constructor
/// </summary>
Position2D::Position2D() = default;

/// <summary>
/// Constructor
/// </summary>
/// <param name="_x">X���W</param>
/// <param name="_y">Y���W</param>
Position2D::Position2D(float _x, float _y)
	: m_x{ _x }
	, m_y{ _y }
{
}

/// <summary>
/// Destructor
/// </summary>
Position2D::~Position2D() = default;

/// <summary>
/// �w��̍��W�܂ł̋����𑪂�
/// </summary>
float Position2D::MeasureUpTo(const Position2D& _there) const
{
	Position2D diff = (*this) - _there;
	Position2D squared{ diff.x() * diff.x(), diff.y() * diff.y() };

	return std::sqrtf(squared.x() + squared.y());
}

/// <summary>
/// �w��̍��W�ւ̌���(DEG)�𑪂�
/// </summary>
float Position2D::AngleMeasureUpTo(const Position2D& _there) const
{
	float dx = _there.x() - x();
	float dy = _there.y() - y();
	float magnitube = std::sqrtf(dx * dx + dy * dy);
	float cos_theta = dx / magnitube;
	float sin_theta = dy / magnitube;

	float angle = std::acos(cos_theta) * 180.f / PI;

	if (sin_theta < 0.f)
		angle = 360.f - angle;

	return angle;
}

// Operator

Position2D& Position2D::operator+=(const Position2D& other)
{
	m_x += other.x();
	m_y += other.y();
	return *this;
}

Position2D& Position2D::operator-=(const Position2D& other)
{
	m_x -= other.x();
	m_y -= other.y();
	return *this;
}

Position2D& Position2D::operator*=(float x)
{
	m_x *= x;
	m_y *= x;
	return *this;
}

Position2D& Position2D::operator/=(float x)
{
	m_x /= x;
	m_y /= x;
	return *this;
}

Position2D operator+(const Position2D& p0, const Position2D& p1)
{
	return Position2D(p0.x() + p1.x(), p0.y() + p1.y());
}

Position2D operator-(const Position2D& p0, const Position2D& p1)
{
	return Position2D(p0.x() - p1.x(), p0.y() - p1.y());
}

Position2D operator*(const Position2D& p, float x)
{
	return Position2D(p.x() * x, p.y() * x);
}

Position2D operator/(const Position2D& p, float x)
{
	return Position2D(p.x() / x, p.y() / x);
}

// Getter

float Position2D::x() const
{
	return m_x;
}

float Position2D::y() const
{
	return m_y;
}

/*Vector2D*/

/// <summary>
/// Constructor
/// </summary>
Vector2D::Vector2D()
	: range{}
	, angle{}
{
}

/// <summary>
/// Constructor
/// </summary>
Vector2D::Vector2D(float _range, float _angle)
	: range{ _range }
	, angle{ _angle }
{
}

/// <summary>
/// Constructor
/// </summary>
Vector2D::Vector2D(const Position2D& _position)
	: Vector2D()
{
	// ���_���W�̐錾
	static const Position2D OriginPosition{ 0.f, 0.f };

	// �e�l�ɍ����悤�ɒl��ϊ����A���
	range = OriginPosition.MeasureUpTo(_position);
	angle = OriginPosition.AngleMeasureUpTo(_position);
}

/// <summary>
/// Destructor
/// </summary>
Vector2D::~Vector2D() = default;

/// <summary>
/// ���݂�Vector��XY-Vector�ɕϊ�����
/// </summary>
/// <returns></returns>
Position2D Vector2D::ChangePosition() const
{
	return Position2D
	(
		cosf(this->GetAngleRAD()) * this->range,
		sinf(this->GetAngleRAD()) * this->range
	);
}

float Vector2D::Cross(const Vector2D& _vector) const
{
	Position2D v1 = this->ChangePosition();
	Position2D v2 = _vector.ChangePosition();

	return std::ceilf(v1.x() * v2.y() - v1.y() * v2.x());
}

Vector2D& Vector2D::operator*=(float valum)
{
	this->range *= valum;

	return *this;
}

/// <summary>
/// �����̎擾
/// </summary>
/// <returns>����</returns>
float Vector2D::GetAngle() const
{
	return angle;
}

/// <summary>
/// �����iRAD�j�̎擾
/// </summary>
/// <returns>�����iRAD�j</returns>
float Vector2D::GetAngleRAD() const
{
	return angle / 180.f * PI;
}

Vector2D operator+(const Vector2D& a, const Vector2D& b)
{
	// �eXYVector���擾
	Position2D a_xyVector = a.ChangePosition();
	Position2D b_xyVector = b.ChangePosition();

	// ���v��XYVector���擾
	Position2D new_xyVector = a_xyVector + b_xyVector;

	// ���v��XYVector��RAVector�ɕϊ�����
	Vector2D new_raVector{ new_xyVector };

	return new_raVector;
}

Vector2D operator-(const Vector2D& a, const Vector2D& b)
{
	// �eXYVector���擾
	Position2D a_xyVector = a.ChangePosition();
	Position2D b_xyVector = b.ChangePosition();

	// ���v��XYVector���擾
	Position2D new_xyVector = a_xyVector - b_xyVector;

	// ���v��XYVector��RAVector�ɕϊ�����
	Vector2D new_raVector{ new_xyVector };

	return new_raVector;
}

Position2D operator+(const Position2D& _position, const Vector2D& _vector)
{
	Position2D AddPosition = _vector.ChangePosition();
	return _position + AddPosition;
}

Position2D operator-(const Position2D& _position, const Vector2D& _vector)
{
	Position2D AddPosition = _vector.ChangePosition();
	return _position - AddPosition;
}

Vector2D operator*(const Vector2D& _vector, float _valum)
{
	return Vector2D(_vector.range * _valum, _vector.angle);
}

Position2D& operator+=(Position2D& _position, const Vector2D& _vector)
{
	Position2D addPosition = _vector.ChangePosition();
	_position += addPosition;
	return _position;
}

Position2D& operator-=(Position2D& _position, const Vector2D& _vector)
{
	Position2D addPosition = _vector.ChangePosition();
	_position -= addPosition;
	return _position;
}

/*Transform2D class*/

/// <summary>
/// Constructor
/// </summary>
Transform2D::Transform2D()
	: m_position{}
	, m_angle{}
{
}

/// <summary>
/// Constructor
/// </summary>
Transform2D::Transform2D(const Position2D& _position, float _angle)
	: m_position{ _position }
	, m_angle{ _angle }
{
}

/// <summary>
/// Destructor
/// </summary>
Transform2D::~Transform2D() = default;

Transform2D& Transform2D::operator=(const Position2D& other)
{
	m_position = other;
	return *this;
}

Transform2D& Transform2D::operator+=(const Position2D& other)
{
	m_position += other;
	return *this;
}

Transform2D& Transform2D::operator-=(const Position2D& other)
{
	m_position -= other;
	return *this;
}

Transform2D& Transform2D::operator=(float angle)
{
	m_angle = angle;
	return *this;
}

Transform2D& Transform2D::operator+=(float angle)
{
	m_angle += angle;
	return *this;
}

Transform2D& Transform2D::operator-=(float angle)
{
	m_angle -= angle;
	return *this;
}

Transform2D& Transform2D::operator+=(const Vector2D& _vector)
{
	m_position += _vector;
	return *this;
}

Transform2D& Transform2D::operator-=(const Vector2D& _vector)
{
	m_position -= _vector;
	return *this;
}
