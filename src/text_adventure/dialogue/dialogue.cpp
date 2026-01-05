#include "dialogue.hpp"
#include <iostream>

DialogueNode::DialogueNode(const std::string nodeId,
                           const std::string defaultNextNodeId)
    : nodeId(nodeId), defaultNextNodeId(defaultNextNodeId)
{
}

void DialogueNode::AddText(std::unique_ptr<RPGText> text)
{
    texts.push_back(std::move(text));
}

void DialogueNode::AddChoice(const std::string &text, const std::string &target)
{
    choices.emplace_back(text, target);
}

const std::string &DialogueNode::GetId() const
{
    return nodeId;
}
RPGText *DialogueNode::GetText(int index)
{
    return texts.at(index).get();
}
int DialogueNode::GetTextCount() const
{
    return texts.size();
}
const std::vector<Choice> &DialogueNode::GetChoices() const
{
    return choices;
}

// void DialogueNode::SetDefaultNext(std::string &nodeId)
// {
//     defaultNextNodeId = nodeId;
// }

bool DialogueNode::HasDefaultNext() const
{
    return !defaultNextNodeId.empty();
}
void DialogueNode::ResetAllTexts()
{
    for (auto &text : texts)
        text->Reset();
}
const std::string &DialogueNode::GetDefaultNext() const
{
    return defaultNextNodeId;
}
