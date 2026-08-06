#pragma once
#include <raylib.h>

#include "Player.h"
#include "Raven_Bot.h"
#include "Raven_SteeringBehaviors.h"
#include "Vector2D.h"
#include "../Core/Actor.h"
#include "../Core/Globals.h"
#include "BehaviourTree/Core/BlackBoard.h"
#include "BehaviourTree/Core/LeafNode.h"
#include "BehaviourTree/Core/Node.h"

using namespace Core;

namespace Game
{
    class MoveActor : public BehaviourTree::LeafNode
    {
        float _duration;
        float _elapsed = 0.f;

    public:
        MoveActor(float duration)
            : _duration(duration)
        {
        }

        BehaviourTree::NodeState tick(BehaviourTree::BlackBoard& bb) override
        {
            // On récupère l'acteur du blackboard 
            auto actor = bb.get<Actor*>("Player", nullptr);
            if (!actor)
                return BehaviourTree::NodeState::FAILURE;

            // On cast l'acteur en Player
            // TODO: pas la meilleur solution, mais pour l'instant ça fera l'affaire
            auto player = static_cast<Player*>(actor);
            player->setDirection(false, true, false, false);

            // On déplace le joueur pendant la durée spécifiée
            Core::log("Start MoveActor");
            _elapsed += GetFrameTime();
            if (_elapsed < _duration)
            {
                player->move();
                return BehaviourTree::NodeState::RUNNING;
            }

            // on arrête le mouvement du joueur après la durée spécifiée
            player->resetDirection();
            _elapsed = 0.f;
            return BehaviourTree::NodeState::SUCCESS;
        }
    };

    class SetDirection : public BehaviourTree::LeafNode
    {
        Inputs _inputs;

    public:
        SetDirection(bool l, bool r, bool d, bool j)
        {
            _inputs.left = l;
            _inputs.right = r;
            _inputs.down = d;
            _inputs.jump = j;
        }

        BehaviourTree::NodeState tick(BehaviourTree::BlackBoard& bb) override
        {
            // On récupère l'acteur du blackboard 
            auto actor = bb.get<Actor*>("Player", nullptr);
            if (!actor)
                return BehaviourTree::NodeState::FAILURE;

            // On cast l'acteur en Player
            // TODO: pas la meilleur solution, mais pour l'instant ça fera l'affaire
            auto player = static_cast<Player*>(actor);
            player->setDirection(_inputs);

            return BehaviourTree::NodeState::SUCCESS;
        }
    };

    class ReachActorTarget : public BehaviourTree::LeafNode
    {
        float _target;

    public:
        ReachActorTarget(float target)
            : _target{target}
        {
        }

        BehaviourTree::NodeState tick(BehaviourTree::BlackBoard& bb) override
        {
            // On récupère l'acteur du blackboard 
            auto actor = bb.get<Actor*>("Player", nullptr);
            if (!actor)
                return BehaviourTree::NodeState::FAILURE;

            // On cast l'acteur en Player
            // TODO: pas la meilleur solution, mais pour l'instant ça fera l'affaire
            auto player = static_cast<Player*>(actor);
            if (player->reachPosition(_target))
                return BehaviourTree::NodeState::SUCCESS;

            player->move();
            return BehaviourTree::NodeState::RUNNING;
        }
    };

    class MoveBotTo : public BehaviourTree::LeafNode
    {
        Vector2D _target;
        Raven_Bot* _bot;

    public:
        MoveBotTo(Raven_Bot* bot, Vector2D target)
            : _bot{ bot }, _target{ target }
        {
        }

        BehaviourTree::NodeState tick(BehaviourTree::BlackBoard& bb) override
        {
            if (_bot->isAtPosition(_target))
            {
                _bot->GetSteering()->ArriveOff();
                return BehaviourTree::NodeState::SUCCESS;
            }

            _bot->GetSteering()->ArriveOn();
            _bot->GetSteering()->SetTarget(_target);
            _bot->UpdateMovement();
            return BehaviourTree::NodeState::RUNNING;
        }
    };
}
