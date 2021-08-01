#include "gamecore.h"

GameCore::GameCore()
{
    srand(time(NULL));

    _gameField = new char*[3];
    for(int i = 0; i < 3; i++)
    {
        _gameField[i] = new char[3] {'.','.','.'};
    }

    _game = true;
    _counter = 8;

    _log = new Logger;
}

void GameCore::startGame()
{
    _log->writeLog("----------NewGame----------");

    randFirstRightMove();

    std::cout   << "Set format game: "
                << "\n1) PvP"
                << "\n2) PvE"
                << "\n3) EvE";

    std::cout << "\nInput: ";

    choiceModeGame();
}

void GameCore::randFirstRightMove()
{
    std::string whoRightMove;

    _xORo = (rand() % 2 == 0) ? true : false;
    _humanStep = (rand() % 2 == 0) ? true : false;

    whoRightMove = (_xORo) ? "Starts - X" : "Starts - O";
    whoRightMove += (_humanStep) ? " | Human" : " | Bot";

    _log->writeLog(whoRightMove);
}

void GameCore::choiceModeGame()
{
    char choice;

    TRY_AGAIN: std::cin >> choice;

    switch (choice)
    {
        case '1':
            _log->writeLog("Mode game - PvP");
            game('1');
            break;
        case '2':
            _bot = new ALBot(_gameField, &_xORo, &_prevMove);
            _log->writeLog("Mode game - PvE");
            game('2');
            break;
        case '3':
            _bot = new ALBot[2];
            for(int i = 0; i < 2; i++)
            {
                _bot[i] = ALBot(_gameField, &_xORo, &_prevMove);
            }
            _log->writeLog("Mode game - EvE");
            game('3');
            break;
        default:
            std::cout << "\nInvalid input, try again: ";
            _log->writeLog("<|>Invalid input<|>");
            goto TRY_AGAIN;
            break;
    }
}

void GameCore::playerInput()
{
    bool step = false;
    short   row = -1,
            column = -1;

    _log->writeLog("Player try input...");

    while (step == false)
    {
        std::cout << "\nInput coordinats field(row/column| 0..2): ";
        while (!(std::cin >> row >> column))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid input, try again: ";
            _log->writeLog("<|>Invalid input<|>");
        }

        step = setXO((row * 10 + column));
    }
}

void GameCore::game(const char modeGame)
{
    system("clear");
    _log->writeLog("----------StartGame----------");
    while (true)
    {
        _log->writeLog("---------- | Step - " + std::to_string(9 - _counter));
        showWhoseStep();
        showField();
        if (modeGame == '1')
        {//Люди сами решат, кто ходит
            playerInput();
        }
        else if (modeGame == '2')
        {//Здесь нужно прописать
            if (_humanStep == true)
            {
                playerInput();
            }
            else
            {
                bool step = false;

                while(step == false)
                {
                    step = setXO(_bot->botInput());
                }
            }
        }
        else if (modeGame == '3')
        {//А ботам пофик
            bool step = false;

            while (step == false)
            {
                if (_xORo == true)
                {
                    step =  setXO(_bot[0].botInput());
                }
                else
                {
                    step =  setXO(_bot[1].botInput());
                }
            }
        }
        changeRightMove();
        checkWinner();

        if (_game == false)
        {
            break;
        }

        system("clear");
        _counter--;
        _humanStep = !_humanStep;
    }
}

