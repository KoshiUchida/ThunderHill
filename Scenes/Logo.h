/**
 * @file   Logo.h
 *
 * @brief  ���S�V�[���̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/05/04
 */

#pragma once
#include "SceneBace.h"
#include <memory>

class Sprite2D;

/// <summary>
/// ���S�V�[��
/// </summary>
class Logo :
    public SceneBace
{
private:
	std::unique_ptr<Sprite2D> ms_Logo;

	int m_Time;

	static constexpr int SceneChangeTime{ 63 };

	// ���S�̓����x
	int m_LogoAlpha;

	// �����x���オ�邩�ǂ���
	bool m_IsUpAlpha;


public:
	// ���C���V�X�e��
	Logo();
	~Logo();
	void Initialize() override;
	void Update()     override;
	void Render()     override;
	void Finalize()   override;
};

