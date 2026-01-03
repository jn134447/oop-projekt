#ifndef DIALOGUE_MANAGER_H
#define DIALOGUE_MANAGER_H

#include <unordered_map>
#include <fstream>

#include "dialogue.hpp"
// #include "game_state.hpp"
#include "game_constants.hpp"

class DialogueManager
{
    // Graph storage
    std::unordered_map<std::string, std::unique_ptr<DialogueNode>> nodes;

    DialogueNode *currentNode = nullptr;
    int currentTextIndex = 0;

    DialogueNode *startNode = nullptr;

    bool showingChoices = false;

    // References (not owned)
    // GameState& gameState;

public:
    // private:
    void LoadFromFile(const std::string &filename);
    DialogueNode *GetNode(const std::string &nodeId);
    DialogueNode *GetCurrentNode();

    // Control flags
    // bool isWaitingForChoice = false;
    // bool isTextAnimating = true;

    // public:
    // DialogueManager(GameState &state);

    // Graph management
    // void AddNode(std::unique_ptr<DialogueNode> node);
    void SetStartNode(const std::string &nodeId);

    // // Current session
    // void StartDialogue(const std::string &nodeId);
    // void EndDialogue();
    // bool IsInDialogue() const;

    // // Text progression
    void Update();      // Call each frame
    void Advance();
    // void AdvanceText(); // Player clicked to advance
    // void SkipToEnd();   // Skip current text animation

    // // Choice handling
    const std::vector<Choice> &GetChoices() const;
    int GetChoicesCount() const;
    void SelectChoice(int choiceIndex);
    void SelectChoice(const std::string &choiceText);

    // // Getters for UI
    RPGText *GetCurrentText() const;
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