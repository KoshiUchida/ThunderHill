/**
 * @file   TitleScene.h
 *
 * @brief  �^�C�g���V�[���̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#pragma once
#include "SceneBace.h"

#include <memory>

#include "../Common/Sprite2D.h"

/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene
	: public SceneBace
{
private:

public:
	// ���C���V�X�e��
	TitleScene();
	~TitleScene();
	void Initialize() override;
	void Update()     override;
	void Render()     override;
	void Finalize()   override;
};

