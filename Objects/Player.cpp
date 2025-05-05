#include "Player.h"
#include <DxLib.h>
#include "../Common/Colors.h"
#include "../WindowSettingItems.h"

static constexpr float Width{ 18.f };
static constexpr float Hight{ 18.f };

Player::Player():
	ObjectBace(Transform2D(Position2D(static_cast<float>(WSI::GetInstance().ScreenCenterX()), static_cast<float>(WSI::GetInstance().ScreenBottom() - 25)), 0.f)),
	m_Collider(m_Transform.GetPosition(), Width, Hight),
	p_Pad{ Joypad::GetInstance() },
	m_MaxPosX{},
	m_MinPosX{}
{
}

Player::~Player() = default;

void Player::Initialize()
{
	WSI& wsi{ WSI::GetInstance() };

	m_MaxPosX = static_cast<float>(wsi.ScreenRight());
	m_MinPosX = static_cast<float>(wsi.ScreenLeft());
}

static constexpr float Speed{ 2.5f };

void Player::Update()
{
	float StickL{ p_Pad.GetLeftThumbLXPercent() };

	if (StickL != 0.f)
	{
		m_Transform.AddPositionX(Speed * StickL);

		float PosX = m_Transform.GetPositionX();

		if (PosX < m_MinPosX)
			m_Transform.SetPositionX(m_MinPosX);
		if (PosX > m_MaxPosX)
			m_Transform.SetPositionX(m_MaxPosX);
	}

	m_Collider.SetPosition(m_Transform.GetPosition());
}

void Player::Render(const Camera& camera)
{
	Collisions::Box box = m_Collider.GetBox();
	DrawBox(static_cast<int>(box.left), static_cast<int>(box.top),
		static_cast<int>(box.right), static_cast<int>(box.bottom),
		Colors::White, true);
}

void Player::Finalize()
{
}

Collisions::BoxCollider& Player::GetCollider()
{
	return m_Collider;
}
