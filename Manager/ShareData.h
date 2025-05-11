/**
 * @file   ShareData.h
 *
 * @brief  �V�F�A�f�[�^�̊Ǘ��N���X�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/05/11
 */
#pragma once
#include <memory>
#include <unordered_map>
#include <string>

class ShareData final
{
private:
	static std::unique_ptr<ShareData> s_Instance;
	std::unordered_map<std::string, std::string> m_Data;

	ShareData();

public:
	~ShareData();

	static ShareData& GetInstance();

	std::string Get(const std::string& key) const;
	void Set(const std::string& key, const std::string& value);

	bool HasKey(const std::string& key) const{
		return m_Data.find(key) != m_Data.end();
	}
};
