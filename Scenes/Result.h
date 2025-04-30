#pragma once
#include "SceneBace.h"
#include "../Manager/Joypad.h"

class Result :
	public SceneBace
{
private:
	Joypad& p_pad;

	bool m_Bottom;

public:
	Result() noexcept;
	~Result() noexcept;
	void Initialize() override;
	void Update()     override;
	void Render()     override;
	void Finalize()   override;
};

