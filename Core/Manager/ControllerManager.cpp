/**
 * @file   ControllerManager.h
 *
 * @brief  コントローラの管理クラスのヘッダファイル
 *
 * @author CatCode
 *
 * @date   20025/01/22
 */

#include "ControllerManager.h"

#include <DxLib.h>
#include "../Common/Error.h"

ControllerManager::ControllerManager()
	: m_keystate{}
{
}

ControllerManager::~ControllerManager()
{
}

void ControllerManager::Update()
{
	// ジョイパッドのキー状態を保存
	const int joypad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// キーボードのキー状態を保存
	char keybord[256];
	GetHitKeyStateAll(keybord);

	// マウスの状態を保存
	const int mouse = GetMouseInput();

	// ジョイパッドの状態を入力
	for (Key lookKey = static_cast<Key>(0); lookKey < Key::Max; lookKey = static_cast<Key>(static_cast<int>(lookKey) + 1))
	{
		// 前回の状態を取得
		bool isPush = m_keystate[static_cast<int>(lookKey)].pressing;

		// ジョイパッドの状態取得
		switch (lookKey)
		{
		case ControllerManager::Key::Up:
			m_keystate[static_cast<int>(lookKey)].pressing = (joypad & PAD_INPUT_UP);
			break;
		case ControllerManager::Key::Down:
			m_keystate[static_cast<int>(lookKey)].pressing = (joypad & PAD_INPUT_DOWN);
			break;
		case ControllerManager::Key::Left:
			m_keystate[static_cast<int>(lookKey)].pressing = (joypad & PAD_INPUT_LEFT);
			break;
		case ControllerManager::Key::Right:
			m_keystate[static_cast<int>(lookKey)].pressing = (joypad & PAD_INPUT_RIGHT);
			break;
		case ControllerManager::Key::First:
			m_keystate[static_cast<int>(lookKey)].pressing = (joypad & PAD_INPUT_1);
			break;
		case ControllerManager::Key::Second:
			m_keystate[static_cast<int>(lookKey)].pressing = (joypad & PAD_INPUT_2);
			break;
		case ControllerManager::Key::Therd:
			m_keystate[static_cast<int>(lookKey)].pressing = (joypad & PAD_INPUT_3);
			break;
		case ControllerManager::Key::Forth:
			m_keystate[static_cast<int>(lookKey)].pressing = (joypad & PAD_INPUT_4);
			break;
		case ControllerManager::Key::W:
			m_keystate[static_cast<int>(lookKey)].pressing = keybord[KEY_INPUT_W];
			break;
		case ControllerManager::Key::A:
			m_keystate[static_cast<int>(lookKey)].pressing = keybord[KEY_INPUT_A];
			break;
		case ControllerManager::Key::S:
			m_keystate[static_cast<int>(lookKey)].pressing = keybord[KEY_INPUT_S];
			break;
		case ControllerManager::Key::D:
			m_keystate[static_cast<int>(lookKey)].pressing = keybord[KEY_INPUT_D];
			break;
		case ControllerManager::Key::R:
			m_keystate[static_cast<int>(lookKey)].pressing = keybord[KEY_INPUT_R];
			break;
		case ControllerManager::Key::Space:
			m_keystate[static_cast<int>(lookKey)].pressing = keybord[KEY_INPUT_SPACE];
			break;
		case ControllerManager::Key::ShiftL:
			m_keystate[static_cast<int>(lookKey)].pressing = keybord[KEY_INPUT_LSHIFT];
			break;
		case ControllerManager::Key::MouseL:
			m_keystate[static_cast<int>(lookKey)].pressing = (mouse & MOUSE_INPUT_LEFT);
			break;
		case ControllerManager::Key::Max:
			printError("コントローラマネージャにて存在しない配列(Max)を見ようとしています。");
			break;
		default:
			printError("コントローラマネージャにて存在しない配列(Default)を見ようとしています。");
			break;
		}

		// Downの状態を判別
		m_keystate[static_cast<int>(lookKey)].down = !isPush && m_keystate[static_cast<int>(lookKey)].pressing;

		// Upの状態を判別
		m_keystate[static_cast<int>(lookKey)].up = isPush && !m_keystate[static_cast<int>(lookKey)].pressing;
	}
}

bool ControllerManager::GetKeyState(const Key& key, KeyState keystate)
{
	switch (keystate)
	{
	case ControllerManager::KeyState::Down:
		return m_keystate[static_cast<int>(key)].down;
		break;
	case ControllerManager::KeyState::Pressing:
		return m_keystate[static_cast<int>(key)].pressing;
		break;
	case ControllerManager::KeyState::Up:
		return m_keystate[static_cast<int>(key)].up;
		break;
	default:
		printError("存在しないキー状態を見ようとしています。");
		break;
	}
	return false;
}