bool GameCore::setXO(short argSet)
{//принимает номер строки, для заполнение ответа в игровое поле
    short   row = argSet / 10,
            column = argSet % 10;

    try
    {//пробуем сходить
        if (row > -1 && row < 3 && column > -1 && column < 3)
        {
            if (_gameField[row][column] == '.')
            {
                if (_xORo == true) _gameField[row][column] = 'X';
                else _gameField[row][column] = 'O';

                _log->writeLog("Input row - " + std::to_string(row) + " column - " + std::to_string(column));
            }
            else
            {
                throw "Position is busy";
            }
            _prevMove = argSet;
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

void GameCore::changeRightMove()
{//Меняет Ходящего (помогите назвать нормально? я спустя пол года, смог)
    _xORo = !_xORo;
}

void GameCore::checkWinner()
{//Проверям, не выйграл ли кто нить
    for (short row = 0; row < 3; row++)
    {//првоеряем строки
        if (_gameField[row][0] == 'X' && _gameField[row][1] == 'X' && _gameField[row][2] == 'X')
        {
            _log->writeLog( "Win - " +
                            std::to_string(row) + " 0" + " | " +
                            std::to_string(row) + " 1" + " | " +
                            std::to_string(row) + " 2"
                            );
            endGame('X');
            return;
        }
        else if (_gameField[row][0] == 'O' && _gameField[row][1] == 'O' && _gameField[row][2] == 'O')
        {
            _log->writeLog( "Win - " +
                            std::to_string(row) + " 0" + " | " +
                            std::to_string(row) + " 1" + " | " +
                            std::to_string(row) + " 2"
                            );
            endGame('O');
        }
    }

    for (short column = 0; column < 3; column++)
    {//проверяем столбцы
        if (_gameField[0][column] == 'X' && _gameField[1][column] == 'X' && _gameField[2][column] == 'X')
        {
            _log->writeLog( "Win - "
                            "0 "  + std::to_string(column) + " | " +
                            "1 " + std::to_string(column) + " | " +
                            "2 " + std::to_string(column)
                            );
            endGame('X');
            return;
        }
        else if (_gameField[0][column] == 'O' && _gameField[1][column] == 'O' && _gameField[2][column] == 'O')
        {
            _log->writeLog( "Win - "
                            "0 "  + std::to_string(column) + " | " +
                            "1 " + std::to_string(column) + " | " +
                            "2 " + std::to_string(column)
                            );
            endGame('O');
            return;
        }
    }

    //Проверяем диоганали
    if (_gameField[0][0] == 'X' && _gameField[1][1] == 'X' && _gameField[2][2] == 'X')
    {
        _log->writeLog( "Win - 0 0 | 1 1 | 2 2");
        endGame('X');
        return;
    }
    else if (_gameField[0][0] == 'O' && _gameField[1][1] == 'O' && _gameField[2][2] == 'O')
    {
        _log->writeLog( "Win - 0 0 | 1 1 | 2 2");
        endGame('O');
        return;
    }
    else if (_gameField[0][2] == 'X' && _gameField[1][1] == 'X' && _gameField[2][0] == 'X')
    {
        _log->writeLog( "Win - 0 2 | 1 1 | 2 0");
        endGame('X');
        return;
    }
    else if (_gameField[0][2] == 'O' && _gameField[1][1] == 'O' && _gameField[2][0] == 'O')
    {
        _log->writeLog( "Win - 0 2 | 1 1 | 2 0");
        endGame('O');
        return;
    }
    //Проверяем диоганали

    else
    {
        if (_counter == 0) endGame('.');
        return;
    }
}

void GameCore::showField()
{//Выводим игровое поле

    std::cout << std::endl;
    _log->writeLog("---------Field---------");

    for (short row = 0; row < 3; row++)
    {
        std::string saveLine;
        std::cout << "  ";
        for (short column = 0; column < 3; column++)
        {
            std::cout << _gameField[row][column] << "   ";
            saveLine += std::string(1, _gameField[row][column]) + "   ";
        }
        _log->writeLog(saveLine);
        std::cout << std::endl;
    }

    _log->writeLog("---------Field---------");
}

void GameCore::showWhoseStep()
{
    std::string whoseStep = "Now step ";

    whoseStep += (_xORo) ? "X" : "O";

    _log->writeLog(whoseStep);
    std::cout << whoseStep;
}

void GameCore::endGame(const char whoWin)
{
    system("clear");
    std::cout << "-----------------------------\n";

    if (whoWin == '.')
    {
        std::cout << "Draw\n";
    }
    else
    {
        std::cout << "Win " << whoWin << "!!!\n";
    }

    std::cout << "-----------------------------\n";
    showField();

    _game = false;
    _log->writeLog("---------EndGame - Win - " + std::string(1, whoWin) + "------------");
    _log->closeLogFile();
}
