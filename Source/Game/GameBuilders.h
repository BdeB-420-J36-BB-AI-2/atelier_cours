#pragma once
#include <vector>

namespace Graphics
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
        static BehaviourTree::BehaviourTree* TestTargetDetection(Raven::Raven_Bot* player, Raven::Raven_Bot* bot, const std::vector<Graphics::Vector2D>& wayPoints);
        static BehaviourTree::BehaviourTree* TestTargetDetectionFromNavMesh(Raven::Raven_Bot* player, Raven::Raven_Bot* bot, const std::vector<Graphics::Vector2D>& targetPoints);
    };
}
