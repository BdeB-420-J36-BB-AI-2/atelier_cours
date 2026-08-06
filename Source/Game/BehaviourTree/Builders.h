#pragma once
#include "ActionLeaves.h"
#include "Composites.h"
#include "DummyLeaves.h"
#include "Core/BehaviourTree.h"

namespace BehaviourTree
{
    class Builders
    {
    public:
        // Testing case for the tree, can be replaced with a more complex tree structure
        static BehaviourTree* TestSequence()
        {
            auto bt = new BehaviourTree();

            auto sn = new Sequence();
            sn->add(new DummySuccess());
            sn->add(new DummyFail());
            sn->add(new DummySuccess());

            bt->setRootNode(sn);

            return bt;
        }

        static BehaviourTree* TestSelector()
        {
            auto bt = new BehaviourTree();

            auto sn = new Selector();
            sn->add(new DummyFail());
            sn->add(new DummySuccess());
            sn->add(new DummyFail());

            bt->setRootNode(sn);

            return bt;
        }

        static BehaviourTree* TestComposites()
        {
            auto bt = new BehaviourTree();
            auto sln = new Selector();
            auto sqn = new Sequence();

            sqn->add(new DummySuccess());
            sqn->add(sln);
            sqn->add(new DummySuccess());

            sln->add(new DummyFail());
            sln->add(new DummyFail());
            sln->add(new DummyFail());

            bt->setRootNode(sqn);

            return bt;
        }

        static BehaviourTree* TestBlackBoard()
        {
            auto bt = new BehaviourTree();

            auto sn = new Sequence();
            sn->add(new DummyWriteData());
            sn->add(new DummyReadData());
            sn->add(new DummySuccess());

            bt->setRootNode(sn);

            return bt;
        }

        static BehaviourTree* TestRunningNode()
        {
            auto bt = new BehaviourTree();
            auto sn = new Selector();
            sn->add(new DummyFail());
            sn->add(new DummyRunning());
            bt->setRootNode(sn);

            return bt;
        }

        static BehaviourTree* TestDelay()
        {
            auto bt = new BehaviourTree();

            auto sn = new Sequence();
            auto delay = new Game::Delay(3);
            sn->add(delay);
            sn->add(new DummySuccess());
            sn->add(delay);
            sn->add(new DummySuccess());

            bt->setRootNode(sn);

            return bt;
        }

        static BehaviourTree* TestParallel()
        {
            auto bt = new BehaviourTree();

            auto pn = new Parallel();

            pn->add(new DummyRunning());
            pn->add(new DummySuccess());

            auto sn = new Sequence();
            // Not good Delay is a class from game code
            sn->add(new Game::Delay(3.0f));
            sn->add(new DummyFail);
            pn->add(sn);

            bt->setRootNode(pn);

            return bt;
        }
    };
}
