#pragma once
#include "Graphics/2D/Vector2D.h"

using namespace Common;
using namespace Graphics;

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
        PlayerBot(Raven::Raven_Scene* bot, const Vector2D& startPos);
        Raven::Raven_Bot* getBot() const { return _bot; }
        void render();
    private:
        Raven::Raven_Bot* _bot;
    };
}
