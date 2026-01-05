#ifndef CONDITION_H
#define CONDITION_H
#pragma once
#include "game_state.hpp"
#include "game_constants.hpp"
#include <memory>

class Condition
{
public:
    virtual ~Condition() = default;
    virtual bool Evaluate(const GameState &gameState) const = 0;
    virtual std::unique_ptr<Condition> Clone() const = 0;
};

using ConditionPtr = std::unique_ptr<Condition>;

class HasItemCondition : public Condition
{
private:
    std::string itemId;
    int quantity;
    std::string comparison;

public:
    HasItemCondition(const std::string &itemId,
                     int quantity = 1,
                     const std::string &comp = GameConsts::condition::comp::GREATER_EQUAL);

    bool Evaluate(const GameState &gameState) const override;
    std::unique_ptr<Condition> Clone() const override;
};

class FlagSetCondition : public Condition
{
private:
    std::string flagId;
    bool value;

public:
    FlagSetCondition(const std::string &flagId,
                     const bool value = true);

    bool Evaluate(const GameState &gameState) const override;
    std::unique_ptr<Condition> Clone() const override;
};

#endif