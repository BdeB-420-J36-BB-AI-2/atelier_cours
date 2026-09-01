#include "PlayerBot.h"

#include "Raven_Scene.h"
#include "Raven_SteeringBehaviors.h"

using namespace Raven;

namespace Game
{
    PlayerBot::PlayerBot(Raven_Scene* scene, const Vector2D& startPos)
    {
        // Hack!! Work around to handle player bot inside Raven_scene
        _bot = scene->GetAllBots().back();
        _bot->Spawn(startPos);
        _bot->SetMaxSpeed(4.0);
        _bot->TakePossession();
        scene->SelectBot(_bot);
    }

    void PlayerBot::render()
    {
        _bot->Render();
    }
}
