#include "dialogue_manager.hpp"
#include "helper.hpp"
#include "game_constants.hpp"
#include "json.hpp"
// #include "config_loader.hpp"
#include <iostream>

DialogueManager::DialogueManager(GameState &state)
    : gameState(state) {}

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

    {
        using namespace GameConsts;

        for (auto &[nodeId, nodeData] : data[node::STORY].items())
        {
            auto node = std::make_unique<DialogueNode>(nodeId,
                                                       nodeData.value(node::DEFAULT_NEXT, ""));

            // Load texts
            for (auto &textData : nodeData[node::TEXTS])
            {
                // Get base style from config
                std::string speaker = textData.value(node::SPEAKER, "");
                const TextStyle &baseStyle = config.GetSpeakerStyle(speaker);

                TextStyle finalStyle;
                finalStyle.LoadFromJSON(textData, baseStyle);

                auto rpgText = std::make_unique<RPGText>(
                    textData[node::CONTENT],
                    finalStyle.GetFontSize(),
                    finalStyle.GetColor(),
                    finalStyle.GetSpeed());

                // Load node actions
                std::vector<ActionFunc> actions;
                if (nodeData.contains(action::ACTIONS))
                {
                    for (auto &actionData : nodeData[action::ACTIONS])
                    {
                        std::string actionType = actionData[action::TYPE];

                        if (actionType == action::GIVE_ITEM)
                        {
                            std::string itemId = actionData[item::ITEM];
                            int quantity = actionData.value(item::QUANTITY, item::QUANTITY_DEFAULT);

                            // Store action to execute later
                            // Create action function
                            actions.push_back(
                                [this, itemId, quantity]()
                                {
                                    std::cout << "ACTION: Giving " << quantity << " " << itemId << std::endl;
                                    gameState.currentCharacter().AddItem(itemId, quantity);
                                });
                        }
                        // TODO: Add more action types here later
                    }
                }

                node->AddEntry(std::move(rpgText), actions);
            }

            // Load choices
            for (auto &choiceData : nodeData[node::CHOICES])
            {
                node->AddChoice(
                    choiceData[node::TEXT],
                    choiceData[node::TARGET]);
            }

            nodes[nodeId] = std::move(node);
        }
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
        GetCurrentText().Update();
    }
}

void DialogueManager::Advance()
{
    if (!currentNode)
        return;

    // Get current text entry
    auto &currentEntry = currentNode->GetEntry(currentTextIndex);

    // If text is still animating, skip it
    if (!currentEntry.GetText().IsComplete())
    {
        currentEntry.GetText().Skip();
        return;
    }

    // Text is complete → EXECUTE ITS ACTIONS
    currentNode->ExecuteEntryActions(currentTextIndex);

    // Move to next text
    currentTextIndex++;

    // Check if we finished all texts
    if (currentTextIndex >= currentNode->GetEntryCount())
    {
        if (currentNode->GetChoices().empty() &&
            currentNode->HasDefaultNext())
        {
            // Auto-advance to next node
            GoToNode(currentNode->GetDefaultNext());
        }
        else
        {
            // Show choices
            showingChoices = true;
        }
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
}

RPGText &DialogueManager::GetCurrentText() const
{
    return currentNode->GetEntry(currentTextIndex).GetText();
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
