/**
 * @file   RsourceManager.h
 *
 * @brief  リソースの管理クラスのヘッダファイル
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
/// リソースの管理クラス
/// </summary>
class ResourceManager final
{
private:
	// 静的な自クラスのポインタ
	static std::unique_ptr<ResourceManager> s_ResourceManager;

public:
	//自クラスへのポインタ取得関数
	static ResourceManager& GetInstance();

private:
	// エイリアス宣言
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
	// 画像データの要求
	int RequestTexture(const std::string& filename);

	// 音データの要求
	int RequestSound(const std::string& filename);

	// フォントデータの要求
	int RequestFont(const std::string& filename, int fontSize);

	// 全リソースの削除
	void Clear();
};

