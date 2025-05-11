/**
 * @file   Player.cpp
 *
 * @brief  プレイヤーオブジェクトのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/05/11
 */
#include "Player.h"

#include <DxLib.h>
#include "../Common/Colors.h"
#include "../WindowSettingItems.h"
#include "../Manager/ResourceManager.h"

static constexpr float Width{ 13.f };
static constexpr float Hight{ Width };

static constexpr float MaxSpeed{ 2.5f };
static constexpr float AccSpeed{ 0.3f };
static constexpr float StoSpeed{ 1.2f };

static constexpr float JumpPower{ -5.f };
static constexpr float MaxGravity{ -JumpPower * 2.f };
static constexpr float AccGravity{ 0.35f };
static constexpr float StoGravity{ MaxGravity };

/// <summary>
/// コンストラクタ
/// </summary>
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
	m_Gravity{ MaxGravity, AccGravity, StoGravity },
	m_JumpSE{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player() = default;

/// <summary>
/// 初期化処理
/// </summary>
void Player::Initialize()
{
	WSI& wsi{ WSI::GetInstance() };

	m_MaxPosX = static_cast<float>(wsi.ScreenRight());
	m_MinPosX = static_cast<float>(wsi.ScreenLeft());

	m_CanJump = true;

	m_Under = m_Transform.GetPositionY();

	ResourceManager& rm{ ResourceManager::GetInstance() };

	m_JumpSE = rm.RequestSound("JumpSE.wav");
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update()
{
	Move();

	Jump();

	m_Collider.SetPosition(m_Transform.GetPosition());
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Render(const Camera& camera)
{
	Collisions::Box box = m_Collider.GetBox();
	DrawBox(static_cast<int>(box.left), static_cast<int>(box.top),
		static_cast<int>(box.right), static_cast<int>(box.bottom),
		Colors::White, true);
}

/// <summary>
/// 終了処理
/// </summary>
void Player::Finalize()
{
	PlaySoundMem(ResourceManager::GetInstance().RequestSound("HaveDamageSE.wav"), DX_PLAYTYPE_BACK);
}

/// <summary>
/// 移動操作処理
/// </summary>
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

/// <summary>
/// ジャンプ操作処理
/// </summary>
void Player::Jump()
{
	if (m_CanJump && p_Pad.GetLeftThumbLY() > 0.f)
	{
		m_CanJump = false;
		m_IsJumping = true;
		m_Gravity.Stop();
		
		PlaySoundMem(m_JumpSE, DX_PLAYTYPE_BACK);
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

/// <summary>
/// コライダーの取得関数
/// </summary>
Collisions::BoxCollider& Player::GetCollider()
{
	return m_Collider;
}
