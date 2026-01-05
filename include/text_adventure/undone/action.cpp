#include "action.hpp"

GiveItemAction::GiveItemAction(const std::string itemId, int quantity)
    : itemId(itemId), quantity(quantity) {}

void GiveItemAction::Execute(GameState &gamestate)
{
    gamestate.currentCharacter().AddItem(itemId, quantity);
}
