/**
 * @file   TimeLimitUI.h
 *
 * @brief  残り時間表示UIのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/05/11
 */
#pragma once
#include "ObjectBace.h"

/// <summary>
/// 残り時間表示UIクラス
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

