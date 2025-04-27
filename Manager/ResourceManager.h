/**
 * @file   RsourceManager.h
 *
 * @brief  ���\�[�X�̊Ǘ��N���X�̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/21
 */

#pragma once
#include <memory>
#include <unordered_map>
#include <string>

/// <summary>
/// ���\�[�X�̊Ǘ��N���X
/// </summary>
class ResourceManager final
{
private:
	// �ÓI�Ȏ��N���X�̃|�C���^
	static std::unique_ptr<ResourceManager> s_ResourceManager;

public:
	//���N���X�ւ̃|�C���^�擾�֐�
	static ResourceManager& GetInstance();

private:
	// �G�C���A�X�錾
	using ResourceCollection = std::unordered_map<std::string, int>;

public:
	static constexpr const char* DEFAULT_TEXTURE_DIRECTORY = "Resources/Textures/";
	static constexpr const char* DEFAULT_SOUND_DIRECTORY   = "Resources/Sounds/";
	static constexpr const char* DEFAULT_FONT_DIRECTORY    = "Resources/Fonts/";

private:
	ResourceCollection m_textures;
	ResourceCollection m_sounds;
	ResourceCollection m_fonts;

public:
	ResourceManager();

	~ResourceManager();

public:
	// �摜�f�[�^�̗v��
	int RequestTexture(const std::string& filename);

	// ���f�[�^�̗v��
	int RequestSound(const std::string& filename);

	// �t�H���g�f�[�^�̗v��
	int RequestFont(const std::string& filename, int fontSize);

	// �S���\�[�X�̍폜
	void Clear();
};

