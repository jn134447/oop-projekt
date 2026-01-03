#ifndef DIALOGUE_NODE_H
#define DIALOGUE_NODE_H

#include "rpg_text.hpp"
// #include "action.hpp"
#include "choice.hpp"
#include <vector>
#include <memory>

class DialogueNode
{
    // struct TextWithActions{
    //     RPGText text;
    //     std::vector<std::unique_ptr<DialogueAction>> actions;
    // };

    std::string nodeId;
    std::vector<std::unique_ptr<RPGText>> texts;
    // std::vector<TextWithActions> texts;
    std::vector<Choice> choices;

    std::string defaultNextNodeId;

    bool visited;

public:
    DialogueNode(const std::string nodeId,
                 const std::string defaultNextNodeId);
    // bool AllTextCompleted() const;
    void AddText(std::unique_ptr<RPGText> text);
    void AddChoice(const std::string &text, const std::string &targetId);

    const std::string &GetId() const;
    RPGText *GetText(int index);
    int GetTextCount() const;
    const std::vector<Choice> &GetChoices() const;

    const std::string &GetDefaultNext() const;
    bool HasDefaultNext() const;
    // void SetDefaultNext(std::string& nodeId);

    void ResetAllTexts() ;
};

#endif