#pragma once
#include "../../Core/Globals.h"
#include "Core/BlackBoard.h"
#include "Core/DecoratorNode.h"
#include "Core/LeafNode.h"

using namespace Core;

namespace Game
{
    class Repeater : public BehaviourTree::DecoratorNode
    {
        uint _maxLoop;
        uint _loop = 0;

    public:
        Repeater(Node* node, uint maxloop = 0)
            : DecoratorNode(node), _maxLoop(maxloop)
        {}

        BehaviourTree::NodeState tick(BehaviourTree::BlackBoard& bb) override
        {
            if (_loop++ < _maxLoop)
                return BehaviourTree::NodeState::RUNNING;

            _loop = 0;
            return BehaviourTree::NodeState::SUCCESS;
        }
    };
}


