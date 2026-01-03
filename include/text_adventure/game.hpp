#ifndef GAME_H
#define GAME_H

#include "manager.hpp"
#include "game_state.hpp"

class Game
{
    GameState state;
    DialogueManager dialogue;
    // UIManager ui;
    // InputManager input;

public:
    void Run();
};

#endif