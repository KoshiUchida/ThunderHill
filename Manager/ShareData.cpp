/**
 * @file   ShareData.cpp
 *
 * @brief  シェアデータの管理クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#include "ShareData.h"

std::unique_ptr<ShareData> ShareData::s_ShareData = nullptr;

ShareData& ShareData::GetInstance()
{
	if (!s_ShareData)
		s_ShareData.reset(new ShareData);

	return *s_ShareData.get();
}

ShareData::ShareData() = default;

ShareData::~ShareData() = default;

std::string ShareData::GetShareData(const std::string& key) const
{
	if (m_shareData.count(key) == 0)
	{
		// TODO:ERROR
		return std::string();
	}

	return m_shareData.at(key);
}

void ShareData::SetSharedData(const std::string& key, const std::string& value)
{
	m_shareData[key] = value;
}
