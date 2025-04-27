#pragma once
#include "ObjectBace.h"
class ThunderGenerater final:
    public ObjectBace
{
public:
    ThunderGenerater();
    ~ThunderGenerater();

	void Initialize() override;
	void Update() override;
	void Render(const Camera& camera) override;
	void Finalize() override;
};

