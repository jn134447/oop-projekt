#include <raylib-cpp.hpp>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

constexpr unsigned int FPS = 60;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    raylib::Window w(screenWidth, screenHeight, "raylib [text] example - writing anim");

    raylib::Text msg("actually craaazy half my job done this shit is doable\n"
                     "in 4 weeks bla bla bla bla bla bla bla bla\n"
                     "bla bla bla bla bla bla bla bla bla bla\n",
                     20, MAROON);

    int framesCounter = 0;
    SetTargetFPS(FPS); // Set our game to run at 60 frames-per-second

    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        // Draw
        //----------------------------------------------------------------------------------
        w.BeginDrawing();

        w.ClearBackground(RAYWHITE);

        if (GuiButton((Rectangle){24, 24, 120, 30}, "#191#speedup"))
        {
            framesCounter += 30;
        }
        else
        {
            framesCounter++;
        }
        if (GuiButton((Rectangle){24, 24 + 10 + 24, 120, 30}, "#191#restart"))
        {
            framesCounter = 0;
        }

        raylib::Text::Draw(msg.text.substr(0, framesCounter / 10), 210, 160, msg.GetFontSize(), msg.GetColor());

        w.EndDrawing();
    }
}