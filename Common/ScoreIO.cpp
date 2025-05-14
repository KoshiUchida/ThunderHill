/**
 * @file   ScoreIO.cpp
 *
 * @brief  �X�R�A�ۑ��ǂݍ��݂̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/05/14
 */
#include "ScoreIO.h"
#include <fstream>
#include <iostream>

bool SaveHighScore(int score, const std::string& filename)
{
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs)
    {
        std::cerr << "�n�C�X�R�A�̕ۑ��Ɏ��s���܂����B\n";
        return false;
    }
    ofs.write(reinterpret_cast<const char*>(&score), sizeof(score));
}

int LoadHighScore(const std::string& filename)
{
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs)
    {
        std::cerr << "�n�C�X�R�A�t�@�C����������܂���B�����l�i0�j���g�p���܂��B\n";
        return 0;
    }

    int score = 0;
    ifs.read(reinterpret_cast<char*>(&score), sizeof(score));

    if (ifs.gcount() != sizeof(score))
    {
        std::cerr << "�n�C�X�R�A�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B�����l�i0�j���g�p���܂��B\n";
        return 0;
    }

    return score;
}
