#include "logger.h"

Logger::Logger()
{
    QDate *currentDay = new QDate;

    std::string fileName =  "log_" +
            std::to_string(currentDay->currentDate().year()) +
            std::to_string(currentDay->currentDate().month()) +
            std::to_string(currentDay->currentDate().day())
            + ".txt";

    logFile.open(fileName, std::ios::app);

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
