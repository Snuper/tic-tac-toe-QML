#include "gamecore.h"

GameCore::GameCore()
{

}

void GameCore::StartGame()
{//Основа игры, всё обнуляем
    char choice;

    _array = new char*[3];
    for(int i = 0; i < 3; i++)
    {//иницилизируем игровое поле
        _array[i] = new char[3] {'.','.','.'};
    }

    _game = true;
    _counter = 8;

    srand(time(NULL));
    if(rand() % 2 == 0) _xORo = true;
    else _xORo = false;

    std::cout   << "Set format game: "
                << "\n1) PvP"
                << "\n1) PvE"
                << "\n1) EvE";

    std::cout << "\nInput: ";

    while(true)
    {//Пока не выберут
        std::cin >> choice;
        if(choice == '1')
        {
            GamePvP();
            break;
        }
        else if(choice == '2')
        {
            GamePvE();
            break;
        }
        else if(choice == '3')
        {
            GameEvE();
            break;
        }

        else
        {
            std::cout << "\nInvalid input, try again: ";
        }
    }
}

void GameCore::PlayerInput()
{
    bool step = false;
    short row, column;

    while(step == false)
    {
        std::cout << "\nInput coordinats field(row/column): ";
        std::cin >> row >> column;
        step = SetXO(row, column);
    }
}

void GameCore::GamePvP()
{
    while(true)
    {
        ShowWhoseStep();
        ShowField();
        PlayerInput();
        ChangeStepXO();
        CheckWinner();

        if(_game == false)
        {
            break;
        }

        system("clear");
        _counter--;
    }
}

void GameCore::GamePvE()
{
    ;
}

void GameCore::GameEvE()
{
    ;
}

bool GameCore::SetXO(short row, short column)
{//принимает номер строки и столбца, для заполнение ответа в игровое поле
    try
    {//пробуем сходить
        if(row > -1 && row < 3 && column > -1 && column < 3)
        {
            if(_array[row][column] == '.')
            {
                if(_xORo == true) _array[row][column] = 'X';
                else _array[row][column] = 'O';
            }
            else
            {
                throw "Position is busy";
            }
            return true;
        }
        else
        {
            throw "Missing memory";
        }

    }

    catch (const char *e)
    {
        std::cout << "\nInvalid input, try again (" << e << ")";
        return false;
    }
}

void GameCore::ChangeStepXO()
{//Меняет Ходящего (помогите назвать нормально)
    _xORo = !_xORo;
}

void GameCore::CheckWinner()
{//Проверям, не выйграл ли кто нить
    for(short row = 0; row < 3; row++)
    {//првоеряем строки
        if(_array[row][0] == 'X' && _array[row][1] == 'X' && _array[row][2] == 'X') EndGame('X');
        else if(_array[row][0] == 'O' && _array[row][1] == 'O' && _array[row][2] == 'O') EndGame('O');
    }

    for(short column = 0; column < 3; column++)
    {//проверяем столбцы
        if(_array[0][column] == 'X' && _array[1][column] == 'X' && _array[2][column] == 'X') EndGame('X');
        else if(_array[0][column] == 'O' && _array[1][column] == 'O' && _array[2][column] == 'O') EndGame('O');
    }

    //Проверяем диоганали
    if(_array[0][0] == 'X' && _array[1][1] == 'X' && _array[2][2] == 'X') EndGame('X');
    else if(_array[0][0] == 'O' && _array[0][0] == 'O' && _array[2][2] == 'O') EndGame('O');
    else if(_array[0][2] == 'X' && _array[1][1] == 'X' && _array[2][0] == 'X') EndGame('X');
    else if(_array[0][2] == 'O' && _array[0][0] == 'O' && _array[2][0] == 'O') EndGame('O');
    //Проверяем диоганали

    else
    {
        if(_counter == 0) EndGame('.');
    }
}

void GameCore::ShowField()
{//Выводим игровое поле

    std::cout << std::endl;

    for(short row = 0; row < 3; row++)
    {
        std::cout << "  ";
        for(short column = 0; column < 3; column++)
        {
            std::cout << _array[row][column] << "   ";
        }
        std::cout << std::endl;
    }
}

void GameCore::ShowWhoseStep()
{
    if(_xORo == true) std::cout << "\nNow step X\n";
    else std::cout << "\nNow step O\n";
}

void GameCore::EndGame(char whoWin)
{
    std::cout << "\n-----------------------------\n";

    if(whoWin == '.')
    {
        std::cout << "Draw";
    }
    else
    {
        std::cout << "Win " << whoWin << "!!!";
    }

    _game = false;
}
