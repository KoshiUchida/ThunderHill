#include "FlyingDebris.h"

#include "DxLib.h"

#include "../WindowSettingItems.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/ObjectManager.h"
#include "../Manager/SceneManager.h"
#include "../Common/CCRandom.h"

#include "../Common/Colors.h"

#include "Player.h"

static constexpr float Width { 11.f };
static constexpr float Height{ Width };

static constexpr float JumpPower{ -2.f };
static constexpr float MaxGravity{ -JumpPower * 2.f };
static constexpr float AccGravity{ 0.2f };
static constexpr float StoGravity{ MaxGravity };

FlyingDebris::FlyingDebris() :
	ObjectBace(Transform2D()),
	m_Collider{ Width, Height },
	m_Under{},
	m_Gravity{ MaxGravity, AccGravity, StoGravity },
	m_Sprite{ ResourceManager::GetInstance().RequestTexture("Umbrella.png") },
	p_PlayerCollider{ nullptr }
{
}

FlyingDebris::~FlyingDebris() = default;

static constexpr int Under{ 20 };

void FlyingDebris::Initialize()
{
	WSI& wsi{ WSI::GetInstance() };

	m_Under = wsi.ScreenBottom() - Under;

	m_Transform.SetPositionX(wsi.ScreenRight());
	m_Transform.SetPositionY(m_Under - CCRandom::GetInstane().Rand(0, 5));

	p_PlayerCollider = &static_cast<Player*>(ObjectManager::GetInstance().GetObjectPtr("Player"))->GetCollider();
}

static constexpr float RotateSpeed{ -7.f };

void FlyingDebris::Update()
{
	m_Transform.AddPositionX(-1.f);

	m_Transform.AddPositionY(JumpPower + m_Gravity.speed());

	if (m_Transform.GetPositionY() >= m_Under)
		m_Gravity.Stop();
	else
		m_Gravity.Up();

	m_Transform.AddRotate(RotateSpeed);

	m_Collider.SetPosition(m_Transform.GetPosition());
	m_Sprite.SetTransform(m_Transform);


	if (Collisions::Detection(m_Collider, *p_PlayerCollider))
		SceneManager::GetInstance().RequestSceneChange("Result");


	if (m_Transform.GetPositionX() < -Under)
		Destroy();
}

void FlyingDebris::Render(const Camera& camera)
{
#if defined(_DEBUG)
	Collisions::Box box = m_Collider.GetBox();
	DrawBox(box.left, box.top, box.right, box.bottom, Colors::SpringGreen, false);
#endif

	m_Sprite.Draw();
}

void FlyingDebris::Finalize()
{
}
