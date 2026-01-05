#include "choice.hpp"

Choice::Choice(std::string text, std::string targetNodeId)
    : text(text), targetNodeId(targetNodeId) {}

const std::string &Choice::GetText() const
{
    return text;
}
const std::string &Choice::GetTargetNodeId() const
{
    return targetNodeId;
}

void Choice::AddCondition(ConditionPtr condition)
{
    conditions.push_back(std::move(condition));
}

bool Choice::IsAvailable(const GameState &gameState) const
{

    for (const auto &condition : conditions)
    {
        if (condition && !condition->Evaluate(gameState))
        {
            return false;
        }
    }
    return true;
}
