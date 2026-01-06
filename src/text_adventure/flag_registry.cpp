#include "flag_registry.hpp"
#include "game_constants.hpp"
#include "json.hpp"

#include <fstream>
#include <iostream>

void FlagRegistry::LoadFromFile(const std::string &filename)
{

    std::ifstream file(filename);
    nlohmann::json data = nlohmann::json::parse(file);

    {
        using namespace GameConsts;

        for (auto &[flagId, value] : data[state::FLAGS].items())
        {
            registeredFlags.insert(flagId);
            defaultValues[flagId] = value.get<bool>();
            std::cout << "Registered flag: " << flagId
                      << " (default: " << (value.get<bool>() ? "true" : "false") << ")" << std::endl;
        }
    }
}

bool FlagRegistry::IsRegistered(const std::string &flagId) const
{
    return registeredFlags.find(flagId) != registeredFlags.end();
}

bool FlagRegistry::GetDefaultValue(const std::string &flagId) const
{
    auto it = defaultValues.find(flagId);
    return it != defaultValues.end() ? it->second : false;
}
