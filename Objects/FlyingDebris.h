#pragma once
#include "ObjectBace.h"

#include "../Common/Collisions.h"
#include "../Common/Motion.h"
#include "../Common/Sprite2D.h"

class FlyingDebris :
    public ObjectBace
{
private:
	Collisions::BoxCollider m_Collider;

	float m_Under;

	Speed m_Gravity;

	Sprite2D m_Sprite;

	Collisions::BoxCollider* p_PlayerCollider;

public:
    FlyingDebris();
    ~FlyingDebris();

	void Initialize() override final;
	void Update() override final;
	void Render(const Camera& camera) override final;
	void Finalize() override final;
};

