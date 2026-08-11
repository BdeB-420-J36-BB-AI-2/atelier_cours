#include "PlayerBot.h"

#include <raylib.h>

#include "Raven_Scene.h"
#include "Raven_SteeringBehaviors.h"

namespace Game
{
    PlayerBot::PlayerBot(Raven_Scene& scene, const Vector2D startPos)
    {
        scene.AddBots(1);
        // Hack!! Work around to handle player bot inside Raven_scene
        _bot = scene.GetAllBots().back();
        _bot->Spawn(startPos);
        _bot->SetMaxSpeed(4.0);
    }

    void PlayerBot::HandleInput()
    {
        Vector2D direction;

        if (IsKeyDown(KEY_LEFT) )
            direction.x -= 1;
        if (IsKeyDown(KEY_RIGHT) )
            direction.x += 1;
        if (IsKeyDown(KEY_UP) )
            direction.y -= 1;
        if (IsKeyDown(KEY_DOWN) )
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
        _bot->UpdateMovement();
        _bot->RotateFacingTowardPosition(_bot->Pos() + _bot->Heading());
    }

    void PlayerBot::render()
    {
        _bot->Render();
    }
}
