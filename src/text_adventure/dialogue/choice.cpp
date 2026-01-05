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