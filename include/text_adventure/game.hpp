#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "game_state.hpp"

class Game
{
    GameState state;
    DialogueManager dialogue;
    UIManager ui;
    InputManager input;

public:
    void Run();
};

#endif