/**
 * @file   TimeUp.h
 *
 * @brief  ���ԏ㏸�A�C�e���I�u�W�F�N�g�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/05/11
 */
#pragma once
#include "ObjectBace.h"

#include "../Common/Collisions.h"
#include "../Common/Sprite2D.h"

/// <summary>
/// ���ԏ㏸�A�C�e���̃I�u�W�F�N�g�N���X
/// </summary>
class TimeUp :
    public ObjectBace
{
private:
	Collisions::BoxCollider m_Collider;

	Sprite2D m_Sprite;

	Collisions::BoxCollider* p_PlayerCollider;

	int m_Time;

public:
	TimeUp(const Position2D& pos) noexcept;
	~TimeUp() noexcept;

	void Initialize() override final;
	void Update    () override final;
	void Render    (const Camera& camera) override final;
	void Finalize  () override final;

private:
	void Collider();
};

