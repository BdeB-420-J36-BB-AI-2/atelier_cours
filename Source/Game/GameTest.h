#pragma once

#include <vector>

#include "Raven_Map.h"
#include "Common/Graph/GraphNodeTypes.h"
#include "Common/Graph/SparseGraph.h"
#include "Graphics/2D/Vector2D.h"
#include "../Core/GameBase.h"
using namespace Common;
using namespace Graphics;

namespace Common
{
    class NavGraphEdge;
}

namespace Raven
{
    class Raven_Panel;
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

    class GameTest : public Core::GameBase
    {
        Raven::Raven_Scene* _scene;
        std::vector<Vector2D> _targetPoints; // TODO: to be deleted, just for testing purpose
        Raven::Raven_Panel* _panel;
        std::vector<std::string> _mapFiles;

        bool _gameComplete = false;
        bool _showPanel = false;
    public:
        static constexpr auto margin = 50;
        GameTest();
        ~GameTest() override;

        void handleInput() override;
        void update() override;
        void DrawGameComplete();
        void render() override;
    }; 
}
