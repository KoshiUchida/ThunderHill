#include "Joypad.h"
#include <cstring>

std::unique_ptr<Joypad> Joypad::s_Joypad = nullptr;

Joypad& Joypad::GetInstance()
{
	if (!s_Joypad)
	{
		s_Joypad.reset(new Joypad);
		s_Joypad->Clear();
	}

	return *s_Joypad.get();
}

void Joypad::Clear() noexcept
{
	memset(&m_PreviousState, 0, sizeof(XINPUT_STATE));
	memset(&m_CurrentState , 0, sizeof(XINPUT_STATE));

	m_IsConnected = false;
	m_UseVirtualInput = false;
	m_VirtualThumbLX = 0;
	m_VirtualThumbLY = 0;
}

Joypad::Joypad() noexcept = default;

Joypad::~Joypad() noexcept = default;

void Joypad::Update() noexcept
{
	m_PreviousState = m_CurrentState;

	memset(&m_CurrentState, 0, sizeof(XINPUT_STATE));
	
	m_IsConnected = (XInputGetState(0, &m_CurrentState) == ERROR_SUCCESS);

	m_UseVirtualInput = !m_IsConnected;

	if (m_UseVirtualInput)
		UpdateVirtualStick();
}

void Joypad::UpdateVirtualStick() noexcept
{
	m_VirtualThumbLX = 0;
	m_VirtualThumbLY = 0;

	// 左（Aまたは←キー）
	if ((GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState(VK_LEFT) & 0x8000))
		m_VirtualThumbLX = -32767;

	// 右（Dまたは→キー）
	if ((GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000))
		m_VirtualThumbLX = 32767;

	// 上（Wまたは↑キー）
	if ((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState(VK_UP) & 0x8000))
		m_VirtualThumbLY = 32767;

	// 下（Sまたは↓キー）
	if ((GetAsyncKeyState('S') & 0x8000) || (GetAsyncKeyState(VK_DOWN) & 0x8000))
		m_VirtualThumbLY = -32767;
}

WORD Joypad::GetVirtualButtons() const noexcept
{
	WORD buttons = 0;

	if (GetAsyncKeyState('Z') & 0x8000)
		buttons |= XINPUT_GAMEPAD_A;
	if (GetAsyncKeyState('X') & 0x8000)
		buttons |= XINPUT_GAMEPAD_B;
	if (GetAsyncKeyState('C') & 0x8000)
		buttons |= XINPUT_GAMEPAD_X;
	if (GetAsyncKeyState('V') & 0x8000)
		buttons |= XINPUT_GAMEPAD_Y;

	return buttons;
}

bool Joypad::IsPressed(WORD button) const noexcept
{
	if (m_IsConnected)
		return (m_CurrentState.Gamepad.wButtons & button) && !(m_PreviousState.Gamepad.wButtons & button);

	else if (m_UseVirtualInput)
	{
		WORD virtualButtons = GetVirtualButtons();
		return (virtualButtons & button);
	}

	return false;
}

bool Joypad::IsReleased(WORD button) const noexcept
{
	if (m_IsConnected)
	{
		return !(m_CurrentState.Gamepad.wButtons & button) && (m_PreviousState.Gamepad.wButtons & button);
	}
	else if (m_UseVirtualInput)
	{
		// 仮想入力ではリリース検出が困難なので、常にfalse
		return false;
	}
	return false;
}

bool Joypad::IsHeld(WORD button) const noexcept
{
	if (m_IsConnected)
		return (m_CurrentState.Gamepad.wButtons & button);

	else if (m_UseVirtualInput)
	{
		WORD virtualButtons = GetVirtualButtons();
		return (virtualButtons & button);
	}

	return false;
}

short Joypad::GetLeftThumbLX() const noexcept
{
	return m_IsConnected ? m_CurrentState.Gamepad.sThumbLX : m_VirtualThumbLX;
}

short Joypad::GetLeftThumbLY() const noexcept
{
	return m_IsConnected ? m_CurrentState.Gamepad.sThumbLY : m_VirtualThumbLY;
}

float Joypad::GetLeftThumbLXPercent() const noexcept
{
	return static_cast<float>(GetLeftThumbLX()) / 32767.0f;
}

float Joypad::GetLeftThumbLYPercent() const noexcept
{
	return static_cast<float>(GetLeftThumbLY()) / 32767.0f;
}
