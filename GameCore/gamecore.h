#ifndef GAMECORE_H
#define GAMECORE_H

#include <iostream>
#include <time.h>
#include "albot.h"
#include "logger.h"

class GameCore
{
public:
    GameCore();
    void startGame();

private:
    bool    _xORo, //True - X; False - O
            _game,
            _humanStep;

    char** _gameField = nullptr; //1 - ряд (X); 2 - столбец (O)..что это?!

    short   _counter,
            _prevMove = -1;

    ALBot *_bot = nullptr;
    Logger *_log;

    bool setXO(short); //ход(записывает ход в игровое поле)
    short toShort(const short* row, const short* column);
    void toGamefieldCoordinates(const short* arg, short* row, short* column);
    void game(const char);
    void choiceModeGame();
    void randFirstRightMove();
    void showWhoseStep();
    void changeRightMove(); //Передает право хода
    void endGame(const char);
    void playerInput();
    void showField(); //вывести игровое поле
    void checkWinner(); //проверка победителя
};

#endif // GAMECORE_H
