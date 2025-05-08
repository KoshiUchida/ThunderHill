#include "FlyingDebrisGenerater.h"

#include "FlyingDebris.h"

int FlyingDebrisGenerater::s_Count = 0;

FlyingDebrisGenerater::FlyingDebrisGenerater() noexcept :
	ObjectBace(Transform2D()),
	s_OM{ ObjectManager::GetInstance() },
	m_Time{}
{
}

FlyingDebrisGenerater::~FlyingDebrisGenerater() noexcept = default;

void FlyingDebrisGenerater::Initialize()
{
}

static constexpr int BasicCoolTime{ 300 };

void FlyingDebrisGenerater::Update()
{
	m_Time++;

	if (m_Time > BasicCoolTime)
	{
		s_OM.AddObject(std::to_string(s_Count++), std::make_unique<FlyingDebris>());

		m_Time = 0;
	}
}

void FlyingDebrisGenerater::Render(const Camera& camera)
{
}

void FlyingDebrisGenerater::Finalize()
{
}
