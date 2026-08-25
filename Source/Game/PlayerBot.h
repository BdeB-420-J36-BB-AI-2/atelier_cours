#pragma once
#include "Common/2D/Vector2D.h"

using namespace Common;

namespace Raven
{
    class Raven_Bot;
    class Raven_Scene;
}

namespace Game
{
    class PlayerBot
    {
    public:
        PlayerBot(Raven::Raven_Scene& scene, const Vector2D);
        void HandleInput();
        void Update();
        void render();
    private:
        Raven::Raven_Bot* _bot;
    };
}
