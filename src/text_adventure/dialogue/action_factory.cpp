#include "action_factory.hpp"
#include "game_constants.hpp"

#include <iostream>

ActionFunc ActionFactory::Create(const nlohmann::json &actionData)
{
    std::string type = actionData["type"];

    {
        using namespace GameConsts::action;
        if (type == MODIFY_ITEM)
            return CreateModifyItem(actionData);
        if (type == SET_FLAG)
            return CreateSetFlag(actionData);
        if (type == SET_VAR)
            return CreateSetVariable(actionData);
        if (type == MODIFY_VAR)
            return CreateModifyVariable(actionData);
        if (type == MODIFY_EFFECT)
            return CreateModifyEffect(actionData);
    }
    std::cerr << "WARNING: Unknown action type: " << type << std::endl;
    throw;
    // return [](GameState &) {};
}

ActionFunc ActionFactory::CreateModifyItem(const nlohmann::json &data)
{
    using namespace GameConsts::item;

    std::string itemId = data[ITEM];
    int quantity = data.value(AMOUNT, AMOUNT_DEFAULT);

    return [itemId, quantity](GameState &gameState)
    {
        std::cout << "ACTION: Giving " << quantity << " " << itemId << std::endl;
        gameState.ModifyItem(itemId, quantity);
    };
}

ActionFunc ActionFactory::CreateSetFlag(const nlohmann::json &data)
{
    using namespace GameConsts::flag;
    std::string flagId = data[FLAG];
    bool value = data.value(VALUE, VALUE_DEFAULT);

    return [flagId, value](GameState &gameState)
    {
        std::cout << "ACTION: Setting flag: " << flagId << " " << value << std::endl;
        gameState.SetFlag(flagId, value);
    };
}

ActionFunc ActionFactory::CreateSetVariable(const nlohmann::json &data)
{
    using namespace GameConsts::var;
    std::string varId = data[VARIABLE];
    int value = data[AMOUNT];

    return [varId, value](GameState &gameState)
    {
        std::cout << "ACTION: Set variable " << varId << " = " << value << std::endl;
        gameState.SetVariable(varId, value);
    };
}

ActionFunc ActionFactory::CreateModifyVariable(const nlohmann::json &data)
{
    using namespace GameConsts::var;
    std::string varId = data[VARIABLE];
    int change = data[AMOUNT];

    return [varId, change](GameState &gameState)
    {
        std::cout << "ACTION: Modify variable " << varId << " by " << change << std::endl;
        gameState.ModifyVariable(varId, change);
    };
}

ActionFunc ActionFactory::CreateModifyEffect(const nlohmann::json &data)
{
    using namespace GameConsts::effect;

    std::string effectId = data[EFFECT];
    int quantity = data.value(AMOUNT, AMOUNT_DEFAULT);

    return [effectId, quantity](GameState &gameState)
    {
        std::cout << "ACTION: Inflicting " << quantity << " " << effectId << std::endl;
        gameState.ModifyEffect(effectId, quantity);
    };
}
