#ifndef DIALOGUE_MANAGER_H
#define DIALOGUE_MANAGER_H
#pragma once

#include <unordered_map>
#include <fstream>

#include "dialogue.hpp"
#include "game_state.hpp"
#include "game_constants.hpp"
#include "config_loader.hpp"

class DialogueManager
{
    ConfigLoader config;
    GameState &gameState;

    // Graph storage
    std::unordered_map<std::string, std::unique_ptr<DialogueNode>> nodes;

    DialogueNode *currentNode = nullptr;
    int currentTextIndex = 0;

    DialogueNode *startNode = nullptr;

    bool showingChoices = false;

    std::string currentStoryFile;

public:
    DialogueManager(GameState &state);

    void LoadStory(const std::string &storyFile,
                   const std::string &configFile);
    void LoadFromFile(const std::string &filename);
    DialogueNode *GetNode(const std::string &nodeId);
    DialogueNode *GetCurrentNode();

    void SetStartNode(const std::string &nodeId);
    void Update(); // Call each frame
    void Advance();

    // Choice handling
    const std::vector<Choice> &GetChoices() const;
    int GetChoicesCount() const;
    void SelectChoice(int choiceIndex);
    void SelectChoice(const std::string &choiceText);

    // getters for ui
    RPGText &GetCurrentText() const;
    int GetCurrentTextIndex() const;
    bool isShowingChoices() const;

    // Navigation
    void GoToNode(const std::string &nodeId);
};

#endif