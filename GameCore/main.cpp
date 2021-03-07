#include <gamecore.h>

int main(void)
{
    char Choise;

    while(true)
    {
        system("clear");

        GameCore *obj = new GameCore;
        obj->StartGame();
        delete obj;

        std::cout << "\nYou wonna play again? (y/n)";
        std::cin >> Choise;
        if (Choise == 'n')
            break;
    }
}
