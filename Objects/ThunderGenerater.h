#pragma once
#include "ObjectBace.h"
#include "../Manager/ObjectManager.h"
#include "../Common/CCRandom.h"
#include "../Common/Sprite2D.h"

class ThunderGenerater final:
    public ObjectBace
{
private:
	ObjectManager& p_om;

	CCRandom& p_ccr;

	static int s_Count;

	int m_Time;

	int m_CoolTime;

	int m_Width;

	int m_Height;

	std::vector<Position2D> m_CloudPositions;

	Sprite2D m_Cloud;

	std::vector<Position2D> m_RainPositions;

	int m_RainBGM;

	ObjectBace* p_Player;

public:
    ThunderGenerater();
    ~ThunderGenerater();

	void Initialize() override;
	void Update() override;
	void Render(const Camera& camera) override;
	void Finalize() override;
};

