#ifndef NOVELIST_FIELD_H
#define NOVELIST_FIELD_H

#include <QObject>
#include "node.h"
#include "projectstore.h"

namespace novelist {

class Field : public Node
{
    Q_OBJECT

public:
    Field(QObject* parent = nullptr)
        : Node{parent}
    {}

    static Field* load(int type, int id);

signals:

protected:
private:
};

} // namespace novelist

#endif // NOVELIST_FIELD_H
