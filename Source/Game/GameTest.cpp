#include "GameTest.h"

#include <raylib.h>

#include "GameActions.h"
#include "GameBuilders.h"
#include "BehaviourTree/Builders.h"

#include "GameConfig.h"
#include "PlayerBot.h"
#include "Raven_Map.h"
#include "Raven_Scene.h"

namespace Game
{
    GameTest::GameTest()
    {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GameTest");
        SetTargetFPS(30);

        _scene = new Raven_Scene();
        _scene->LoadMap("maps/blank400x400.map");

        _bot = _scene->GetAllBots().front();
        _bot->Spawn(Vector2D(margin, margin));
        _bot->SetMaxSpeed(2.0);

        const auto mapWidth = _scene->GetMap()->GetSizeX();
        const auto mapHeight = _scene->GetMap()->GetSizeY();

        _player = new PlayerBot(*_scene, Vector2D(mapWidth * 0.5, mapHeight * 0.5));

        _tree = GameBuilders::TestMoveBotTo(_bot, _scene);

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
            _player->render();
            _scene->Render();
            if (_gameComplete)
                DrawGameComplete();
            DrawFPS(20, 20);
        }
        EndDrawing();
    }
}
