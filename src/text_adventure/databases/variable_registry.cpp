#include "variable_registry.hpp"
#include "game_constants.hpp"
#include "json.hpp"

#include <fstream>
#include <iostream>

void VariableRegistry::LoadFromFile(const std::string &filename)
{

    std::ifstream file(filename);
    nlohmann::json data = nlohmann::json::parse(file);
    {
        using namespace GameConsts;

        for (auto &[varId, value] : data[state::VARIABLES].items())
        {
            registeredVariables.insert(varId);
            defaultValues[varId] = value.get<int>();
            std::cout << "Registered variable: " << varId
                      << " (default: " << value.get<int>() << ")" << std::endl;
        }
    }
}

bool VariableRegistry::IsRegistered(const std::string &varId) const
{
    return registeredVariables.find(varId) != registeredVariables.end();
}

int VariableRegistry::GetDefaultValue(const std::string &varId) const
{
    auto it = defaultValues.find(varId);
    return it != defaultValues.end() ? it->second : 0;
}
