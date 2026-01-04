#include "dialogue_manager.hpp"
#include "helper.hpp"
#include "game_constants.hpp"
#include "json.hpp"
// #include "config_loader.hpp"

void DialogueManager::LoadGame(const std::string &storyFile, const std::string &configFile)
{
    config.LoadFromFile(configFile);
    LoadFromFile(storyFile);
}

void DialogueManager::LoadFromFile(const std::string &filename)
{
    currentStoryFile = filename;
    std::ifstream file(filename);
    nlohmann::json data = nlohmann::json::parse(file);

    for (auto &[nodeId, nodeData] : data.items())
    {
        auto node = std::make_unique<DialogueNode>(nodeId,
                                                   nodeData.value(GameConsts::node::DEFAULT_NEXT, ""));

        // Load texts
        for (auto &textData : nodeData[GameConsts::node::TEXTS])
        {
            // Get base style from config
            std::string speaker = textData.value(GameConsts::node::SPEAKER, "");
            const TextStyle &baseStyle = config.GetSpeakerStyle(speaker);

            TextStyle finalStyle;
            finalStyle.LoadFromJSON(textData, baseStyle);

            auto rpgText = std::make_unique<RPGText>(
                textData[GameConsts::node::TEXT],
                finalStyle.GetFontSize(),
                finalStyle.GetColor(),
                finalStyle.GetSpeed());

            node->AddText(std::move(rpgText));
        }

        // Load choices
        for (auto &choiceData : nodeData[GameConsts::node::CHOICES])
        {
            node->AddChoice(
                choiceData[GameConsts::node::TEXT],
                choiceData[GameConsts::node::TARGET]);
        }

        nodes[nodeId] = std::move(node);
    }
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
    GoToNode(currentNode->GetChoices().at(choiceIndex).GetTargetNodeId());
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
