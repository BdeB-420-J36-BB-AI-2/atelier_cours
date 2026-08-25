#include "GameTest.h"

#include <Code_Utilities_Light_v2.h>
#include <raylib.h>

#include "GameActions.h"
#include "GameBuilders.h"
#include "BehaviourTree/Builders.h"

#include "GameConfig.h"
#include "PlayerBot.h"
#include "Raven_Map.h"
#include "Raven_Scene.h"
#include "Graph/HandyGraphFunctions.h"

namespace Game
{
    GameTest::GameTest()
    {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GameTest");
        SetTargetFPS(30);
        BdB::srandInt(static_cast<int>(time(nullptr)));

        _scene = new Raven_Scene();
        _scene->LoadMap("maps/blank400x400.map");

        _bot = _scene->GetAllBots().front();
        _bot->SetMaxSpeed(2.0);

        const auto mapWidth = _scene->GetMap()->GetSizeX();
        const auto mapHeight = _scene->GetMap()->GetSizeY();

        const auto NumCellsX = 10;
        const auto NumCellsY = 10;

        _graph = new SparseGraph<NavGraphNode<>, NavGraphEdge>(true);
        GraphHelper_CreateGrid(*_graph, mapWidth, mapHeight, NumCellsX, NumCellsY);

        _player = new PlayerBot(*_scene, Vector2D(mapWidth * 0.5, mapHeight * 0.5));

        // on recupére 2 noeuds aléatoires du graph
        auto nodeCount = _graph->NumNodes();
        auto startPoint = BdB::randInt(0, nodeCount);
        auto endPoint = BdB::randInt(0, nodeCount);
        _targetPoints.push_back(_graph->GetNode(startPoint).Pos());
        _targetPoints.push_back(_graph->GetNode(endPoint).Pos());

        // Le bot doit être spawné sur le startNode noeud du graph
        auto botStart = _graph->GetNode(startPoint).Pos();
        _bot->Spawn(botStart);

        // on calcule le chemin entre les 2 noeuds du graph (start -> end)
        Graph_SearchAStar<NavMeshGraph, Heuristic_Euclid> pathSearchStart(*_graph, startPoint, endPoint);
        auto pathNodes = pathSearchStart.GetPathToTarget();
        for (const auto node : pathNodes)
            _wayPoints.push_back(_graph->GetNode(node).Pos());

        // on calcule le chemin entre les 2 noeuds du graph (start -> end)
        Graph_SearchAStar<NavMeshGraph, Heuristic_Euclid> pathReturnSearch(*_graph, endPoint, startPoint);
        auto pathNodesReturn = pathReturnSearch.GetPathToTarget();
        for (const auto node : pathNodesReturn)
            _wayPoints.push_back(_graph->GetNode(node).Pos());

        _tree = GameBuilders::TestTargetDetection(_scene, _wayPoints);

        _loop = true;
    }

    GameTest::~GameTest()
    {
        delete _tree;
        _tree = nullptr;

        delete _scene;
        _scene = nullptr;

        delete _player;
        _player = nullptr;

        delete _graph;
        _graph = nullptr;
        CloseWindow();
    }

    void GameTest::HandlePlayerDirection()
    {
        auto directionPressed = IsKeyDown(KEY_LEFT)
            || IsKeyDown(KEY_RIGHT)
            || IsKeyDown(KEY_DOWN)
            || IsKeyDown(KEY_UP)
            || IsKeyDown(KEY_SPACE);

        /*if (directionPressed)
            _player.setDirection(
                IsKeyDown(KEY_LEFT),
                IsKeyDown(KEY_RIGHT),
                IsKeyDown(KEY_DOWN),
                (IsKeyDown(KEY_UP) || IsKeyDown(KEY_SPACE))
            );
        else
            _player.resetDirection();*/
    }

    void GameTest::handleInput()
    {
        // Direction pressed
        _player->HandleInput();

        _loop = !WindowShouldClose();
    }

    void GameTest::update()
    {
        if (_gameComplete)
            return;

        if (!_tree->isComplete())
            _tree->tick();
        else
            _gameComplete = true;

        // Physics
        _player->Update();
    }

    void GameTest::DrawGameComplete()
    {
        DrawText("Game Complete!", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 40, GREEN);
    }

    void GameTest::render()
    {
        BeginDrawing();
        {
            ClearBackground(BLANK);

            GraphHelper_DrawUsingGDI(*_graph, GraphicsContext::grey);

            // display path
            gfx.BluePen();
            gfx.BlueBrush();
            for (size_t i = 0; i < _wayPoints.size(); ++i)
                gfx.Circle(_wayPoints[i], 3);

            // display target
            gfx.RedPen();
            gfx.RedBrush();
            for (size_t i = 0; i < _targetPoints.size(); ++i)
            {
                gfx.Circle(_targetPoints[i], 6);
                gfx.TextColor(GraphicsContext::red);
                gfx.TextAtPos(_targetPoints[i] + Vector2D(8, -8), std::to_string(i + 1));
            }

            auto& bb = _tree->getBlackBoard();

            auto target = bb.get<Vector2D>("CurrentTarget", {});
            if (target != Vector2D())
            {
                gfx.TextColor(GraphicsContext::green);
                gfx.TextAtPos(target + Vector2D(8, -8), "Target");
            }

            _player->render();
            _scene->Render();

            if (_gameComplete)
                DrawGameComplete();
            DrawFPS(20, 20);
        }
        EndDrawing();
    }
}
