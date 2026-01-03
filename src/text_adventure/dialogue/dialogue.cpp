#include "dialogue.hpp"

DialogueNode::DialogueNode(const std::string nodeId)
    : nodeId(nodeId)
{
}

void DialogueNode::AddText(std::unique_ptr<RPGText> text)
{
    texts.push_back(std::move(text));
}

void DialogueNode::AddChoice(const std::string &text, const std::string &target)
{
    choices.push_back({text, target});
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
const std::vector<Choice> &DialogueNode::GetChoices() const {
    return choices;
}