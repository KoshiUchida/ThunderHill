/**
 * @file   Thunder.h
 *
 * @brief  ���I�u�W�F�N�g�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 *
 * @date   2025/05/11
 */
#pragma once
#include "ObjectBace.h"

#include <vector>
#include "../Common/Collisions.h"

/// <summary>
/// ���I�u�W�F�N�g�̃N���X
/// </summary>
class Thunder final :
	public ObjectBace
{
private:
	// �Ȃ��������W�̏W��
	std::vector<Position2D> m_Curves;

    // �������n�_
    Collisions::BoxCollider m_Fall;

    // �o�ߎ���
    int m_Time;

    // ���̋O�Ղ�\�����邩
    bool m_DrawThunderLine;

    // �d���̔����Ă��镔��
    Collisions::LinesCollider m_Line;

    // �����������̑���
    static int s_Count;

public:
	Thunder(const Position2D& spownPosition);
	~Thunder();

	void Initialize() override;
	void Update() override;
	void Render(const Camera& camera) override;
	void Finalize() override;

private:
    void Collider();

private:
    struct Position {
        int x, y;
    };

    struct Mouse {
        Position pos;
        Position rota;
        int life;

        void step() {
            pos.x += rota.x;
            pos.y += rota.y;
            life--;
        }

        bool isAlive() const {
            return life > 0;
        }
    };

    void Simulate();
};



