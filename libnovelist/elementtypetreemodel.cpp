#include "elementtypetreemodel.h"
#include "elementtype.h"
#include "fieldtype.h"
#include "valuetype.h"

void ElementTypeTreeModel::setElementTypes(const QList<ElementType *> &elementTypes)
{
    if (mElementTypes == elementTypes)
        return;

    clear();

    mElementTypes = elementTypes;

    invisibleRootItem()->setColumnCount(2);

    for (ElementType *et : std::as_const(mElementTypes)) {
        QStandardItem *e1 = new QStandardItem{QIcon{!et->icon().isEmpty() ? et->icon()
                                                                          : "elementtype.svg"},
                                              et->label()};
        e1->setData(QVariant::fromValue(et));
        e1->setColumnCount(2);

        QStandardItem *e2 = new QStandardItem{""};

        appendRow({e1, e2});

        for (FieldType *ft : et->fieldTypes()) {
            QStandardItem *f1 = new QStandardItem{QIcon{!ft->icon().isEmpty() ? ft->icon()
                                                                              : "fieldtype.svg"},
                                                  ft->label()};
            f1->setData(QVariant::fromValue(ft));
            f1->setColumnCount(2);

            QStandardItem *f2 = new QStandardItem{""};

            e1->appendRow({f1, f2});

            for (ValueType *vt : ft->valueTypes()) {
                QStandardItem *v1 = new QStandardItem{QIcon{!vt->icon().isEmpty()
                                                                ? vt->icon()
                                                                : "valuetype.svg"},
                                                      vt->label()};
                v1->setData(QVariant::fromValue(vt));

                QStandardItem *v2 = new QStandardItem{""};

                f1->appendRow({v1, v2});
            }
        }

        // appendRow({e1, e2});
    }

    emit elementTypesChanged();
}
