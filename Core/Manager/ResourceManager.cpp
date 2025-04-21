/**
 * @file   RsourceManager.cpp
 *
 * @brief  ���\�[�X�̊Ǘ��N���X�̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/04/21
 */

#include "ResourceManager.h"

#include <DxLib.h>
#include "../Common/Error.h"

std::unique_ptr<ResourceManager> ResourceManager::s_ResourceManager = nullptr;

ResourceManager& ResourceManager::GetInstance()
{
	if (!s_ResourceManager)
		s_ResourceManager.reset(new ResourceManager());

	return *s_ResourceManager.get();
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
ResourceManager::ResourceManager() = default;

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResourceManager::~ResourceManager()
{
	// �S���\�[�X�̉��
	Clear();
}

/// <summary>
/// �摜�f�[�^�̗v��
/// </summary>
/// <param name="filename">�t�@�C���̖��O</param>
/// <returns>�e�N�X�`���̃n���h���������̓G���[�l</returns>
int ResourceManager::RequestTexture(const std::string& filename)
{
	if (m_textures.count(filename) == 0)
	{
		std::string fullPath = DEFAULT_TEXTURE_DIRECTORY + filename;
		int textureHandle = LoadGraph(fullPath.c_str());

		if (textureHandle == -1)
		{
			printError("�G���[�F�t�@�C��" + fullPath + "���J���܂���ł����B\n");

			return -1;
		}


		m_textures.insert(std::make_pair(filename, textureHandle));
	}

	return m_textures[filename];
}

/// <summary>
/// ���f�[�^�̗v��
/// </summary>
/// <param name="filename">�t�@�C���̖��O</param>
/// <returns>�T�E���h�̃n���h���������̓G���[�l</returns>
int ResourceManager::RequestSound(const std::string& filename)
{
	if (m_sounds.count(filename) == 0)
	{
		std::string fullPath = DEFAULT_SOUND_DIRECTORY + filename;
		int soundHandle = LoadSoundMem(fullPath.c_str());

		if (soundHandle == -1)
		{
			printError("�G���[�F�t�@�C��" + fullPath + "���J���܂���ł����B\n");

			return -1;
		}


		m_sounds.insert(std::make_pair(filename, soundHandle));
	}

	return m_sounds[filename];
}

/// <summary>
/// �t�H���g�f�[�^�̗v��
/// </summary>
int ResourceManager::RequestFont(const std::string& filename, int fontSize)
{
	if (m_fonts.count(filename) == 0)
	{
		std::string fullPath = DEFAULT_FONT_DIRECTORY + filename;
		int fontsHandle = CreateFontToHandle(fullPath.c_str(), fontSize, -1, DX_FONTTYPE_NORMAL);

		if (fontsHandle == -1)
		{
			printError("�G���[�F�t�@�C��" + fullPath + "���J���܂���ł����B\n");

			return -1;
		}


		m_fonts.insert(std::make_pair(filename, fontsHandle));
	}

	return m_fonts[filename];
}

/// <summary>
/// �S���\�[�X�̍폜
/// </summary>
void ResourceManager::Clear()
{
	// �e�N�X�`�����폜
	for (auto& element : m_textures)
	{
		DeleteGraph(element.second);
	}
	m_textures.clear();

	// �T�E���h���폜
	for (auto& element : m_sounds)
	{
		DeleteSoundMem(element.second);
	}
	m_sounds.clear();

	// �t�H���g���폜
	for (auto& element : m_fonts)
	{
		DeleteFontToHandle(element.second);
	}
	m_fonts.clear();
}
