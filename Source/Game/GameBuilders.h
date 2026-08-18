#pragma once
#include <vector>

struct Vector2D;
class Raven_Bot;
class Raven_Scene;

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
        static BehaviourTree::BehaviourTree* TestMoveBotTo(Raven_Bot* bot, Raven_Scene* scene);
        static BehaviourTree::BehaviourTree* TestTargetDetection(Raven_Scene* scene, const std::vector<Vector2D>& wayPoints);
    };
}
