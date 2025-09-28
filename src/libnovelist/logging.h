#ifndef NOVELIST_LOGGING_H
#define NOVELIST_LOGGING_H

#include <QLoggingCategory>
#include <QTextStream>

Q_DECLARE_LOGGING_CATEGORY(LOGNOVELIST)
Q_DECLARE_LOGGING_CATEGORY(LOGNOVELISTAI)

/*
template<typename D>
class Logger
{
public:
    class Stream
    {
    public:
        Logger* logger;
        int category;
        QDebug debug;
        QString message;
        QTextStream stream{&message};

        ~Stream() { emit static_cast<D*>(logger)->logged(category, message); }

        template<typename T>
        Stream& operator<<(const T& v)
        {
            stream << v;
            debug << v;
            return *this;
        }
    };

    [[nodiscard]] Stream logDebug(const char* file,
                                  int line = 0,
                                  const char* function = 0,
                                  const char* category = 0) const
    {
        return {this, 0, QMessageLogger{file, line, function, category}.debug()};
    }
    [[nodiscard]] Stream logInfo(const char* file,
                                 int line = 0,
                                 const char* function = 0,
                                 const char* category = 0) const
    {
        return {this, 1, QMessageLogger{file, line, function, category}.info()};
    }
    [[nodiscard]] Stream logWarning(const char* file,
                                    int line = 0,
                                    const char* function = 0,
                                    const char* category = 0) const
    {
        return {this, 2, QMessageLogger{file, line, function, category}.warning()};
    }
    [[nodiscard]] Stream logCritical(const char* file,
                                     int line = 0,
                                     const char* function = 0,
                                     const char* category = 0) const
    {
        return {this, 3, QMessageLogger{file, line, function, category}.critical()};
    }
    [[nodiscard]] Stream logFatal(const char* file,
                                  int line = 0,
                                  const char* function = 0,
                                  const char* category = 0) const
    {
        return {this, 4, QMessageLogger{file, line, function, category}.fatal()};
    }
};

#define DEBUG(CATEGORY) logDebug(__FILE__, __LINE__, Q_FUNC_INFO)
#define INFO(CATEGORY) logInfo(__FILE__, __LINE__, Q_FUNC_INFO)
#define WARNING(CATEGORY) logWarning(__FILE__, __LINE__, Q_FUNC_INFO)
#define CRITICAL(CATEGORY) logCritical(__FILE__, __LINE__, Q_FUNC_INFO)
#define FATAL(CATEGORY) logFatal(__FILE__, __LINE__, Q_FUNC_INFO)

*/

#endif // NOVELIST_LOGGING_H
