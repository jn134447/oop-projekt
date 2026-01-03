#ifndef ACTION_H
#define ACTION_H
#pragma once

#include "game_state.hpp"
#include <climits>

enum class ActionType
{
    GIVE_ITEM,
    REMOVE_ITEM,
    SET_FLAG,      // boolean flag
    SET_VARIABLE,  // numeric/string variable
    MODIFY_STAT,   // health, gold, reputation
    TRIGGER_EVENT, // custom event
    UNLOCK_ACHIEVEMENT,
};

class DialogueAction
{
public:
    virtual ~DialogueAction() = default;
    virtual void Execute(GameState &gameState);

protected:
    ActionType type;
};

class GiveItemAction : public DialogueAction
{
private:
    std::string itemId;
    int quantity;

public:
    GiveItemAction(const std::string itemId, int quantity = 1);
    void Execute(GameState &gamestate) override;
};

class SetFlagAction : public DialogueAction
{
private:
    std::string flagId;
    bool value;

public:
    SetFlagAction(const std::string flagId, bool value);
    void Execute(GameState &gamestate) override;
};

class ModifyStatAction : public DialogueAction
{
private:
    std::string statId;
    int delta;
    int minValue;
    int maxValue;

public:
    ModifyStatAction(const std::string &statId,
                     int delta,
                     int min = INT_MIN,
                     int max = INT_MAX);
    void Execute(GameState &gamestate) override;
};

#endif