#pragma once

#include <vector>

#include "Common/Graph/GraphNodeTypes.h"
#include "Common/Graph/SparseGraph.h"
#include "Common/2D/Vector2D.h"
#include "../Core/GameBase.h"
using namespace Common;

namespace Common
{
    class NavGraphEdge;
}

namespace Raven
{
    class Raven_Scene;
    class Raven_Bot;
}

namespace BehaviourTree
{
    class BehaviourTree;
}

namespace Game
{
    class PlayerBot;

    using NavMeshGraph = SparseGraph<NavGraphNode<>, NavGraphEdge>;

    class GameTest : public Core::GameBase
    {
        PlayerBot* _player;
        Raven::Raven_Bot* _bot;
        Raven::Raven_Scene* _scene;
        std::vector<Vector2D> _targetPoints;
        std::vector<Vector2D> _wayPoints;
        NavMeshGraph* _graph;

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
