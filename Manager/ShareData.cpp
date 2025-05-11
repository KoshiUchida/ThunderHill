/**
 * @file   ShareData.cpp
 *
 * @brief  シェアデータの管理クラスのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/05/11
 */

#include "ShareData.h"

std::unique_ptr<ShareData> ShareData::s_Instance = nullptr;

ShareData& ShareData::GetInstance()
{
	if (!s_Instance)
		s_Instance.reset(new ShareData);

	return *s_Instance.get();
}

ShareData::ShareData() = default;

ShareData::~ShareData() = default;

std::string ShareData::Get(const std::string& key) const
{
	auto it = m_Data.find(key);
	if (it == m_Data.end())
		return std::string();

	return it->second;
}

void ShareData::Set(const std::string& key, const std::string& value)
{
	m_Data[key] = value;
}
