/**
 * @file   Motion.cpp
 *
 * @brief  動きや運動に関するのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/01/06
 */

#include "Motion.h"

/*Speed Class*/

/// <summary>
/// Constructor
/// </summary>
Speed::Speed(const float& _max, const float& _acc, const float& _sto)
	: m_Speed{ 0.f }
	, m_Max{ _max }
	, m_Acc{ _acc }
	, m_Sto{ _sto }
{
}

/// <summary>
/// Destructor
/// </summary>
Speed::~Speed()
{
}

/// <summary>
/// Accelerator
/// </summary>
void Speed::Up(float _rate)
{
	m_Speed += m_Acc * _rate;

	if (m_Speed > m_Max)
		m_Speed = m_Max;
}

/// <summary>
/// Stop
/// </summary>
void Speed::Stop(float _rate)
{
	m_Speed -= m_Sto * _rate;

	if (m_Speed < 0.f)
		m_Speed = 0.f;
}


/*Operator*/

float Speed::operator=(const Speed& s)
{
	float sf = s.m_Speed;
	return sf;
}
