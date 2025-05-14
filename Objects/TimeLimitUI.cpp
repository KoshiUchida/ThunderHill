/**
 * @file   TimeLimitUI.cpp
 *
 * @brief  残り時間表示UIのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/05/14
 */
#include "TimeLimitUI.h"

#include "DxLib.h"
#include <string>
#include "../Common/Colors.h"
#include "../Common/ScoreIO.h"

#include "../Manager/SceneManager.h"
#include "../Manager/ShareData.h"

TimeLimitUI::TimeLimitUI() noexcept :
	ObjectBace(Transform2D(Position2D(10.f, 10.f), 0.f)),
	m_Time{},
	m_LiveTime{}
{
}

TimeLimitUI::~TimeLimitUI() noexcept = default;

static constexpr int FirstTimeLimit{ 1500 };

void TimeLimitUI::Initialize()
{
	m_Time = FirstTimeLimit;
	m_LiveTime = 0;
}

void TimeLimitUI::Update()
{
	m_Time--;
	m_LiveTime++;

	if (m_Time <= 0)
	{
		SceneManager::GetInstance().RequestSceneChange("Result");
	}
}

static constexpr unsigned int Color{ Colors::White };

void TimeLimitUI::Render(const Camera& camera)
{
	std::string String = "Time : " + std::to_string(m_Time);

	DrawString(m_Transform.GetPositionX(), m_Transform.GetPositionY(), String.c_str(), Color);
}

void TimeLimitUI::Finalize()
{
	ShareData& p_sd{ ShareData::GetInstance() };

	int data = LoadHighScore();

	if (data && data < m_LiveTime || !data)
		SaveHighScore(m_LiveTime);


	p_sd.Set("Score", std::to_string(m_LiveTime));

}

void TimeLimitUI::AddTime(int time)
{
	m_Time += time;
}
