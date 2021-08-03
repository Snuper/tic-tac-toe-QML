#include "albot.h"

ALBot::ALBot(){}

ALBot::ALBot(const bool* xORo, const short* prevMove, char** gameField)
    : _xORo(xORo), _prevMove(prevMove), _gameField(gameField) {}

short ALBot::botInput()
{
    toGamefieldCoordinates(_prevMove, &_rowPrevMove, &_columnPrevMove);

    if (!analyzingGameField())
    {
        randomInput();
    }

    return toShort(&_row, &_column);
}

void ALBot::randomInput()
{   
    _row = 0 + rand() % (3 - 0);
    _column = 0 + rand() % (3 - 0);
}

bool ALBot::analyzingGameField()
{
    findEmptyCells();
    if(lineChecking()) return true;
    return false;
}

short ALBot::toShort(const short *row, const short *column)
{
   return *row * 10 + *column;
}

void ALBot::toGamefieldCoordinates(const short *arg, short *row, short *column)
{
    *row = *arg / 10;
    *column = *arg % 10;
}

bool ALBot::lineChecking()
{
    /*
    Если вы или ваш противник поставили две отметки на одной линии, ставьте
    отметку в оставшейся на этой линии клетке
    */
    short   emptyRow,
            emptyColumn,
            counterEmpty,
            column,
            row;

    for (short i = 0; i < (short)_emptyCels.size(); i++)
    {
        toGamefieldCoordinates(&_emptyCels[i], &emptyRow, &emptyColumn);

        for (column = 0, counterEmpty = 0; column < 3; column++)
        {//првоеряем строки
            counterEmpty = (_gameField[emptyRow][column] == '.') ? counterEmpty + 1 : counterEmpty ;
        }

        if (counterEmpty == 1 && sameSimbols(&emptyRow, &emptyColumn))
        {
            return true;
        }

        for (row = 0, counterEmpty = 0; row < 3; row++)
        {//проверяем столбцы
            counterEmpty = (_gameField[row][emptyColumn] == '.') ? counterEmpty + 1 : counterEmpty ;
        }

        if (counterEmpty == 1)
        {
            _row = emptyRow;
            _column = emptyColumn;
            return true;
        }
    }
    /*
    //Проверяем диоганали
    if (_gameField[0][0] == 'X' && _gameField[1][1] == 'X' && _gameField[2][2] == 'X')
    {
    }
    else if (_gameField[0][0] == 'O' && _gameField[1][1] == 'O' && _gameField[2][2] == 'O')
    {
    }
    else if (_gameField[0][2] == 'X' && _gameField[1][1] == 'X' && _gameField[2][0] == 'X')
    {
    }
    else if (_gameField[0][2] == 'O' && _gameField[1][1] == 'O' && _gameField[2][0] == 'O')
    {
    }
    //Проверяем диоганали
    */

    return false;
}

bool ALBot::sameSimbols(short *row, short *column)
{

    return false;
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
