/**
 * @file   Error.h
 *
 * @brief  エラー表示関数群のヘッダファイル
 *
 * @author CatCode
 *
 * @date   11/03
 */

#include "Error.h"

#include <iostream>
#include <DxLib.h>

/// <summary>
/// エラーメッセージを表示する
/// </summary>
/// <param name="errorMessage">エラー内容</param>
void printError(const std::string& errorMessage)
{
	// セルにエラーメッセージを出力
	std::cerr << errorMessage << std::endl;

	// マウスが非表示の際に表示に切り替える
	if (!GetMouseDispFlag())
		SetMouseDispFlag(TRUE);

	// エラーメッセージを生成
	MessageBox(NULL, errorMessage.c_str(), "エラー", MB_OK | MB_ICONERROR);
}
