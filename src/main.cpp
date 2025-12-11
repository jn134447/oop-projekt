#include <raylib-cpp.hpp>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "text_adventure.hpp"

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

    // raylib::Text msg("actually craaazy half my job done this shit is doable\n"
    //                  "in 4 weeks bla bla bla bla bla bla bla bla\n"
    //                  "bla bla bla bla bla bla bla bla bla bla\n",
    //                  20, MAROON);
    RPGText msg("actually craaazy half my job done this shit is doable\n"
                "in 4 weeks bla bla bla bla bla bla bla bla\n"
                "bla bla bla bla bla bla bla bla bla bla\n",
                20, MAROON, 15);

    SetTargetFPS(FPS); // Set our game to run at 60 frames-per-second

    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        // update
        if (raylib::Keyboard::IsKeyDown(KEY_SPACE))
        {
            msg.Update(8);
        }
        else
        {
            msg.Update();
        }
        if (raylib::Keyboard::IsKeyDown(KEY_BACKSPACE))
            msg.ForceComplete();
        if (raylib::Keyboard::IsKeyDown(KEY_ENTER))
            msg.Reset();

        // draw
        w.BeginDrawing();
        w.ClearBackground(RAYWHITE);
        msg.Draw(210, 100);

        w.EndDrawing();
    }
}