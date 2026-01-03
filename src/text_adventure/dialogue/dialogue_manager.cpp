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
        auto node = std::make_unique<DialogueNode>(nodeId);

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
