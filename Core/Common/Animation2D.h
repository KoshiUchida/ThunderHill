/**
 * @file   Animation.h
 *
 * @brief  �A�j���[�V�����̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2024/12/04
 */

#pragma once
#include "Sprite2D.h"
#include <vector>
#include <string>

class Camera;

/// <summary>
/// �A�j���[�V�����f�[�^�̍ŏ��\����
/// </summary>
struct AnimationStep
{
	int time;
	int number;
};

/// <summary>
/// �A�j���[�V�����N���X
/// </summary>
class Animation2D
	: public Sprite2D
{
private:
	// �A�j���[�V�����f�[�^
	std::vector<AnimationStep> m_AnimationData;

	// ���݂̎���
	int m_Time;

public:
	/*���C���V�X�e��*/
	Animation2D(const std::string filename, const int texture, const int chipWidth, const int chipHeight, const float exRate = 1.f);
	~Animation2D();
	void Render();
	void Render(const Camera& camera);
	void ResetTime() { m_Time = 0; }
};

