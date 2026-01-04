#pragma once
#include <string>

namespace GameConsts {
    // JSON field names
    namespace node {
        const std::string TEXT = "text";
        // const std::string CONTENT = "content";
        const std::string COLOR = "color";
        const std::string FONT_SIZE = "font_size";
        const std::string SPEED = "speed";
        const std::string CHOICES = "choices";
        const std::string TARGET = "target";
        const std::string TEXTS = "texts";
        const std::string DEFAULT_NEXT = "default_next";
        const std::string SPEAKER = "speaker";
    }
    namespace config {
        const std::string CONFIG = "config";
        const std::string TEXT_STYLE = "text_style";
        const std::string DEFAULT = "default";
        const std::string SPEAKERS = "speakers";
    };
    namespace Files{
        const std::string CONFIG = "../assets/config.json";
        const std::string STORY = "../assets/story.json";
    }
    
    // Item IDs
    namespace Items {
        // const std::string HEALTH_POTION = "health_potion";
        // const std::string RUSTY_KEY = "rusty_key";
        // const std::string GOLD_COINS = "gold_coins";
    }
    
    // Status effect IDs
    namespace Effects {
        // const std::string DREAD = "dread";
        // const std::string POISON = "poison";
        // const std::string BLESSED = "blessed";
    }
    
}