#include "condition_factory.hpp"
#include "game_constants.hpp"

ConditionPtr ConditionFactory::CreateFromJSON(const nlohmann::json &data)
{
    {
        using namespace GameConsts;
        std::string type = data[condition::TYPE];

        if (type == condition::HAS_ITEM)
        {
            return std::make_unique<ItemCondition>(
                data[item::ITEM],
                data.value(item::QUANTITY, item::QUANTITY_DEFAULT),
                data.value(condition::COMP, condition::comp::GREATER_EQUAL));
        }
        else if (type == condition::FLAG_SET)
        {
            return std::make_unique<FlagCondition>(
                data[flag::FLAG],
                data.value(flag::VALUE, flag::VALUE_DEFAULT),
                data.value(condition::COMP, condition::comp::EQUAL));
        }
        else if (type == condition::VAR_COMP)
        {
            return std::make_unique<VariableCondition>(
                data[var::VARIABLE],
                data.value(var::VALUE, var::VALUE_DEFAULT),
                data.value(condition::COMP, condition::comp::GREATER_EQUAL));
        }
        // Add more types...

        return nullptr; // Unknown condition type
    }
}