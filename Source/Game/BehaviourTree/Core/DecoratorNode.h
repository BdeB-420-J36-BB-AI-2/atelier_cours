#pragma once
#include "Node.h"

namespace BehaviourTree
{
    class DecoratorNode : public Node
    {
    public:
        DecoratorNode(Node* child)
            : _child(child)
        {
        }
        ~DecoratorNode() = default;

    protected:
        Node* _child;
    };
}