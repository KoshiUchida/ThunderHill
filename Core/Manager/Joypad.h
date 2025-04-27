/**
 * @file   Joypad.h
 *
 * @brief  �W���C�p�b�h�̊Ǘ��N���X�̃w�b�_�t�@�C��
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
/// �W���C�p�b�h�̊Ǘ��N���X
/// </summary>
class Joypad final
{
	/**
	* �g�p��̒���
	* �K���X�V�����֐����ǂ����ŌĂяo���Ȃ��Ƃ����Ȃ�
	*/

private:
	// ���g�̎���
	static std::unique_ptr<Joypad> s_Joypad;

public:
	// ���̂̎擾�֐�
	static Joypad& GetInstance();

	void Clear();

private:
	// ���͏��
	XINPUT_STATE m_PreviousState;
	XINPUT_STATE m_CurrentState;

	// �ڑ����
	bool m_IsConnected;
	// ���z���͂̎g�p����
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
	// ���͔���
	bool IsPressed (WORD button) const;
	bool IsReleased(WORD button) const;
	bool IsHeld    (WORD button) const;

	// �X�e�B�b�N�擾
	short GetLeftThumbLX() const;
	short GetLeftThumbLY() const;

	float GetLeftThumbLXPercent() const;
	float GetLeftThumbLYPercent() const;
};

