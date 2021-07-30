#include "albot.h"

ALBot::ALBot()  {}

ALBot::ALBot(char** gameField, const bool& xORo, const short& prevMove)
    : _xORo(xORo), _gameField(gameField), _prevMove(prevMove) {}

short ALBot::botInput()
{
    short   row = _prevMove / 10,
            column = _prevMove % 10;

    row = 0 + rand() % (3 - 0);
    column = 0 + rand() % (3 - 0);

    return (row * 10 + column);
}

void ALBot::analyzingGameField()
{
    ;
}

void ALBot::fiendEmptyCells()
{
    ;
}

void ALBot::showField()
{//Выводим игровое поле

    std::cout << std::endl;
    std::cout << "---------Field ALBOT---------";

    std::cout << "Settings: " << std::endl;
    std::cout << "  xORo = " << _xORo << std::endl;
    std::cout << "  prevMove = " << _prevMove << std::endl;
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
