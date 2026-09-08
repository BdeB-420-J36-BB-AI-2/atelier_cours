#include "GameTest.h"

#include <Code_Utilities_Light_v2.h>
#include <raylib.h>

#include "GameActions.h"
#include "GameBuilders.h"
#include "BehaviourTree/Builders.h"

#include "GameConfig.h"
#include "Raven_Map.h"
#include "Raven_Panel.h"
#include "Raven_Scene.h"
#include "Graph/HandyGraphFunctions.h"

using namespace Graphics;

namespace Game
{
    GameTest::GameTest()
    {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GameTest");
        SetTargetFPS(30);
        BdB::srandInt(static_cast<int>(time(nullptr)));

        _scene = new Raven_Scene();
        _panel = new Raven_Panel(*_scene);
        _scene->LoadMap("maps/clearDM1.map");

        const auto mapWidth = _scene->GetMap()->GetSizeX();
        const auto mapHeight = _scene->GetMap()->GetSizeY();

        _graph = &_scene->GetMap()->GetNavGraph();

        auto player = _scene->GetAllBots().back();

        for (auto bot : _scene->GetAllBots())
        {
            bot->SetMaxSpeed(1.0);
            // on recupére 2 noeuds aléatoires du graph
            auto nodeCount = _graph->NumNodes();
            auto startPoint = BdB::randInt(0, nodeCount);
            auto endPoint = BdB::randInt(0, nodeCount);
            auto spawnPoint = BdB::randInt(0, nodeCount);

            std::vector<Vector2D> targetPoints;
            targetPoints.push_back(_graph->GetNode(startPoint).Pos());
            targetPoints.push_back(_graph->GetNode(endPoint).Pos());

            // Le bot doit être spawné sur le startNode noeud du graph
            auto botStart = _graph->GetNode(spawnPoint).Pos();
            bot->Spawn(botStart);

            bot->SetBrain(GameBuilders::TestTargetDetectionFromNavMesh(player, bot, targetPoints));
        }

        _loop = true;
    }

    GameTest::~GameTest()
    {
        delete _scene;
        _scene = nullptr;

        CloseWindow();
    }

    void GameTest::handleInput()
    {
        _loop = !WindowShouldClose();

        auto key = GetKeyPressed();
        if (key == KEY_TAB)
            _showPanel = !_showPanel;

        if (!_showPanel && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            _scene->ClickRightMouseButton(Vector2D{(double)GetMouseX(), (double)GetMouseY()});
            if (auto bot = _scene->PossessedBot(); bot && bot->isPossessed())
                bot->SetMaxSpeed(4.f);
        }
    }

    void GameTest::update()
    {
        if (_gameComplete)
            return;

        _scene->Update();

        for (auto bot : _scene->GetAllBots())
        {
            if (bot->GetBrain()->isComplete())
            {
                _gameComplete = true;
                break;
            }
        }
    }

    void GameTest::DrawGameComplete()
    {
        DrawText("Game Complete!", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 40, GREEN);
    }

    void GameTest::render()
    {
        gfx.StartDrawing();
        {
            gfx.ClearBackground(GfxWhite);

            GraphHelper_DrawUsingGDI(*_graph, GraphicsContext::grey);

            _scene->Render();

            if (_showPanel)
                _panel->ProcessUIPanel(_mapFiles);

            if (_gameComplete)
                DrawGameComplete();
        }
        gfx.StopDrawing();
    }
} // namespace Game
