// ui_manager.cpp
#include "ui_manager.hpp"
#include <iostream>

UIManager::UIManager(GameState &gameState, DialogueManager &dialogueManager, bool debug)
    : gameState(gameState),
      dialogueManager(dialogueManager),
      showDebugInfo(debug),
      // Initialize layout values
      textStartX(50),
      textStartY(50),
      textLineSpacing(40),
      choiceStartX(50),
      choiceStartY(500),
      choiceSpacing(40),
      debugStartX(1000),
      flagsStartY(50),
      variablesStartY(300),
      inventoryStartX(1000),
      inventoryStartY(500),
      effectsStartX(700),
      effectsStartY(500),
      debugSpacing(40),
      // Initialize colors
      backgroundColor(RAYWHITE),
      defaultTextColor(BLACK),
      activeChoiceColor(BLACK),
      inactiveChoiceColor(GRAY),
      flagTrueColor(GREEN),
      flagFalseColor(RED),
      inventoryColor(DARKBROWN),
      effectsColor(DARKBLUE),
      variableColor(DARKBROWN),
      lineSpacingMultiplier(1.5f)
{
    // Nothing else to initialize
}

void UIManager::Draw()
{
    // Draw main dialogue text
    DrawCurrentDialogue();
    DrawInventory();
    DrawEffects();

    // Draw choices if available
    if (dialogueManager.isShowingChoices())
    {
        DrawChoices();
    }

    // Draw debug info if enabled
    if (showDebugInfo)
    {
        DrawDebugPanel();
    }
}

void UIManager::DrawCurrentDialogue()
{
    const auto *currentNode = dialogueManager.GetCurrentNode();
    if (!currentNode)
        return;

    int currentTextIndex = dialogueManager.GetCurrentTextIndex();

    for (int i = 0; i <= currentTextIndex; i++)
    {
        if (i < currentNode->GetEntryCount())
        {
            const auto &entry = currentNode->GetEntry(i);
            const auto &text = entry.GetText();

            // Calculate position for this text entry
            int x = textStartX;

            // Dynamic Y position based on accumulated line heights
            int y = textStartY;
            for (int j = 0; j < i; j++)
            {
                if (j < currentNode->GetEntryCount())
                {
                    const auto &prevText = currentNode->GetEntry(j).GetText();
                    float prevFontSize = prevText.GetFontSize();
                    y += static_cast<int>(prevFontSize * lineSpacingMultiplier);
                }
            }

            // Use RPGText's own Draw method
            text.Draw(x, y);
        }
    }
}

void UIManager::DrawChoices()
{
    const auto &choices = dialogueManager.GetChoices();

    for (size_t i = 0; i < choices.size(); i++)
    {
        bool available = choices[i].IsAvailable(gameState);

        int x = choiceStartX;
        int y = choiceStartY + (static_cast<int>(i) * choiceSpacing);

        // Draw choice number
        std::string numberText = std::to_string(i + 1) + ") ";
        raylib::Color numberColor = available ? activeChoiceColor : inactiveChoiceColor;
        raylib::DrawText(numberText, x, y, 20, numberColor);

        // Draw choice text
        int numberWidth = raylib::MeasureText(numberText, 20);
        std::string choiceText = choices[i].GetText();

        raylib::Color textColor = available ? activeChoiceColor : inactiveChoiceColor;
        raylib::DrawText(choiceText, x + numberWidth, y, 20, textColor);

        // Optional: Draw a lock icon for unavailable choices
        if (!available)
        {
            raylib::DrawText("X", x - 30, y, 20, inactiveChoiceColor);
        }
    }
}

void UIManager::DrawDebugPanel()
{
    DrawFlags();
    DrawVariables();
    // DrawInventory();
}

void UIManager::DrawFlags()
{
    int y = flagsStartY;

    for (const auto &flag : gameState.GetCurrentFlags())
    {
        std::string flagText = flag.first + " [" + (flag.second ? "ON" : "OFF") + "]";
        raylib::Color color = flag.second ? flagTrueColor : flagFalseColor;
        raylib::DrawText(flagText, debugStartX, y, 20, color);
        y += debugSpacing;
    }
}

void UIManager::DrawVariables()
{
    int y = variablesStartY;

    for (const auto &var : gameState.GetCurrentVariables())
    {
        std::string varText = var.first + " [" + std::to_string(var.second) + "]";
        raylib::DrawText(varText, debugStartX, y, 20, variableColor);
        y += debugSpacing;
    }
}

void UIManager::DrawInventory()
{
    int y = inventoryStartY;

    const auto &inventory = gameState.currentCharacter().GetInventory();
    const auto &itemLoader = gameState.GetItemLoader();

    for (const auto &item : inventory)
    {
        if (item.second > 0)
        {
            const auto &itemData = itemLoader.GetItem(item.first);
            std::string itemText = itemData.GetDisplayName() + " [" + std::to_string(item.second) + "]";
            raylib::DrawText(itemText, debugStartX, y, 20, inventoryColor);
            y += debugSpacing;
        }
    }
}

void UIManager::DrawEffects()
{
    int y = effectsStartY;

    const auto &effects = gameState.currentCharacter().GetEffects();
    const auto &effectLoader = gameState.GetEffectLoader();

    for (const auto &effect : effects)
    {
        if (effect.second > 0)
        {
            const auto &effectData = effectLoader.GetEffect(effect.first);
            std::string effectText = effectData.GetDisplayName() + " x" + std::to_string(effect.second);
            raylib::DrawText(effectText, debugStartX, y, 20, inventoryColor);
            y += debugSpacing;
        }
    }
}

void UIManager::HandleInput()
{
    // Handle text advancement
    if (!dialogueManager.isShowingChoices())
    {
        // Space to speed up text
        if (raylib::Keyboard::IsKeyDown(KEY_SPACE))
        {
            // Get current text and speed it up
            int currentIndex = dialogueManager.GetCurrentTextIndex();
            if (currentIndex < dialogueManager.GetCurrentNode()->GetEntryCount())
            {
                auto &currentText = dialogueManager.GetCurrentNode()
                                        ->GetEntry(currentIndex)
                                        .GetText();
                currentText.Update(8); // Fast update
            }
        }

        // Enter to advance
        if (raylib::Keyboard::IsKeyPressed(KEY_ENTER))
        {
            dialogueManager.Advance();
        }
    }

    // Handle choices
    HandleChoiceInput();
}

bool UIManager::HandleChoiceInput()
{
    if (!dialogueManager.isShowingChoices())
        return false;

    const auto &choices = dialogueManager.GetChoices();

    for (size_t i = 0; i < choices.size() && i < 9; i++)
    {
        if (choices[i].IsAvailable(gameState) && IsKeyPressed(KEY_ONE + static_cast<int>(i)))
        {
            dialogueManager.SelectChoice(static_cast<int>(i));
            return true;
        }
    }

    return false;
}