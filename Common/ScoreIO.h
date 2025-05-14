/**
 * @file   ScoreIO.h
 *
 * @brief  スコア保存読み込みのヘッダーファイル
 *
 * @author CatCode
 *
 * @date   2025/05/14
 */
#pragma once
#include <string>

/// <summary>
/// ハイスコアの保存
/// </summary>
bool SaveHighScore(int score, const std::string& filename = "highscore.dat");

/// <summary>
/// ハイスコアの読み込み
/// </summary>
int LoadHighScore(const std::string& filename = "highscore.dat");