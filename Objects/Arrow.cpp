#include "Arrow.h"

#include <DxLib.h>

#include "../WindowSettingItems.h"
#include "../Manager/ResourceManager.h"

Arrow::Arrow() noexcept :
	ObjectBace(Transform2D()),
	s_Joypad{ Joypad::GetInstance() },
	m_Index{},
	m_Active{ false },
	m_Sprite{ ResourceManager::GetInstance().RequestTexture("Arrow.png") },
	m_MoveSE{ ResourceManager::GetInstance().RequestSound("ArrowSE.wav") }
{
}

Arrow::~Arrow() noexcept = default;

void Arrow::Initialize()
{
	WSI& wsi{ WSI::GetInstance() };

	m_Poses.push_back(Position2D(wsi.ScreenCenterX() - 30.f, wsi.ScreenBottom() - 55.f));
	m_Poses.push_back(Position2D(wsi.ScreenCenterX() - 30.f, wsi.ScreenBottom() - 40.f));

	m_Sprite.SetPosition(m_Poses[0]);
}

void Arrow::Update()
{
	if (m_Active && s_Joypad.GetLeftThumbLY())
	{
		PlaySoundMem(m_MoveSE, DX_PLAYTYPE_BACK);

		if (s_Joypad.GetLeftThumbLY() > 0)
		{
			m_Index--;

			if (m_Index < 0)
				m_Index = m_Poses.size() - 1;
		}
		else
		{
			m_Index++;
			if (m_Index >= m_Poses.size())
				m_Index = 0;
		}

		m_Sprite.SetPosition(m_Poses[m_Index]);
		m_Active = false;
	}

	else if (!m_Active && s_Joypad.GetLeftThumbLY() == 0.f)
		m_Active = true;
}

void Arrow::Render(const Camera& camera)
{
	m_Sprite.Draw();
}

void Arrow::Finalize()
{
}
