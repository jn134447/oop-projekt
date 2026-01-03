#include "dialogue_manager.hpp"
#include "helper.hpp"
#include "game_constants.hpp"
#include "json.hpp"

void DialogueManager::LoadFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    nlohmann::json data = nlohmann::json::parse(file);

    // std::unordered_map<std::string, std::unique_ptr<DialogueNode>> nodes;

    for (auto &[nodeId, nodeData] : data.items())
    {
        auto node = std::make_unique<DialogueNode>(nodeId,
                                                   nodeData.value(GameConsts::JSON::DEFAULT_NEXT, ""));

        // Load texts
        for (auto &textData : nodeData[GameConsts::JSON::TEXTS])
        {
            auto rpgText = std::make_unique<RPGText>(
                textData[GameConsts::JSON::CONTENT],
                textData[GameConsts::JSON::FONT_SIZE],
                LoadColorFromJSON(textData[GameConsts::JSON::COLOR]),
                textData.value(GameConsts::JSON::SPEED, 10));

            node->AddText(std::move(rpgText));
        }

        // Load choices
        for (auto &choiceData : nodeData[GameConsts::JSON::CHOICES])
        {
            node->AddChoice(
                choiceData[GameConsts::JSON::TEXT],
                choiceData[GameConsts::JSON::TARGET]);
        }

        nodes[nodeId] = std::move(node);
    }

    // return nodes;
}

DialogueNode *DialogueManager::GetNode(const std::string &nodeId)
{
    return nodes.at(nodeId).get();
}

DialogueNode *DialogueManager::GetCurrentNode()
{
    return currentNode;
}

void DialogueManager::SetStartNode(const std::string &nodeId)
{
    startNode = GetNode(nodeId);
}

void DialogueManager::Update()
{
    if (!currentNode)
        return;

    if (!showingChoices)
    {
        // Update current text animation
        GetCurrentText()->Update();
    }
}

void DialogueManager::Advance()
{
    if (GetCurrentText()->IsComplete())
    {
        currentTextIndex++;
        if (currentTextIndex >= currentNode->GetTextCount())
        {
            if (currentNode->GetChoices().empty() &&
                currentNode->HasDefaultNext())
            {
                // Auto-go to next node
                GoToNode(currentNode->GetDefaultNext());
            }
            else
            {
                showingChoices = true;
            }
        }
    }
    else
    {
        GetCurrentText()->Skip();
    }
}

int DialogueManager::GetChoicesCount() const
{
    if (!currentNode)
        return 0;
    return currentNode->GetChoices().size();
}

const std::vector<Choice> &DialogueManager::GetChoices() const
{
    static std::vector<Choice> empty;
    if (!currentNode)
        return empty;
    return currentNode->GetChoices();
}

void DialogueManager::SelectChoice(int choiceIndex)
{
    GoToNode(currentNode->GetChoices().at(choiceIndex).targetNodeID);
    currentTextIndex = 0;
    showingChoices = false;
}

RPGText *DialogueManager::GetCurrentText() const
{
    return currentNode->GetText(currentTextIndex);
}

int DialogueManager::GetCurrentTextIndex() const
{
    return currentTextIndex;
}

bool DialogueManager::isShowingChoices() const
{
    return showingChoices;
}

void DialogueManager::GoToNode(const std::string &nodeId)
{
    DialogueNode *newNode = GetNode(nodeId);
    if (!newNode)
        return;

    // Reset for new node
    currentNode = newNode;
    currentTextIndex = 0;
    showingChoices = false;
    currentNode->ResetAllTexts();
}
