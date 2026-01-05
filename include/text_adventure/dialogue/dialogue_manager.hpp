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
    GameState& gameState;

    // Graph storage
    std::unordered_map<std::string, std::unique_ptr<DialogueNode>> nodes;

    DialogueNode *currentNode = nullptr;
    int currentTextIndex = 0;

    DialogueNode *startNode = nullptr;

    bool showingChoices = false;

    std::string currentStoryFile;

public:
    // private:
    DialogueManager(GameState &state);

    void LoadGame(const std::string &storyFile,
                  const std::string &configFile);
    void LoadFromFile(const std::string &filename);
    DialogueNode *GetNode(const std::string &nodeId);
    DialogueNode *GetCurrentNode();

    // Control flags
    // bool isWaitingForChoice = false;
    // bool isTextAnimating = true;

    // public:

    // Graph management
    // void AddNode(std::unique_ptr<DialogueNode> node);
    void SetStartNode(const std::string &nodeId);

    // // Current session
    // void StartDialogue(const std::string &nodeId);
    // void EndDialogue();
    // bool IsInDialogue() const;

    // // Text progression
    void Update(); // Call each frame
    void Advance();
    // void AdvanceText(); // Player clicked to advance
    // void SkipToEnd();   // Skip current text animation

    // // Choice handling
    const std::vector<Choice> &GetChoices() const;
    int GetChoicesCount() const;
    void SelectChoice(int choiceIndex);
    void SelectChoice(const std::string &choiceText);

    // // Getters for UI
    RPGText &GetCurrentText() const;
    int GetCurrentTextIndex() const;
    // bool IsWaitingForPlayerChoice() const;
    // bool IsTextAnimationComplete() const;
    bool isShowingChoices() const;
    // void ResetCurrentNodeAllText();

    // // Navigation
    void GoToNode(const std::string &nodeId);
    // bool CanGoBack() const;
    // void GoBack(); // Optional: backtrack

    // private:
    // void ExecuteCurrentTextActions();
    // void UpdateChoiceAvailability();
    // void TransitionToNode(const std::string &nodeId);
};

#endif