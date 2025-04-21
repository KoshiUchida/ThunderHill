/**
 * @file   FileIO.cpp
 *
 * @brief  �t�@�C�����o�͊֐��̃\�[�X�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/02/10
 */

#include "FileIO.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include "Error.h"

#define DEFAULT_DATA_DIRECTORY "Resources\\Datas\\"

using namespace std;
using json = nlohmann::json;

/// <summary>
/// CSV�t�@�C���̓ǂݍ���
/// </summary>
/// <param name="filename">�t�@�C����</param>
/// <returns>�}�g���b�N�X�z��f�[�^</returns>
vector<vector<int>> ReadCSV(const string& filename)
{
	vector<vector<int>> csvData;
    const string fullpath = DEFAULT_DATA_DIRECTORY + filename;
	ifstream file(fullpath);
	string line;

	if (!file.is_open())
	{
		printError("�t�@�C�����J���܂���ł��� : " + filename);
		return csvData;
	}

    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        vector<int> row;

        while (getline(ss, cell, ',')) {
            row.push_back(stoi(cell));
        }

        csvData.push_back(row);
    }

    file.close();
    return csvData;
}

/// <summary>
/// �A�j���[�V�����f�[�^�̓ǂݎ��
/// </summary>
/// <param name="filename">�t�@�C�����O</param>
/// <returns>�A�j���[�V�����f�[�^</returns>
std::vector<AnimationStep> ReadAnimation(const std::string& filename)
{
    // �t�@�C���ǂݎ��̊��S�ȃp�X
    const std::string fullpath = DEFAULT_DATA_DIRECTORY + filename;

    // �t�@�C���̓ǂݍ���
    std::ifstream file(fullpath);
    json j;
    file >> j;
    file.close();

    // �f�[�^�̒��o
    std::vector<AnimationStep> animationData;
    for (const auto& item : j["animations"]) {
        AnimationStep frame{};
        frame.time = item["time"];
        frame.number = item["number"];
        animationData.push_back(frame);
    }

    // �߂�l�̕ԋp
    return animationData;
}

WindowSettings ReadWindowSettings(const std::string& filename)
{
    const std::string fullpath = DEFAULT_DATA_DIRECTORY + filename;

    std::ifstream file(fullpath);
    json j;
    file >> j;
    file.close();

    WindowSettings settings;
    settings.WindowTitle = j["WindowTitle"];
    settings.WindowSizeExtendRate = j["WindowSizeExtendRate"];
    settings.FragChangeWindowMode = j["FlagChangeWindowMode"];
    settings.Screen.width = j["Screen"]["width"];
    settings.Screen.height = j["Screen"]["height"];
    settings.ColorBitDepth = j["ColorBitDepth"];
    settings.RunTimeMin = j["RunTimeMin"];
    settings.Volume = j["Volume"];
    settings.Font = j["Font"].get<std::string>();
    settings.FontSize = j["FontSize"];
    settings.FragOutApplicationLogValid = j["FragOutApplicationLogValid"];


    return settings;
}

