#pragma once
#include <memory>
#include <random>

class CCRandom final
{
private:
	static std::unique_ptr<CCRandom> s_CCRandom;

	std::random_device m_rd;
	std::mt19937 m_rng;

public:
	CCRandom();

public:
	static CCRandom& GetInstane();

	std::mt19937& GetMt19937();

	template<typename T>
	T Rand(T min, T max);
};

template<typename T>
inline T CCRandom::Rand(T min, T max)
{
	std::uniform_int_distribution<T> dist(min, max);
	return dist(m_rng);
}
