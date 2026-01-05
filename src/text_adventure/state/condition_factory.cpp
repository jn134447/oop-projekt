#include "condition_factory.hpp"
#include "game_constants.hpp"

ConditionPtr ConditionFactory::CreateFromJSON(const nlohmann::json &data)
{
    {
        using namespace GameConsts;
        std::string type = data[condition::TYPE];

        if (type == condition::HAS_ITEM)
        {
            return std::make_unique<HasItemCondition>(
                data[item::ITEM],
                data.value(item::QUANTITY, item::QUANTITY_DEFAULT),
                data.value(condition::COMP, condition::comp::GREATER_EQUAL));
        }
        else if (type == "flag_set") {
            return std::make_unique<FlagSetCondition>(
                data["flag"],
                data.value("value", true)
            );
        }
        // Add more types...

        return nullptr; // Unknown condition type
    }
}