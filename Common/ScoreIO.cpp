/**
 * @file   ScoreIO.cpp
 *
 * @brief  スコア保存読み込みのソースファイル
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
        std::cerr << "ハイスコアの保存に失敗しました。\n";
        return false;
    }
    ofs.write(reinterpret_cast<const char*>(&score), sizeof(score));
}

int LoadHighScore(const std::string& filename)
{
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs)
    {
        std::cerr << "ハイスコアファイルが見つかりません。初期値（0）を使用します。\n";
        return 0;
    }

    int score = 0;
    ifs.read(reinterpret_cast<char*>(&score), sizeof(score));

    if (ifs.gcount() != sizeof(score))
    {
        std::cerr << "ハイスコアファイルの読み込みに失敗しました。初期値（0）を使用します。\n";
        return 0;
    }

    return score;
}
