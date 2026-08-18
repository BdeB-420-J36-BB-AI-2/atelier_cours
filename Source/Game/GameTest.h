#pragma once

#include <vector>

#include "Vector2D.h"
#include "../Core/GameBase.h"

class Raven_Scene;
class Raven_Bot;

namespace BehaviourTree
{
    class BehaviourTree;
}

namespace Game
{
    class PlayerBot;

    class GameTest : public Core::GameBase
    {
        BehaviourTree::BehaviourTree* _tree;
        PlayerBot* _player;
        Raven_Bot* _bot;
        Raven_Scene* _scene;
        std::vector<Vector2D> _wayPoints;

        bool _gameComplete = false;
    public:
        static constexpr auto margin = 50;
        GameTest();
        ~GameTest() override;
        void HandlePlayerDirection();

        void handleInput() override;
        void update() override;
        void DrawGameComplete();
        void render() override;
    }; 
}
