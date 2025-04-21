/**
 * @file   FileIO.cpp
 *
 * @brief  ファイル入出力関数のソースファイル
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
/// CSVファイルの読み込み
/// </summary>
/// <param name="filename">ファイル名</param>
/// <returns>マトリックス配列データ</returns>
vector<vector<int>> ReadCSV(const string& filename)
{
	vector<vector<int>> csvData;
    const string fullpath = DEFAULT_DATA_DIRECTORY + filename;
	ifstream file(fullpath);
	string line;

	if (!file.is_open())
	{
		printError("ファイルを開けませんでした : " + filename);
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
/// アニメーションデータの読み取り
/// </summary>
/// <param name="filename">ファイル名前</param>
/// <returns>アニメーションデータ</returns>
std::vector<AnimationStep> ReadAnimation(const std::string& filename)
{
    // ファイル読み取りの完全なパス
    const std::string fullpath = DEFAULT_DATA_DIRECTORY + filename;

    // ファイルの読み込み
    std::ifstream file(fullpath);
    json j;
    file >> j;
    file.close();

    // データの抽出
    std::vector<AnimationStep> animationData;
    for (const auto& item : j["animations"]) {
        AnimationStep frame{};
        frame.time = item["time"];
        frame.number = item["number"];
        animationData.push_back(frame);
    }

    // 戻り値の返却
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

