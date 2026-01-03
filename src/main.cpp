#include <raylib-cpp.hpp>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "rpg_text.hpp"

// #include "game_state.hpp"

constexpr unsigned int FPS = 60;

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;

    raylib::Window w(screenWidth, screenHeight, "raylib [text] example - writing anim");

    RPGText msg("bla bla bla bla bla bla bla bla bla bla\n"
                "bla bla bla bla bla bla bla bla bla bla\n"
                "bla bla bla bla bla bla bla bla bla bla\n",
                20, MAROON, 10);

    SetTargetFPS(FPS);
    while (!w.ShouldClose())
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
        if (raylib::Keyboard::IsKeyPressed(KEY_ENTER))
            msg.Skip();
        if (raylib::Keyboard::IsKeyPressed(KEY_BACKSPACE))
            msg.Reset();
        if (raylib::Keyboard::IsKeyPressed(KEY_P)) 
        {
            if (msg.IsPaused())
                msg.Resume();
            else
                msg.Pause();
        }
        

        // draw
        w.BeginDrawing();
        w.ClearBackground(RAYWHITE);

        msg.Draw(210, 100);

        w.EndDrawing();
    }
}