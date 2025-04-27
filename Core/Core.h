/**
 * @file   Core.h
 *
 * @brief  �V�X�e����������̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2024/11/11
 */

#pragma once
#include <memory>

class WSI;
class SceneManager;

/// <summary>
/// �R�A�N���X
/// </summary>
class Core
{
private:
	// �I��
	bool m_IsEnd;

	// �E�B���h�E�̐ݒ�
	WSI* mp_wsi;

	/*�}�l�[�W���֘A*/
	// �V�[���}�l�[�W��
	std::unique_ptr<SceneManager>      m_sceneManager;

public:
	/*���C���V�X�e��*/
	Core(WSI* pWSI);
	~Core();
	void Initialize();
	void Update();
	void Render();
	void Finalize();

	/*�擾*/
	bool isEnd() const { return m_IsEnd; }
};

