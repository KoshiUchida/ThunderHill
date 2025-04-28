#pragma once
#include "ObjectBace.h"
#include <vector>

class Thunder final :
	public ObjectBace
{
private:
	// �Ȃ��������W�̏W��
	std::vector<Position2D> m_Curves;

    // �������n�_
    Position2D m_Fall;

    // �o�ߎ���
    int m_Time;

    // ���̋O�Ղ�\�����邩
    bool m_DrawThunderLine;

public:
	Thunder(const Position2D& spownPosition);
	~Thunder();

	void Initialize() override;
	void Update() override;
	void Render(const Camera& camera) override;
	void Finalize() override;

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



