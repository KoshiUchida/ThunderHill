#include "ThunderGenerater.h"

#include "../Manager/ResourceManager.h"
#include "../WindowSettingItems.h"
#include <string>
#include "Thunder.h"
#include "DxLib.h"
#include "../Common/Colors.h"

int ThunderGenerater::s_Count = 0;

ThunderGenerater::ThunderGenerater() :
	ObjectBace(Transform2D(), 6),
	p_om{ ObjectManager::GetInstance() },
	p_ccr{ CCRandom::GetInstane() },
	m_Time{},
	m_CoolTime{},
	m_Width{},
	m_Height{},
	m_Cloud{ ResourceManager::GetInstance().RequestTexture ("Clound.png"), 0.5f },
	m_RainBGM{ ResourceManager::GetInstance().RequestSound("RainBGM.ogg") }
{
}

ThunderGenerater::~ThunderGenerater() = default;

static constexpr int CloudVolume{ 40 };
static constexpr int CoolTimeMax{ 60 };
static constexpr int CoolTimeMin{ 30 };

void ThunderGenerater::Initialize()
{
	m_Time = 0;
	m_CoolTime = CoolTimeMax;
	m_Width = WSI::GetInstance().ScreenRight();
	m_Height = WSI::GetInstance().ScreenBottom();

	m_Cloud.Initialize();

	for (int i{ 0 }; i < CloudVolume; i++)
	{
		m_CloudPositions.push_back(Position2D(static_cast<float>(p_ccr.Rand(0, m_Width)), static_cast<float>(p_ccr.Rand(35, 60))));
	}

	PlaySoundMem(m_RainBGM, DX_PLAYTYPE_LOOP);
}

void ThunderGenerater::Update()
{
	m_Time++;

	if (m_Time >= m_CoolTime)
	{
		Position2D newPosition{ static_cast<float>(p_ccr.Rand(0, m_Width)), 40.f };

		p_om.AddObject( std::to_string(s_Count) + "Thunder", std::make_unique<Thunder>(newPosition));

		m_Time = 0;
		s_Count++;
		m_CoolTime = p_ccr.Rand(CoolTimeMin, CoolTimeMax);
	}

	m_RainPositions.push_back(Position2D(static_cast<float>(p_ccr.Rand(0, m_Width)), 40.f));

	for (size_t i{ 0 }; i < m_RainPositions.size(); i++)
	{
		m_RainPositions[i] += Position2D(1.f, 10.f);

		if (m_RainPositions[i].y() > m_Height)
		{
			m_RainPositions.erase(m_RainPositions.begin() + i);
			i--;
		}
	}
}

void ThunderGenerater::Render(const Camera& camera)
{
	for (size_t i{ 0 }; i < m_RainPositions.size(); i++)
	{
		DrawLine(m_RainPositions[i].x(), m_RainPositions[i].y(),
			m_RainPositions[i].x(), m_RainPositions[i].y() - 5.f,
			Colors::White);
	}

	for (int i{ 0 }; i < CloudVolume; i++)
	{
		m_Cloud.SetPosition(m_CloudPositions[i]);
		m_Cloud.Draw();
	}
}

void ThunderGenerater::Finalize()
{
	StopSoundMem(m_RainBGM);
}
