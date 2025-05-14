/**
 * @file   ScoreIO.h
 *
 * @brief  �X�R�A�ۑ��ǂݍ��݂̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/05/14
 */
#pragma once
#include <string>

/// <summary>
/// �n�C�X�R�A�̕ۑ�
/// </summary>
bool SaveHighScore(int score, const std::string& filename = "highscore.dat");

/// <summary>
/// �n�C�X�R�A�̓ǂݍ���
/// </summary>
int LoadHighScore(const std::string& filename = "highscore.dat");