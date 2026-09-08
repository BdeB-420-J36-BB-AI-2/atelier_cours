#pragma once

#include "BlackBoard.h"
#include "Node.h"

namespace BehaviourTree
{
    class BehaviourTree
    {
    private:
        Node* _rootNode = nullptr;

        BlackBoard _blackboard;
        NodeState _treeState = NodeState::RUNNING;

    public:
        BehaviourTree() = default;

        ~BehaviourTree()
        {
            delete _rootNode;
            _rootNode = nullptr;
        }

        BlackBoard& getBlackBoard()
        {
            return _blackboard;
        }

        void setRootNode(Node* rootNode)
        {
            _rootNode = rootNode;
        }

        void Reset()
        {
            if (_rootNode)
                _rootNode->reset();
        }

        NodeState tick()
        {
            if (!_rootNode)
                return NodeState::FAILURE;

            _treeState = _rootNode->tick(_blackboard);
            if (_treeState == NodeState::SUCCESS)
                Core::log("BT Process complete");

            return _treeState;
        }

        bool isComplete() const
        {
            // Tree is consider complete if the root node has returned either SUCCESS or FAILURE
            return _treeState != NodeState::RUNNING;
        };
    };
} // namespace BehaviourTree
