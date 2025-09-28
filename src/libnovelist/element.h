#ifndef NOVELIST_ELEMENT_H
#define NOVELIST_ELEMENT_H

#include <QObject>
#include "node.h"
#include "projectstore.h"

namespace novelist {

class Element : public Node
{
    Q_OBJECT

public:
    Element(QObject* parent = nullptr)
        : Node{parent}
    {}

    static Element* load(int type, int id);

signals:

protected:
private:
};

} // namespace novelist

#endif // NOVELIST_ELEMENT_H
