#include "albot.h"

ALBot::ALBot()
{

}

short ALBot::botInput()
{
    short row;
    short column;

    row = 0 + rand() % (3 - 0);
    column = 0 + rand() % (3 - 0);

    return (row * 10 + column);
}
