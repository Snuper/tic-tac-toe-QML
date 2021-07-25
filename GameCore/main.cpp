#include <gamecore.h>

int main(void)
{
    char choise;

    while (true)
    {
        system("clear");

        GameCore *obj = new GameCore;
        obj->StartGame();
        delete obj;

        std::cout << "\nYou wonna play again? (y/n)";
        std::cin >> choise;
        if (choise == 'n')
            break;
    }
}
