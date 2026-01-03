#pragma once

#include "dialogue_node.hpp"
#include "rpg_text.hpp"

#include <string>
#include <fstream>
#include <unordered_map>
#include <memory>
#include <json.hpp>  // or your JSON library

class DialogueLoader {
public:
    static std::unordered_map<std::string, std::unique_ptr<DialogueNode>> 
    LoadFromFile(const std::string& filename) {
        
        std::ifstream file(filename);
        nlohmann::json data = nlohmann::json::parse(file);
        
        std::unordered_map<std::string, std::unique_ptr<DialogueNode>> nodes;
        
        for (auto& [nodeId, nodeData] : data.items()) {
            auto node = std::make_unique<DialogueNode>(nodeId);
            
            // Load texts
            for (auto& textData : nodeData["texts"]) {
                auto rpgText = std::make_unique<RPGText>(
                    textData["content"],
                    textData["font_size"],
                    raylib::Color(
                        textData["color"][0],
                        textData["color"][1],
                        textData["color"][2],
                        textData["color"][3]
                    ),
                    textData.value("speed", 10)
                );
                node->AddText(std::move(rpgText));
            }
            
            // Load choices
            for (auto& choiceData : nodeData["choices"]) {
                node->AddChoice(
                    choiceData["text"],
                    choiceData["target"]
                );
            }
            
            nodes[nodeId] = std::move(node);
        }
        
        return nodes;
    }
};