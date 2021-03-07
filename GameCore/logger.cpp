#include "logger.h"

Logger::Logger()
{
    QDate *currentDay = new QDate;

    std::string nameFile =  "log_" +
            std::to_string(currentDay->currentDate().year()) +
            std::to_string(currentDay->currentDate().month()) +
            std::to_string(currentDay->currentDate().day())
            + ".txt";

    logFile.open(nameFile, std::ios::app);

    delete currentDay;
}

void Logger::closeLogFile()
{
    logFile.close();
}

void Logger::writeLog(std::string newLog)
{
    logFile << std::endl << newLog;
}
