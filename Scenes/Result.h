#pragma once
#include "SceneBace.h"

class Result :
	public SceneBace
{
public:
	Result() noexcept;
	~Result() noexcept;
	void Initialize() override;
	void Update()     override;
	void Render()     override;
	void Finalize()   override;
};

