#include "Player.h"
#include <DxLib.h>
#include "../Common/Colors.h"
#include "../WindowSettingItems.h"

static constexpr float Width{ 20.f };

Player::Player()
	: ObjectBace(Transform2D(Position2D(static_cast<float>(WSI::GetInstance().ScreenCenterX()), static_cast<float>(WSI::GetInstance().ScreenBottom() - 10)), 0.f))
	, m_Collider(m_Transform.GetPosition(), Width, Width)
	, p_Pad{ Joypad::GetInstance() }
{
}

Player::~Player() = default;

void Player::Initialize()
{
}

static constexpr float Speed{ 5.f };

void Player::Update()
{
	float StickL{ p_Pad.GetLeftThumbLXPercent() };

	if (StickL != 0.f)
		m_Transform.AddPositionX(Speed * StickL);

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
