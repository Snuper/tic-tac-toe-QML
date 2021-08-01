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
    const short   *_prevMove = nullptr;
    char    **_gameField = nullptr; //1 - ряд (X); 2 - столбец (O)..что это?!
    short   **emptyCels = nullptr,
            _row,
            _column,
            _rowPrevMove,
            _columnPrevMove;

    bool analyzingGameField();
    void findEmptyCells();
    void showBotInfo();
    void randomInput();
};

#endif // ALBOT_H
