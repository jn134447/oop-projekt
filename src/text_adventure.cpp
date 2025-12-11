#include "text_adventure.hpp"

#include <vector>
#include "raylib-cpp.hpp"

RPGText::RPGText(const std::string &text,
                 float fontSize,
                 const raylib::Color &color,
                 unsigned short speed)
    : raylib::Text(text, fontSize, color),
      fullText(text),
      speed(speed)
{
}

void RPGText::Update(unsigned short incrementValue)
{
    // Only increment frames if we haven't reached full text length
    if (framesCounter / speed < fullText.length())
    {
        framesCounter += incrementValue;
    }
}

void RPGText::Reset()
{
    framesCounter = 0;
}

void RPGText::SetSpeed(unsigned short newSpeed)
{
    speed = newSpeed;
}

bool RPGText::IsComplete() const
{
    return framesCounter / speed >= fullText.length();
}

void RPGText::ForceComplete()
{
    framesCounter = fullText.length() * speed;
}

void RPGText::Draw(int posX, int posY) const
{
    std::string visibleText = fullText.substr(0, framesCounter / speed);

    raylib::Text::Draw(visibleText, posX, posY, fontSize, color);
}

std::string RPGText::GetVisibleText() const
{
    return fullText.substr(0, framesCounter / speed);
}