#include <raylib-cpp.hpp>
#include "rpg_text.hpp"
// #include "dialogue_node.hpp"
// #include "json_loader.hpp"
#include "dialogue_manager.hpp"

constexpr unsigned int FPS = 60;

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;
    raylib::Window w(screenWidth, screenHeight, "Text Adventure");

    DialogueManager dialogueManager;

    // 1. LOAD STORY
    dialogueManager.LoadFromFile("../assets/temp.json");

    // 2. START AT FIRST NODE
    dialogueManager.SetStartNode("start");
    dialogueManager.GoToNode("start");

    SetTargetFPS(FPS);

    while (!w.ShouldClose())
    {
        // UPDATE
        dialogueManager.Update();

        if (!dialogueManager.isShowingChoices())
        {
            // Space to speed up
            if (raylib::Keyboard::IsKeyDown(KEY_SPACE))
            {
                dialogueManager.GetCurrentText()->Update(8);
            }

            // Enter to advance text or go to choices
            if (raylib::Keyboard::IsKeyPressed(KEY_ENTER))
            {
                dialogueManager.Advance();
            }
        }
        else
        {
            // Number keys to select choice
            for (int i = 0; i < dialogueManager.GetChoicesCount(); i++)
            {
                if (raylib::Keyboard::IsKeyPressed(KEY_ONE + i))
                {
                    // Change node
                    dialogueManager.SelectChoice(i);
                    break;
                }
            }
        }

        // DRAW
        w.BeginDrawing();
        w.ClearBackground(RAYWHITE);

        if (!dialogueManager.isShowingChoices())
        {
            // Draw ALL texts up to current index
            for (int i = 0; i <= dialogueManager.GetCurrentTextIndex(); i++)
            {
                // Only draw if this text exists
                if (i < dialogueManager.GetCurrentNode()->GetTextCount())
                {
                    dialogueManager.GetCurrentNode()->GetText(i)->Draw(50, 50 + (i * 40));
                }
            }
        }
        else
        {
            // Draw choices
            auto &choices = dialogueManager.GetCurrentNode()->GetChoices();
            for (int i = 0; i < choices.size(); i++)
            {
                DrawText(TextFormat("[%d] %s", i + 1, choices[i].text.c_str()),
                         50, 100 + (i * 40), 20, BLACK);
            }
        }

        w.EndDrawing();
    }
}