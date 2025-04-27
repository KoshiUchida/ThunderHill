/**
 * @file   Motion.h
 *
 * @brief  動きや運動に関するのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/01/06
 */

#pragma once

/// <summary>
/// Speed Class
/// </summary>
class Speed
{
private:
	// Now Speed
	float m_Speed;

	// Max Speed
	float m_Max;

	// Acceleration Power
	float m_Acc;

	// Stop Power
	float m_Sto;

public:
	/*Main System*/

	Speed(const float& _max, const float& _acc, const float& _sto);
	~Speed();
	void Up  (float _rate = 1.f);
	void Stop(float _rate = 1.f);


	/*Getter*/
	float speed() const { return m_Speed; }


	/*Operator*/

	float operator= (const Speed& s);
};