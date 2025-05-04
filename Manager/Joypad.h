/**
 * @file   Joypad.h
 *
 * @brief  ジョイパッドの管理クラスのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/05/04
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
	* 
	* Xinputを使用しているため、DxLibと競合が発生する
	*/

private:
	// 自身の実体
	static std::unique_ptr<Joypad> s_Joypad;

public:
	// 実体の取得関数
	static Joypad& GetInstance();

	void Clear() noexcept;

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


	Joypad() noexcept;

public:
	~Joypad() noexcept;

	void Update() noexcept;

private:
	void UpdateVirtualStick() noexcept;
	WORD GetVirtualButtons() const noexcept;

public:
	// 入力判定
	bool IsPressed (WORD button) const noexcept;
	bool IsReleased(WORD button) const noexcept;
	bool IsHeld    (WORD button) const noexcept;

	// スティック取得
	short GetLeftThumbLX() const noexcept;
	short GetLeftThumbLY() const noexcept;

	float GetLeftThumbLXPercent() const noexcept;
	float GetLeftThumbLYPercent() const noexcept;

	// 接続されているか
	bool IsConnected() const noexcept
	{
		return m_IsConnected;
	};
};

