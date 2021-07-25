#ifndef GAMECORE_H
#define GAMECORE_H

#include <iostream>
#include <time.h>
#include <typeinfo>
#include "albot.h"
#include "logger.h"

class GameCore
{
public:
    GameCore();
    void StartGame();

private:
    bool    _xORo, //True - X; False - O
            _game,
            _humanStep;

    char** _gameField = nullptr; //1 - ряд (X); 2 - столбец (O)..что это?!

    short _counter;

    ALBot *_bot = nullptr;

    bool SetXO(short); //ход(записывает ход в игровое поле)

    Logger *_log;

    void Game(const char);
    void ChoiceModeGame();
    void RandFirstRightMove();
    void ShowWhoseStep();
    void ChangeRightMove(); //Передает право хода
    void EndGame(const char);
    void PlayerInput();
    void ShowField(); //вывести игровое поле
    void CheckWinner(); //проверка победителя
};

#endif // GAMECORE_H
