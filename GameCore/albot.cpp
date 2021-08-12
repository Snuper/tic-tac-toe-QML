#include "albot.h"

ALBot::ALBot(){}

ALBot::ALBot(const bool* xORo, const short* prevMove, char** gameField)
    : _xORo(xORo), _prevMove(prevMove), _gameField(gameField) {}

short ALBot::botInput()
{
    analyzingGameField();
    return toShort(&_row, &_column);
}

void ALBot::randomInput()
{
    short randNumber;
    randNumber = 0 + rand() % (_emptyCels.size() - 0);

    toGamefieldCoordinates(&_emptyCels[randNumber], &_row, &_column);
}

void ALBot::analyzingGameField()
{
    findEmptyCells();
    if (lineSearching(1)) return;
    if (lineSearching(2)) return;
    if (centerCellCheck()) return;
    if (mirrorMove()) return;
    if (cornerCellCheck()) return;
    randomInput();
}

short ALBot::toShort(const short *row, const short *column)
{
   return *row * 10 + *column;
}

short ALBot::toShort(const short row, const short column)
{
   return row * 10 + column;
}

void ALBot::toGamefieldCoordinates(const short *arg, short *row, short *column)
{
    *row = *arg / 10;
    *column = *arg % 10;
}

bool ALBot::lineSearching(short requiredNumberEmpty)
{
    /*
    swtich(requiredNumberEmpty)
    case 1 : Ход, который контрит победную линию противника или создает победную линию себе
    case 2 : Ход, который создаст две линии по две отметки
    */
    short   emptyRow,
            emptyColumn,
            counterEmpty,
            column,
            row;

    std::vector<short> argCell;

    bool    mainDiagona;


    for (short i = 0; i < (short)_emptyCels.size(); i++)
    {
        toGamefieldCoordinates(&_emptyCels[i], &emptyRow, &emptyColumn);

        for (column = 0, counterEmpty = 0; column < 3; column++)
        {//првоеряем строки
            counterEmpty = (_gameField[emptyRow][column] == '.') ? counterEmpty + 1 : counterEmpty;
            if (column != emptyColumn)
            {
                argCell.push_back(toShort(&emptyRow, &column));
            }
        }

        if (lineChecking(&counterEmpty, &requiredNumberEmpty, &emptyRow, &emptyColumn, &argCell))
        {
            return true;
        }

        for (row = 0, counterEmpty = 0; row < 3; row++)
        {//проверяем столбцы
            counterEmpty = (_gameField[row][emptyColumn] == '.') ? counterEmpty + 1 : counterEmpty;
            if (row != emptyRow)
            {
                argCell.push_back(toShort(&row, &emptyColumn));
            }
        }

        if (lineChecking(&counterEmpty, &requiredNumberEmpty, &emptyRow, &emptyColumn, &argCell))
        {
            return true;
        }

        if (((mainDiagona = (_emptyCels[i] == 0 || _emptyCels[i] == 22) ? true : false) ^ (_emptyCels[i] == 2 || _emptyCels[i] == 20)) || _emptyCels[i] == 11)
        {//Проверяем диоганали
            short   incColDig,
                    row;

            bool centerCell = true; //флаг, который смениться при первом прохождении поиска диагонали, для центральной ячейки

            if (!mainDiagona)
            {
                row = 0;
                column = 2;
                incColDig = -1;
            }

            else
            {
                CenterCellDoubleCheck: //Проверяем главную диагональ для центральной ячейки
                row = 0;
                column = 0;
                incColDig = 1;
            }

            for (counterEmpty = 0; row < 3; row++, column += incColDig)
            {
                counterEmpty = (_gameField[row][column] == '.') ? counterEmpty + 1 : counterEmpty;
                if (column != emptyColumn)
                {
                    argCell.push_back(toShort(&row, &column));
                }
            }

            if (lineChecking(&counterEmpty, &requiredNumberEmpty, &emptyRow, &emptyColumn, &argCell))
            {
                return true;
            }
            else if (_emptyCels[i] == 11 && centerCell == true)
            {
                centerCell = false;
                goto CenterCellDoubleCheck;
            }
        }
    }

    return false;
}

bool ALBot::lineChecking(const short *counterEmpty, const short *requiredNumberEmpty,
                         const short *emptyRow, const short *emptyColumn,
                         std::vector<short> *argCell)
{
    if (*counterEmpty == *requiredNumberEmpty)
    {
        if (*requiredNumberEmpty == 1)
        {
            if (sameSimbols(argCell))
            {
                _row = *emptyRow;
                _column = *emptyColumn;
                return true;
            }
        }
        else
        {
            short   tempRow,
                    tempColumn;

            toGamefieldCoordinates(&argCell->at(0), &tempRow, &tempColumn);

            if ((_gameField[tempRow][tempColumn] == 'X' && (_xORo)) or (_gameField[tempRow][tempColumn] == 'O' && (!_xORo)))
            {
                _row = *emptyRow;
                _column = *emptyColumn;
                return true;
            }
        }
    }
    else
    {
        argCell->clear();
    }

    return false;
}

bool ALBot::sameSimbols(std::vector <short> *argCell)
{
    short   row[2],
            column[2];

    for (short i = 0; i < (short)argCell->size(); i++)
    {
        toGamefieldCoordinates(&argCell->at(i), &row[i], &column[i]);
    }

    argCell->clear();

    return (_gameField[row[0]][column[0]] == _gameField[row[1]][column[1]]) ? true : false;
}

void ALBot::findEmptyCells()
{
    _emptyCels.clear();

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
}

bool ALBot::centerCellCheck()
{
    if (_gameField[1][1] == '.')
    {
        _row = 1;
        _column = 1;
        return true;
    }

    return false;
}

bool ALBot::mirrorMove()
{
    if (*_prevMove == 0 || *_prevMove == 22)
    {
        if (_gameField[0][2] == '.')
        {
            _row = 0;
            _column = 2;
            return true;
        }
        if (_gameField[2][0] == '.')
        {
            _row = 2;
            _column = 0;
            return true;
        }
    }

    if (*_prevMove == 2 || *_prevMove == 20)
    {
        if (_gameField[0][0] == '.')
        {
            _row = 0;
            _column = 0;
            return true;
        }
        if (_gameField[2][2] == '.')
        {
            _row = 2;
            _column = 2;
            return true;
        }
    }

    return false;
}

bool ALBot::cornerCellCheck()
{
    if (_gameField[0][0] == '.')
    {
        _row = 0;
        _column = 0;
        return true;
    }
    else if (_gameField[0][2] == '.')
    {
        _row = 0;
        _column = 2;
        return true;
    }
    else if (_gameField[2][0] == '.')
    {
        _row = 2;
        _column = 0;
        return true;
    }
    else if (_gameField[2][2] == '.')
    {
        _row = 2;
        _column = 2;
        return true;
    }
    return false;
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
