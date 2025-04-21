/**
 * @file   ControllerManager.h
 *
 * @brief  �R���g���[���̊Ǘ��N���X�̃w�b�_�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/01/22
 */

#pragma once

/// <summary>
/// �R���g���[���̊Ǘ��N���X
/// </summary>
class ControllerManager
{
public:
	/*Joypad�̃L�[�I��̂��߂̒�`*/
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

	/*�L�[�̓���̏�Ԏ擾�̂��߂̒�`*/
	enum class KeyState
	{
		Down,
		Pressing,
		Up
	};

private:
	/*�W���C�p�b�h�̃L�[��ԕۑ��̂��߂̍\����*/
	struct KeyStates
	{
		bool down;
		bool pressing;
		bool up;
	} m_keystate[static_cast<long long unsigned>(Key::Max)];

public:
	/*���C���V�X�e��*/
	ControllerManager();
	~ControllerManager();
	void Update();

	/*�擾*/
	bool GetKeyState(const Key& key, KeyState keystate = KeyState::Pressing);
};

