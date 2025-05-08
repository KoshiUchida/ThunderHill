#pragma once
#include "ObjectBace.h"

#include "../Manager/ObjectManager.h"

class FlyingDebrisGenerater :
    public ObjectBace
{
private:
	ObjectManager& s_OM;

	static int s_Count;

    int m_Time;

public:
    FlyingDebrisGenerater() noexcept;
    ~FlyingDebrisGenerater() noexcept;
	void Initialize() override final;
	void Update() override final;
	void Render(const Camera& camera) override final;
	void Finalize() override final;

};

