#include "TimeLimitUI.h"
#include "../Manager/SceneManager.h"
#include "DxLib.h"
#include <string>
//#include ""

TimeLimitUI::TimeLimitUI() noexcept :
	ObjectBace(Transform2D()),
	m_Time{}
{
}

TimeLimitUI::~TimeLimitUI() noexcept = default;

static constexpr int FirstTimeLimit{ 100 };

void TimeLimitUI::Initialize()
{
	m_Time = FirstTimeLimit;
}

void TimeLimitUI::Update()
{
	m_Time--;

	if (m_Time >= 0)
	{
		SceneManager::GetInstance().RequestSceneChange("Result");
	}
}

static constexpr unsigned int Color{};

void TimeLimitUI::Render(const Camera& camera)
{
	//DrawString(m_Transform.GetPositionX(), m_Transform.GetPositionY(), "écÇËÅF" + std::to_string(m_Time), );
}

void TimeLimitUI::Finalize()
{
}
