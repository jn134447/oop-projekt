#include "dialogue_manager.hpp"
#include "helper.hpp"
#include "game_constants.hpp"
#include "json.hpp"
// #include "config_loader.hpp"
#include "condition_factory.hpp"

#include <iostream>

DialogueManager::DialogueManager(GameState &state)
    : gameState(state) {}

void DialogueManager::LoadStory(const std::string &storyFile, const std::string &configFile)
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

                RPGText rpgText(
                    textData[node::CONTENT],
                    finalStyle.GetFontSize(),
                    finalStyle.GetColor(),
                    finalStyle.GetSpeed());

                // Load node actions
                std::vector<ActionFunc> actions;
                if (textData.contains(action::ACTIONS))
                {
                    for (auto &actionData : textData[action::ACTIONS])
                    {
                        std::string actionType = actionData[action::TYPE];

                        if (actionType == action::MODIFY_ITEM)
                        {
                            // std::string itemId = actionData[item::ITEM];
                            // int quantity = actionData.value(item::DELTA, item::DELTA_DEFAULT);

                            // if (!gameState.GetItemLoader().ItemExists(itemId))
                            // {
                            //     std::cerr << "ERROR in node '" << nodeId << "': Unknown item '"
                            //               << itemId << "' in action" << std::endl;
                            //     // Option: skip, throw, or use default
                            // }

                            // // Store action to execute later
                            // // Create action function
                            // actions.push_back(
                            //     [this, itemId, quantity]()
                            //     {
                            //         std::cout << "ACTION: Giving " << quantity << " " << itemId << std::endl;
                            //         gameState.ModifyItem(itemId, quantity);
                            //     });
                        }
                        else if (actionType == action::SET_FLAG)
                        {
                            // std::string flagId = actionData[flag::FLAG];
                            // bool value = actionData.value(flag::VALUE, flag::VALUE_DEFAULT);

                            // // Store action to execute later
                            // // Create action function
                            // actions.push_back(
                            //     [this, flagId, value]()
                            //     {
                            //         std::cout << "ACTION: Setting flag: " << flagId << " " << value << std::endl;
                            //         gameState.SetFlag(flagId, value);
                            //     });
                        }
                        else if (actionType == action::SET_VAR)
                        {
                            // std::string varId = actionData[var::VARIABLE];
                            // int value = actionData[var::VALUE];

                            // actions.push_back(
                            //     [this, varId, value]()
                            //     {
                            //         std::cout << "ACTION: Set variable " << varId << " = " << value << std::endl;
                            //         gameState.SetVariable(varId, value);
                            //     });
                        }
                        else if (actionType == action::MODIFY_VAR)
                        {
                            std::string varId = actionData[var::VARIABLE];
                            int change = actionData[var::CHANGE];

                            actions.push_back(
                                [this, varId, change]()
                                {
                                    std::cout << "ACTION: Modify variable " << varId << " by " << change << std::endl;
                                    gameState.ModifyVariable(varId, change);
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
                Choice choice(choiceData[node::TEXT], choiceData[node::TARGET]);

                if (choiceData.contains("conditions"))
                {
                    for (auto &condData : choiceData["conditions"])
                    {
                        auto condition = ConditionFactory::CreateFromJSON(condData);
                        if (condition)
                        {
                            choice.AddCondition(std::move(condition));
                        }
                    }
                }

                node->AddChoice(std::move(choice));
            }

            nodes[nodeId] = std::move(node);
        }
    }
}

DialogueNode *DialogueManager::GetNode(const std::string &nodeId)
{
    auto it = nodes.find(nodeId);
    if (it != nodes.end())
    {
        return it->second.get();
    }

    std::cerr << "ERROR: Node '" << nodeId << "' not found!" << std::endl;
    return nullptr;
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
    currentNode->ExecuteEntryActions(gameState, currentTextIndex);

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
    static const std::vector<Choice> empty;
    if (!currentNode)
        return empty;
    return currentNode->GetChoices();
}

void DialogueManager::SelectChoice(int choiceIndex)
{
    const auto &choices = currentNode->GetChoices();

    if (choiceIndex < 0 || choiceIndex >= choices.size())
    {
        std::cerr << "ERROR: Invalid choice index " << choiceIndex << std::endl;
        return;
    }

    GoToNode(choices[choiceIndex].GetTargetNodeId());
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
