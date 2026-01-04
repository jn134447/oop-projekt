#include "config_loader.hpp"
#include "json.hpp"
#include <fstream>
#include "game_constants.hpp"
#include "helper.hpp"

void ConfigLoader::LoadFromFile(const std::string &filename)
{
    nlohmann::json data = nlohmann::json::parse(std::ifstream(filename));

    // load text styles
    {
        using namespace GameConsts;

        // load default
        auto textStyles = data[config::CONFIG][config::TEXT_STYLE];

        defaultTextStyle.LoadFromJSON(textStyles[config::DEFAULT],
                                      TextStyle());

        // load speakers
        for (auto &[speakerId, speakerData] : textStyles[config::SPEAKERS].items())
        {
            TextStyle speakerStyle;
            speakerStyle.LoadFromJSON(speakerData, defaultTextStyle);
            speakers[speakerId] = speakerStyle;
        }
    }
}

const TextStyle &ConfigLoader::GetDefaultTextStyle() const
{
    return defaultTextStyle;
}

const TextStyle &ConfigLoader::GetSpeakerStyle(const std::string &speaker) const
{
    auto it = speakers.find(speaker);
    if (it != speakers.end())
    {
        return it->second;
    }
    return GetDefaultTextStyle();
}

void TextStyle::LoadFromJSON(const json &textData, const TextStyle &fallback)
{
    color = fallback.color;
    fontSize = fallback.fontSize;
    speed = fallback.speed;

    // override defaults
    if (textData.contains(GameConsts::node::COLOR))
    {
        color = GetColorFromJSON(textData[GameConsts::node::COLOR]);
    }
    if (textData.contains(GameConsts::node::FONT_SIZE))
    {
        fontSize = textData[GameConsts::node::FONT_SIZE];
    }
    if (textData.contains(GameConsts::node::SPEED))
    {
        speed = textData[GameConsts::node::SPEED];
    }
}

const raylib::Color &TextStyle::GetColor() const
{
    return color;
}

float TextStyle::GetFontSize() const
{
    return fontSize;
}

unsigned short TextStyle::GetSpeed() const
{
    return speed;
}
