/**
 * @file   Joypad.h
 *
 * @brief  ジョイパッドの管理クラスのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/04/26
 */

#pragma once
#include <memory>
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "Xinput.lib")

/// <summary>
/// ジョイパッドの管理クラス
/// </summary>
class Joypad final
{
	/**
	* 使用上の注意
	* 必ず更新処理関数をどこかで呼び出さないといけない
	*/

private:
	// 自身の実体
	static std::unique_ptr<Joypad> s_Joypad;

public:
	// 実体の取得関数
	static Joypad& GetInstance();

	void Clear();

private:
	// 入力状態
	XINPUT_STATE m_PreviousState;
	XINPUT_STATE m_CurrentState;

	// 接続状態
	bool m_IsConnected;
	// 仮想入力の使用許可
	bool m_UseVirtualInput;

	short m_VirtualThumbLX;
	short m_VirtualThumbLY;


	Joypad();

public:
	~Joypad();

	void Update();

private:
	void UpdateVirtualStick();
	WORD GetVirtualButtons() const;

public:
	// 入力判定
	bool IsPressed (WORD button) const;
	bool IsReleased(WORD button) const;
	bool IsHeld    (WORD button) const;

	// スティック取得
	short GetLeftThumbLX() const;
	short GetLeftThumbLY() const;

	float GetLeftThumbLXPercent() const;
	float GetLeftThumbLYPercent() const;
};

