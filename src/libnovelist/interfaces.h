#ifndef NOVELIST_INTERFACES_H
#define NOVELIST_INTERFACES_H

#include <QMetaEnum>
#include <QObject>

namespace novelist {

class Loadable
{
public:
    virtual ~Loadable() = default;

    virtual bool reload() = 0;
};

class Saveable
{
public:
    virtual ~Saveable() = default;

    virtual bool save() = 0;
};

class Dbable
{
public:
    virtual ~Dbable() = default;

    [[nodiscard]] virtual quint64 rowid() const;

protected:
    virtual void setRowid(quint64 rowid);
};

class ProjectStore;

class Storable : public Loadable, public Saveable, public Dbable
{
public:
    virtual ~Storable() = default;

    virtual void recycle() = 0;
    virtual void reuse(const QVariantMap& values) = 0;

    [[nodiscard]] virtual ProjectStore* projectStore() const = 0;
};

class Throwable
{
public:
    enum Error {
        NoError,
        NoProjectStoreError,
        ProjectStoreLoadError,
        ProjectStoreSaveError,
        UnknownProjectStoreError,
    };

    virtual ~Throwable() = default;

    virtual void throwError(int code, QString message, const char* file = 0, const int line = 0) = 0;

    void throwError(
        int code, QString message, QVariantMap arguments, const char* file = 0, const int line = 0)
    {
        while (!arguments.isEmpty()) {
            message = message.arg(arguments.firstKey() + ':' + arguments.first().toString());
            arguments.erase(arguments.begin());
        }
        throwError(code, message, file, line);
    }
    void throwError(int code, const char* file = 0, const int line = 0)
    {
        throwError(code, errorMessage(code), file, line);
    }
    void throwError(int code, QVariantMap arguments, const char* file = 0, const int line = 0)
    {
        QString message = errorMessage(code);
        while (!arguments.isEmpty()) {
            if (!message.isEmpty())
                message += ", ";
            message += arguments.firstKey() + ':' + arguments.first().toString();
            arguments.erase(arguments.begin());
        }
        throwError(code, message, file, line);
    }

    virtual void throwWarning(
        int code, QString message, QVariantMap arguments, const char* file = 0, const int line = 0)
        = 0;

    static void initializeErrorMesages();

protected:
    static QString errorMessage(int code) { return mErrorMessages.value(code); }
    static void setErrorMessage(int code, const QString& message)
    {
        mErrorMessages[code] = message;
    }

private:
    inline static QHash<int, QString> mErrorMessages;
};

} // namespace novelist

#endif // NOVELIST_INTERFACES_H
