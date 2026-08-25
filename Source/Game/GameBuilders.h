#pragma once
#include <vector>

namespace Common
{
    struct Vector2D;
}

namespace Raven
{
    class Raven_Bot;
    class Raven_Scene;
}


namespace BehaviourTree
{
    class BehaviourTree;
}

namespace Game
{
    class Player;

    class GameBuilders
    {
    public:
        static BehaviourTree::BehaviourTree* TestMovePlayer(Player* player);
        static BehaviourTree::BehaviourTree* TestMovePlayerToLimit(Player* player);
        static BehaviourTree::BehaviourTree* TestMoveBotTo(Raven::Raven_Bot* bot, Raven::Raven_Scene* scene);
        static BehaviourTree::BehaviourTree* TestTargetDetection(Raven::Raven_Scene* scene, const std::vector<Common::Vector2D>& wayPoints);
    };
}
