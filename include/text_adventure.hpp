#ifndef TEXT_ADVENTURE
#define TEXT_ADVENTURE

#include <vector>
#include "raylib-cpp.hpp"

class RPGText : public raylib::Text
{
    std::size_t framesCounter = 0;
    unsigned short speed;
    std::string fullText;

public:
    RPGText(const std::string &text,
            float fontSize,
            const raylib::Color &color,
            unsigned short speed = 10);

    void Draw(int posX, int posY) const;
    void Update(unsigned short incrementValue = 1);
    void Reset();
    void SetSpeed(unsigned short newSpeed);
    bool IsComplete() const;
    void ForceComplete();

    std::string GetVisibleText() const;
};

#endif