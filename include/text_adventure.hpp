#ifndef TEXT_ADVENTURE
#define TEXT_ADVENTURE

#include <vector>
#include "raylib-cpp.hpp"

class RPGText : public raylib::Text
{
    std::size_t framesCounter = 0;
    unsigned short speed;
    std::string fullText;
    bool isPaused = false;
    bool isComplete = false;

public:
    RPGText(const std::string &text,
            float fontSize,
            const raylib::Color &color,
            unsigned short speed = 10,
            const raylib::Font &font = GetFontDefault(),
            float spacing = 0);

    void Update(unsigned short incrementValue = 1);
    void Draw(int posX, int posY) const;

    void Skip();
    void Reset();

    void Pause();
    void Resume();
    bool IsPaused() const;
    bool IsComplete() const;

    void SetSpeed(unsigned short newSpeed);

    std::string GetVisibleText() const;
};

#endif