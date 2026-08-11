#pragma once
#include "../../Core/Globals.h"
#include "Core/BlackBoard.h"
#include "Core/DecoratorNode.h"

using namespace Core;

namespace BehaviourTree
{
    class Repeater : public DecoratorNode
    {
        uint _maxLoop;
        uint _loop = 0;

    public:
        Repeater(Node* node, uint maxloop = 0)
            : DecoratorNode(node), _maxLoop(maxloop)
        {}

        NodeState tick(BlackBoard& bb) override
        {
            NodeState state = _child->tick(bb);

            if (state == NodeState::RUNNING)
                return NodeState::RUNNING;

            if (_maxLoop == 0 || _loop++ < _maxLoop)
                return NodeState::RUNNING;

            _loop = 0;
            return NodeState::SUCCESS;
        }
    };

    class IfThenElse : public DecoratorNode
    {
        Node* _then;
        Node* _else;
    public:
        IfThenElse(Node* ifNode, Node* thenNode, Node* elseNode)
            : DecoratorNode(ifNode), _then(thenNode), _else(elseNode)
        {}

        NodeState tick(BlackBoard& bb) override
        {
            NodeState state = _child->tick(bb);
            if (state == NodeState::SUCCESS)
                return _then->tick(bb);
            
            if (state == NodeState::FAILURE)
                return _else->tick(bb);

            return NodeState::RUNNING;
        }
    };
}


