/**
 * @file   TitleScene.h
 *
 * @brief  �^�C�g���V�[���̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/21
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
	TitleScene(WSI* wsi, SceneManager* sceneManager);
	~TitleScene();
	void Initialize() override;
	void Update()     override;
	void Render()     override;
	void Finalize()   override;
};

