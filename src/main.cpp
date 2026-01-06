#include <raylib-cpp.hpp>

#include "ke_engine.hpp"

#include <iostream>

constexpr unsigned int FPS = 60;

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;
    raylib::Window w(screenWidth, screenHeight, "Text Adventure");

    Engine engine;
    if (!engine.Init())
    {
        std::cerr << "Failed to initialize engine" << std::endl;
        return 1;
    }

    engine.StartStory("test_start");

    SetTargetFPS(FPS);

    while (!w.ShouldClose())
    {
        // UPDATE
        engine.Update();
        engine.HandleInput();

        // DRAW
        w.BeginDrawing();
        w.ClearBackground(RAYWHITE);
        // ui.Draw()

        engine.DrawUI();

        w.EndDrawing();
    }
    // // ui.drawNodes()
    // // Draw ALL texts up to current index
    // for (int i = 0; i <= dialogueManager.GetCurrentTextIndex(); i++)
    // {
    //     // Only draw if this text exists
    //     if (i < dialogueManager.GetCurrentNode()->GetEntryCount())
    //     {
    //         dialogueManager.GetCurrentNode()->GetEntry(i).GetText().Draw(50, 50 + (i * 40));
    //     }
    // }

    // // ui.drawFlags()
    // {
    //     int i = 0;
    //     for (auto &flag : gameState.GetCurrentFlags())
    //     {
    //         bool on = flag.second;

    //         raylib::Color textColor = on ? raylib::Color::Green() : raylib::Color::Red();
    //         raylib::DrawText(TextFormat("%s [%d]", flag.first.c_str(), flag.second), 1000, 50 + (i * 40), 20, textColor);
    //         i++;
    //     }
    // }

    // // ui.drawInventory()
    // {
    //     int i = 0;
    //     for (auto &item : gameState.currentCharacter().GetInventory())
    //     {
    //         const char *displayName = gameState.GetItemLoader().GetItem(item.first).GetDisplayName().c_str();
    //         const char *description = gameState.GetItemLoader().GetItem(item.first).GetDescription().c_str();
    //         raylib::DrawText(TextFormat("%s [%d]\ndesc: %s", displayName, item.second, description),
    //                          1000, 500 + (i * 80), 20, raylib::Color::DarkBrown());
    //         i++;
    //     }
    // }
    // {
    //     int i = 0;
    //     for (auto &var : gameState.GetCurrentVariables())
    //     {
    //         raylib::DrawText(TextFormat("%s [%d]", var.first.c_str(), var.second),
    //                          1000, 300 + (i * 40), 20, raylib::Color::DarkBrown());
    //         i++;
    //     }
    // }

    // // ui.drawChoices()
    // if (dialogueManager.isShowingChoices())
    // {
    //     const auto &choices = dialogueManager.GetChoices();

    //     // Draw all choices, grey out unavailable ones
    //     for (int i = 0; i < choices.size() && i < 9; i++)
    //     {
    //         bool available = choices[i].IsAvailable(gameState);

    //         Color textColor = available ? BLACK : GRAY;
    //         DrawText(TextFormat("[%d] %s", i + 1, choices[i].GetText().c_str()),
    //                  50, 500 + (i * 40), 20, textColor);

    //         // Input check for THIS specific choice
    //         if (available && IsKeyPressed(KEY_ONE + i))
    //         {
    //             dialogueManager.SelectChoice(i);
    //         }
    //     }
    // }
}