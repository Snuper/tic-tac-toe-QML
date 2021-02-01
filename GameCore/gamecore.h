#ifndef GAMECORE_H
#define GAMECORE_H
#include <iostream>

class GameCore
{
public:
    GameCore();
    void StartGame();
    //основа игры
    void SetXO();
    //в чей ход записывает

private:
    short **Array = nullptr;

    bool CheckWinner();
    //проверка победителя

    bool Turn;
};

#endif // GAMECORE_H
