#ifndef DIALOGUE_NODE_H 
#define DIALOGUE_NODE_H 

#include "rpg_text.hpp"
#include "action.hpp"
#include "choice.hpp"
#include <vector>
#include <memory>

class DialogueNode
{
    struct TextWithActions{
        RPGText text;
        std::vector<std::unique_ptr<DialogueAction>> actions;
    };

    std::string nodeId;

    std::vector<TextWithActions> texts;
    std::vector<Choice> choices;

    bool visited;

public:
    DialogueNode(const std::string nodeId);
    bool AllTextCompleted() const;
};

#endif