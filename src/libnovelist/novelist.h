#ifndef NOVELIST_NOVELIST_H
#define NOVELIST_NOVELIST_H

#include <QObject>

namespace novelist {

class Novelist : public QObject
{
    Q_OBJECT

public:
    Novelist(QObject* parent = nullptr);
};

} // namespace novelist

#endif // NOVELIST_NOVELIST_H
