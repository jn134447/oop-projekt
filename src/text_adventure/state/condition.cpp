#include "condition.hpp"
#include "game_constants.hpp"

HasItemCondition::HasItemCondition(const std::string &itemId,
                                   int quantity,
                                   const std::string &comp)
    : itemId(itemId), quantity(quantity), comparison(comp) {}

bool HasItemCondition::Evaluate(const GameState &gameState) const
{
    int current = gameState.currentCharacter().GetItemCount(itemId);

    {
        using namespace GameConsts::condition;

        if (comparison == comp::EQUAL)
            return current == quantity;
        if (comparison == comp::NOT_EQUAL)
            return current != quantity;
        if (comparison == comp::GREATER_THAN)
            return current > quantity;
        if (comparison == comp::LESS_THAN)
            return current < quantity;
        if (comparison == comp::GREATER_EQUAL)
            return current >= quantity;
        if (comparison == comp::LESS_EQUAL)
            return current <= quantity;
    }

    return current >= quantity; // Default
}

std::unique_ptr<Condition> HasItemCondition::Clone() const
{
    return std::make_unique<HasItemCondition>(*this);
}
