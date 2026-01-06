#include <raylib-cpp.hpp>

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
        // ui.Draw()

        // ui.drawNodes()
        // Draw ALL texts up to current index
        for (int i = 0; i <= dialogueManager.GetCurrentTextIndex(); i++)
        {
            // Only draw if this text exists
            if (i < dialogueManager.GetCurrentNode()->GetEntryCount())
            {
                dialogueManager.GetCurrentNode()->GetEntry(i).GetText().Draw(50, 50 + (i * 40));
            }
        }

        // ui.drawFlags()
        {
            int i = 0;
            for (auto &flag : gameState.GetCurrentFlags())
            {
                bool on = flag.second;

                raylib::Color textColor = on ? raylib::Color::Green() : raylib::Color::Red();
                raylib::DrawText(TextFormat("%s [%d]", flag.first.c_str(), flag.second), 1000, 50 + (i * 40), 20, textColor);
                i++;
            }
        }

        // ui.drawInventory()
        {
            int i = 0;
            for (auto &item : gameState.currentCharacter().GetInventory())
            {
                const char *displayName = gameState.GetItemLoader().GetItem(item.first).GetDisplayName().c_str();
                const char *description = gameState.GetItemLoader().GetItem(item.first).GetDescription().c_str();
                raylib::DrawText(TextFormat("%s [%d]\ndesc: %s", displayName, item.second, description),
                                 1000, 500 + (i * 80), 20, raylib::Color::DarkBrown());
                i++;
            }
        }
        {
            int i = 0;
            for (auto &var : gameState.GetCurrentVariables())
            {
                raylib::DrawText(TextFormat("%s [%d]", var.first.c_str(), var.second),
                                 1000, 300 + (i * 40), 20, raylib::Color::DarkBrown());
                i++;
            }
        }

        // ui.drawChoices()
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