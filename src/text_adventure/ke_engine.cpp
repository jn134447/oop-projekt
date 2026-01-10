#include "ke_engine.hpp"

#include <iostream>

Engine::Engine(bool debug)
    : gameState(flagRegistry, itemLoader, varRegistry, effectLoader),
      dialogueManager(gameState),
      uiManager(gameState, dialogueManager, debug)
{
}

bool Engine::Init(const std::string &itemsFile, const std::string &flagsFile, const std::string &variablesFile, const std::string &storyFile, const std::string &configFile)
{
    try
    {
        itemLoader.LoadFromFile(itemsFile);
        flagRegistry.LoadFromFile(flagsFile);
        varRegistry.LoadFromFile(variablesFile);

        configLoader.LoadFromFile(configFile);

        dialogueManager.LoadStory(storyFile, configFile);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Engine initialization failed: " << e.what() << std::endl;
        return false;
    }
}

void Engine::StartStory(const std::string &startNode)
{
    dialogueManager.SetStartNode(startNode);
    dialogueManager.GoToNode(startNode);
}

void Engine::Update()
{
    dialogueManager.Update();
}

void Engine::DrawUI()
{
    uiManager.Draw();
}

void Engine::HandleInput()
{
    uiManager.HandleInput();
}

GameState &Engine::GetGameState()
{
    return gameState;
}

DialogueManager &Engine::GetDialogueManager()
{
    return dialogueManager;
}

const DialogueManager &Engine::GetDialogueManager() const
{
    return dialogueManager;
}
