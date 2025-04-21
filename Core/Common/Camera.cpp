/**
 * @file   Camera.h
 *
 * @brief  �J�����̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/01/15
 */

#include "Camera.h"

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
/// ���[���h���W���X�N���[�����W�ɕϊ�
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
/// �X�N���[�����W�����[���h���W�ɕϊ�
/// </summary>
Position2D Camera::ConvertScreenToWorldPosition(const Position2D& _position) const
{
	float x = static_cast<float>(m_Screen.width ) / (-2.f) + m_Position.x() + _position.x();
	float y = static_cast<float>(m_Screen.height) / (-2.f) + m_Position.y() + _position.y();
	return Position2D(x, y);
}
