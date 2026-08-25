#include "PlayerBot.h"

#include <raylib.h>

#include "Raven_Scene.h"
#include "Raven_SteeringBehaviors.h"

using namespace Raven;

namespace Game
{
    PlayerBot::PlayerBot(Raven_Scene& scene, const Vector2D startPos)
    {
        scene.AddBots(1);
        // Hack!! Work around to handle player bot inside Raven_scene
        _bot = scene.GetAllBots().back();
        _bot->Spawn(startPos);
        _bot->SetMaxSpeed(4.0);
        _bot->TakePossession();
    }

    void PlayerBot::HandleInput()
    {
        Vector2D direction;

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
            direction.x -= 1;
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
            direction.x += 1;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
            direction.y -= 1;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
            direction.y += 1;

        if (direction.isZero())
            _bot->GetSteering()->SeekOff();
        else
        {
            direction.Normalize();

            _bot->GetSteering()->SeekOn();
            _bot->GetSteering()->SetTarget(_bot->Pos() + direction);

        }
    }

    void PlayerBot::Update()
    {
        _bot->RotateFacingTowardPosition(_bot->Pos() + _bot->Heading());
    }

    void PlayerBot::render()
    {
        _bot->Render();
    }
}
