/**
 * @file   Geometry2D.h
 *
 * @brief  幾何変換関連クラスのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/01/12
 */

#pragma once


 /// <summary>
 /// π
 /// </summary>
static constexpr float PI{ 3.14159f };

/// <summary>
/// Zero
/// </summary>
static constexpr float Zero{ 0.0f };

/// <summary>
/// Float型の下桁の桁数
/// </summary>
static constexpr float FLOAT_PRECISION_LIMIT{ 1000.f };
//
//float RoundToDecimalPlaces(float val);

/// <summary>
/// ２次元座標クラス
/// </summary>
class Position2D
{
private:
	float m_x;
	float m_y;

public:
	/*Main System*/
	Position2D();
	Position2D(float _x, float _y);
	~Position2D();

	/*Sub System*/
	// 指定の座標までの距離を測る
	float MeasureUpTo(const Position2D& _there) const;
	// 指定の座標への向き(DEG)を測る
	float AngleMeasureUpTo(const Position2D& _there) const;

	/*Operator*/
	friend Position2D operator+(const Position2D& p0, const Position2D& p1);
	friend Position2D operator-(const Position2D& p0, const Position2D& p1);
	Position2D& operator+=(const Position2D& other);
	Position2D& operator-=(const Position2D& other);

	friend Position2D operator*(const Position2D& p, float x);
	Position2D& operator*=(float x);
	friend Position2D operator/(const Position2D& p, float x);
	Position2D& operator/=(float x);

	/*Setter*/
	void SetX(float _x) { m_x = _x; }
	void SetY(float _y) { m_y = _y; }

	/*Getter*/
	float x() const;
	float y() const;
};

/// <summary>
/// ２次元ベクタークラス
/// </summary>
class Vector2D
{
public:
	float range;
	float angle;

	/*Main System*/
	Vector2D();
	Vector2D(float _range, float _angle);
	Vector2D(const Position2D& _position);
	~Vector2D();

	/*Sub System*/
	// XY-Vectorに変換する
	Position2D ChangePosition() const;

	// 他のベクトルとの外積
	float Cross(const Vector2D& _vector) const;

	/*Operator*/
	friend Vector2D operator+(const Vector2D& a, const Vector2D& b);
	friend Vector2D operator-(const Vector2D& a, const Vector2D& b);

	// 座標へのベクトル演算
	friend Position2D operator+(const Position2D& _position, const Vector2D& _vector);
	friend Position2D operator-(const Position2D& _position, const Vector2D& _vector);

	// スカラー倍
	friend Vector2D operator*(const Vector2D& _vector, float _valum);
	Vector2D& operator*=(float valum);

	/*Getter*/
	float GetAngle() const;
	float GetAngleRAD() const;
};

Position2D& operator+=(Position2D& _position, const Vector2D& _vector);
Position2D& operator-=(Position2D& _position, const Vector2D& _vector);

/// <summary>
/// ２次元トランスフォームクラス
/// </summary>
class Transform2D
{
private:
	// 座標
	Position2D m_position;

	// 回転
	float m_angle;

public:
	/*Main System*/
	Transform2D();
	Transform2D(const Position2D& _position, float _angle);
	~Transform2D();

	/*Operator*/
	Transform2D& operator= (const Position2D& other);
	Transform2D& operator+=(const Position2D& other);
	Transform2D& operator-=(const Position2D& other);

	Transform2D& operator= (float angle);
	Transform2D& operator+=(float angle);
	Transform2D& operator-=(float angle);

	Transform2D& operator+=(const Vector2D& _vector);
	Transform2D& operator-=(const Vector2D& _vector);

	/*Setter*/
	void SetPosition(const Position2D& _position) { *this = _position; }
	void SetPosition(const float& _x, const float& _y) { *this = Position2D{ _x, _y }; }
	void SetRotate(const float& _angle) { *this = _angle; }

	/*Getter*/
	float      GetPositionX() const { return m_position.x(); }
	float      GetPositionY() const { return m_position.y(); }
	Position2D GetPosition()  const { return m_position; }
	float      GetAngle()     const { return m_angle; }
	float      GetAngleRAD()  const { return m_angle / 180.f * PI; }

	Position2D* GetPositionPointer() { return &m_position; }

	/*Addtion*/
	void AddPositionX(const float& _x) { this->m_position += Position2D(_x, 0.f); }
	void AddPositionY(const float& _y) { this->m_position += Position2D(0.f, _y); }
};

