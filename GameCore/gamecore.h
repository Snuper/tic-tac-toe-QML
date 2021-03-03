#ifndef GAMECORE_H
#define GAMECORE_H

#include <iostream>
#include <time.h>
#include <typeinfo>
#include "albot.h"

class GameCore
{
public:
    GameCore();
    void StartGame(); //основа игры

private:
    bool    _xORo, //True - X; False - O
            _game,
            _humanStep;

    char** _array = nullptr; //1 - ряд (X); 2 - столбец (O)

    short _counter; //счетчик

    ALBot *_bot = nullptr;

    bool SetXO(short); //ход(записывает ход в игровое поле)

    void Game(char);
    void ShowWhoseStep();
    void ChangeStepXO(); //Меняет X на O, не придумал ничего лучше(
    void EndGame(char); //Заканчивает игру
    void PlayerInput();
    void ShowField(); //вывести игровое поле
    void CheckWinner(); //проверка победителя
};

#endif // GAMECORE_H
