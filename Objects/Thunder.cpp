/**
 * @file   Thunder.cpp
 *
 * @brief  雷オブジェクトのソースファイル
 *
 * @author CatCode
 *
 * @date   2025/05/11
 */
#include "Thunder.h"

#include <DxLib.h>
#include "../Common/Colors.h"

#include "../WindowSettingItems.h"
#include "../Common/CCRandom.h"
#include "../Manager/ObjectManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"

#include "Player.h"
#include "TimeUp.h"

using namespace std;

int Thunder::s_Count{ 0 };

static constexpr int   Thickness{ 5 };
static constexpr float FallExRate{ 1.1f };

/// <summary>
/// コンストラクタ
/// </summary>
Thunder::Thunder(const Position2D& spownPosition) :
	ObjectBace(Transform2D(spownPosition, 0.f)),
    m_Time{},
    m_DrawThunderLine{},
    m_Fall{ Position2D(), Thickness * 2.f, Thickness * 2.f * FallExRate }
{
}

/// <summary>
/// デストラクタ
/// </summary>
Thunder::~Thunder() = default;

/// <summary>
/// 初期化処理
/// </summary>
void Thunder::Initialize()
{
    Simulate();

    m_Time = 0;

    m_DrawThunderLine = false;

    m_Line = Collisions::LinesCollider(m_Curves);
}

/// <summary>
/// 更新処理
/// </summary>
void Thunder::Update()
{
    m_Time++;

    if (m_Time == 100)
    {
        m_DrawThunderLine = true;
        PlaySoundMem(ResourceManager::GetInstance().RequestSound("ThunderSE" + to_string(CCRandom::GetInstane().Rand(0, 1)) + ".wav"), DX_PLAYTYPE_BACK);
    }
    else if (m_Time >= 125)
    {
        m_IsDestroy = true;
    }

    if (!m_DrawThunderLine)
        return;

    Collider();
}

static constexpr float NoneDraw{ 1.5f };
static constexpr float CurveExRate{ 0.35f };
static constexpr unsigned int ThunderColor{ Colors::Yellow };

/// <summary>
/// 描画処理
/// </summary>
void Thunder::Render(const Camera& camera)
{
    if (m_DrawThunderLine && m_Time % 3)
    {
        for (int i{ 1 }; i < m_Curves.size(); i++)
        {
            DrawBox(m_Curves[i - 1].x() - Thickness * CurveExRate, m_Curves[i - 1].y() - Thickness * CurveExRate,
                m_Curves[i - 1].x() + Thickness * CurveExRate, m_Curves[i - 1].y() + Thickness * CurveExRate,
                ThunderColor, true);

            if (m_Curves[i - 1].MeasureUpTo(m_Curves[i]) < NoneDraw)
                continue;

            DrawLine(
                static_cast<int>(m_Curves[i - 1].x()), static_cast<int>(m_Curves[i - 1].y()),
                static_cast<int>(m_Curves[i].x()), static_cast<int>(m_Curves[i].y()),
                ThunderColor, Thickness);
        }
    }

    if (m_DrawThunderLine || m_Time % 4)
    {
        Collisions::Box FallBox{ m_Fall.GetBox() };
        DrawBox(FallBox.left, FallBox.top,
            FallBox.right, FallBox.bottom,
            ThunderColor, true);
    }
}

static constexpr int MaxCount{ 100 };
static constexpr int ItemPopRand{ 4 };

/// <summary>
/// 終了処理
/// </summary>
void Thunder::Finalize()
{
    if (CCRandom::GetInstane().Rand(0, ItemPopRand))
        return;

    ObjectManager::GetInstance().AddObject("TimeUp" + to_string(s_Count++), make_unique<TimeUp>(m_Fall.GetPosition()));
    if (s_Count > MaxCount)
        s_Count = 0;
}

/// <summary>
/// 重なり処理
/// </summary>
void Thunder::Collider()
{
    ObjectManager& om{ ObjectManager::GetInstance() };
    Player* player{ static_cast<Player*>(om.GetObjectPtr("Player")) };

    if (!player)
        return;

    if (Collisions::Detection(player->GetCollider(), m_Fall) || Collisions::Detection(m_Line, player->GetCollider()))
        SceneManager::GetInstance().RequestSceneChange("Result");
}

int clamp(const int& val, const int& low, const int& high) {
    return std::max<int>(low, std::min<int>(val, high));
}

constexpr int Rage = 6;
constexpr int SubLife = 5;

/// <summary>
/// 雷のシミュレーション
/// </summary>
void Thunder::Simulate()
{
	CCRandom& rand{ CCRandom::GetInstane() };
	Position mainPos{ m_Transform.GetPositionX(), m_Transform.GetPositionY() };
	Position mainDir{ 0, 1 };
	vector<Mouse> branches;
	float bottom{ static_cast<float>(WSI::GetInstance().ScreenBottom()) - 20.f };

	while (mainPos.y < bottom) {

        mainPos.x += mainDir.x;
        mainPos.y += mainDir.y;

        // ランダム変化
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

    m_Fall.SetPosition(Position2D(mainPos.x, mainPos.y));
}
