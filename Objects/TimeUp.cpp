/**
 * @file   TimeUp.cpp
 *
 * @brief  ���ԏ㏸�A�C�e���I�u�W�F�N�g�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/05/11
 */
#include "TimeUp.h"

#include <DxLib.h>
#include "../Common/Colors.h"

#include "../Manager/ResourceManager.h"
#include "../Manager/ObjectManager.h"

#include "Player.h"
#include "TimeLimitUI.h"

static constexpr float Width{ 11.f };
static constexpr float Height{ Width };

/// <summary>
/// �R���X�g���N�^
/// </summary>
TimeUp::TimeUp(const Position2D& pos) noexcept:
	ObjectBace(Transform2D(pos, 0.f)),
	m_Collider{ Width, Height },
	m_Sprite  { ResourceManager::GetInstance().RequestTexture("Timer.png") },
	p_PlayerCollider{ nullptr },
	m_Time{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TimeUp::~TimeUp() noexcept = default;

/// <summary>
/// ����������
/// </summary>
void TimeUp::Initialize()
{
	m_Collider.SetPosition(GetPosition());

	p_PlayerCollider = &static_cast<Player*>(ObjectManager::GetInstance().GetObjectPtr("Player"))->GetCollider();

	m_Time = 0;
}

static constexpr int LiveTime{ 300 };

/// <summary>
/// �X�V����
/// </summary>
void TimeUp::Update()
{
	m_Time++;
	if (m_Time >= LiveTime)
		Destroy();

	Collider();

	m_Sprite.SetPosition(GetPosition());
}

/// <summary>
/// �`�揈��
/// </summary>
void TimeUp::Render(const Camera& camera)
{
	m_Sprite.Draw();

#if defined(_DEBUG)
	Collisions::Box box = m_Collider.GetBox();

	DrawBox(box.left, box.top, box.left, box.bottom,
		Colors::SpringGreen, false);
#endif
}

/// <summary>
/// �I������
/// </summary>
void TimeUp::Finalize()
{
}

static constexpr int AddTimeVol{ 50 };

/// <summary>
/// �d�Ȃ菈��
/// </summary>
void TimeUp::Collider()
{
	if (Collisions::Detection(*p_PlayerCollider, m_Collider))
	{
		static_cast<TimeLimitUI*>(ObjectManager::GetInstance().GetObjectPtr("TimeLimitUI"))->AddTime(AddTimeVol);

		PlaySoundMem(ResourceManager::GetInstance().RequestSound("TimeUpSE.wav"), DX_PLAYTYPE_BACK);

		Destroy();
	}
}
