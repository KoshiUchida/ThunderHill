/**
 * @file   Collisions.h
 *
 * @brief  �R���W���������̃w�b�_�t�@�C��
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
	/// BoxCollision���m�̂����蔻��
	/// </summary>
	/// <param name="box1">��ƂȂ�BoxCollision</param>
	/// <param name="box2">����Ώۂ�BoxCollision</param>
	/// <param name="isLine">�������܂߂邩</param>
	/// <returns>true = �������Ă��� false = �������Ă��Ȃ�</returns>
	bool Detection(const BoxCollision& box1, const BoxCollision& box2, bool isLine = true);

	/// <summary>
	/// �~�Ɠ_�̂����蔻��
	/// </summary>
	/// <param name="point1">�~�̍��W</param>
	/// <param name="range">�~�̔��a</param>
	/// <param name="point2">�_�̍��W</param>
	/// <returns>true = �������Ă��� false = �������Ă��Ȃ�</returns>
	bool Detection(const Position2D& point1, float range, const Position2D& point2);

	/// <summary>
	/// BoxCollision�Ɠ_�̂����蔻��
	/// </summary>
	/// <param name="box">��ƂȂ�R���C�_�[</param>
	/// <param name="point">���肷��_</param>
	/// <returns>true = �������Ă��� false = �������Ă��Ȃ�</returns>
	bool Detection(const BoxCollision& box, const Position2D& point);

	/// <summary>
	/// �l�p�Ɠ_�̂����蔻��
	/// </summary>
	/// <param name="x1">�l�p�̍ō����_�̍��WX</param>
	/// <param name="y1">�l�p�̍ō����_�̍��WY</param>
	/// <param name="x2">�l�p�̍ŉE��_�̍��WX</param>
	/// <param name="y2">�l�p�̍ŉE��_�̍��WY</param>
	/// <param name="point">�_�̍��W</param>
	/// <returns>true = �������Ă��� false = �������Ă��Ȃ�</returns>
	bool Detection(float x1, float y1, float x2, float y2, const Position2D& point);

	/// <summary>
	/// CircleCollision��BoxCollision�̂����蔻��
	/// </summary>
	/// <param name="circle">��ƂȂ�CircleCollision</param>
	/// <param name="box">����Ώۂ�BoxCollision</param>
	/// <returns></returns>
	bool Detection(const CircleCollision& circle, const BoxCollision& box);

	bool Detection(const CircleCollision& circle, const CircleCollision& box);
	
	/// <summary>
	/// BoxCollision���m�̐ڐG��
	/// </summary>
	/// <param name="box1">��ƂȂ�BoxCollision</param>
	/// <param name="box2">����Ώۂ�BoxCollision</param>
	/// <returns>�ڐG�ӂ������͐ڐG���Ă��Ȃ�</returns>
	BoxCollision::TOUCH_AREA DetectionTouchArea(const BoxCollision& box1, const BoxCollision& box2);
};

