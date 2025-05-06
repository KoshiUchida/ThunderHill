#include "Player.h"
#include <DxLib.h>
#include "../Common/Colors.h"
#include "../WindowSettingItems.h"

static constexpr float Width{ 18.f };
static constexpr float Hight{ 18.f };

static constexpr float MaxSpeed{ 2.5f };
static constexpr float AccSpeed{ 0.3f };
static constexpr float StoSpeed{ 1.2f };

static constexpr float JumpPower{ -5.f };
static constexpr float MaxGravity{ -JumpPower * 2.f };
static constexpr float AccGravity{ 0.5f };
static constexpr float StoGravity{ MaxGravity };

Player::Player():
	ObjectBace(Transform2D(Position2D(static_cast<float>(WSI::GetInstance().ScreenCenterX()), static_cast<float>(WSI::GetInstance().ScreenBottom() - 25)), 0.f)),
	m_Collider(m_Transform.GetPosition(), Width, Hight),
	p_Pad{ Joypad::GetInstance() },
	m_MaxPosX{},
	m_MinPosX{},
	m_Speed{ MaxSpeed, AccSpeed, StoSpeed },
	m_CanJump{},
	m_IsJumping{},
	m_Under{},
	m_Gravity{ MaxGravity, AccGravity, StoGravity }
{
}

Player::~Player() = default;

void Player::Initialize()
{
	WSI& wsi{ WSI::GetInstance() };

	m_MaxPosX = static_cast<float>(wsi.ScreenRight());
	m_MinPosX = static_cast<float>(wsi.ScreenLeft());

	m_CanJump = true;

	m_Under = m_Transform.GetPositionY();
}

void Player::Update()
{
	Move();

	Jump();

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

void Player::Move()
{
	float StickL{ p_Pad.GetLeftThumbLXPercent() };

	if (StickL != 0.f)
		m_Speed.Up();
	else
		m_Speed.Stop();

	m_Transform.AddPositionX(m_Speed.speed() * StickL);

	float PosX = m_Transform.GetPositionX();

	if (PosX < m_MinPosX)
		m_Transform.SetPositionX(m_MinPosX);
	if (PosX > m_MaxPosX)
		m_Transform.SetPositionX(m_MaxPosX);
}

void Player::Jump()
{
	if (m_CanJump && p_Pad.GetLeftThumbLY() > 0.f)
	{
		m_CanJump = false;
		m_IsJumping = true;
		m_Gravity.Stop();
	}

	if (!m_IsJumping)
		return;

	m_Transform.AddPositionY(JumpPower + m_Gravity.speed());

	m_Gravity.Up();

	if (m_Transform.GetPositionY() >= m_Under)
	{
		m_IsJumping = false;
		m_CanJump = true;
	}
}

Collisions::BoxCollider& Player::GetCollider()
{
	return m_Collider;
}
