#ifndef LOGGER_H
#define LOGGER_H

#include <QFile>
#include <QTextStream>
#include <QMutex>
#include <QDebug>

namespace s21 {
    class Logger {
    public:
        Logger(const Logger&) = delete;
        void operator =(const Logger&) = delete;

        static Logger& instance();
        void log(const QString& message);
        void clearLog();
    private:
        Logger();
        ~Logger();

        QFile file;
        QTextStream *out;
        QMutex mutex;
    };
}

#endif
