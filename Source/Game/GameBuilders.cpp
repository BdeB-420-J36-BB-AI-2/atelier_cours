#pragma once
#include "GameBuilders.h"

#include "GameActions.h"
#include "GameConfig.h"
#include "GameTest.h"
#include "Player.h"
#include "Raven_Map.h"
#include "Raven_Scene.h"
#include "BehaviourTree/ActionLeaves.h"
#include "BehaviourTree/Composites.h"
#include "BehaviourTree/Decorators.h"
#include "BehaviourTree/DummyLeaves.h"
#include "BehaviourTree/Core/BehaviourTree.h"

namespace Game
{
    BehaviourTree::BehaviourTree* GameBuilders::TestMovePlayer(Player* player)
    {
        auto bt = new BehaviourTree::BehaviourTree();

        BehaviourTree::BlackBoard &bb = bt->getBlackBoard();
        bb.set<Actor*>("Player", player);

        auto sn = new BehaviourTree::Sequence();
        sn->add(new Delay(3.0f));
        sn->add(new MoveActor(1.0f));
        sn->add(new BehaviourTree::DummySuccess());

        bt->setRootNode(sn);

        return bt;
    }

    BehaviourTree::BehaviourTree* GameBuilders::TestMovePlayerToLimit(Player* player)
    {
        auto bt = new BehaviourTree::BehaviourTree();

        BehaviourTree::BlackBoard& bb = bt->getBlackBoard();
        bb.set<Actor*>("Player", player);

        auto sn = new BehaviourTree::Sequence();
        sn->add(new Delay(3.0f));

        // move to the right
        sn->add(new SetDirection(false, true, false, false));
        sn->add(new ReachActorTarget(SCREEN_WIDTH - PLAYER_WIDTH));

        // move to the left
        sn->add(new SetDirection(true, false, false, false));
        sn->add(new ReachActorTarget(0.f));

        // resert direction
        sn->add(new SetDirection(false, false, false, false));
        sn->add(new BehaviourTree::DummySuccess());

        bt->setRootNode(sn);

        return bt;
    }

    BehaviourTree::BehaviourTree* GameBuilders::TestMoveBotTo(Raven_Bot* bot, Raven_Scene* scene)
    {
        auto bt = new BehaviourTree::BehaviourTree();

        const auto mapWidth = scene->GetMap()->GetSizeX();
        const auto mapHeight = scene->GetMap()->GetSizeY();

        const std::vector<Vector2D> wayPoints = {
            Vector2D(GameTest::margin, GameTest::margin),
            Vector2D(mapWidth - GameTest::margin, GameTest::margin),
            Vector2D(mapWidth - GameTest::margin, mapHeight - GameTest::margin),
            Vector2D(GameTest::margin, mapHeight - GameTest::margin)
        };

        auto sequence = new BehaviourTree::Sequence();
        for (auto way_point : wayPoints)
            sequence->add(new MoveBotTo(bot, way_point));

        BehaviourTree::Node* repeater = new BehaviourTree::Repeater(sequence);

        bt->setRootNode(repeater);
        return bt;
    }

    BehaviourTree::BehaviourTree* GameBuilders::TestTargetDetection(Raven_Scene* scene, const std::vector<Vector2D>& wayPoints)
    {
        auto bt = new BehaviourTree::BehaviourTree();
        // TODO: implement this function to test target detection behavior
        // Action MoveBotTo should be used to move the bot to a specific position
        // create on action leaf IsTargetInRange
        // 1. if (IsTargetInRange)
        //     2. then: MoveBotTo Target
        // 3. else
        //      MoveBotTo Waypoint (patrol Sequence)

        const auto mapWidth = scene->GetMap()->GetSizeX();
        const auto mapHeight = scene->GetMap()->GetSizeY();

        // On assume que le premier bot est le AI agent et le second bot est le joueur. 
        // TODO: Il faudrait améliorer cette partie pour gérer plusieurs bots et joueurs.
        Raven_Bot* bot = scene->GetAllBots().front();
        Raven_Bot* player = scene->GetAllBots().back();

        auto patrolSequence = new BehaviourTree::Sequence();
        for (auto way_point : wayPoints)
            patrolSequence->add(new MoveBotTo(bot, way_point));

        BehaviourTree::Node* patrolRepeater = new BehaviourTree::Repeater(patrolSequence);
        
        // Detect action
        auto detectPlayer = new IsTargetInRange(bot, player, 150.0f);

        // Chase action
        auto chasePlayer = new ChaseTarget(bot, player);

        // IfThenElse Decorator
        auto ifThenElse = new BehaviourTree::IfThenElse(detectPlayer, chasePlayer, patrolRepeater);

        bt->setRootNode(ifThenElse);
        return bt;
    }
}
