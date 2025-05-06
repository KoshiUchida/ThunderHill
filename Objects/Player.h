#pragma once
#include "ObjectBace.h"
#include "../Common/Collisions.h"
#include "../Manager/Joypad.h"
#include "../Common/Motion.h"

class Player final:
    public ObjectBace
{
private:
	Collisions::BoxCollider m_Collider;

	Joypad& p_Pad;

	float m_MinPosX;
	float m_MaxPosX;

	Speed m_Speed;

	bool m_CanJump;
	bool m_IsJumping;

	float m_Under;

	Speed m_Gravity;

public:
	Player();
	~Player();
	void Initialize() override;
	void Update() override;
	void Render(const Camera& camera) override;
	void Finalize() override;

private:
	void Move();
	void Jump();

public:
	Collisions::BoxCollider& GetCollider();
};

