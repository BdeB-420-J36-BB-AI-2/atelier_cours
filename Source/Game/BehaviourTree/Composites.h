#pragma once
#include "../../Core/Globals.h"
#include "Core/BlackBoard.h"
#include "Core/CompositeNode.h"

namespace BehaviourTree
{
    class Sequence : public CompositeNode
    {
        uint _currentIndex = 0;

    public:
        NodeState tick(BlackBoard& bb) override
        {
            for (auto i = _currentIndex; i < _nodes.size(); ++i)
            {
                NodeState state = _nodes[i]->tick(bb);
                // On enregistre l'index du noeud courant si il est en cours d'exécution, 
                // pour reprendre à partir de ce noeud lors du prochain tick
                if (state == NodeState::RUNNING)
                    _currentIndex = i;

                if (state != NodeState::SUCCESS)
                    return state;
            }

            _currentIndex = 0;
            return NodeState::SUCCESS;
        }
    };

    class Selector : public CompositeNode
    {
        uint _currentIndex = 0;

    public:
        NodeState tick(BlackBoard& bb) override
        {
            for (auto i = _currentIndex; i < _nodes.size(); ++i)
            {
                NodeState state = _nodes[i]->tick(bb);

                // On enregistre l'index du noeud courant si il est en cours d'exécution, 
                // pour reprendre à partir de ce noeud lors du prochain tick
                if (state == NodeState::RUNNING)
                    _currentIndex = i;

                if (state != NodeState::FAILURE)
                    return state;
            }

            _currentIndex = 0;
            return NodeState::FAILURE;
        }
    };

    class Parallel : public CompositeNode
    {
    public:
        NodeState tick(BlackBoard& bb) override
        {
            int successCount = 0;
            for (auto node : _nodes)
            {
                auto status = node->tick(bb);
                if (status == NodeState::FAILURE)
                    return NodeState::FAILURE;

                if (status == NodeState::SUCCESS)
                    ++successCount;
            }

            if (successCount == _nodes.size())
                return NodeState::SUCCESS;

            return NodeState::RUNNING;
        }
    };
}
