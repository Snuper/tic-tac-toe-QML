#ifndef ALBOT_H
#define ALBOT_H

#include <iostream>

class ALBot
{//Automatically Learning Bot
public:
    ALBot(char**, const bool&, const short&);
    ALBot();

    short botInput();

private:
    bool    _xORo; //True - X; False - O
    char** _gameField = nullptr; //1 - ряд (X); 2 - столбец (O)..что это?!
    short   _prevMove;

    void analyzingGameField();
    void fiendEmptyCells();
    void showField();
};

#endif // ALBOT_H
