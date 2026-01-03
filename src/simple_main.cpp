#include <raylib-cpp.hpp>
#include "rpg_text.hpp"
#include "dialogue_node.hpp"
#include "json_loader.hpp"

constexpr unsigned int FPS = 60;

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;
    raylib::Window w(screenWidth, screenHeight, "Text Adventure");

    // 1. LOAD STORY
    auto nodes = DialogueLoader::LoadFromFile("../assets/temp.json");
    
    // 2. START AT FIRST NODE
    std::string currentNodeId = "start";
    DialogueNode* currentNode = nodes[currentNodeId].get();
    int currentTextIndex = 0;
    bool showingChoices = false;
    
    SetTargetFPS(FPS);
    
    while (!w.ShouldClose())
    {
        // UPDATE
        if (!showingChoices) {
            // Update current text animation
            if (currentTextIndex < currentNode->GetTextCount()) {
                RPGText* currentText = currentNode->GetText(currentTextIndex);
                currentText->Update();
                
                // Space to speed up
                if (raylib::Keyboard::IsKeyDown(KEY_SPACE)) {
                    currentText->Update(8);
                }
                
                // Enter to advance text or go to choices
                if (raylib::Keyboard::IsKeyPressed(KEY_ENTER)) {
                    if (currentText->IsComplete()) {
                        currentTextIndex++;
                        if (currentTextIndex >= currentNode->GetTextCount()) {
                            showingChoices = true;
                        }
                    } else {
                        currentText->Skip();
                    }
                }
            }
        } else {
            // We're showing choices
            auto& choices = currentNode->GetChoices();
            
            // Number keys to select choice
            for (int i = 0; i < choices.size(); i++) {
                if (raylib::Keyboard::IsKeyPressed(KEY_ONE + i)) {
                    // Change node
                    currentNodeId = choices[i].target;
                    currentNode = nodes[currentNodeId].get();
                    currentTextIndex = 0;
                    showingChoices = false;
                    break;
                }
            }
        }
        
        // DRAW
        w.BeginDrawing();
        w.ClearBackground(RAYWHITE);
        
        if (!showingChoices && currentTextIndex < currentNode->GetTextCount()) {
            // Draw current text
            currentNode->GetText(currentTextIndex)->Draw(50, 50);
        } else if (showingChoices) {
            // Draw choices
            auto& choices = currentNode->GetChoices();
            for (int i = 0; i < choices.size(); i++) {
                DrawText(TextFormat("[%d] %s", i + 1, choices[i].text.c_str()), 
                         50, 100 + (i * 40), 20, BLACK);
            }
        }
        
        w.EndDrawing();
    }
}