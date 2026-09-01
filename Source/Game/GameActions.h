#pragma once
#include <raylib.h>

#include "Player.h"
#include "Raven/Raven_Bot.h"
#include "Raven_SteeringBehaviors.h"
#include "Graphics/2D/Vector2D.h"
#include "../Core/Actor.h"
#include "../Core/Globals.h"
#include "BehaviourTree/Core/BlackBoard.h"
#include "BehaviourTree/Core/LeafNode.h"
#include "BehaviourTree/Core/Node.h"
#include "navigation/PathEdge.h"
#include "navigation/Raven_PathPlanner.h"

using namespace Core;
using namespace Common;
using namespace Graphics;
using namespace Raven;

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

    // Move bot to a specific position
    class MoveBotTo : public BehaviourTree::LeafNode
    {
        Vector2D _target;
        Raven_Bot* _bot;

    public:
        MoveBotTo(Raven_Bot* bot, Vector2D target)
            : _bot{bot}, _target{target}
        {
        }

        BehaviourTree::NodeState tick(BehaviourTree::BlackBoard& bb) override
        {
            if (_bot->isAtPosition(_target))
            {
                _bot->GetSteering()->ArriveOff();
                return BehaviourTree::NodeState::SUCCESS;
            }

            bb.set<Vector2D>("CurrentTarget", _target);

            _bot->GetSteering()->ArriveOn();
            _bot->GetSteering()->SetTarget(_target);
            _bot->RotateFacingTowardPosition(_bot->Pos() + _bot->Heading());
            return BehaviourTree::NodeState::RUNNING;
        }
    };

    // Move bot to a specific destination through a navmesh path
    class MoveBotToDestination : public BehaviourTree::LeafNode
    {
        Vector2D _destination;
        Raven_Bot* _bot;
        std::list<PathEdge> _path;

    public:
        MoveBotToDestination(Raven_Bot* bot, Vector2D target)
            : _bot{ bot }, _destination{ target }
        {
            auto* planner = _bot->GetPathPlanner();

            // Si il est possible de marcher directement vers la destination, on rajoute manuellement un PathEdge vers la destination
            if (_bot->canWalkTo(_destination))
                _path.emplace_back(_bot->Pos(), _destination, NavGraphEdge::normal);
            else if (planner->RequestPathToPosition(_destination))
                _path = planner->GetPath();
        }

        BehaviourTree::NodeState tick(BehaviourTree::BlackBoard& bb) override
        {
            if (_path.empty() || _bot->isAtPosition(_destination))
            {
                _bot->GetSteering()->ArriveOff();
                return BehaviourTree::NodeState::SUCCESS;
            }

            auto& edge = _path.front();
            auto edgePosition = edge.Destination();

            if (!_bot->isAtPosition(edgePosition))
            {
                bb.set<Vector2D>("CurrentTarget", edgePosition);

                _bot->GetSteering()->ArriveOn();
                _bot->GetSteering()->SetTarget(edgePosition);
                _bot->RotateFacingTowardPosition(_bot->Pos() + _bot->Heading());
            }
            else
                _path.pop_front();

            return BehaviourTree::NodeState::RUNNING;
        }
    };

    class ChaseTarget : public BehaviourTree::LeafNode
    {
        Raven_Bot* _bot;
        Raven_Bot* _target;

    public:
        ChaseTarget(Raven_Bot* bot, Raven_Bot* target)
            : _bot{bot}, _target{target}
        {
        }

        BehaviourTree::NodeState tick(BehaviourTree::BlackBoard& bb) override
        {
            _bot->GetSteering()->ArriveOn();
            _bot->GetSteering()->SetTarget(_target->Pos());

            bb.set<Vector2D>("CurrentTarget", _target->Pos());

            _bot->RotateFacingTowardPosition(_bot->Pos() + _bot->Heading());
            return BehaviourTree::NodeState::RUNNING;
        }
    };

    class IsTargetInRange : public BehaviourTree::LeafNode
    {
        Raven_Bot* _bot;
        Raven_Bot* _target;
        float _range;

    public:
        IsTargetInRange(Raven_Bot* bot, Raven_Bot* target, float range)
            : _bot{bot}, _target{target}, _range{range}
        {
        }

        BehaviourTree::NodeState tick(BehaviourTree::BlackBoard& bb) override
        {
            const auto inRange = Vec2DDistance(_bot->Pos(), _target->Pos()) <= _range;
            // Implementation for checking if target is in range
            return inRange ? BehaviourTree::NodeState::SUCCESS : BehaviourTree::NodeState::FAILURE;
        }
    };
}
