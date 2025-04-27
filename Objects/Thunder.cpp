#include "Thunder.h"
#include <DxLib.h>
#include "../Common/Colors.h"
#include "../Common/CCRandom.h"
#include "../WindowSettingItems.h"

using namespace std;

Thunder::Thunder(const Position2D& spownPosition) :
	ObjectBace(Transform2D(spownPosition, 0.f)),
    m_Time{}
{
}

Thunder::~Thunder()
{
}

void Thunder::Initialize()
{
    Simulate();

    m_Time = 0;
}

void Thunder::Update()
{
    m_Time++;
}

static constexpr int Thickness{ 5 };
static constexpr float NoneDraw{ 2.5f };
static constexpr float CurveExRate{ 0.3f };

void Thunder::Render(const Camera& camera)
{
	for (int i{ 1 }; i < m_Curves.size(); i++)
    {
        DrawBox(m_Curves[i - 1].x() - Thickness * CurveExRate, m_Curves[i - 1].y() - Thickness * CurveExRate,
            m_Curves[i - 1].x() + Thickness * CurveExRate, m_Curves[i - 1].y() + Thickness * CurveExRate,
            Colors::LightBlue, true);

        if (m_Curves[i - 1].MeasureUpTo(m_Curves[i]) < NoneDraw)
            continue;
        DrawLine(
            static_cast<int>(m_Curves[i - 1].x()), static_cast<int>(m_Curves[i - 1].y()),
            static_cast<int>(m_Curves[i].x()), static_cast<int>(m_Curves[i].y()),
            Colors::LightBlue, Thickness);
    }

    DrawBox(m_Fall.x() - Thickness, m_Fall.y() - Thickness,
        m_Fall.x() + Thickness, m_Fall.y() + Thickness,
        Colors::LightBlue, true);
}

void Thunder::Finalize()
{
}

int clamp(const int& val, const int& low, const int& high) {
    return std::max<int>(low, std::min<int>(val, high));
}

constexpr int Rage = 5;
constexpr int SubLife = 5;

void Thunder::Simulate()
{
	CCRandom& rand{ CCRandom::GetInstane() };
	Position mainPos{ m_Transform.GetPositionX(), m_Transform.GetPositionY() };
	Position mainDir{ 0, 1 };
	vector<Mouse> branches;
	float bottom{ static_cast<float>(WSI::GetInstance().ScreenBottom()) };

	while (mainPos.y < bottom) {

        mainPos.x += mainDir.x;
        mainPos.y += mainDir.y;

        // ƒ‰ƒ“ƒ_ƒ€•Ï‰»
        if (rand.Rand(0, Rage - 1) == 0) {

            m_Curves.push_back(Position2D(mainPos.x, mainPos.y));

            mainDir.x += (rand.Rand(0, 1) == 0) ? 1 : -1;
            mainDir.x = clamp(mainDir.x, -1, 1);

            if (rand.Rand(0, 1) == 0) {
                int branchX = clamp(mainDir.x + ((rand.Rand(0, 2) == 0) ? 1 : -1), -1, 1);
                branches.push_back(Mouse{ mainPos, { branchX, 1 }, SubLife });
            }
        }


        for (auto& m : branches) {
            if (m.isAlive()) {
                m.step();
            }
        }

        branches.erase(remove_if(branches.begin(), branches.end(),
            [](const Mouse& m) { return !m.isAlive(); }),
            branches.end());
	}

    m_Fall = Position2D(mainPos.x, mainPos.y);
}
