/**
 * @file   ObjectBace.cpp
 *
 * @brief  �I�u�W�F�N�g�x�[�X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/01/12
 */

#include "ObjectBace.h"

#include "../Common/Camera.h"

/// <summary>
/// Constructor
/// </summary>
ObjectBace::ObjectBace(const Transform2D& _transform, int _layer, const std::string& _tag)
	: m_Transform{ _transform }
	, m_Layer    { _layer }
	, m_IsDestroy{}
	, m_Tag      { _tag }
	, m_ShareData1{}
{
}

/// <summary>
/// Destructor
/// </summary>
ObjectBace::~ObjectBace() = default;

Position2D ObjectBace::GetPosition(const Camera& camera)
{
	return camera.ConvertWorldToScreenPosition(m_Transform.GetPosition());
}

ObjectBace& ObjectBace::operator+=(const Position2D& other)
{
	m_Transform += other;

	return *this;
}

ObjectBace& ObjectBace::operator-=(const Position2D& other)
{
	m_Transform -= other;

	return *this;
}

ObjectBace& ObjectBace::operator+=(const Vector2D& other)
{
	m_Transform += other;

	return *this;
}

ObjectBace& ObjectBace::operator-=(const Vector2D& other)
{
	m_Transform -= other;

	return *this;
}
