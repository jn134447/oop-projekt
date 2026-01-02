#ifndef TEMPLATE_H
#define TEMPLATE_H


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