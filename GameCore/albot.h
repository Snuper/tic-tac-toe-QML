#ifndef ALBOT_H
#define ALBOT_H

#include <iostream>
#include <vector>

class ALBot
{//Automatically Learning Bot
public:
    ALBot(const bool* xORo, const short* prevMove, char** gameField);
    ALBot();

    short botInput();

private:
    const bool    *_xORo = nullptr; //True - X; False - O
    const short   *_prevMove = nullptr;
    char    **_gameField = nullptr; //1 - ряд (X); 2 - столбец (O)..что это?!
    short   _row,
            _column,
            _rowPrevMove,
            _columnPrevMove;
    std::vector<short> _emptyCels;

    bool analyzingGameField();
    bool lineChecking();
    bool sameSimbols(std::vector<short> *argCell);
    short toShort(const short* row, const short* column);
    short toShort(const short row, const short column);
    void toGamefieldCoordinates(const short* arg, short* row, short* column);
    void findEmptyCells();
    void showBotInfo();
    void randomInput();
};

#endif // ALBOT_H
