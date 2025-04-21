/**
 * @file   AnimationManaager.h
 *
 * @brief  �A�j���[�V�����̊Ǘ��N���X�̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/01/10
 */

#include "AnimationManager.h"

#include "../Common/Animation2D.h"
#include "../Common/Error.h"
#include "../Common/Camera.h"

/// <summary>
/// �R���X�g���N�g
/// </summary>
AnimationManager::AnimationManager()
	: m_animations         {}
	, m_pCurrentAnimation  { nullptr }
	, m_pRequestedAnimation{ nullptr }
	, m_CurrentName        {}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
AnimationManager::~AnimationManager()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="position">���W</param>
/// <param name="rotate">����</param>
void AnimationManager::Update(const Transform2D& _transform)
{
	if (m_pCurrentAnimation)
	{
		// �A�j���[�V�����̍��W���X�V
		m_pCurrentAnimation->SetTransform(_transform);

		// �e�N�X�`���̌����𒲂ׂ�
		m_pCurrentAnimation->FlipTexture(_transform.GetAngle() < 270.f && _transform.GetAngle() > 90.f || _transform.GetAngle() < -90.f && _transform.GetAngle() > -270.f);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void AnimationManager::Render()
{
	// �V�[���̕ύX�v�����������ꍇ�̓V�[���̕ύX���s��
	if (m_pRequestedAnimation)
	{
		ChangeAnimation();
	}

	// ���݂̃V�[����`��
	if (m_pCurrentAnimation)
		m_pCurrentAnimation->Draw();
}

/// <summary>
/// �`�揈��
/// </summary>
void AnimationManager::Render(const Camera& camera)
{
	// �V�[���̕ύX�v�����������ꍇ�̓V�[���̕ύX���s��
	if (m_pRequestedAnimation)
	{
		ChangeAnimation();
	}

	// ���݂̃V�[����`��
	if (m_pCurrentAnimation)
		m_pCurrentAnimation->Render(camera);
}

/// <summary>
/// �A�j���[�V�����̒ǉ�
/// </summary>
/// <param name="sceneName">�o�^�A�j���[�V�����̖��O</param>
/// <param name="animation">�o�^�A�j���[�V����</param>
void AnimationManager::addAnimation(const std::string& animationName, std::unique_ptr<Animation2D> animation)
{
	m_animations.emplace(animationName, std::move(animation));
}

/// <summary>
/// �J�n�A�j���[�V�����̐ݒ�
/// </summary>
/// <param name="startAnimationName">�J�n�A�j���[�V�����̖��O</param>
void AnimationManager::SetStartAnimation(const std::string& startAnimationName)
{
	RequestAnimationChange(startAnimationName);
	m_CurrentName = startAnimationName;
}

/// <summary>
/// �A�j���[�V�����ύX�̗v��
/// </summary>
/// <param name="changeAnimation">�ύX�\��̃A�j���[�V������</param>
void AnimationManager::RequestAnimationChange(const std::string& changeAnimation)
{
	if (m_animations.count(changeAnimation) == 0)
	{
		printError(changeAnimation + "�A�j���[�V�����͓o�^����Ă��܂���B");
		return;
	}

	if (m_pCurrentAnimation)
		nowTransform = m_pCurrentAnimation->GetTransform();

	m_CurrentName = changeAnimation;
	m_pRequestedAnimation = m_animations[changeAnimation].get();
}

/// <summary>
/// �A�j���[�V�����̕ύX
/// </summary>
void AnimationManager::ChangeAnimation()
{
	if (!m_pRequestedAnimation)
		return;

	m_pCurrentAnimation = m_pRequestedAnimation;

	m_pCurrentAnimation->Initialize();
	m_pCurrentAnimation->ResetTime();
	m_pCurrentAnimation->SetTransform(nowTransform);

	m_pRequestedAnimation = nullptr;
}