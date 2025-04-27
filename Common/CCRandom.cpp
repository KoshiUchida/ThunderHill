#include "CCRandom.h"

std::unique_ptr<CCRandom> CCRandom::s_CCRandom = nullptr;

CCRandom::CCRandom() :
	m_rng(m_rd())
{
}

CCRandom& CCRandom::GetInstane()
{
	if (!s_CCRandom)
		s_CCRandom.reset(new CCRandom());

	return *s_CCRandom.get();
}

std::mt19937& CCRandom::GetMt19937()
{
	return m_rng;
}
