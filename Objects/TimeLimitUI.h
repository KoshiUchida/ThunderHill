#pragma once
#include "ObjectBace.h"
class TimeLimitUI :
    public ObjectBace
{
private:
    int m_Time;

    int m_LiveTime;

public:
    TimeLimitUI() noexcept;
    ~TimeLimitUI() noexcept;
    void Initialize() override;
    void Update() override;
    void Render(const Camera& camera) override;
    void Finalize() override;
};

