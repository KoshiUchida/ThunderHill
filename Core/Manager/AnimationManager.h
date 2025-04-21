/**
 * @file   AnimationManaager.h
 *
 * @brief  �A�j���[�V�����̊Ǘ��N���X�̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2024/11/04
 */

#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <DxLib.h>
#include "../Common/Geometry2D.h"

class Animation2D;
class Camera;

/// <summary>
/// �A�j���[�V�����̊Ǘ��N���X
/// </summary>
class AnimationManager
{
private:
	// �G�C���A�X�錾
	using AnimationCollection = std::unordered_map<std::string, std::unique_ptr<Animation2D>>;

	// �A�j���[�V�����̏W��
	AnimationCollection m_animations;

	// ���݂̃A�j���[�V����
	Animation2D* m_pCurrentAnimation;
	// �ύX�v���̂������A�j���[�V����
	Animation2D* m_pRequestedAnimation;

	// ���݂̃A�j���[�V�����̖��O
	std::string m_CurrentName;

	// ���݂̃g�����X�t�H�[��
	Transform2D nowTransform;

public:
	/*���C���V�X�e��*/
	AnimationManager();
	~AnimationManager();
	void Update(const Transform2D& _transform);
	void Render();
	void Render(const Camera& camera);

	// �A�j���[�V�����̓o�^
	void addAnimation(const std::string& animationName, std::unique_ptr<Animation2D> animation);

	// �X�^�[�g�̃A�j���[�V�����̐ݒ�
	void SetStartAnimation(const std::string& startAnimationName);

	// �A�j���[�V�����ύX�̗v��
	void RequestAnimationChange(const std::string& changeAnimation);

private:
	// �A�j���[�V�����̕ύX
	void ChangeAnimation();

public:
	/*�擾*/
	std::string GetCurrentName() { return m_CurrentName; }
};

