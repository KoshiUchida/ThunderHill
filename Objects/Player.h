#pragma once
#include "ObjectBace.h"
#include "../Common/Collisions.h"
#include "../Manager/Joypad.h"

class Player final:
    public ObjectBace
{
private:
	Collisions::BoxCollision m_Collider;

	Joypad& p_Pad;

	float m_MinPosX;
	float m_MaxPosX;

public:
	Player();
	~Player();
	void Initialize() override;
	void Update() override;
	void Render(const Camera& camera) override;
	void Finalize() override;

	Collisions::BoxCollision& GetCollider();
};

