/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#if __has_include(<basestorage.h>)
#  include <basestorage.h>
#endif
#if __has_include(<element.h>)
#  include <element.h>
#endif
#if __has_include(<elementstorage.h>)
#  include <elementstorage.h>
#endif
#if __has_include(<elementtype.h>)
#  include <elementtype.h>
#endif
#if __has_include(<elementtypelistmodel.h>)
#  include <elementtypelistmodel.h>
#endif
#if __has_include(<elementtypestorage.h>)
#  include <elementtypestorage.h>
#endif
#if __has_include(<elementtypetablemodel.h>)
#  include <elementtypetablemodel.h>
#endif
#if __has_include(<elementtypetreemodel.h>)
#  include <elementtypetreemodel.h>
#endif
#if __has_include(<field.h>)
#  include <field.h>
#endif
#if __has_include(<fieldlistmodel.h>)
#  include <fieldlistmodel.h>
#endif
#if __has_include(<fieldstorage.h>)
#  include <fieldstorage.h>
#endif
#if __has_include(<fieldtype.h>)
#  include <fieldtype.h>
#endif
#if __has_include(<fieldtypelistmodel.h>)
#  include <fieldtypelistmodel.h>
#endif
#if __has_include(<fieldtypestorage.h>)
#  include <fieldtypestorage.h>
#endif
#if __has_include(<node.h>)
#  include <node.h>
#endif
#if __has_include(<nodelistmodel.h>)
#  include <nodelistmodel.h>
#endif
#if __has_include(<nodestorage.h>)
#  include <nodestorage.h>
#endif
#if __has_include(<nodetype.h>)
#  include <nodetype.h>
#endif
#if __has_include(<nodetypestorage.h>)
#  include <nodetypestorage.h>
#endif
#if __has_include(<novelist.h>)
#  include <novelist.h>
#endif
#if __has_include(<project.h>)
#  include <project.h>
#endif
#if __has_include(<projectstorage.h>)
#  include <projectstorage.h>
#endif
#if __has_include(<projecttype.h>)
#  include <projecttype.h>
#endif
#if __has_include(<projecttypestorage.h>)
#  include <projecttypestorage.h>
#endif
#if __has_include(<storable.h>)
#  include <storable.h>
#endif
#if __has_include(<storage.h>)
#  include <storage.h>
#endif
#if __has_include(<value.h>)
#  include <value.h>
#endif
#if __has_include(<valuelistmodel.h>)
#  include <valuelistmodel.h>
#endif
#if __has_include(<valuestorage.h>)
#  include <valuestorage.h>
#endif
#if __has_include(<valuetype.h>)
#  include <valuetype.h>
#endif
#if __has_include(<valuetypelistmodel.h>)
#  include <valuetypelistmodel.h>
#endif
#if __has_include(<valuetypestorage.h>)
#  include <valuetypestorage.h>
#endif


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_libnovelist()
{
    QT_WARNING_PUSH QT_WARNING_DISABLE_DEPRECATED
    qmlRegisterTypesAndRevisions<BaseStorage>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<BaseTypeStorage>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<Element>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<ElementStorage>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<ElementType>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<ElementTypeListModel>("libnovelist", 1);
    qmlRegisterAnonymousType<QAbstractItemModel, 254>("libnovelist", 1);
    QMetaType::fromType<ElementTypeListModel::Role>().id();
    qmlRegisterTypesAndRevisions<ElementTypeStorage>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<ElementTypeTableModel>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<ElementTypeTreeModel>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<Field>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<FieldListModel>("libnovelist", 1);
    QMetaType::fromType<FieldListModel::Role>().id();
    qmlRegisterTypesAndRevisions<FieldStorage>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<FieldType>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<FieldTypeListModel>("libnovelist", 1);
    QMetaType::fromType<FieldTypeListModel::Role>().id();
    qmlRegisterTypesAndRevisions<FieldTypeStorage>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<Node>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<NodeListModel>("libnovelist", 1);
    QMetaType::fromType<NodeListModel::Role>().id();
    qmlRegisterTypesAndRevisions<NodeStorage>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<NodeType>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<NodeTypeStorage>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<Novelist>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<Project>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<ProjectStorage>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<ProjectType>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<ProjectTypeStorage>("libnovelist", 1);
    QMetaType::fromType<QStandardItemModel *>().id();
    qmlRegisterTypesAndRevisions<Storable>("libnovelist", 1);
    QMetaType::fromType<Storable::Type>().id();
    QMetaType::fromType<Storable::Flag>().id();
    qmlRegisterTypesAndRevisions<Storage>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<Value>("libnovelist", 1);
    QMetaType::fromType<Value::Type>().id();
    qmlRegisterTypesAndRevisions<ValueListModel>("libnovelist", 1);
    QMetaType::fromType<ValueListModel::Role>().id();
    qmlRegisterTypesAndRevisions<ValueStorage>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<ValueType>("libnovelist", 1);
    qmlRegisterTypesAndRevisions<ValueTypeListModel>("libnovelist", 1);
    QMetaType::fromType<ValueTypeListModel::Role>().id();
    qmlRegisterTypesAndRevisions<ValueTypeStorage>("libnovelist", 1);
    QT_WARNING_POP
    qmlRegisterModule("libnovelist", 1, 0);
}

static const QQmlModuleRegistration libnovelistRegistration("libnovelist", qml_register_types_libnovelist);
