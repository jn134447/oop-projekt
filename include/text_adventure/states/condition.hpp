#ifndef CONDITION_H
#define CONDITION_H
#pragma once

// #include "game_state.hpp"
// #include "game_constants.hpp"

#include <memory>
#include <string>

class GameState;

class Condition
{
public:
    virtual ~Condition() = default;
    virtual bool Evaluate(const GameState &gameState) const = 0;
    virtual std::unique_ptr<Condition> Clone() const = 0;
};

using ConditionPtr = std::unique_ptr<Condition>;

class ItemCondition : public Condition
{
private:
    std::string itemId;
    int quantity;
    std::string comparison;

public:
    ItemCondition(const std::string &itemId,
                  int quantity,
                  const std::string &comp);

    bool Evaluate(const GameState &gameState) const override;
    std::unique_ptr<Condition> Clone() const override;
};

class FlagCondition : public Condition
{
private:
    std::string flagId;
    bool value;
    std::string comparison;

public:
    FlagCondition(const std::string &flagId,
                  const bool value,
                  std::string comp);

    bool Evaluate(const GameState &gameState) const override;
    std::unique_ptr<Condition> Clone() const override;
};

class VariableCondition : public Condition
{
private:
    std::string varId;
    int value;
    std::string comparison;

public:
    VariableCondition(const std::string &varId,
                      const int value,
                      const std::string &comp);

    bool Evaluate(const GameState &gameState) const override;
    std::unique_ptr<Condition> Clone() const override;
};

#endif