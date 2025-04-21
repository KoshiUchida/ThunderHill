/**
 * @file   ControllerManager.h
 *
 * @brief  コントローラの管理クラスのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/01/22
 */

#pragma once

/// <summary>
/// コントローラの管理クラス
/// </summary>
class ControllerManager
{
public:
	/*Joypadのキー選定のための定義*/
	enum class Key
	{
		Up,
		Down,
		Left,
		Right,
		First,
		Second,
		Therd,
		Forth,
		W,
		A,
		S,
		D,
		R,
		Space,
		ShiftL,
		MouseL,
		Max
	};

	/*キーの特定の状態取得のための定義*/
	enum class KeyState
	{
		Down,
		Pressing,
		Up
	};

private:
	/*ジョイパッドのキー状態保存のための構造体*/
	struct KeyStates
	{
		bool down;
		bool pressing;
		bool up;
	} m_keystate[static_cast<long long unsigned>(Key::Max)];

public:
	/*メインシステム*/
	ControllerManager();
	~ControllerManager();
	void Update();

	/*取得*/
	bool GetKeyState(const Key& key, KeyState keystate = KeyState::Pressing);
};

