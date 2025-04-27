/**
 * @file   ObjectBace.h
 *
 * @brief  オブジェクトベースのヘッダファイル
 *
 * @author CatCode
 *
 * @date   2025/04/27
 */

#pragma once
#include <string>
#include "../Common/Geometry2D.h"

class Camera;

/// <summary>
/// オブジェクトの基底クラス
/// </summary>
class ObjectBace
{
protected:
	// Common
	Transform2D m_Transform;

	int m_Layer;

	bool m_IsDestroy;

	std::string m_Tag;

public:
	/*Main System*/
	ObjectBace(const Transform2D& _transform, int _layer = 5, const std::string& _tag = "None");
	virtual ~ObjectBace();
	virtual void Initialize()                 = 0;
	virtual void Update()                     = 0;
	virtual void Render(const Camera& camera) = 0;
	virtual void Finalize()                   = 0;

	/*Getter*/
	Position2D GetPosition() const { return m_Transform.GetPosition(); }
	Position2D GetPosition(const Camera& camera);
	int        layer()       const { return m_Layer; }
	bool       isDestroy()   const { return m_IsDestroy; }
	bool*      GetIsDestroyPointer() { return &m_IsDestroy; }
	std::string GetTag()     const { return m_Tag; }

	/*Operator*/
	ObjectBace& operator+=(const Position2D& other);
	ObjectBace& operator-=(const Position2D& other);
	ObjectBace& operator+=(const Vector2D&   other);
	ObjectBace& operator-=(const Vector2D&   other);
};
