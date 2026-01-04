#include "rpg_text.hpp"

#include <vector>
#include "raylib-cpp.hpp"

RPGText::RPGText(const std::string &text,
                 float fontSize,
                 const raylib::Color &color,
                 unsigned short speed,
                 const raylib::Font &font,
                 float spacing)
    : raylib::Text(text, fontSize, color, font, spacing),
      fullText(text),
      speed(speed)
{
}

void RPGText::Update(unsigned short delta)
{
    if (isPaused || isComplete)
        return;

    if (framesCounter / speed >= fullText.length())
    {
        isComplete = true;
        return;
    }

    framesCounter += delta;
}
void RPGText::Draw(int posX, int posY) const
{
    std::string visibleText = fullText.substr(0, framesCounter / speed);
    raylib::Text::Draw(visibleText, posX, posY, fontSize, color);
}

void RPGText::Pause() { isPaused = true; }
void RPGText::Resume() { isPaused = false; }
bool RPGText::IsPaused() const { return isPaused; }
bool RPGText::IsComplete() const { return isComplete; }

void RPGText::Reset()
{
    if (IsPaused())
        return;
    framesCounter = 0;
    isComplete = false;
}
void RPGText::Skip()
{
    if (IsPaused())
        return;
    framesCounter = fullText.length() * speed;
    isComplete = true;
}

void RPGText::SetSpeed(unsigned short newSpeed) { speed = newSpeed; }

std::string RPGText::GetVisibleText() const { return fullText.substr(0, framesCounter / speed); }