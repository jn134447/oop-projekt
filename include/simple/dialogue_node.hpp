// #pragma once
// #include "rpg_text.hpp"
// #include <vector>
// #include <string>
// #include <memory>

// struct SimpleChoice {
//     std::string text;
//     std::string target;
// };

// class DialogueNode {
// private:
//     std::string id;
//     std::vector<std::unique_ptr<RPGText>> texts;
//     std::vector<SimpleChoice> choices;
    
// public:
//     DialogueNode(const std::string& nodeId) : id(nodeId) {}
    
//     void AddText(std::unique_ptr<RPGText> text) {
//         texts.push_back(std::move(text));
//     }
    
//     void AddChoice(const std::string& text, const std::string& target) {
//         choices.push_back({text, target});
//     }
    
//     // Simple getters
//     const std::string& GetId() const { return id; }
//     RPGText* GetText(int index) { return texts[index].get(); }
//     int GetTextCount() const { return texts.size(); }
//     const std::vector<SimpleChoice>& GetChoices() const { return choices; }
// };