/**
 * @file   Sprite2D.h
 *
 * @brief  �X�v���C�g�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/05/08
 */

#pragma once
#include "Geometry2D.h"

class Camera;

/// <summary>
/// �񎟌��X�v���C�g�N���X
/// </summary>
class Sprite2D
{
protected:
	// ���W
	Transform2D m_Transform;

	// �e�N�X�`���̃n���h��
	int m_TextureHandle;

	// �\������y�[�W
	int m_Page;

	// �g�嗦
	float m_exRate;

	// �؂���T�C�Y
	int m_TileWidth;
	int m_TileHeight;

	// ���]�t���b�O
	bool m_FlipFlag;

public:
	/*���C���V�X�e��*/
	Sprite2D(const int texture, const float exRate = 1.f);
	Sprite2D(const int texture, const int tileWidth, const int tileHeight, const float exRate = 1.f);
	virtual ~Sprite2D() = default;
	virtual void Initialize(const Transform2D _transform = Transform2D(Position2D(0.f, 0.f), 0.f));
	void Draw();
	void Draw(const Camera& camera);

	// �e�N�X�`���̔��]
	void FlipTexture()                { m_FlipFlag = !m_FlipFlag; }
	void FlipTexture(const bool flip) { m_FlipFlag = flip; }

	/*�ݒ�/�擾*/
	void SetTransform(const Transform2D _transform) { m_Transform = _transform; }
	void SetPosition (const Position2D _position)   { m_Transform = _position; }
	void SetAngle    (const float& _angle)          { m_Transform = _angle; }
	void SetPage     (const int number)             { m_Page = number; }

	Transform2D GetTransform() const { return m_Transform; }
};

