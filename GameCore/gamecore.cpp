#include "gamecore.h"

GameCore::GameCore()
{
    srand(time(NULL));

    _array = new char*[3];
    for(int i = 0; i < 3; i++)
    {//иницилизируем игровое поле
        _array[i] = new char[3] {'.','.','.'};
    }

    _game = true;
    _counter = 8;

    _log = new Logger;
}

void GameCore::StartGame()
{//Основа игры, всё обнуляем
    char choice;

    _log->writeLog("----------NewGame----------");

    if(rand() % 2 == 0)
    {
        _xORo = true;
        _log->writeLog("Starts - X");
    }
    else
    {
        _xORo = false;
        _log->writeLog("Starts - O");
    }

    std::cout   << "Set format game: "
                << "\n1) PvP"
                << "\n2) PvE"
                << "\n3) EvE";

    std::cout << "\nInput: ";

    while(true)
    {//Пока не выберут
        std::cin >> choice;
        if(choice == '1')
        {
            _log->writeLog("Set game - PvP");
            Game('1');
            break;
        }
        else if(choice == '2')
        {
            _bot = new ALBot;
            _log->writeLog("Set game - PvE");
            Game('2');
            break;
        }
        else if(choice == '3')
        {
            _bot = new ALBot[2];
            _log->writeLog("Set game - EvE");
            Game('3');
            break;
        }

        else
        {
            std::cout << "\nInvalid input, try again: ";
            _log->writeLog("<|>Invalid input<|>");
        }
    }
}

void GameCore::PlayerInput()
{
    bool step = false;
    short row, column;

    _log->writeLog("Player try input...");

    while(step == false)
    {
        std::cout << "\nInput coordinats field(row/column): ";
        std::cin >> row >> column;

        step = SetXO((row * 10 + column));
    }
}

void GameCore::Game(char modeGame)
{
    _log->writeLog("----------StartGame----------");
    while(true)
    {
        _log->writeLog("---------- | Step - " + std::to_string(9 - _counter));
        ShowWhoseStep();
        ShowField();
        if(modeGame == '1')
        {//Люди сами решат, кто ходит
            PlayerInput();
        }
        else if(modeGame == '2')
        {//Здесь нужно прописать
            if(_humanStep == true)
            {
                PlayerInput();
            }
            else
            {
                bool step = false;

                while(step == false)
                {
                    step = SetXO(_bot->botInput());
                }
            }
        }
        else if(modeGame == '3')
        {//А ботам пофик
            bool step = false;

            while(step == false)
            {
                if(_xORo == true)
                {
                    step =  SetXO(_bot[0].botInput());
                }
                else
                {
                    step =  SetXO(_bot[1].botInput());
                }
            }
        }
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

bool GameCore::SetXO(short argSet)
{//принимает номер строки и столбца, для заполнение ответа в игровое поле
    short   row = argSet / 10,
            column = argSet % 10;

    try
    {//пробуем сходить
        if(row > -1 && row < 3 && column > -1 && column < 3)
        {
            if(_array[row][column] == '.')
            {
                if(_xORo == true) _array[row][column] = 'X';
                else _array[row][column] = 'O';

                _log->writeLog("Input row - " + std::to_string(row) + " column - " + std::to_string(column));
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
        _log->writeLog("<|>Invalid input, try again (" + (std::string)e + ")<|>");
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
        if(_array[row][0] == 'X' && _array[row][1] == 'X' && _array[row][2] == 'X')
        {
            _log->writeLog( "Win - " +
                            std::to_string(row) + " 0" + " | " +
                            std::to_string(row) + " 1" + " | " +
                            std::to_string(row) + " 2"
                            );
            EndGame('X');
            return;
        }
        else if(_array[row][0] == 'O' && _array[row][1] == 'O' && _array[row][2] == 'O')
        {
            _log->writeLog( "Win - " +
                            std::to_string(row) + " 0" + " | " +
                            std::to_string(row) + " 1" + " | " +
                            std::to_string(row) + " 2"
                            );
            EndGame('O');
        }
    }

    for(short column = 0; column < 3; column++)
    {//проверяем столбцы
        if(_array[0][column] == 'X' && _array[1][column] == 'X' && _array[2][column] == 'X')
        {
            _log->writeLog( "Win - "
                            "0 "  + std::to_string(column) + " | " +
                            "1 " + std::to_string(column) + " | " +
                            "2 " + std::to_string(column)
                            );
            EndGame('X');
            return;
        }
        else if(_array[0][column] == 'O' && _array[1][column] == 'O' && _array[2][column] == 'O')
        {
            _log->writeLog( "Win - "
                            "0 "  + std::to_string(column) + " | " +
                            "1 " + std::to_string(column) + " | " +
                            "2 " + std::to_string(column)
                            );
            EndGame('O');
            return;
        }
    }

    //Проверяем диоганали
    if(_array[0][0] == 'X' && _array[1][1] == 'X' && _array[2][2] == 'X')
    {
        _log->writeLog( "Win - 0 0 | 1 1 | 2 2");
        EndGame('X');
        return;
    }
    else if(_array[0][0] == 'O' && _array[1][1] == 'O' && _array[2][2] == 'O')
    {
        _log->writeLog( "Win - 0 0 | 1 1 | 2 2");
        EndGame('O');
        return;
    }
    else if(_array[0][2] == 'X' && _array[1][1] == 'X' && _array[2][0] == 'X')
    {
        _log->writeLog( "Win - 0 2 | 1 1 | 2 0");
        EndGame('X');
        return;
    }
    else if(_array[0][2] == 'O' && _array[1][1] == 'O' && _array[2][0] == 'O')
    {
        _log->writeLog( "Win - 0 2 | 1 1 | 2 0");
        EndGame('O');
        return;
    }
    //Проверяем диоганали

    else
    {
        if(_counter == 0) EndGame('.');
        return;
    }
}

void GameCore::ShowField()
{//Выводим игровое поле

    std::cout << std::endl;
    _log->writeLog("---------Field---------");

    for(short row = 0; row < 3; row++)
    {
        std::string saveLine;
        std::cout << "  ";
        for(short column = 0; column < 3; column++)
        {
            std::cout << _array[row][column] << "   ";
            saveLine += std::string(1, _array[row][column]) + "   ";
        }
        _log->writeLog(saveLine);
        std::cout << std::endl;
    }

    _log->writeLog("---------Field---------");
}

void GameCore::ShowWhoseStep()
{
    if(_xORo == true)
    {
        _log->writeLog("Now step X");
        std::cout << "\nNow step X\n";
    }
    else
    {
        _log->writeLog("Now step O");
        std::cout << "\nNow step O\n";
    }
}

void GameCore::EndGame(char whoWin)
{
    system("clear");

    std::cout << "-----------------------------\n";

    if(whoWin == '.')
    {
        std::cout << "Draw\n";
    }
    else
    {
        std::cout << "Win " << whoWin << "!!!\n";
    }

    std::cout << "-----------------------------\n";

    ShowField();

    _game = false;

    _log->writeLog("---------EndGame - Win - " + std::string(1, whoWin) + "------------");

    _log->closeLogFile();
}
