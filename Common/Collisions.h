/**
 * @file   Collisions.h
 *
 * @brief  �R���W���������̃w�b�_�t�@�C��
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
	/// ���\����
	/// </summary>
	struct Line
	{
		Position2D start;
		Position2D end;
	};

	/// <summary>
	/// ���\����
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
	/// ���R���C�_�[
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
	/// �~�R���C�_�[
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

		// �ݒ�
		void SetStartPosition(const Position2D& pos);
		void SetEndPosition(const Position2D& pos);

		// �擾
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
	/// �A���R���C�_�[
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
		// �擾
		std::vector<Position2D>& GetPositions();
		std::vector<Position2D>* GetPositionsPointer();
		CircleCollider& GetActiveCircle();
	};

	/// <summary>
	/// BoxCollision���m�̂����蔻��
	/// </summary>
	/// <param name="box1">��ƂȂ�BoxCollision</param>
	/// <param name="box2">����Ώۂ�BoxCollision</param>
	/// <param name="isLine">�������܂߂邩</param>
	/// <returns>true = �������Ă��� false = �������Ă��Ȃ�</returns>
	bool Detection(const BoxCollider& box1, const BoxCollider& box2, bool isLine = true);

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
	bool Detection(const BoxCollider& box, const Position2D& point);

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
	bool Detection(const CircleCollider& circle, const BoxCollider& box);

	/// <summary>
	/// �~�R���C�_�[���m�̏d�Ȃ蔻��
	/// </summary>
	bool Detection(const CircleCollider& circle1, const CircleCollider& circle2);

	/// <summary>
	/// ���R���C�_�[���m�̏d�Ȃ蔻��
	/// </summary>
	bool Detection(const LineCollider& line1, const LineCollider& line2);

	/// <summary>
	/// �A���R���C�_�[�Ɛ��R���C�_�[�̏d�Ȃ蔻��
	/// </summary>
	bool Detection(LinesCollider& lines, const LineCollider& line);

	/// <summary>
	/// �A���R���C�_�[�Ɣ��R���C�_�[�̏d�Ȃ蔻��
	/// </summary>
	bool Detection(LinesCollider& lines, const BoxCollider& box);
	
	/// <summary>
	/// BoxCollision���m�̐ڐG��
	/// </summary>
	/// <param name="box1">��ƂȂ�BoxCollision</param>
	/// <param name="box2">����Ώۂ�BoxCollision</param>
	/// <returns>�ڐG�ӂ������͐ڐG���Ă��Ȃ�</returns>
	BoxCollider::TOUCH_AREA DetectionTouchArea(const BoxCollider& box1, const BoxCollider& box2);
};

