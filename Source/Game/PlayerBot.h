#pragma once
#include "Vector2D.h"

class Raven_Bot;
class Raven_Scene;

namespace Game
{
    class PlayerBot
    {
    public:
        PlayerBot(Raven_Scene& scene, const Vector2D);
        void HandleInput();
        void Update();
        void render();
    private:
        Raven_Bot* _bot;
    };
}
