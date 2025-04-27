/**
 * @file   Animation2D.cpp
 *
 * @brief  �A�j���[�V�����̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2024/12/04
 */

#include "Animation2D.h"

#include "FileIO.h"
#include "Camera.h"
//#include "../Screen.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Animation2D::Animation2D(const std::string filename, const int texture, const int chipWidth, const int chipHeight, const float exRate)
	: Sprite2D(texture, chipWidth, chipHeight, exRate)
	, m_Time{}
{
	// �A�j���[�V�����f�[�^�̓ǂݍ���
	m_AnimationData = ReadAnimation(filename);

	// ���̃v���W�F�N�g�̃����^�C���ɍ��킹��
	for (int i = 0; i < m_AnimationData.size(); i++)
	{
		//m_AnimationData[i].time /= scr::RunTime;
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Animation2D::~Animation2D()
{
	m_AnimationData.clear();
}

/// <summary>
/// �`�揈��
/// </summary>
void Animation2D::Render()
{
	// �؂�ւ��^�C���ł��邩���m�F
	for (int i = 0; i < this->m_AnimationData.size(); i++)
	{
		if (this->m_Time == this->m_AnimationData[i].time)
			this->m_Page = this->m_AnimationData[i].number;
	}

	// �X�v���C�g�̕`��
	this->Draw();

	// �^�C���̍X�V
	this->m_Time++;

	// �^�C�����A�j���[�V�����̍ő�̐؂�ւ��^�C���̐ݒ�𒴂����Ƃ��ɂO�ɂ��ǂ�
	if (this->m_Time > this->m_AnimationData[this->m_AnimationData.size() - 1].time)
	{
		this->m_Time = 0;
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void Animation2D::Render(const Camera& camera)
{
	// �؂�ւ��^�C���ł��邩���m�F
	for (int i = 0; i < this->m_AnimationData.size(); i++)
	{
		if (this->m_Time == this->m_AnimationData[i].time)
			this->m_Page = this->m_AnimationData[i].number;
	}

	// �X�v���C�g�̕`��
	this->Draw(camera);

	// �^�C���̍X�V
	this->m_Time++;

	// �^�C�����A�j���[�V�����̍ő�̐؂�ւ��^�C���̐ݒ�𒴂����Ƃ��ɂO�ɂ��ǂ�
	if (this->m_Time > this->m_AnimationData[this->m_AnimationData.size() - 1].time)
	{
		this->m_Time = 0;
	}
}
