#ifndef ALBOT_H
#define ALBOT_H

#include <iostream>

class ALBot
{//Automatically Learning Bot
public:
    ALBot(char**, const bool*, const short*);
    ALBot();

    short botInput();

private:
    const bool    *_xORo = nullptr; //True - X; False - O
    char    **_gameField = nullptr; //1 - ряд (X); 2 - столбец (O)..что это?!
    const short   *_prevMove = nullptr;

    void analyzingGameField();
    void fiendEmptyCells();
    void showField();
};

#endif // ALBOT_H
