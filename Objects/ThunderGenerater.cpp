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
	m_RainBGM{ ResourceManager::GetInstance().RequestSound("RainBGM.ogg") },
	p_Player{ nullptr }
{
}

ThunderGenerater::~ThunderGenerater() = default;

static constexpr int CloudVolume{ 40 };
static constexpr int CoolTimeMax{ 60 };
static constexpr int CoolTimeMin{ 30 };

static constexpr int CloudPosYMax{ 60 };
static constexpr int CloudPosYMin{ 35 };

void ThunderGenerater::Initialize()
{
	m_Time = 0;
	m_CoolTime = CoolTimeMax;
	m_Width = WSI::GetInstance().ScreenRight();
	m_Height = WSI::GetInstance().ScreenBottom();

	m_Cloud.Initialize();

	for (int i{ 0 }; i < CloudVolume; i++)
	{
		m_CloudPositions.push_back(Position2D(static_cast<float>(p_ccr.Rand(0, m_Width)), static_cast<float>(p_ccr.Rand(CloudPosYMin, CloudPosYMax))));
	}

	PlaySoundMem(m_RainBGM, DX_PLAYTYPE_LOOP);

	p_Player = p_om.GetObjectPtr("Player");
}

static constexpr float GeneratePosY{ 40.f };

void ThunderGenerater::Update()
{
	m_Time++;

	if (m_Time >= m_CoolTime)
	{
		Position2D newPosition;

		if (p_ccr.Rand(0, 5))
			newPosition = Position2D(static_cast<float>(p_ccr.Rand(0, m_Width)), GeneratePosY);
		else
			newPosition = Position2D(p_Player->GetPosition().x(), GeneratePosY);

		p_om.AddObject( std::to_string(s_Count) + "Thunder", std::make_unique<Thunder>(newPosition));

		m_Time = 0;
		s_Count++;
		m_CoolTime = p_ccr.Rand(CoolTimeMin, CoolTimeMax);
	}

	m_RainPositions.push_back(Position2D(static_cast<float>(p_ccr.Rand(10, m_Width * 14 / 10)), GeneratePosY));
	m_RainPositions.push_back(Position2D(static_cast<float>(p_ccr.Rand(10, m_Width * 14 / 10)), GeneratePosY));

	for (size_t i{ 0 }; i < m_RainPositions.size(); i++)
	{
		m_RainPositions[i] += Position2D(-6.f, 10.f);

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
			m_RainPositions[i].x() + 5.f, m_RainPositions[i].y() - 5.f,
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
