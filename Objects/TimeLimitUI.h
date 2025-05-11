/**
 * @file   TimeLimitUI.h
 *
 * @brief  �c�莞�ԕ\��UI�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/05/11
 */
#pragma once
#include "ObjectBace.h"

/// <summary>
/// �c�莞�ԕ\��UI�N���X
/// </summary>
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

    void AddTime(int time);
};

