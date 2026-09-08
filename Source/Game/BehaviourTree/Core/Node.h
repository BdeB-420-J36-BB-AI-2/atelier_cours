#pragma once

namespace BehaviourTree
{
    class BlackBoard;

    enum class NodeState
    {
        SUCCESS,
        FAILURE,
        RUNNING
    };

    class Node
    {
    public:
        virtual ~Node() = default;
        virtual NodeState tick(BlackBoard& bb) = 0;

        void reset()
        {
            onReset();
        }

    protected:
        Node() = default;

        virtual void onReset() { }
    };
}
