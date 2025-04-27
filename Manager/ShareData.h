/**
 * @file   ShareData.h
 *
 * @brief  シェアデータの管理クラスのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#pragma once
#include <memory>
#include <unordered_map>
#include <string>

class ShareData final
{
private:
	static std::unique_ptr<ShareData> s_ShareData;

public:
	static ShareData& GetInstance();

private:
	std::unordered_map<std::string, std::string> m_shareData;

	ShareData();
public:
	~ShareData();

	// 共有データの取得
	std::string GetShareData(const std::string& key) const;

	// 共有データの設定
	void SetSharedData(const std::string& key, const std::string& value);
};
