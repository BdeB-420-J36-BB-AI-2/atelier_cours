#include "GameTest.h"

#include <raylib.h>

#include "GameBuilders.h"
#include "BehaviourTree/Builders.h"

#include "GameConfig.h"

namespace Game
{
    GameTest::GameTest() :
        _player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)
    {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GameTest");
        SetTargetFPS(30);

        _tree = GameBuilders::TestMovePlayerToLimit(&_player);
        //_tree = BehaviourTree::Builders::TestParallel();
        _player.setHealth(10);
        _loop = true;
    }

    GameTest::~GameTest()
    {
        delete _tree;
        _tree = nullptr;
        CloseWindow();
    }

    void GameTest::HandlePlayerDirection()
    {
        auto directionPressed = IsKeyDown(KEY_LEFT)
            || IsKeyDown(KEY_RIGHT)
            || IsKeyDown(KEY_DOWN)
            || IsKeyDown(KEY_UP)
            || IsKeyDown(KEY_SPACE);

        if (directionPressed)
            _player.setDirection(
                IsKeyDown(KEY_LEFT),
                IsKeyDown(KEY_RIGHT),
                IsKeyDown(KEY_DOWN),
                (IsKeyDown(KEY_UP) || IsKeyDown(KEY_SPACE))
            );
        else
            _player.resetDirection();
    }

    void GameTest::handleInput()
    {
        // Mouse
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            _player.setPosition(GetMouseX(), GetMouseY());

        // Direction pressed
        //HandlePlayerDirection();

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
        _player.update();
    }

    void GameTest::DrawGameComplete()
    {
        DrawText("Game Complete!", SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 40, GREEN);
    }

    void GameTest::render()
    {
        BeginDrawing();
        {
            ClearBackground(BLANK);
            _player.render();
            if (_gameComplete)
                DrawGameComplete();
            DrawFPS(20, 20);
        }
        EndDrawing();
    }
}
