#pragma once
#include <set>
#include <vector>

#include "Node.h"

namespace BehaviourTree
{
    class CompositeNode : public Node
    {
    public:
        virtual ~CompositeNode()
        {
            std::set uniques(_nodes.begin(), _nodes.end());
            for (Node* node : uniques)
                delete node;
        }

        void add(Node* node)
        {
            _nodes.push_back(node);
        }

    protected:
        std::vector<Node*> _nodes;
        CompositeNode() = default;

        void onReset() override
        {
            for (Node* node : _nodes)
                node->reset();
        }
    };
}
