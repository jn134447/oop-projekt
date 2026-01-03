#ifndef DIALOGUE_MANAGER_H
#define DIALOGUE_MANAGER_H

#include <unordered_map>
#include "dialogue.hpp"
#include "game_state.hpp"

class DialogueManager {
private:
    // Graph storage
    std::unordered_map<std::string, std::unique_ptr<DialogueNode>> nodes;
    
    // Current state
    DialogueNode* currentNode = nullptr;
    int currentTextIndex = 0;  // Which text block we're showing
    
    // References (not owned)
    GameState& gameState;
    
    // Control flags
    bool isWaitingForChoice = false;
    bool isTextAnimating = true;
    
public:
    DialogueManager(GameState& state);
    
    // Graph management
    void AddNode(std::unique_ptr<DialogueNode> node);
    void SetStartNode(const std::string& nodeId);
    
    // Current session
    void StartDialogue(const std::string& nodeId);
    void EndDialogue();
    bool IsInDialogue() const;
    
    // Text progression
    void Update();  // Call each frame
    void AdvanceText();  // Player clicked to advance
    void SkipToEnd();  // Skip current text animation
    
    // Choice handling
    const std::vector<Choice*>& GetAvailableChoices() const;
    void SelectChoice(int choiceIndex);
    void SelectChoice(const std::string& choiceText);
    
    // Getters for UI
    RPGText* GetCurrentRPGText() const;
    bool IsWaitingForPlayerChoice() const;
    bool IsTextAnimationComplete() const;
    
    // Navigation
    void GoToNode(const std::string& nodeId);
    bool CanGoBack() const;
    void GoBack();  // Optional: backtrack
    
private:
    void ExecuteCurrentTextActions();
    void UpdateChoiceAvailability();
    void TransitionToNode(const std::string& nodeId);
};

#endif