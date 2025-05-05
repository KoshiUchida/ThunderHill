#pragma once
#include "ObjectBace.h"
#include <vector>
#include "../Common/Collisions.h"

class Thunder final :
	public ObjectBace
{
private:
	// 曲がった座標の集合
	std::vector<Position2D> m_Curves;

    // 落ちた地点
    Collisions::BoxCollider m_Fall;

    // 経過時間
    int m_Time;

    // 雷の軌跡を表示するか
    bool m_DrawThunderLine;

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



