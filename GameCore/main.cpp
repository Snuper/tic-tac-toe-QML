#include <gamecore.h>

int main(int argc, char *argv[])
{
    char Choise;

    while(true)
    {
        GameCore *obj = new GameCore;
        obj->StartGame();
        delete obj;

        std::cout << "You wonna Play again?";
        std::cin >> Choise;
        if (Choise == 'n')
            break;
    }
}
