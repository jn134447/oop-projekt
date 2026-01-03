#ifndef CHOICE_H
#define CHOICE_H

#include "rpg_text.hpp"
// #include "game_state.hpp"
// #include "action.hpp"
// #include "condition.hpp"

#include "json.hpp"
using json = nlohmann::json;
#include <vector>

class Choice
{
public:
    std::string text;
    std::string targetNodeID;
    // std::vector<DialogueAction> actions;
    // std::vector<Condition> conditions;

    // bool isAvailable = true;      // For greyed out/disabled display
    // bool hasBeenSelected = false; // Track if ever chosen

// public:
    // Constructors
    // Choice() = default;
    // Choice(const std::string &text, const std::string &target);

    // Getters
    // const std::string &GetDisplayText() const;
    // const std::string &GetTargetNodeId() const;
    // bool IsAvailable() const;
    // bool HasBeenSelected() const;

    // // Condition checking
    // void UpdateAvailability(const GameState &state);
    // bool MeetsConditions(const GameState &state) const;

    // // Actions
    // void ExecuteActions(GameState &state);
    // void MarkAsSelected();

    // // Conditions/Actions management
    // void AddCondition(const Condition &condition);
    // void AddAction(const DialogueAction &action);
    // const std::vector<Condition> &GetConditions() const;
    // const std::vector<DialogueAction> &GetActions() const;

    // // Serialization
    // static Choice FromJSON(const json &data);
    // json ToJSON() const;

    // // Reset state (for replay)
    // void Reset();
};

#endif