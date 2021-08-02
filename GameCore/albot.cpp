#include "albot.h"

ALBot::ALBot(){}

ALBot::ALBot(char** gameField, const bool* xORo, const short* prevMove)
    : _xORo(xORo), _gameField(gameField), _prevMove(prevMove) {}

short ALBot::botInput()
{
    _rowPrevMove = *_prevMove / 10;
    _columnPrevMove = *_prevMove % 10;

    if (!analyzingGameField())
    {
        randomInput();
    }

    return (_row * 10 + _column);
}

void ALBot::randomInput()
{   
    _row = 0 + rand() % (3 - 0);
    _column = 0 + rand() % (3 - 0);
}

bool ALBot::analyzingGameField()
{
    findEmptyCells();
    if(twoInLine()) return true;
    return false;
}

bool ALBot::twoInLine()
{
    /*
    Если вы или ваш противник поставили две отметки на одной линии, ставьте
    отметку в оставшейся на этой линии клетке
    */
    short   row,
            column;

    for (short i = 0; i < (short)_emptyCels.size(); i++)
    {
        row = _emptyCels[i] / 10;
        column = _emptyCels[i] % 10;
        if (_emptyCels[i] == 0 || _emptyCels[i] == 2 || _emptyCels[i] == 20 || _emptyCels[i] == 22)
        {
            ;
        }
    }
}

void ALBot::findEmptyCells()
{
    for (short row = 0; row < 3; row++)
    {
        for (short column = 0; column < 3; column++)
        {
            if (_gameField[row][column] == '.')
            {
                _emptyCels.push_back(row * 10 + column);
            }
        }
    }
    _emptyCels.clear();
}

void ALBot::showBotInfo()
{//Выводит всю инфу, что видит бот
    std::cout << std::endl;
    std::cout << "---------Field ALBOT---------";

    std::cout << "\nSettings: " << std::endl;
    std::cout << "  xORo = " << *_xORo << std::endl;
    std::cout << "  prevMove = " << *_prevMove << std::endl;
    std::cout << "  gameField (&) = " << _gameField << std::endl;

    for (short row = 0; row < 3; row++)
    {
        std::string saveLine;
        std::cout << "  ";
        for (short column = 0; column < 3; column++)
        {
            std::cout << _gameField[row][column] << "   ";
            saveLine += std::string(1, _gameField[row][column]) + "   ";
        }
        std::cout << std::endl;
    }

    std::cout << "---------Field ALBOT---------";
}
