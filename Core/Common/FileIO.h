/**
 * @file   FileIO.h
 *
 * @brief  �t�@�C�����o�͊֐��̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/02/10
 */

#pragma once
#include <vector>
#include <string>
#include "Animation2D.h"
#include "../../WindowSettingItems.h"

std::vector<std::vector<int>> ReadCSV(const std::string& filename);

std::vector<AnimationStep> ReadAnimation(const std::string& filename);

WindowSettings ReadWindowSettings(const std::string& filename);