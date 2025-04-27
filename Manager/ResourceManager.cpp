/**
 * @file   RsourceManager.cpp
 *
 * @brief  リソースの管理クラスのソースファイル
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
/// コンストラクタ
/// </summary>
ResourceManager::ResourceManager() = default;

/// <summary>
/// デストラクタ
/// </summary>
ResourceManager::~ResourceManager()
{
	// 全リソースの解放
	Clear();
}

/// <summary>
/// 画像データの要求
/// </summary>
/// <param name="filename">ファイルの名前</param>
/// <returns>テクスチャのハンドルもしくはエラー値</returns>
int ResourceManager::RequestTexture(const std::string& filename)
{
	if (m_textures.count(filename) == 0)
	{
		std::string fullPath = DEFAULT_TEXTURE_DIRECTORY + filename;
		int textureHandle = LoadGraph(fullPath.c_str());

		if (textureHandle == -1)
		{
			printError("エラー：ファイル" + fullPath + "を開けませんでした。\n");

			return -1;
		}


		m_textures.insert(std::make_pair(filename, textureHandle));
	}

	return m_textures[filename];
}

/// <summary>
/// 音データの要求
/// </summary>
/// <param name="filename">ファイルの名前</param>
/// <returns>サウンドのハンドルもしくはエラー値</returns>
int ResourceManager::RequestSound(const std::string& filename)
{
	if (m_sounds.count(filename) == 0)
	{
		std::string fullPath = DEFAULT_SOUND_DIRECTORY + filename;
		int soundHandle = LoadSoundMem(fullPath.c_str());

		if (soundHandle == -1)
		{
			printError("エラー：ファイル" + fullPath + "を開けませんでした。\n");

			return -1;
		}


		m_sounds.insert(std::make_pair(filename, soundHandle));
	}

	return m_sounds[filename];
}

/// <summary>
/// フォントデータの要求
/// </summary>
int ResourceManager::RequestFont(const std::string& filename, int fontSize)
{
	if (m_fonts.count(filename) == 0)
	{
		std::string fullPath = DEFAULT_FONT_DIRECTORY + filename;
		int fontsHandle = CreateFontToHandle(fullPath.c_str(), fontSize, -1, DX_FONTTYPE_NORMAL);

		if (fontsHandle == -1)
		{
			printError("エラー：ファイル" + fullPath + "を開けませんでした。\n");

			return -1;
		}


		m_fonts.insert(std::make_pair(filename, fontsHandle));
	}

	return m_fonts[filename];
}

/// <summary>
/// 全リソースの削除
/// </summary>
void ResourceManager::Clear()
{
	// テクスチャを削除
	for (auto& element : m_textures)
	{
		DeleteGraph(element.second);
	}
	m_textures.clear();

	// サウンドを削除
	for (auto& element : m_sounds)
	{
		DeleteSoundMem(element.second);
	}
	m_sounds.clear();

	// フォントを削除
	for (auto& element : m_fonts)
	{
		DeleteFontToHandle(element.second);
	}
	m_fonts.clear();
}
