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

    bool lineSearching(short requiredNumberEmpty);
    bool sameSimbols(std::vector<short> *argCell);
    bool lineChecking(const short *counterEmpty, const short *requiredNumberEmpty,
                      const short *emptyRow, const short *emptyColumn,
                      std::vector<short> *argCell);
    bool centerCellCheck();
    bool mirrorMove();
    bool cornerCellCheck();
    short toShort(const short* row, const short* column);
    short toShort(const short row, const short column);
    void toGamefieldCoordinates(const short* arg, short* row, short* column);
    void findEmptyCells();
    void showBotInfo();
    void randomInput();
    void analyzingGameField();
};

#endif // ALBOT_H
