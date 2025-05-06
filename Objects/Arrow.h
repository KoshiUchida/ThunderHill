#pragma once
#include "ObjectBace.h"

#include <vector>

#include "../Manager/Joypad.h"

#include "../Common/Sprite2D.h"

class Arrow :
    public ObjectBace
{
private:
	Joypad& s_Joypad;

	int m_Index;
	std::vector<Position2D> m_Poses;

	bool m_Active;

	Sprite2D m_Sprite;

	int m_MoveSE;

public:
    Arrow() noexcept;
    ~Arrow() noexcept;
	void Initialize() override final;
	void Update() override final;
	void Render(const Camera& camera) override final;
	void Finalize() override final;

	int GetIndex() const { return m_Index; }
};

