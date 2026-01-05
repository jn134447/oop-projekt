#include "dialogue.hpp"
#include <iostream>

DialogueNode::DialogueNode(const std::string nodeId,
                           const std::string defaultNextNodeId)
    : nodeId(nodeId), defaultNextNodeId(defaultNextNodeId)
{
}

void DialogueNode::AddEntry(RPGText text, std::vector<ActionFunc> actions)
{
    entries.emplace_back(std::move(text), std::move(actions));
}

void DialogueNode::AddChoice(const std::string &text, const std::string &target)
{
    choices.emplace_back(text, target);
}

const std::string &DialogueNode::GetNodeId() const
{
    return nodeId;
}

DialogueEntry &DialogueNode::GetEntry(int index)
{
    return entries.at(index);
}

int DialogueNode::GetEntryCount() const
{
    return entries.size();
}

void DialogueNode::AddChoice(Choice choice)
{
    choices.push_back(std::move(choice));
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
    for (auto &text : entries)
        text.GetText().Reset();
}

void DialogueNode::ExecuteEntryActions(const int index)
{
    for (auto &action : GetEntry(index).GetActions())
    {
        if (action)
        {             // Check if valid function
            action(); // Execute it!
        }
    }
}

const std::string &DialogueNode::GetDefaultNext() const
{
    return defaultNextNodeId;
}

DialogueEntry::DialogueEntry(RPGText text, std::vector<ActionFunc> actions)
    : text(std::move(text)), actions(std::move(actions)) {}

RPGText &DialogueEntry::GetText()
{
    return text;
}

std::vector<ActionFunc> &DialogueEntry::GetActions()
{
    return actions;
}
