/**
 * @file   Joypad.h
 *
 * @brief  �W���C�p�b�h�̊Ǘ��N���X�̃w�b�_�t�@�C��
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
/// �W���C�p�b�h�̊Ǘ��N���X
/// </summary>
class Joypad final
{
	/**
	* �g�p��̒���
	* �K���X�V�����֐����ǂ����ŌĂяo���Ȃ��Ƃ����Ȃ�
	* 
	* Xinput���g�p���Ă��邽�߁ADxLib�Ƌ�������������
	*/

private:
	// ���g�̎���
	static std::unique_ptr<Joypad> s_Joypad;

public:
	// ���̂̎擾�֐�
	static Joypad& GetInstance();

	void Clear() noexcept;

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


	Joypad() noexcept;

public:
	~Joypad() noexcept;

	void Update() noexcept;

private:
	void UpdateVirtualStick() noexcept;
	WORD GetVirtualButtons() const noexcept;

public:
	// ���͔���
	bool IsPressed (WORD button) const noexcept;
	bool IsReleased(WORD button) const noexcept;
	bool IsHeld    (WORD button) const noexcept;

	// �X�e�B�b�N�擾
	short GetLeftThumbLX() const noexcept;
	short GetLeftThumbLY() const noexcept;

	float GetLeftThumbLXPercent() const noexcept;
	float GetLeftThumbLYPercent() const noexcept;

	// �ڑ�����Ă��邩
	bool IsConnected() const noexcept
	{
		return m_IsConnected;
	};
};

