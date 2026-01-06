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

    ItemLoader itemLoader;
    itemLoader.LoadFromFile(GameConsts::files::ITEMS);
    FlagRegistry flagRegistry;
    flagRegistry.LoadFromFile(GameConsts::files::FLAGS);
    VariableRegistry varRegistry;
    varRegistry.LoadFromFile(GameConsts::files::VARIABLES);

    GameState gameState(flagRegistry, itemLoader, varRegistry);
    DialogueManager dialogueManager(gameState);

    // 1. LOAD STORY
    dialogueManager.LoadStory(GameConsts::files::STORY,
                              GameConsts::files::CONFIG);

    // 2. START AT FIRST NODE
    dialogueManager.SetStartNode("test_start");
    dialogueManager.GoToNode("test_start");

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
                dialogueManager.GetCurrentText().Update(8);
            }

            // Enter to advance text or go to choices
            if (raylib::Keyboard::IsKeyPressed(KEY_ENTER))
            {
                dialogueManager.Advance();
            }
        }

        // DRAW
        w.BeginDrawing();
        w.ClearBackground(RAYWHITE);

        // Draw ALL texts up to current index
        for (int i = 0; i <= dialogueManager.GetCurrentTextIndex(); i++)
        {
            // Only draw if this text exists
            if (i < dialogueManager.GetCurrentNode()->GetEntryCount())
            {
                dialogueManager.GetCurrentNode()->GetEntry(i).GetText().Draw(50, 50 + (i * 40));
            }
        }

        {
            int i = 0;
            for (auto &flag : gameState.GetCurrentFlags())
            {
                bool on = flag.second;

                raylib::Color textColor = on ? raylib::Color::Green() : raylib::Color::Red();
                raylib::DrawText(TextFormat("%s [%d]", flag.first.c_str(), flag.second), 800, 50 + (i * 40), 20, textColor);
                i++;
            }
        }

        if (dialogueManager.isShowingChoices())
        {
            const auto &choices = dialogueManager.GetChoices();

            // Draw all choices, grey out unavailable ones
            for (int i = 0; i < choices.size() && i < 9; i++)
            {
                bool available = choices[i].IsAvailable(gameState);

                Color textColor = available ? BLACK : GRAY;
                DrawText(TextFormat("[%d] %s", i + 1, choices[i].GetText().c_str()),
                         50, 500 + (i * 40), 20, textColor);

                // Input check for THIS specific choice
                if (available && IsKeyPressed(KEY_ONE + i))
                {
                    dialogueManager.SelectChoice(i);
                }
            }
        }

        w.EndDrawing();
    }
}