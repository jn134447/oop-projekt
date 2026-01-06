#include "condition.hpp"
#include "game_constants.hpp"
#include "helper.hpp"

ItemCondition::ItemCondition(const std::string &itemId,
                             int quantity,
                             const std::string &comp)
    : itemId(itemId), quantity(quantity), comparison(comp) {}

bool ItemCondition::Evaluate(const GameState &gameState) const
{
    int current = gameState.currentCharacter().GetItemCount(itemId);
    return Compare<int>(current, quantity, comparison);
}

std::unique_ptr<Condition> ItemCondition::Clone() const
{
    return std::make_unique<ItemCondition>(*this);
}

FlagCondition::FlagCondition(const std::string &flagId, const bool value, std::string comp)
    : flagId(flagId), value(value), comparison(comp) {}

bool FlagCondition::Evaluate(const GameState &gameState) const
{
    bool current = gameState.GetFlag(flagId);
    return Compare<bool>(current, value, comparison);
}

std::unique_ptr<Condition> FlagCondition::Clone() const
{
    return std::make_unique<FlagCondition>(*this);
}

VariableCondition::VariableCondition(const std::string &varId,
                                     const int value,
                                     const std::string &comp)
    : varId(varId), value(value), comparison(comp)
{
}

bool VariableCondition::Evaluate(const GameState &gameState) const
{
    int current = gameState.GetVariable(varId);
    return Compare<int>(current, value, comparison);
}

std::unique_ptr<Condition> VariableCondition::Clone() const
{
    return std::make_unique<VariableCondition>(*this);
}
