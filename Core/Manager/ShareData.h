/**
 * @file   ShareData.h
 *
 * @brief  �V�F�A�f�[�^�̊Ǘ��N���X�̃w�b�_�[�t�@�C��
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

	// ���L�f�[�^�̎擾
	std::string GetShareData(const std::string& key) const;

	// ���L�f�[�^�̐ݒ�
	void SetSharedData(const std::string& key, const std::string& value);
};
