#pragma once

#include "Player.h"
#include "../Core/GameBase.h"

class Raven_Scene;
class Raven_Bot;

namespace BehaviourTree
{
    class BehaviourTree;
}

namespace Game
{
    class GameTest : public GameBase
    {
        BehaviourTree::BehaviourTree* _tree;
        Player _player;
        Raven_Bot* _bot;
        Raven_Scene* _scene;

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
